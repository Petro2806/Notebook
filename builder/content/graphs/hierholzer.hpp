/**
 * Description: Finds an Eulerian cycle in a directed graph.
 * $g[u]$ is the vector of pairs $(v, \text{edgeIndex})$.
 * Returns $\{-1\}$ if there is no Eulerian cycle.
 * Otherwise, returns the vector of edge indices.
 */
VI hierholzer()
{
	VI degIn(n);
	FOR(u, 0, n)
		for (auto [v, id] : g[u])
			degIn[v]++;
	FOR(u, 0, n)
		if (degIn[u] != SZ(g[u]))
			return {-1};
	deque<PII> d;
	int v = 0, k = 0;
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
			return {-1};
		d.PB(g[v].back());
		g[v].pop_back();
		v = d.back().F;
	}
	VI res;
	for (auto [u, id] : d)
		res.PB(id);
	return res;
}
