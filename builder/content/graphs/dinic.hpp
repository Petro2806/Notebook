/**
 * Description: Finds the maximum flow in a network.
 * Time: O(n^2 m). If all capacities are less than $c$, then the complexity of the Dinic is bounded by $O(\min(n^{\frac{2}{3}}, \sqrt{c m}) \cdot c m)$.
 */
struct Graph
{
	struct Edge
	{
		int from, to;
		LL cap, flow;
	};
	
	int n;
	vector<Edge> edges;
	vector<VI> g;
	VI d, p;
	
	Graph(int _n): n(_n), g(n), d(n), p(n) {}
	void addEdge(int from, int to, LL cap)
	{
		assert(0 <= from && from < n);
		assert(0 <= to && to < n);
		assert(0 <= cap);
		g[from].PB(SZ(edges));
		edges.PB({from, to, cap, 0});
		g[to].PB(SZ(edges));
		edges.PB({to, from, 0, 0});
	}
	int bfs(int s, int t)
	{
		fill(ALL(d), -1);
		d[s] = 0;
		queue<int> q;
		q.push(s);
		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			for (int e : g[v])
			{
				int to = edges[e].to;
				if (edges[e].flow < edges[e].cap && d[to] == -1)
				{
					d[to] = d[v] + 1;
					q.push(to);
				}
			}
		}
		return d[t];
	}
	LL dfs(int v, int t, LL flow)
	{
		if (v == t || flow == 0)
			return flow;
		for (; p[v] < SZ(g[v]); p[v]++)
		{
			int e = g[v][p[v]], to = edges[e].to;
			LL c = edges[e].cap, f = edges[e].flow;
			if (f < c && (to == t || d[to] == d[v] + 1))
			{
				LL push = dfs(to, t, min(flow, c - f));
				if (push > 0)
				{
					edges[e].flow += push;
					edges[e ^ 1].flow -= push;
					return push;
				}
			}
		}
		return 0;
	}
	LL flow(int s, int t)
	{
		assert(0 <= s && s < n);
		assert(0 <= t && t < n);
		assert(s != t);
		LL flow = 0;
		while (bfs(s, t) != -1)
		{
			fill(ALL(p), 0);
			while (true)
			{
				LL f = dfs(s, t, LINF);
				if (f == 0)
					break;
				flow += f;
			}
		}
		return flow;
	}
};
