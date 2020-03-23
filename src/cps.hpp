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
*
******************************************************************************/

//#ifndef GRIDS_HPP_INCLUDED
//#define GRIDS_HPP_INCLUDED

#include <vector>
#include <memory>

#include "proj.h"
#include "proj/util.hpp"

NS_PROJ_START

class PROJ_GCC_DLL CommonPoints
{
private:
	int m_noOfPoints = 0;
protected:
	std::string m_format{};

public:

	PROJ_FOR_TEST virtual ~CommonPoints();

	PROJ_FOR_TEST int NoOfPoints() const { return m_noOfPoints;	}
};

NS_PROJ_END
