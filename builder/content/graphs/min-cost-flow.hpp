struct Graph
{
	struct Edge
	{
		int from, to;
		int cap, flow;
		LL cost;
	};
	
	int _n;
	vector<Edge> edges;
	vector<VI> g;
	vector<LL> d;
	VI p, w;
	
	Graph(): _n(0) {}
	Graph(int n): _n(n), g(n), d(n), p(n), w(n) {}
	
	void addEdge(int from,int to, int cap, LL cost)
	{
		assert(0 <= from && from < _n);
		assert(0 <= to && to < _n);
		assert(0 <= cap);
		assert(0 <= cost);
		g[from].PB(SZ(edges));
		edges.PB({from, to, cap, 0, cost});
		g[to].PB(SZ(edges));
		edges.PB({to, from, 0, 0, -cost});
	}
	
	pair<int, LL> flow(int s, int t)
	{
		assert(0 <= s && s < _n);
		assert(0 <= t && t < _n);
		assert(s != t);
		int flow = 0;
		LL cost = 0;
		while (true)
		{
			fill(ALL(d), LINF);
			fill(ALL(p), -1);
			fill(ALL(w), 0);
			queue<int> q1, q2;
			w[s] = 1;
			d[s] = 0;
			q2.push(s);
			while (!q1.empty() || !q2.empty())
			{
				int v;
				if (!q1.empty())
				{
					v = q1.front();
					q1.pop();
				}
				else
				{
					v = q2.front();
					q2.pop();
				}
				for (int e : g[v])
				{
					if (edges[e].flow == edges[e].cap)
						continue;
					int to = edges[e].to;
					LL newDist = d[v] + edges[e].cost;
					if (newDist < d[to])
					{
						d[to] = newDist;
						p[to] = e;
						if (w[to] == 0)
							q2.push(to);
						else if (w[to] == 2)
							q1.push(to);
						w[to] = 1;
					}
				}
				w[v] = 2;
			}
			if (p[t] == -1)
				break;
			int curFlow = INF;
			LL curCost = 0;
			for (int v = t; v != s;)
			{
				int e = p[v];
				curFlow = min(curFlow, 
				edges[e].cap - edges[e].flow);
				curCost += edges[e].cost;
				v = edges[e].from;
			}
			for (int v = t; v != s;)
			{
				int e = p[v];
				edges[e].flow += curFlow;
				edges[e ^ 1].flow -= curFlow;
				v = edges[e].from;
			}
			flow += curFlow;
			cost += curCost * curFlow;
		}
		return {flow, cost};
	}
};
