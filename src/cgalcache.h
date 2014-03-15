#ifndef CGALCACHE_H
#define CGALCACHE_H

#include <QList>
#include <QHash>
#include "cache.h"
#include "cgal.h"
#include "cgalpolygon.h"
#include "cgalprimitive.h"

class CGALCache : public Cache
{
public:
	typedef CGAL::FT FT;
	CGALCache();
	void cacheValue(CGAL::FT&);
	void cachePoint(Point);
	void cachePoint(CGAL::FT&,CGAL::FT&,CGAL::FT&);
	void cachePolygon();
	void cachePrimitive();
	Primitive* fetchPrimitive();
private:
	QList<CGAL::FT> allValues;
	typedef QList<uint> i_Point;
	i_Point values;
	QHash<i_Point,CGAL::Point3> allPoints;
	typedef QList<i_Point> i_Polygon;
	i_Polygon points;
	QHash<i_Polygon,CGALPolygon*> allPolygons;
	typedef QList<i_Polygon> i_Primitive;
	i_Primitive polygons;
	QHash<i_Primitive,CGALPrimitive*> allPrimitives;
	CGALPrimitive* primitive;
};

inline uint qHash(const QList<uint>& h,uint seed)
{
	uint k;
	foreach(uint i,h)
	k^=i;
	return k^seed;
}

template <class T>
inline uint qHash(const QList<T>& h,uint seed)
{
	uint k;
	foreach(T i,h)
	k=qHash(k,seed)^qHash(i,seed);
	return k;
}
#endif // CGALCACHE_H
