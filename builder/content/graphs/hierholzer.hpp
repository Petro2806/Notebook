/**
 * Description: Hierholzer's algorithm finds an Eulerian cycle in a directed graph.
 * $g[u]$ is the vector of pairs $(v, \text{edgeIndex})$.
 * Returns empty if there is no Eulerian cycle.
 * Otherwise, returns the vector of edge indices.
 */
VI hierholzer()
{
	VI degIn(n);
	FOR(i, 0, n)
		for (auto [j, id] : g[i])
			degIn[j]++;
	FOR(i, 0, n)
		if (degIn[i] != SZ(g[i]))
			return {};
	deque<PII> d;
	int v = 0;
	int k = 0;
	while (SZ(d) < m)
	{
		while (k < m && g[v].empty())
		{
			d.push_front(d.back());
			d.pop_back();
			v = d.back().F;
			k++;
		}
		if (k == m)
			return {};
		d.PB(g[v].back());
		g[v].pop_back();
		v = d.back().F;
	}
	VI res;
	for (auto [u, id] : d)
		res.PB(id);
	return res;
}
