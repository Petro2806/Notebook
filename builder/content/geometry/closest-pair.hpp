/**
 * Description: Returns the distance between the closest points
 * Time: O(n \log n)
 */
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
