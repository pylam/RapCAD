#include "cgalcache.h"

CGALCache::CGALCache()
{
}

void CGALCache::cacheValue(CGAL::FT& n)
{
	if(!allValues.contains(n)) {
		allValues.append(n);
	}
	uint k=allValues.indexOf(n);
	values.append(k);
}

void CGALCache::cachePoint(Point pt)
{
	decimal x,y,z;
	pt.getXYZ(x,y,z);

	FT fx(x);
	FT fy(y);
	FT fz(z);
	cacheValue(fx);
	cacheValue(fy);
	cacheValue(fz);

	cachePoint(fx,fy,fz);
}

void CGALCache::cachePoint(CGAL::FT& x,CGAL::FT& y,CGAL::FT& z)
{
	if(!allPoints.contains(values)) {
		CGAL::Point3 p(x,y,z);
		allPoints.insert(values,p);
	}

	points.append(values);

	values.clear();

}

void CGALCache::cachePolygon()
{
	if(!allPolygons.contains(points)) {
		CGALPolygon* pg=new CGALPolygon();
		foreach(i_Point ip, points)
			pg->append(allPoints.value(ip));

		allPolygons.insert(points,pg);
	}

	polygons.append(points);

	points.clear();
}

void CGALCache::cachePrimitive()
{
	if(!allPrimitives.contains(polygons)) {
		CGALPrimitive* pr=new CGALPrimitive();
		foreach(i_Polygon ip, polygons)
			pr->appendPolygon(allPolygons.value(ip));

		allPrimitives.insert(polygons,pr);

		primitive=pr;
	} else {
		CGALPrimitive* pr=allPrimitives.value(polygons);
		primitive=static_cast<CGALPrimitive*>(pr->copy());
	}
}

Primitive* CGALCache::fetchPrimitive()
{
	return primitive;
}
