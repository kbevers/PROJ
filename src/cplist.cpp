/************************************************************************
* Copyright (c) 2020, Sveinung Himle <sveinung.himle at kartverket.no>
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
***********************************************************************/
#define PJ_LIB__

#ifndef FROM_PROJ_CPP
#define FROM_PROJ_CPP
#endif

#include <errno.h>
#include <stddef.h>
#include <string.h>

#include "cplist.hpp"
#include "cps.hpp"
#include "filemanager.hpp"
#include "proj/internal/internal.hpp"
#include "proj.h"
#include "proj_internal.h"

#include <algorithm>
#include <cmath>

static PJ_COMMONPOINTS *list = nullptr;
#define PJ_MAX_PATH_LENGTH 1024

NS_PROJ_START

using namespace internal;

CommonPointSet::CommonPointSet() = default;

// ---------------------------------------------------------------------------

CommonPointSet::~CommonPointSet() = default;

// ---------------------------------------------------------------------------

std::unique_ptr<CommonPointSet> CommonPointSet::open(PJ_CONTEXT *ctx, const std::string &filename)
{
	if (filename == "null")
	{
		auto set = std::unique_ptr<CommonPointSet>(new CommonPointSet());
		set->m_name = filename;
		set->m_format = "null";
	 	set->m_cps.push_back(std::unique_ptr<Common_Points>(new Common_Points()));

		return set;
	}
	auto fp = FileManager::open_resource_file(ctx, filename.c_str());
	if (!fp)
		return nullptr;
	
	const auto actualName(fp->name());

	if (ends_with(actualName, "cpt") || ends_with(actualName, "CPT"))
	{
		auto cp = Common_Points::open(ctx, std::move(fp), filename /*actualName*/);
	
		if (!cp)
			return nullptr;

		if (!cp->load(ctx))
			return nullptr;
		
		auto set = std::unique_ptr<CommonPointSet>(new CommonPointSet());
		set->m_name = filename;
		set->m_format = "cpt";
		set->m_cps.push_back(std::unique_ptr<Common_Points>(cp));

		return set;
	}

	return nullptr;
};

// ---------------------------------------------------------------------------

ListOfCps pj_cp_init(PJ *P, const char *cpkey)
{
	std::string key("s");
	key += cpkey;

	const char *cpnames = pj_param(P->ctx, P->params, key.c_str()).s;
	if (cpnames == nullptr)
		return {};
	
	auto list = internal::split(std::string(cpnames), ',');
	ListOfCps cps;

	for (const auto &cpnameStr : list) 
	{
		const char *cpname = cpnameStr.c_str();
		bool canFail = false;
		if (cpname[0] == '@')
		{
			canFail = true;
			cpname++;
		}
		auto cpSet = CommonPointSet::open(P->ctx, cpname);
		if (!cpSet)
		{
			if (!canFail)
			{
		 	//	if (proj_context_errno(P->ctx) != PJD_ERR_NETWORK_ERROR) 
				{
					pj_ctx_set_errno(P->ctx, PJD_ERR_FAILED_TO_LOAD_CPT);
				}
				return {};
			}
			pj_ctx_set_errno(P->ctx, 0);
		}
		else
		{
			cps.emplace_back(std::move(cpSet));
		}	
	}
	return cps;
} 

// ---------------------------------------------------------------------------

Common_Points* findCp(const ListOfCps &cps, const PJ_LPZ &input)
{
	for (const auto &cpSet : cps)
	{
		if (cpSet->cpAt(input.phi, input.phi) != nullptr)
		{
			return cpSet->cpAt(input.phi, input.phi);
		}
		//return nullptr;
		//	return cpSet;

		/*
		cpSetOut = cpSet.get();

		if (cpSetOut == nullptr)
			return nullptr;

		if (cpSetOut->Cps().size() == 0)
			return nullptr;
		*/
		// TODO: Add extent area in cpt-file.
		//	return cpSet->Cps();
	}
	return nullptr;
}

// ---------------------------------------------------------------------------

Common_Points *CommonPointSet::cpAt(double lon, double lat) const
{
	for (const auto &cp : m_cps)
	{ 
		if (cp->cpAt(lon, lat) != nullptr)
			return cp.get();			   
	}
	return nullptr;
}

NS_PROJ_END

// ---------------------------------------------------------------------------

static int pj_cplist_merge(projCtx ctx, const char *cp_name, PJ_COMMONPOINTS ***p_list, int *p_listcount, int *p_list_max)
{
	int match = 0;
	PJ_COMMONPOINTS *this_cp, *tail = nullptr;
	
	for (this_cp = list; this_cp != nullptr; this_cp = this_cp->next)
	{
		if (strcmp(this_cp->cp_name, cp_name) == 0)
		{
			match = 1;

			if (this_cp->cp == nullptr)
				return 0;

			if (*p_listcount >= *p_list_max - 2)
			{
				PJ_COMMONPOINTS **new_list;

				int new_max = *p_list_max + 20;

				new_list = (PJ_COMMONPOINTS **)pj_calloc(new_max, sizeof(void *));
				
				if (!new_list) 
				{
					pj_ctx_set_errno(ctx, ENOMEM);
					return 0;
				}
				if (*p_list != nullptr)
				{
					memcpy(new_list, *p_list, sizeof(void *) * (*p_list_max));
					pj_dalloc(*p_list);
				}
				*p_list = new_list;
				*p_list_max = new_max;
			}

			(*p_list)[(*p_listcount)++] = this_cp;
			(*p_list)[*p_listcount] = nullptr;
		}
		tail = this_cp;
	}

	if (match == 1)
		return 1;

	this_cp = pj_commonpoints_init(ctx, cp_name);
	
	if (this_cp == nullptr)
	{
		return 0;
	}

	if (tail != nullptr)
		tail->next = this_cp;
	else 
		list = this_cp;

	return pj_cplist_merge(ctx, cp_name, p_list, p_listcount, p_list_max);
}

// ---------------------------------------------------------------------------

PJ_COMMONPOINTS **pj_cplist(projCtx ctx, const char *lists, int *list_count)
{
	const char *s;
	PJ_COMMONPOINTS **list = nullptr;
	int list_max = 0;

	pj_errno = 0;
	*list_count = 0;
	 
	for (s = lists; *s != '\0'; )
	{
		size_t end_char;
		int required = 1;
		char name[PJ_MAX_PATH_LENGTH];

		if (*s == '@')
		{
			required = 0;
			s++;
		}

		for (end_char = 0; s[end_char] != '\0' && s[end_char] != ','; end_char++)
		{
		}

		if (end_char >= sizeof(name))
		{
			pj_dalloc(list);
			pj_ctx_set_errno(ctx, PJD_ERR_FAILED_TO_LOAD_CPT);
			pj_release_lock();
			return nullptr;
		}

		strncpy(name, s, end_char);
		name[end_char] = '\0';

		s += end_char;
		if (*s == ',')
			s++;

		if (!pj_cplist_merge(ctx, name, &list, list_count, &list_max) && required)
		{
			pj_dalloc(list);
			pj_ctx_set_errno(ctx, PJD_ERR_FAILED_TO_LOAD_CPT);
			pj_release_lock();
			return nullptr;
		}
		else
			pj_errno = 0;
	}
	pj_release_lock();

	return list;
}
