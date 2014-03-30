#include "cache.h"

Cache::Cache()
{
}

void Cache::cachePoint(const Point& pt)
{
	decimal x,y,z;
	pt.getXYZ(x,y,z);
	values.append(x);
	values.append(y);
	values.append(z);

	points.append(values);
	values.clear();
}

void Cache::cachePolygon()
{
	polygons.append(points);
	points.clear();
}

void Cache::cacheReset()
{
	values.clear();
	points.clear();
	polygons.clear();
}

void Cache::cachePrimitive(Primitive* pr)
{
	allPrimitives.insert(polygons,pr->copy());
	polygons.clear();
}

Primitive* Cache::fetchPrimitive()
{
	if(allPrimitives.contains(polygons)) {
		Primitive* pr=allPrimitives.value(polygons);
		return pr->copy();
	}
	return NULL;
}
