#include "cgalcache.h"
#include <QDebug>

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
#if Q_DEBUG
	} else {
		qDebug() << "Point cache hit.";
#endif
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
#if Q_DEBUG
	} else {
		qDebug() << "Polygon cache hit.";
#endif
	}

	polygons.append(points);

	points.clear();
}

void CGALCache::cachePrimitive()
{
	if(!allPrimitives.contains(polygons)) {
		CGALPrimitive* pr=new CGALPrimitive();
		foreach(i_Polygon ip, polygons) {
			CGALPolygon* pg=allPolygons.value(ip);
			if(pg)
				pr->appendPolygon(pg);
		}

		allPrimitives.insert(polygons,pr);

		primitive=pr;
	} else {
#if Q_DEBUG
		qDebug() << "Primitive cache hit.";
#endif
		CGALPrimitive* pr=allPrimitives.value(polygons);
		primitive=static_cast<CGALPrimitive*>(pr->copy());
	}

	polygons.clear();
}

Primitive* CGALCache::fetchPrimitive()
{
	return primitive;
}
