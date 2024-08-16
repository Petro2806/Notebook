// Returns the circumcenter of triangle abc.
// The circumcircle of a triangle is a circle that passes through all three vertices.
Pt circumCenter(const Pt& a, Pt b, Pt c)
{
	b = b - a;
	c = c - a;
	assert(sgn(cross(b, c)) != 0);
	return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2;
}
// Returns circle-line intersection points
vector<Pt> circleLine(const Pt& o, db r, const Line& l)
{
	db h2 = r * r - l.sqDist(o);
	if (sgn(h2) == -1)
		return {};
	Pt p = l.proj(o);
	if (sgn(h2) == 0)
		return {p};
	Pt h = perp(l.n) * sqrt(h2) / abs(l.n);
	return {p - h, p + h};
}
// Returns circle-circle intersection points
vector<Pt> circleCircle(const Pt& o1, db r1, const Pt& o2, db r2)
{
	Pt d = o2 - o1;
	db d2 = sq(d);
	if (sgn(d2) == 0)
	{
		// assuming the circles don't coincide
		assert(sgn(r2 - r1) != 0);
		return {};
	}
	db pd = (d2 + r1 * r1 - r2 * r2) / 2;
	db h2 = r1 * r1 - pd * pd / d2;
	if (sgn(h2) == -1)
		return {};
	Pt p = o1 + d * pd / d2;
	if (sgn(h2) == 0)
		return {p};
	Pt h = perp(d) * sqrt(h2 / d2);
	return {p - h, p + h};
}
