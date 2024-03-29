// Checks if `p` is in the disk (the region in a plane
// bounded by a circle) of diameter [ab]
bool inDisk(const Pt& a, const Pt& b, const Pt& p)
{
	return sgn(dot(a - p, b - p)) <= 0;
}
// Checks if `p` lies on segment [ab]
bool onSegment(const Pt& a, const Pt& b, const Pt& p)
{
	return sgn(orient(a, b, p)) == 0 && inDisk(a, b, p);
}
// Checks if the segments [ab] and [cd] intersect
// properly (their intersection is one point
// which is not an endpoint of either segment)
bool properInter(const Pt& a, const Pt& b, const Pt& c, const Pt& d)
{
	db oa = orient(c, d, a);
	db ob = orient(c, d, b);
	db oc = orient(a, b, c);
	db od = orient(a, b, d);
	return sgn(oa) * sgn(ob) == -1 && sgn(oc) * sgn(od) == -1;
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
db segSeg(const Pt& a, const Pt& b, const Pt& c, const Pt& d)
{
	if (properInter(a, b, c, d))
		return 0;
	return min({segPt(a, b, c), segPt(a, b, d),
			segPt(c, d, a), segPt(c, d, b)});
}
