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
	vector<LL> e;
	VI h, current;
	queue<int> q;
	void init(int _n)
	{
		n = _n;
		edges.clear();
		g.clear();
		g.resize(n);
		e.assign(n, 0);
		h.assign(n, 0);
		current.assign(n, 0);
	}
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
	void initializePreflow(int s)
	{
		h[s] = n;
		for (int i : g[s])
		{
			Edge& edge = edges[i];
			if (edge.cap > 0)
			{
				edge.flow = edge.cap;
				edges[i ^ 1].flow = -edge.cap;
				e[edge.to] = edge.cap;
				e[s] -= edge.cap;
			}
		}
	}
	void push(int i)
	{
		Edge& edge = edges[i];
		int delta = min(e[edge.from], edge.cap - edge.flow);
		edge.flow += delta;
		edges[i ^ 1].flow -= delta;
		e[edge.from] -= delta;
		if (e[edge.to] == 0)
			q.push(edge.to);
		e[edge.to] += delta;
	}
	void relabel(int u)
	{
		h[u] = 4 * n + 47;
		for (int i : g[u])
		{
			const Edge& edge = edges[i];
			if (edge.flow < edge.cap)
				h[u] = min(h[u], h[edge.to] + 1);
		}
	}
	void discharge(int u)
	{
		while (e[u] > 0)
		{
			for (; e[u] > 0 && current[u] < SZ(g[u]); current[u]++)
			{
				int i = g[u][current[u]];
				const Edge& edge = edges[i];
				if (edge.flow < edge.cap && h[u] == h[edge.to] + 1)
					push(i);
			}
			if (e[u] > 0)
			{
				relabel(u);
				current[u] = 0;
			}
		}
	}
	LL flow(int s, int t)
	{
		assert(0 <= s && s < n);
		assert(0 <= t && t < n);
		assert(s != t);
		initializePreflow(s);
		FOR(u, 0, n)
		{
			if (e[u] > 0)
				q.push(u);
		}
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			if (u != t)
				discharge(u);
		}
		return e[t];
	}
};
