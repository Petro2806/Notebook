// Returns the circumcenter of triangle abc
Pt circumCenter(const Pt& a, Pt b, Pt c)
{
	b = b - a;
	c = c - a;
	assert(sgn(cross(b, c)) != 0);
	return a + perp(b * sq(c) - c * sq(b))
		/ cross(b, c) / 2;
}
// Returns circle-line intersection points
vector<Pt> circleLine(const Pt& o, db r,
	const Line& l)
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
vector<Pt> circleCircle(const Pt& o1, db r1,
	const Pt& o2, db r2)
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
// Finds common tangents (outer or inner)
// If there are 2 tangents, returns the pairs of
// tangency points on each circle (p1, p2)
// If there is 1 tangent, the circles are tangent
// to each other at some point p, res contains p
// 4 times, and the tangent line can be found as
// line(o1, p).perpThrough(p)
// The same code can be used to find the tangent
// to a circle through a point by setting r2 to 0
// (in which case `inner` doesn't matter)
vector<pair<Pt, Pt>> tangents(const Pt& o1,
	db r1, const Pt& o2, db r2, bool inner)
{
	if (inner)
		r2 = -r2;
	Pt d = o2 - o1;
	db dr = r1 - r2, d2 = sq(d),
		h2 = d2 - dr * dr;
	if (sgn(d2) == 0 || sgn(h2) < 0)
	{
		assert(sgn(h2) != 0);
		return {};
	}
	vector<pair<Pt, Pt>> res;
	for (db sign : {-1, 1})
	{
		Pt v = (d * dr + perp(d) * sqrt(h2)
			* sign) / d2;
		res.PB({o1 + v * r1, o2 + v * r2});
	}
	return res;
}
// Returns the smallest enclosing circle of `v`
// Expected time: O(n)
pair<Pt, db> welzl(vector<Pt> v)
{
	int n = SZ(v), k = 0, idxes[2];
	mt19937 rng;
	shuffle(ALL(v), rng);
	Pt c = v[0];
	db r = 0;
	while (true)
	{
		FOR(i, k, n)
		{
			if (sgn(abs(v[i] - c) - r) > 0)
			{
				swap(v[i], v[k]);
				if (k == 0)
					c = v[0];
				else if (k == 1)
					c = (v[0] + v[1]) / 2;
				else
					c = circumCenter(
						v[0], v[1],	v[2]);
				r = abs(v[0] - c);
				if (k < i)
				{
					if (k < 2)
						idxes[k++] = i;
					shuffle(v.begin() + k,
						v.begin() + i + 1, rng);
					break;
				}
			}
			while (k > 0 && idxes[k - 1] == i)
				k--;
			if (i == n - 1)
				return {c, r};
		}
	}
}
