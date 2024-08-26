/**
 * Description: Colors the edges so that the vertices,
 * connected with the same color are still connected if you delete any vertex.
 * Time: $O(m)$
 **/

struct Graph
{
	int n, m;
	vector<PII> edges;
	vector<VI> g;

	VI used, par;
	VI tin, low, inComp;
	int t = 0, c = 0;
	VI st;

	// components of vertices
	// a vertex can be in several components
	vector<VI> verticesCol;
	// components of edges
	vector<VI> components;
	// col[i] - component of the i-th edge
	VI col;
	
	Graph(int _n = 0, int _m = 0): n(_n), m(_m), edges(m), g(n), 
	used(n), par(n, -1), tin(n), low(n), inComp(n), col(m, -1) {}
	
	void addEdge(int a, int b, int i)
	{
		assert(0 <= a && a < n);
		assert(0 <= b && b < n);
		assert(0 <= i && i < m);
		
		edges[i] = MP(a, b);
		g[a].PB(i);
		g[b].PB(i);
	}
	
	void addComp()
	{
		unordered_set<int> s;
		s.reserve(7 * SZ(components[c]));
		for (auto e : components[c])
		{
			s.insert(edges[e].F);
			s.insert(edges[e].S);
			inComp[edges[e].F] = true;
			inComp[edges[e].S] = true;
		}
		verticesCol.PB(VI(ALL(s)));
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
					components.PB({});
					while (st.back() != e)
					{
						components[c].PB(st.back());
						col[st.back()] = c;
						
						st.pop_back();
					}
					components[c].PB(st.back());
					addComp();
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
	void build()
	{			
		FOR (i, 0, n)
		{
			if (used[i]) continue;
			dfs(i, -1);
			if (st.empty()) continue;
			components.PB({});
			while (!st.empty())
			{
				int e = st.back();
				col[e] = c;
				components[c].PB(e);
				st.pop_back();
			}
			addComp();
			c++;
		}
		FOR (i, 0, n)
			if (!inComp[i])
				verticesCol.PB(VI(1, i));
	}
};
