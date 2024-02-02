/**
 * Description: Finds an Eulerian path in a directed or undirected (defined by template parameter) graph.
 * Most likely, you need only one directedness and can delete some code.
 * $g$ is a graph with $n$ vertices. $g[u]$ is a vector of pairs $(v, \text{edge_id})$. $m$ is the number of edges in the graph.
 * The vertices are numbered from $0$ to $n - 1$, and the edges - from $0$ to $m - 1$.
 * If there is no Eulerian path, returns {{-1}, {-1}}.
 * Otherwise, returns the path in the form (vertices, edges) with vertices containing $m + 1$ elements and edges containing $m$ elements.
 * The edge with number edges$[i]$ is from vertices$[i]$ to vertices$[i + 1]$.
 * If you need an Eulerian cycle, check vertices[0] = vertices.back().
 */
template<bool directed>
pair<VI, VI> hierholzer(vector<vector<PII>> g, int m)
{
	int n = SZ(g), v1 = -1, v2 = -1;
	bool bad = false;
	if (directed)
	{
		VI degIn(n);
		FOR(u, 0, n)
			for (auto [v, e] : g[u])
				degIn[v]++;
		FOR(u, 0, n)
		{
			bad |= abs(degIn[u] - SZ(g[u])) > 1;
			if (degIn[u] < SZ(g[u]))
			{
				bad |= v2 != -1;
				v2 = u;
			}
			else if (degIn[u] > SZ(g[u]))
			{
				bad |= v1 != -1;
				v1 = u;
			}
		}
	}
	else
	{
		FOR(u, 0, n)
		{
			if (SZ(g[u]) & 1)
			{
				bad |= v2 != -1;
				if (v1 == -1)
					v1 = u;
				else
					v2 = u;
			}
		}
	}
	if (bad)
		return {{-1}, {-1}};
	if (v1 != -1)
	{
		g[v1].PB({v2, m});
		if (!directed)
			g[v2].PB({v1, m});
		m++;
	}
	deque<PII> d;
	VI used(m);
	int v = 0, k = 0;
	while (m > 0 && g[v].empty())
		v++;
	while (SZ(d) < m)
	{		
		while (k < m)
		{
			while (!g[v].empty() && used[g[v].back().S])
				g[v].pop_back();
			if (!g[v].empty())
				break;
			d.push_front(d.back());
			d.pop_back();
			v = d.back().F;
			k++;
		}
		if (k == m)
			return {{-1}, {-1}};
		d.PB(g[v].back());
		used[g[v].back().S] = true;
		g[v].pop_back();
		v = d.back().F;
	}
	while (v1 != -1 && d.back().S != m - 1)
	{
		d.push_front(d.back());
		d.pop_back();
		v = d.back().F;
	}
	VI vertices = {v}, edges;
	for (auto [u, e] : d)
	{
		vertices.PB(u);
		edges.PB(e);
	}
	if (v1 != -1)
	{
		vertices.pop_back();
		edges.pop_back();
	}
	return {vertices, edges};
}
