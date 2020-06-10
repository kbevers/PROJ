/*****************************************************************************
* Project:	PROJ
* Purpose:	GeoJson Multipolygon
* Author:	Sveinung Himle <sveinung.himle at kartverket.no>
*
******************************************************************************
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
******************************************************************************/

#include <vector>

#include "proj.h"
#include "proj/util.hpp"
#include "point_in_polygon.h"
#include "filemanager.hpp"

NS_PROJ_START

// ---------------------------------------------------------------------------

class PROJ_GCC_DLL Polygon
{
protected:
	PJ_CONTEXT *m_ctx;
	int m_areaid;
public:
	PROJ_FOR_TEST Polygon(const int &areaid);
	PROJ_FOR_TEST virtual ~Polygon();
	PROJ_FOR_TEST const int &Id() const { return m_areaid; }
	PROJ_FOR_TEST vector<PolygonPoint> m_pointList;
	//PROJ_FOR_TEST virtual void reassign_context(PJ_CONTEXT *ctx) = 0;
};

// ---------------------------------------------------------------------------

class PROJ_GCC_DLL GeoJsonMultiPolygon : public Polygon
{
protected:
	std::vector<std::unique_ptr<GeoJsonMultiPolygon>> m_children{};
	//GeoJsonMultiPolygon(__int32 &areaid);
public:
	PROJ_FOR_TEST GeoJsonMultiPolygon(int &areaid);
	PROJ_FOR_TEST static GeoJsonMultiPolygon *open(PJ_CONTEXT *ctx, std::unique_ptr<File> fp, const std::string &name);
	PROJ_FOR_TEST ~GeoJsonMultiPolygon() override; 
	PROJ_FOR_TEST bool IsPointInArea(PJ_LP *lp);
	PROJ_FOR_TEST void reassign_context(PJ_CONTEXT *ctx);
    //PROJ_FOR_TEST virtual void reassign_context(PJ_CONTEXT *ctx) = 0;
};

// ---------------------------------------------------------------------------

class PROJ_GCC_DLL GeoJsonMultiPolygonSet
{	
protected:
	PJ_CONTEXT *m_ctx;
	std::string m_name{};
	std::string m_format{};
	std::vector<std::unique_ptr<GeoJsonMultiPolygon>> m_polygons{};

	GeoJsonMultiPolygonSet();
	GeoJsonMultiPolygonSet(PJ_CONTEXT *ctx);

public:
    PROJ_FOR_TEST virtual ~GeoJsonMultiPolygonSet();

	PROJ_FOR_TEST static std::unique_ptr<GeoJsonMultiPolygonSet> open(PJ_CONTEXT *ctx, const std::string &filename);
	PROJ_FOR_TEST static std::unique_ptr<GeoJsonMultiPolygonSet> parse(PJ_CONTEXT *ctx, std::unique_ptr<File> fp);

	PROJ_FOR_TEST const std::string &name() const { return m_name; }
 	PROJ_FOR_TEST const std::string &format() const { return m_format; }
	PROJ_FOR_TEST const std::vector<std::unique_ptr<GeoJsonMultiPolygon>> &polygons() const { return m_polygons; } 
    PROJ_FOR_TEST void reassign_context(PJ_CONTEXT *ctx);
	// PROJ_FOR_TEST virtual void reassign_context(PJ_CONTEXT *ctx) = 0;	
	PROJ_FOR_TEST virtual bool reopen(PJ_CONTEXT *ctx);	
};

typedef std::vector<std::unique_ptr<GeoJsonMultiPolygonSet>> ListOfMultiPolygons;
ListOfMultiPolygons pj_polygon_init(PJ *P, const char *polygonkey);
int areaIdPoint(PJ *P, const ListOfMultiPolygons &, PJ_LP *);
 
NS_PROJ_END
