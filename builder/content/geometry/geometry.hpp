struct Pt
{
	db x, y;
	Pt operator+(const Pt& p) const
	{
		return {x + p.x, y + p.y};
	}
	Pt operator-(const Pt& p) const
	{
		return {x - p.x, y - p.y};
	}
	Pt operator*(db d) const
	{
		return {x * d, y * d};
	}
	Pt operator/(db d) const
	{
		return {x / d, y / d};
	}
};
// Returns the squared absolute value
db sq(const Pt& p)
{
	return p.x * p.x + p.y * p.y;
}
// Returns the absolute value
db abs(const Pt& p)
{
	return sqrt(sq(p));
}
// Returns -1 for negative numbers, 0 for zero,
// and 1 for positive numbers
int sgn(db x)
{
	return (EPS < x) - (x < -EPS);
}
// Returns `p` rotated counter-clockwise by `a`
Pt rot(const Pt& p, db a)
{
	db co = cos(a), si = sin(a);
	return {p.x * co - p.y * si,
		p.x * si + p.y * co};
}
// Returns `p` rotated counter-clockwise by 90
Pt perp(const Pt& p)
{
	return {-p.y, p.x};
}
// Returns the dot product of `p` and `q`
db dot(const Pt& p, const Pt& q)
{
	return p.x * q.x + p.y * q.y;
}
// Returns the angle between `p` and `q`
db angle(const Pt& p, const Pt& q)
{
	return acos(clamp(dot(p, q) / abs(p) /
		abs(q), (db)-1.0, (db)1.0));
}
// Returns the cross product of `p` and `q`
db cross(const Pt& p, const Pt& q)
{
	return p.x * q.y - p.y * q.x;
}
// Positive if R is on the left side of PQ,
// negative on the right side,
// and zero if R is on the line containing PQ
db orient(const Pt& p, const Pt& q, const Pt& r)
{
	return cross(q - p, r - p) / abs(q - p);
}
// Checks if a polygon `v` is convex
bool isConvex(const vector<Pt>& v)
{
	bool hasPos = false, hasNeg = false;
	int n = SZ(v);
	FOR(i, 0, n)
	{
		int o = sgn(orient(v[i], v[(i + 1) % n],
			v[(i + 2) % n]));
		hasPos |= o > 0;
		hasNeg |= o < 0;
	}
	return !(hasPos && hasNeg);
}
// Checks if argument of `p` is in [-pi, 0)
bool half(const Pt& p)
{
	assert(sgn(p.x) != 0 || sgn(p.y) != 0);
	return sgn(p.y) == -1 ||
		(sgn(p.y) == 0 && sgn(p.x) == -1);
}
// Polar sort of vectors in `v` around `o`
void polarSortAround(const Pt& o, vector<Pt>& v)
{
	sort(ALL(v), [o](const Pt& p, const Pt& q)
	{
		bool hp = half(p - o), hq = half(q - o);
		if (hp != hq)
			return hp < hq;
		int s = sgn(cross(p, q));
		if (s != 0)
			return s == 1;
		return sq(p - o) < sq(q - o);
	});
}
// Returns the distance of the closest points
db closestPair(vector<Pt> v)
{
	sort(ALL(v), [](const Pt& p, const Pt& q)
	{
		return sgn(p.x - q.x) < 0;
	});
	set<pair<db, db>> s;
	int n = SZ(v), ptr = 0;
	db h = 1e18;
	FOR(i, 0, n)
	{
		for (auto it = s.lower_bound(
			MP(v[i].y - h, v[i].x)); it != s.end()
			&& sgn(it->F - (v[i].y + h)) <= 0; it++)
		{
			Pt q = {it->S, it->F};
			h = min(h, abs(v[i] - q));
		}
		for (; sgn(v[ptr].x - (v[i].x - h)) <= 0;
			ptr++)
			s.erase({v[ptr].y, v[ptr].x});
		s.insert({v[i].y, v[i].x});
	}
	return h;
}
// Example:
// cout << a + b << " " << a - b << "\n";
ostream& operator<<(ostream& os, const Pt& p)
{
	return os << "(" << p.x << "," << p.y << ")";
}
struct Line
{
	// Equation of the line is dot(n, p) + c = 0
	Pt n;
	db c;
	Line (const Pt& _n, db _c): n(_n), c(_c) {}
	// The line containing two points `p` and `q`
	Line(const Pt& p, const Pt& q):
		n(perp(q - p)), c(-dot(n, p)) {}
	// The "positive side": dot(n, p) + c > 0
	// The "negative side": dot(n, p) + c < 0
	db side(const Pt& p) const
	{
		return dot(n, p) + c;
	}
	// Returns the distance from `p`
	db dist(const Pt& p) const
	{
		return abs(side(p)) / abs(n);
	}
	// Returns the squared distance from `p`
	db sqDist(const Pt& p) const
	{
		return side(p) * side(p) / (db)sq(n);
	}
	// Returns the perpendicular line through `p`
	Line perpThrough(const Pt& p) const
	{
		return {p, p + n};
	}
	// Compares `p` and `q` by their projection
	bool cmpProj(const Pt& p, const Pt& q) const
	{
		return sgn(cross(p, n) - cross(q, n)) < 0;
	}
	// Returns the orthogonal projection of `p`
	Pt proj(const Pt& p) const
	{
		return p - n * side(p) / sq(n);
	}
	// Returns the reflection of `p` by the line
	Pt refl(const Pt& p) const
	{
		return p - n * 2 * side(p) / sq(n);
	}
};
// Checks if `l1` and `l2` are parallel
bool parallel(const Line& l1, const Line& l2)
{
	return sgn(cross(l1.n, l2.n)) == 0;
}
// Returns the intersection point
Pt inter(const Line& l1, const Line& l2)
{
	db d = cross(l1.n, l2.n);
	assert(sgn(d) != 0);
	return perp(l2.n * l1.c - l1.n * l2.c) / d;
}
// Checks if `p` is in the disk of diameter [ab]
bool inDisk(const Pt& a, const Pt& b,
	const Pt& p)
{
	return sgn(dot(a - p, b - p)) <= 0;
}
// Checks if `p` lies on segment [ab]
bool onSegment(const Pt& a, const Pt& b,
	const Pt& p)
{
	return sgn(orient(a, b, p)) == 0
		&& inDisk(a, b, p);
}
// Checks if the segments [ab] and [cd] intersect
// properly (their intersection is one point
// which is not an endpoint of either segment)
bool properInter(const Pt& a, const Pt& b,
	const Pt& c, const Pt& d)
{
	db oa = orient(c, d, a);
	db ob = orient(c, d, b);
	db oc = orient(a, b, c);
	db od = orient(a, b, d);
	return sgn(oa) * sgn(ob) == -1
		&& sgn(oc) * sgn(od) == -1;
}
// Returns the distance between [ab] and `p`
db segPt(const Pt& a, const Pt& b, const Pt& p)
{
	Line l(a, b);
	assert(sgn(sq(l.n)) != 0);
	if (l.cmpProj(a, p) && l.cmpProj(p, b))
		return l.dist(p);
	return min(abs(p - a), abs(p - b));
}
// Returns the distance between [ab] and [cd]
db segSeg(const Pt& a, const Pt& b, const Pt& c,
	const Pt& d)
{
	if (properInter(a, b, c, d))
		return 0;
	return min({segPt(a, b, c), segPt(a, b, d),
			segPt(c, d, a), segPt(c, d, b)});
}
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
