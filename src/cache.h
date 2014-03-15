#ifndef CACHE_H
#define CACHE_H

#include "primitive.h"

class Cache
{
public:
	virtual void cachePrimitive() {}
	virtual void cachePolygon() {}
	virtual void cachePoint(Point) {}
	virtual Primitive* fetchPrimitive() {
		return NULL;
	}
};

#endif // CACHE_H
