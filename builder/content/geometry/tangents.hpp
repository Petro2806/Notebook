/**
 * Description: Finds common tangents (outer or inner) to two circles.
 * If there are two tangents, returns the pairs of tangency points on each circle $(p_1, p_2)$.
 * If there is one tangent, the circles are tangent to each other at some point $p$, $\text{res}$ contains $p$ four times, and the tangent line can be found as \texttt{line(o1, p).perpThrough(p)}.
 * The same code can be used to find the tangent to a circle through a point by setting $r_2$ to $0$ (in which case \texttt{inner} doesn't matter).
 */
vector<pair<Pt, Pt>> tangents(const Pt& o1,	db r1,
	const Pt& o2, db r2, bool inner)
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
		Pt v = (d * dr + perp(d) * sqrt(h2)	* sign) / d2;
		res.PB({o1 + v * r1, o2 + v * r2});
	}
	return res;
}
