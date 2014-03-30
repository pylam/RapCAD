#include "cgalcache.h"
#include <QDebug>

CGALCache::CGALCache()
{
}

void CGALCache::cacheValue(const decimal& n)
{
	if(!allValues.contains(n)) {
		allValues.append(n);
	}
	uint k=allValues.indexOf(n);
	values.append(k);
}

void CGALCache::cachePoint(const Point& pt)
{
	decimal x,y,z;
	pt.getXYZ(x,y,z);
	cacheValue(x);
	cacheValue(y);
	cacheValue(z);

	points.append(values);
	values.clear();
}

void CGALCache::cachePolygon()
{
	polygons.append(points);
	points.clear();
}

void CGALCache::cacheReset()
{
	values.clear();
	points.clear();
	polygons.clear();
}

void CGALCache::cachePrimitive(Primitive* pr)
{
	allPrimitives.insert(polygons,pr->copy());
	polygons.clear();
}

Primitive* CGALCache::fetchPrimitive()
{
	if(allPrimitives.contains(polygons)) {
		Primitive* pr=allPrimitives.value(polygons);
		return pr->copy();
	}
	return NULL;
}
