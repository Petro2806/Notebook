/**
 * Description: Finds all triangles in a graph. 
 * Each triangle $(v, u, w)$ increments the cnt.	
 * Time: $O(m \cdot \sqrt{m})$
 **/

int triangles(int n, vector<PII> edges)
{
	vector<VI> g(n);
	int m = SZ(edges);
	VI deg(n, 0);
	FOR(i, 0, m)
	{
		auto [u, v] = edges[i];
		assert(0 <= u && u < n);
		assert(0 <= v && v < n);
		deg[u]++;
		deg[v]++;
	}
	FOR (i, 0, m)
	{
		auto [u, v] = edges[i];
		if (MP(deg[u], u) < MP(deg[v], v))
			g[u].PB(v);
		else
			g[v].PB(u);
	}
	int cnt = 0;
	VI used(n, 0);
	FOR (v, 0, n)
	{
		for (auto u : g[v]) 
			used[u] = 1;
		for (auto u : g[v])
		{
			for(auto w : g[u])
			{
				if (used[w])
				{
					cnt++;
				}
			}
		}
		for (auto u : g[v]) 
			used[u] = 0;
	}
	return cnt;
}
