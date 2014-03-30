#ifndef CACHE_H
#define CACHE_H

#include <QtGlobal>
#include <QVector>
#include <QHash>
#include "primitive.h"

class Cache
{
public:
	Cache();
	void cacheValue(const decimal&);
	void cachePoint(const Point&);
	void cachePolygon();
	void cachePrimitive(Primitive*);
	Primitive* fetchPrimitive();
	void cacheReset();
private:
	typedef QVector<decimal> i_Point;
	i_Point values;
	typedef QVector<i_Point> i_Polygon;
	i_Polygon points;
	typedef QVector<i_Polygon> i_Primitive;
	i_Primitive polygons;
	QHash<i_Primitive,Primitive*> allPrimitives;
};

#if (QT_VERSION < QT_VERSION_CHECK(5, 3, 0))
static inline uint hash(const uchar *p, int len, uint seed) Q_DECL_NOTHROW
{
	uint h = seed;
	for (int i = 0; i < len; ++i)
		h = 31 * h + p[i];

	return h;
}

/*! \relates QHash
	\since 5.3

	Returns the hash value for the \a key, using \a seed to seed the calculation.
*/
inline uint qHash(double key, uint seed) Q_DECL_NOTHROW
{
	return key != 0.0  ? hash(reinterpret_cast<const uchar *>(&key), sizeof(key), seed) : seed ;
}
#endif

template <class T>
inline uint qHash(const QVector<T>& l,uint seed)
{
	uint h = seed;
	foreach(T i,l)
		h = 31 * h + qHash(i,seed);

	return h;
}
#endif // CACHE_H
