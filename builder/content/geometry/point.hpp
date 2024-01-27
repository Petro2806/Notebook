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
// Returns the angle between `p` and `q` in [0, pi]
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
	sort(ALL(v), [o](Pt p, Pt q)
	{
		p = p - o;
		q = q - o;
		bool hp = half(p), hq = half(q);
		if (hp != hq)
			return hp < hq;
		int s = sgn(cross(p, q));
		if (s != 0)
			return s == 1;
		return sq(p) < sq(q);
	});
}
// Example:
// cout << a + b << " " << a - b << "\n";
ostream& operator<<(ostream& os, const Pt& p)
{
	return os << "(" << p.x << "," << p.y << ")";
}
