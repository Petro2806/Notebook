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
