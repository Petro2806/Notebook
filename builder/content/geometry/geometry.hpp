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
db sq(const Pt& p)
{
	return p.x * p.x + p.y * p.y;
}
db abs(const Pt& p)
{
	return sqrt(sq(p));
}
int sgn(db x)
{
	return (EPS < x) - (x < -EPS);
}
Pt rot(const Pt& p, db a)
{
	db co = cos(a), si = sin(a);
	return {p.x * co - p.y * si, p.x * si + p.y * co};
}
Pt perp(const Pt& p)
{
	return {-p.y, p.x};
}
db dot(const Pt& p, const Pt& q)
{
	return p.x * q.x + p.y * q.y;
}
db angle(const Pt& p, const Pt& q)
{
	return acos(clamp(dot(p, q) / abs(p) / abs(q), (db)-1.0, (db)1.0));
}
db cross(const Pt& p, const Pt& q)
{
	return p.x * q.y - p.y * q.x;
}
// positive if R is on the left side of PQ,
// negative on the right side,
// and zero if R is on the line containing PQ
db orient(const Pt& p, const Pt& q, const Pt& r)
{
	return cross(q - p, r - p) / abs(q - p);
}
bool isConvex(const vector<Pt>& v)
{
	bool hasPos = false, hasNeg = false;
	int n = SZ(v);
	FOR(i, 0, n)
	{
		int o = sgn(orient(v[i], v[(i + 1) % n], v[(i + 2) % n]));
		hasPos |= o > 0;
		hasNeg |= o < 0;
	}
	return !(hasPos && hasNeg);
}
bool half(const Pt& p)
{
	assert(sgn(p.x) != 0 || sgn(p.y) != 0);
	return sgn(p.y) == -1 || (sgn(p.y) == 0 && sgn(p.x) == -1);
}
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
		for (auto it = s.lower_bound(MP(v[i].y - h, v[i].x));
			it != s.end() && sgn(it->F - (v[i].y + h)) <= 0; it++)
		{
			Pt q = {it->S, it->F};
			h = min(h, abs(v[i] - q));
		}
		for (; sgn(v[ptr].x - (v[i].x - h)) <= 0; ptr++)
			s.erase({v[ptr].y, v[ptr].x});
		s.insert({v[i].y, v[i].x});
	}
	return h;
}
ostream& operator<<(ostream& os, const Pt& p)
{
	return os << "(" << p.x << "," << p.y << ")";
}
struct Line
{
	Pt n;
	db c;
	Line(const Pt& p, const Pt& q): n(perp(q - p)), c(-dot(n, p)) {}
	db side(const Pt& p) const
	{
		return dot(n, p) + c;
	}
	db dist(const Pt& p) const
	{
		return abs(side(p)) / abs(n);
	}
	db sqDist(const Pt& p) const
	{
		return side(p) * side(p) / (db)sq(n);
	}
	Line perpThrough(const Pt& p) const
	{
		return {p, p + n};
	}
	bool cmpProj(const Pt& p, const Pt& q) const
	{
		return sgn(cross(p, n) - cross(q, n)) == -1;
	}
	Pt proj(const Pt& p) const
	{
		return p - n * side(p) / sq(n);
	}
	Pt refl(const Pt& p) const
	{
		return p - n * 2 * side(p) / sq(n);
	}
};
bool parallel(const Line& l1, const Line& l2)
{
	return sgn(cross(l1.n, l2.n)) == 0;
}
Pt inter(const Line& l1, const Line& l2)
{
	db d = cross(l1.n, l2.n);
	assert(sgn(d) != 0);
	return perp(l2.n * l1.c - l1.n * l2.c) / d;
}
// checks if a point P lies in the disk of diameter [AB]
bool inDisk(const Pt& a, const Pt& b, const Pt& p)
{
	return sgn(dot(a - p, b - p)) <= 0;
}
bool onSegment(const Pt& a, const Pt& b, const Pt& p)
{
	return sgn(orient(a, b, p)) == 0 && inDisk(a, b, p);
}
bool properInter(const Pt& a, const Pt& b, const Pt& c, const Pt& d)
{
	db oa = orient(c, d, a);
	db ob = orient(c, d, b);
	db oc = orient(a, b, c);
	db od = orient(a, b, d);
	return sgn(oa) * sgn(ob) == -1 && sgn(oc) * sgn(od) == -1;
}
db segPt(const Pt& a, const Pt& b, const Pt& p)
{
	Line l(a, b);
	assert(sgn(sq(l.n)) != 0);
	if (l.cmpProj(a, p) && l.cmpProj(p, b))
		return l.dist(p);
	return min(abs(p - a), abs(p - b));
}
db segSeg(const Pt& a, const Pt& b, const Pt& c, const Pt& d)
{
	if (properInter(a, b, c, d))
		return 0;
	return min({segPt(a, b, c), segPt(a, b, d),
			segPt(c, d, a), segPt(c, d, b)});
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
bool above(const Pt& a, const Pt& p)
{
	return sgn(p.y - a.y) >= 0;
}
bool crossesRay(const Pt& a, const Pt& p, const Pt& q)
{
	return sgn((above(a, q) - above(a, p)) * orient(a, p, q)) == 1;
}
// if strict, returns false when A is on the boundary
bool inPolygon(const vector<Pt>& v, const Pt& a, bool strict = true)
{
	int numCrossings = 0;
	int n = SZ(v);
	FOR(i, 0, n)
	{
		if (onSegment(v[i], v[(i + 1) % n], a))
			return !strict;
		numCrossings += crossesRay(a, v[i], v[(i + 1) % n]);
	}
	return numCrossings & 1;
}
vector<Pt> convexHull(vector<Pt> v)
{
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
		while (SZ(lower) > 1 && sgn(orient(lower[SZ(lower) - 2], lower.back(), p)) < 0)
			lower.pop_back();
		while (SZ(upper) > 1 && sgn(orient(upper[SZ(upper) - 2], upper.back(), p)) > 0)
			upper.pop_back();
		lower.PB(p);
		upper.PB(p);
	}
	reverse(ALL(upper));
	lower.insert(lower.end(), upper.begin() + 1, prev(upper.end()));
	return lower;
}
Pt circumCenter(const Pt& a, Pt b, Pt c)
{
	b = b - a;
	c = c - a;
	assert(sgn(cross(b, c)) != 0);
	return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2;
}
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
vector<Pt> circleCircle(const Pt& o1, db r1, const Pt& o2, db r2)
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
// if there are 2 tangents, it returns res with two pairs of points:
// the pairs of tangency points on each circle (P1, P2)
//
// if there is 1 tangent, the circles are tangent to each other
// at some point P, res just contains P 4 times, and the tangent
// line can be found as line(o1, p).perpThrough(p)
//
// the same code can be used to find the tangent to a circle
// passing through a point by setting r2 to 0
// (in which case the value of inner doesn't matter)
vector<pair<Pt, Pt>> tangents(const Pt& o1, db r1, const Pt& o2, db r2, bool inner)
{
	if (inner)
		r2 = -r2;
	Pt d = o2 - o1;
	db dr = r1 - r2, d2 = sq(d), h2 = d2 - dr * dr;
	if (sgn(d2) == 0 || sgn(h2) < 0)
	{
		assert(sgn(h2) != 0);
		return {};
	}
	vector<pair<Pt, Pt>> res;
	for (db sign : {-1, 1})
	{
		Pt v = (d * dr + perp(d) * sqrt(h2) * sign) / d2;
		res.PB({o1 + v * r1, o2 + v * r2});
	}
	return res;
}
