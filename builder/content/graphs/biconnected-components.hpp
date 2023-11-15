struct Graph
{
	vector<PII> edges;
	vector<VI> g;

	//Components for edges 
	VI col;
	VI used, par;
	VI tin, low;
	int t = 1, c = 1;
	vector<int> st;
	
	int n, m;
	
	void init(int _n, int _m)
	{
		n = _n;
		m = _m;
		
		edges.assign(m, {0, 0});
		g.assign(n, {});
		
		col.assign(m, 0);
		
		tin.assign(n, 0);
		used.assign(n, 0);
		par.assign(n, -1);
		used.assign(n, 0);

		t = c = 1;
	}	
	

	void addEdge(int a, int b, int i)
	{
		assert(0 <= a && a < n);
		assert(0 <= b && b < n);
		assert(0 <= i && i < m);
		
		edges[i] = MP(a, b);
		g[a].PB(i);
		g[b].PB(i);
	}

	void dfs(int v, int p = -1)
	{
		used[v] = 1;
		par[v] = p;
		low[v] = tin[v] = t++;
		int cnt = 0;
		for (auto e : g[v])
		{
			int to = edges[e].F;
			if (to == v)
				to = edges[e].S;
				
			if (p == to) continue;
			if (!used[to])
			{
				cnt++;
				st.PB(e);
				dfs(to, v);
				
				low[v] = min(low[v], low[to]);
				
				if ((par[v] == -1 && cnt > 1) || 
				(par[v] != -1 && low[to] >= tin[v]))
				{
					while (st.back() != e)
					{
						col[st.back()] = c;
						st.pop_back();
					}
					col[st.back()] = c++;
					st.pop_back();
				}
			}
			else
			{
				low[v] = min(low[v], tin[to]);
				if (tin[to] < tin[v])
					st.PB(e);
			}
		}	
	}
};
