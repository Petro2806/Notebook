/**
 * Description: Finds the minimum cost maximum flow in a network.
 * If the network contains negative-cost edges, uncomment \texttt{initPotentials}.
 * Time: $O(|F| \cdot m \log n)$ without negative-cost edges, and $O(|F| \cdot m \log n + n m)$ with negative-cost edges.
 */
struct Graph
{
	struct Edge
	{
		int from, to;
		int cap, flow;
		LL cost;
	};
	
	int n;
	vector<Edge> edges;
	vector<VI> g;
	VL pi, d;
	VI pred;
	
	Graph(int _n = 0): n(_n), g(n), pi(n), d(n), pred(n) {}
	
	void addEdge(int from, int to, int cap, LL cost)
	{
		assert(0 <= from && from < n);
		assert(0 <= to && to < n);
		assert(0 <= cap);
		g[from].PB(SZ(edges));
		edges.PB({from, to, cap, 0, cost});
		g[to].PB(SZ(edges));
		edges.PB({to, from, 0, 0, -cost});
	}
	/*void initPotentials(int s)
	{
		vector<vector<pair<int, LL>>> gr(n);
		FOR(v, 0, n)
		{
			for (int e : g[v])
			{
				const Edge& edge = edges[e];
				if (edge.flow < edge.cap)
					gr[v].PB({edge.to, edge.cost});
			}
		}
		pi = spfa(gr, n, s);
	}*/
	pair<int, LL> flow(int s, int t)
	{
		assert(0 <= s && s < n);
		assert(0 <= t && t < n);
		assert(s != t);
		//initPotentials(s);
		int flow = 0;
		LL cost = 0;
		for (int it = 0; ; it++)
		{
			fill(ALL(d), LINF);
			fill(ALL(pred), -1);
			d[s] = 0;
			priority_queue<pair<LL, int>> q;
			q.push({0, s});
			while (!q.empty())
			{
				auto [dv, v] = q.top();
				q.pop();
				if (it > 0 && v == t)
					break;
				if (-dv != d[v])
					continue;
				for (int i : g[v])
				{
					if (edges[i].flow == edges[i].cap)
						continue;
					int to = edges[i].to;
					LL nd = d[v] + edges[i].cost + pi[v] - pi[to];
					if (nd < d[to])
					{
						d[to] = nd;
						pred[to] = i;
						q.push({-nd, to});
					}
				}
			}
			if (d[t] == LINF)
				break;
			int curFlow = INF;
			for (int v = t; v != s;)
			{
				int i = pred[v];
				curFlow = min(curFlow, edges[i].cap - edges[i].flow);
				v = edges[i].from;
			}
			for (int v = t; v != s;)
			{
				int i = pred[v];
				edges[i].flow += curFlow;
				edges[i ^ 1].flow -= curFlow;
				v = edges[i].from;
			}
			flow += curFlow;
			cost += (d[t] + pi[t] - pi[s]) * curFlow;
			FOR(u, 0, n)
				if (it == 0 || d[u] <= d[t])
					pi[u] += d[u] - d[t];
		}
		return {flow, cost};
	}
};
