#ifndef CGALCACHE_H
#define CGALCACHE_H

#include <QList>
#include <QHash>
#include "cache.h"
#include "cgal.h"
#include "cgalpolygon.h"
#include "cgalprimitive.h"
#include "onceonly.h"

class CGALCache : public Cache
{
public:
	CGALCache();
	void cacheValue(const decimal&);
	void cachePoint(const Point&);
	void cachePolygon();
	void cachePrimitive(Primitive*);
	Primitive* fetchPrimitive();
	void cacheReset();
private:
	QList<decimal> allValues;
	typedef QList<uint> i_Point;
	i_Point values;
	typedef QList<i_Point> i_Polygon;
	i_Polygon points;
	typedef QList<i_Polygon> i_Primitive;
	i_Primitive polygons;
	QHash<i_Primitive,Primitive*> allPrimitives;
};

inline uint qHash(const QList<uint>& l,uint seed)
{
	uint hash = 17;
	foreach(uint i,l)
		hash *= 31 + i;

	return hash+seed;
}

template <class T>
inline uint qHash(const QList<T>& l,uint seed)
{
	uint hash = 17; //Magic fairy dust (should be prime)
	foreach(T i,l)
		hash *= 31 + qHash(i,seed);

	return hash+seed;
}
#endif // CGALCACHE_H
