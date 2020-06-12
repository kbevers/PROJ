#pragma once

#define PJ_LIB__

using namespace std;

#include <algorithm>
#include <math.h>

#define INF 10000

/*************************************************************************************
*
*  https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
*
**************************************************************************************/
//namespace
//{	
	struct PolygonPoint
	{
		double x;
		double y;
	};

	static bool onSegment(PolygonPoint p, PolygonPoint q, PolygonPoint r)
	{
		if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
			q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
			return true;

		return false;
	}

	static double orientation(PolygonPoint p, PolygonPoint q, PolygonPoint r)
	{
		double val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

		if (val == 0)
			return 0;

		return (val > 0) ? 1 : 2;
	}

	static bool doIntersect(PolygonPoint p1, PolygonPoint q1, PolygonPoint p2, PolygonPoint q2)
	{
		double o1 = orientation(p1, q1, p2);
		double o2 = orientation(p1, q1, q2);
		double o3 = orientation(p2, q2, p1);
		double o4 = orientation(p2, q2, q1);

		if (o1 != o2 && o3 != o4)
			return true;

		if (o1 == 0 && onSegment(p1, p2, q1))
			return true;

		if (o2 == 0 && onSegment(p1, q2, q1))
			return true;

		if (o3 == 0 && onSegment(p2, p1, q2))
			return true;

		if (o4 == 0 && onSegment(p2, q1, q2))
			return true;

		return false;
	}

	static inline bool isInside(PolygonPoint polygon[], int n, PolygonPoint p)
	{
		if (n < 3)
			return false;

		PolygonPoint extreme = { INF, p.y };

		int count = 0, i = 0;

		do
		{
			int next = (i + 1) % n;

			if (doIntersect(polygon[i], polygon[next], p, extreme))
			{
				if (orientation(polygon[i], p, polygon[next]) == 0)
					return onSegment(polygon[i], p, polygon[next]);

				count++;
			}
			i = next;
		} while (i != 0);

		return count & 1;
	}
//}
