#ifndef CACHE_H
#define CACHE_H

#include "primitive.h"

class Cache
{
public:
	virtual void cachePrimitive(Primitive*) {}
	virtual void cachePolygon() {}
	virtual void cachePoint(const Point&) {}
	virtual Primitive* fetchPrimitive() { return NULL; }
	virtual void cacheReset() {}
};

#endif // CACHE_H
