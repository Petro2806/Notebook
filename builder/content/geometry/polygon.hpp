// Returns the area of triangle abc
db areaTriangle(const Pt& a, const Pt& b,
	const Pt& c)
{
	return abs(cross(b - a, c - a)) / 2.0;
}
// Returns the area of polygon `v`
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
// `v` must not contain duplicated vertices
bool inConvexPolygon(const vector<Pt>& v,
	const Pt& a)
{
	if (sgn(orient(v.back(), v[0], a)) < 0
		|| sgn(orient(v[0], v[1], a)) < 0)
		return false;
	int i = lower_bound(v.begin() + 2, v.end(),
		a, [&](const Pt& p, const Pt& q)
	{
		return sgn(orient(v[0], p, q)) > 0;
	}) - v.begin();
	return sgn(orient(v[i - 1], v[i], a)) >= 0;
}
// Returns true if `p` is at least as high as `a`
bool above(const Pt& a, const Pt& p)
{
	return sgn(p.y - a.y) >= 0;
}
// Checks if [pq] crosses the ray from `a`
bool crossesRay(const Pt& a, const Pt& p,
	const Pt& q)
{
	return sgn((above(a, q) - above(a, p))
		* orient(a, p, q)) == 1;
}
// Checks if point `a` is inside the polygon
// If `strict`, false when `a` is on the boundary
bool inPolygon(const vector<Pt>& v, const Pt& a,
	bool strict = true)
{
	int numCrossings = 0;
	int n = SZ(v);
	FOR(i, 0, n)
	{
		if (onSegment(v[i], v[(i + 1) % n], a))
			return !strict;
		numCrossings +=
			crossesRay(a, v[i], v[(i + 1) % n]);
	}
	return numCrossings & 1;
}
// Returns the counter-clockwise convex hull
vector<Pt> convexHull(vector<Pt> v)
{
	if (SZ(v) <= 1)
		return v;
	sort(ALL(v), [](const Pt& p, const Pt& q)
	{
		int dx = sgn(p.x - q.x);
		if (dx != 0)
			return dx < 0;
		return sgn(p.y - q.y) < 0;
	});
	vector<Pt> lower, upper;
	for (const Pt& p : v)
	{
		while (SZ(lower) > 1
			&& sgn(orient(lower[SZ(lower) - 2],
			lower.back(), p)) <= 0)
			lower.pop_back();
		while (SZ(upper) > 1
			&& sgn(orient(upper[SZ(upper) - 2],
			upper.back(), p)) >= 0)
			upper.pop_back();
		lower.PB(p);
		upper.PB(p);
	}
	reverse(ALL(upper));
	lower.insert(lower.end(), upper.begin() + 1,
		prev(upper.end()));
	return lower;
}
// Returns the indices of tangent points
PII tangetsToConvexPolygon(const vector<Pt>& v,
	const Pt& p)
{
	int n = SZ(v), i = 0;
	while (sgn(orient(p, v[i], v[(i + 1) % n]))
		* sgn(orient(p, v[i],
		v[(i + n - 1) % n])) > 0)
		i++;
	int s1 = 1, s2 = -1;
	if (sgn(orient(p, v[i], v[(i + 1) % n]))
		== s1 || sgn(orient(p, v[i],
		v[(i + n - 1) % n])) == s2)
		swap(s1, s2);
	PII res;
	int l = i, r = i + n - 1;
	while (r - l > 1)
	{
		int m = (l + r) / 2;
		if (sgn(orient(p, v[i], v[m % n])) != s1
			&& sgn(orient(p, v[m % n],
			v[(m + 1) % n])) != s1)
			l = m;
		else
			r = m;
	}
	res.F = r % n;
	l = i;
	r = i + n - 1;
	while (r - l > 1)
	{
		int m = (l + r) / 2;
		if (sgn(orient(p, v[i], v[m % n])) == s2
			|| sgn(orient(p, v[m % n],
			v[(m + 1) % n])) != s2)
			l = m;
		else
			r = m;
	}
	res.S = r % n;
	return res;
}
// Returns the Minkowski sum of two convex
// polygons
vector<Pt> minkowskiSum(const vector<Pt>& v1,
	const vector<Pt>& v2)
{
	auto comp = [](const Pt& p, const Pt& q)
	{
		return sgn(p.x - q.x) < 0
			|| (sgn(p.x - q.x) == 0
			&& sgn(p.y - q.y) < 0);
	};
	int i1 = min_element(ALL(v1), comp)
		- v1.begin();
	int i2 = min_element(ALL(v2), comp)
		- v2.begin();
	vector<Pt> res;
	int n1 = SZ(v1), n2 = SZ(v2),
		j1 = 0, j2 = 0;
	while (j1 < n1 || j2 < n2)
	{
		const Pt& p1 = v1[(i1 + j1) % n1];
		const Pt& q1 = v1[(i1 + j1 + 1) % n1];
		const Pt& p2 = v2[(i2 + j2) % n2];
		const Pt& q2 = v2[(i2 + j2 + 1) % n2];
		if (SZ(res) >= 2 && onSegment(
			res[SZ(res) - 2], p1 + p2,
			res.back()))
			res.pop_back();
		res.PB(p1 + p2);
		int s = sgn(cross(q1 - p1, q2 - p2));
		if (j1 < n1 && (j2 == n2 || s > 0
			|| (s == 0 && (SZ(res) < 2
			|| sgn(dot(res.back()
			- res[SZ(res) - 2],
			q1 + p2 - res.back())) > 0))))
			j1++;
		else
			j2++;
	}
	if (SZ(res) > 2
		&& onSegment(res[SZ(res) - 2], res[0],
		res.back()))
		res.pop_back();
	return res;
}
// Returns the counter-clockwise ordered vertices
// of the half-plane intersection. Returns empty
// if the intersection is empty. Adds a bounding
// box to ensure a finite area
vector<Pt> hplaneInter(vector<Line> lines)
{
	const db C = 1e9;
	lines.PB({{-C, C}, {-C, -C}});
	lines.PB({{-C, -C}, {C, -C}});
	lines.PB({{C, -C}, {C, C}});
	lines.PB({{C, C}, {-C, C}});
	sort(ALL(lines), []
		(const Line& l1, const Line& l2)
	{
		bool h1 = half(l1.n), h2 = half(l2.n);
		if (h1 != h2)
			return h1 < h2;
		int p = sgn(cross(l1.n, l2.n));
		if (p != 0)
			return p > 0;
		return sgn(l1.c / abs(l1.n)
			- l2.c / abs(l2.n)) < 0;
	});
	lines.erase(unique(ALL(lines), parallel),
		lines.end());
	deque<pair<Line, Pt>> d;
	for (const Line& l : lines)
	{
		while (SZ(d) > 1 && sgn(l.side(
			(d.end() - 1)->S)) < 0)
			d.pop_back();
		while (SZ(d) > 1 && sgn(l.side(
			(d.begin() + 1)->S)) < 0)
			d.pop_front();
		if (!d.empty() && sgn(cross(
			d.back().F.n, l.n)) <= 0)
			return {};
		if (SZ(d) < 2 || sgn(d.front().F.side(
			inter(l, d.back().F))) >= 0)
		{
			Pt p;
			if (!d.empty())
			{
				p = inter(l, d.back().F);
				if (!parallel(l, d.front().F))
					d.front().S = inter(l,
						d.front().F);
			}
			d.PB({l, p});
		}
	}
	vector<Pt> res;
	for (auto [l, p] : d)
	{
		if (res.empty()
			|| sgn(sq(p - res.back())) > 0)
			res.PB(p);
	}
	return res;
}
