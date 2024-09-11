/**
 * Description: Finds an arbitrary triangulation of a simple polygon with
 * no three collinear vertices.
 **/
vector<tuple<int, int, int>> earClipping(const vector<Pt>& v)
{
	int n = SZ(v);
	vector<tuple<int, int, int>> res;
	VI indices(n), ear(n), reflex(n);
	iota(ALL(indices), 0);
	auto updReflexStatus = [&](int i)
	{
		int sz = SZ(indices),
			pos = find(ALL(indices), i) - indices.begin();
		int iPrev = indices[(pos + sz - 1) % sz],
			iNext = indices[(pos + 1) % sz];
		reflex[i] = orient(v[iPrev], v[i], v[iNext]) < 0;
	};
	auto updEarStatus = [&](int i)
	{
		if (reflex[i])
		{
			ear[i] = 0;
			return;
		}
		int sz = SZ(indices),
			pos = find(ALL(indices), i) - indices.begin();
		int iPrev = indices[(pos + sz - 1) % sz],
			iNext = indices[(pos + 1) % sz];
		ear[i] = 1;
		for (int j : indices)
		{
			if (j != iPrev && j != i && j != iNext && reflex[j]
				&& inConvexPolygon({v[iPrev], v[i], v[iNext]}, v[j]))
			{
				ear[i] = 0;
				break;
			}
		}
	};
	FOR(i, 0, n)
		updReflexStatus(i);
	FOR(i, 0, n)
		updEarStatus(i);
	RFOR(sz, n + 1, 3)
	{
		int i = 0;
		while (!ear[indices[i]])
			i++;
		int iPrev = indices[(i + sz - 1) % sz], iNext = indices[(i + 1) % sz];
		res.PB({iPrev, indices[i], iNext});
		indices.erase(indices.begin() + i);
		updReflexStatus(iPrev);
		updReflexStatus(iNext);
		updEarStatus(iPrev);
		updEarStatus(iNext);
	}
	return res;
}
