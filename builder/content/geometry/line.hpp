struct Line
{
	// Equation of the line is dot(n, p) + c = 0
	Pt n;
	db c;
	Line (const Pt& _n, db _c): n(_n), c(_c) {}
	// n is the normal vector to the left of PQ
	Line(const Pt& p, const Pt& q):
		n(perp(q - p)), c(-dot(n, p)) {}
	// The "positive side": dot(n, p) + c > 0
	// The "negative side": dot(n, p) + c < 0
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
		return sgn(cross(p, n) - cross(q, n)) < 0;
	}
	Pt proj(const Pt& p) const
	{
		return p - n * side(p) / sq(n);
	}
	Pt reflect(const Pt& p) const
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