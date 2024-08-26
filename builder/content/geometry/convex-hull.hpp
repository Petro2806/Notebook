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
		while (SZ(lower) > 1 && 
			sgn(orient(lower[SZ(lower) - 2], lower.back(), p)) <= 0)
			lower.pop_back();
		while (SZ(upper) > 1 && 
			sgn(orient(upper[SZ(upper) - 2], upper.back(), p)) >= 0)
			upper.pop_back();
		lower.PB(p);
		upper.PB(p);
	}
	reverse(ALL(upper));
	lower.insert(lower.end(), next(upper.begin()), prev(upper.end()));
	return lower;
}
