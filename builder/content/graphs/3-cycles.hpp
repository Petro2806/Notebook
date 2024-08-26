/**
 * Description: Finds all triangles in a graph. 
 * Each triangle $(v, u, w)$ increments the cnt.	
 * Time: $O(m \cdot \sqrt{m})$
 **/

int triangles(int n)
{
	vector<VI> ng(n);
	FOR (v, 0, n)
		for (auto u : g[v])
			if (MP(SZ(g[v]), v) < MP(SZ(g[u]), u))
				ng[v].PB(u);
	int cnt = 0;
	VI used(n, 0);
	FOR (v, 0, n)
	{
		for (auto u : ng[v]) 
			used[u] = 1;
		for (auto u : ng[v])
			for(auto w : ng[u])
				if (used[w])
					cnt++;
		for (auto u : ng[v]) 
			used[u] = 0;
	}
	return cnt;
}

