int triangles(int n, int m)
{
	FOR (i, 0, m)
	{
		auto [u, v] = edges[i];
        if (MP(deg[u], u) < MP(deg[v], v))
            g[u].PB(v);
        else
			g[v].PB(u);
    }
    int cnt = 0;
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
