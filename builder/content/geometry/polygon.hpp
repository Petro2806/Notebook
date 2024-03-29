bool isConvex(const vector<Pt>& v)
{
	bool hasPos = false, hasNeg = false;
	int n = SZ(v);
	FOR(i, 0, n)
	{
		int s = sgn(orient(v[i], v[(i + 1) % n], v[(i + 2) % n]));
		hasPos |= s > 0;
		hasNeg |= s < 0;
	}
	return !(hasPos && hasNeg);
}
db areaTriangle(const Pt& a, const Pt& b, const Pt& c)
{
	return abs(cross(b - a, c - a)) / 2.0;
}
db areaPolygon(const vector<Pt>& v)
{
	db area = 0.0;
	int n = SZ(v);
	FOR(i, 0, n)
		area += cross(v[i], v[(i + 1) % n]);
	return abs(area) / 2.0;
}
// Checks if point `a` is inside the convex
// polygon `v`. Returns true if on the boundary.
// `v` must not contain duplicated vertices.
// Time: O(log n)
bool inConvexPolygon(const vector<Pt>& v, const Pt& a)
{
	assert(SZ(v) >= 2);
	if (SZ(v) == 2)
		return onSegment(v[0], v[1], a);
	if (sgn(orient(v.back(), v[0], a)) < 0
		|| sgn(orient(v[0], v[1], a)) < 0)
		return false;
	int i = lower_bound(v.begin() + 2, v.end(), a, 
	[&](const Pt& p, const Pt& q)
	{
		return sgn(orient(v[0], p, q)) > 0;
	}) - v.begin();
	return sgn(orient(v[i - 1], v[i], a)) >= 0;
}
bool above(const Pt& a, const Pt& p)
{
	return sgn(p.y - a.y) >= 0;
}
bool crossesRay(const Pt& a, const Pt& p,
	const Pt& q)
{
	return sgn((above(a, q) - above(a, p))
		* orient(a, p, q)) == 1;
}
// Checks if point `a` is inside the polygon
// If `strict`, false when `a` is on the boundary
bool inPolygon(const vector<Pt>& v, const Pt& a, bool strict = true)
{
	int numCrossings = 0;
	int n = SZ(v);
	FOR(i, 0, n)
	{
		if (onSegment(v[i], v[(i + 1) % n], a))
			return !strict;
		numCrossings +=	crossesRay(a, v[i], v[(i + 1) % n]);
	}
	return numCrossings & 1;
}
