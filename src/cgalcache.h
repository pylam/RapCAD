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

inline static QString print(QList<uint> l)
{
	QString result;
	OnceOnly first;
	foreach(uint i,l) {
		if(!first())
			result.append(",");
		result.append(QString().setNum(i));
	}
	/*result.append(" key: ");
	uint k = qHash(l);
	result.append(QString().setNum(k));*/
	return result;
}

template <class T>
inline static QString print(QList<T> l)
{
	QString result;
	foreach(T i,l) {
		result.append("[");
		result.append(print(i));
		result.append("]");
	}
	/*result.append(" key: ");
	uint k = qHash(l);
	result.append(QString().setNum(k));*/
	return result;
}
/*
inline uint qHash(const QList<uint>& h,uint seed)
{
	//uint k;
	//foreach(uint i,h)
	//	k^=i;
	//return k^seed;
	return qHash(print(h));
}
*/
template <class T>
inline uint qHash(const QList<T>& h/*,uint seed*/)
{
	//uint k;
	//foreach(T i,h)
	//	k=qHash(k/*,seed*/)^qHash(i/*,seed*/);
	//return k;
	return qHash(print(h));
}
#endif // CGALCACHE_H
