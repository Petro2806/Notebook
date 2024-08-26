/**
 * Description: Finds the maximum matching in a graph.
 * Time: O(n^2 m)
 */
struct Graph
{
	int n;
	vector<VI> g;
	VI label, first, mate;
	
	Graph(int _n = 0): n(_n), g(n + 1), label(n + 1), 
		first(n + 1), mate(n + 1) {}
	
	void addEdge(int u, int v)
	{
		assert(0 <= u && u < n);
		assert(0 <= v && v < n);
		u++;
		v++;
		g[u].PB(v);
		g[v].PB(u);
	}
	void augmentPath(int v, int w)
	{
		int t = mate[v];
		mate[v] = w;
		if (mate[t] != v)
			return;
		if (label[v] <= n)
		{
			mate[t] = label[v];
			augmentPath(label[v], t);
			return;
		}
		int x = label[v] / (n + 1); 
		int y = label[v] % (n + 1);
		augmentPath(x, y);
		augmentPath(y, x);
	}
	int findMaxMatching()
	{
		FOR(i, 0, n + 1)
			assert(mate[i] == 0);
		int mt = 0;
		DSU dsu;
		FOR(u, 1, n + 1)
		{
			if (mate[u] != 0)
				continue;
			fill(ALL(label), -1);
			iota(ALL(first), 0);
			dsu.init(n + 1);
			label[u] = 0;
			dsu.unite(u, 0);
			queue<int> q;
			q.push(u);
			while (!q.empty())
			{
				int x = q.front();
				q.pop();
				for (int y: g[x])
				{
					if (mate[y] == 0 && y != u)
					{
						mate[y] = x;
						augmentPath(x, y);
						while (!q.empty())
							q.pop();
						mt++;
						break;
					}
					if (label[y] < 0)
					{
						int v = mate[y];
						if (label[v] < 0)
						{
							label[v] = x;
							dsu.unite(v, y);
							q.push(v);
						}
					}
					else
					{
						int r = first[dsu.find(x)],	s = first[dsu.find(y)];
						if (r == s)
							continue;
						int edgeLabel = (n + 1) * x + y;
						label[r] = label[s] = -edgeLabel;
						int join;
						while (true)
						{
							if (s != 0)
								swap(r, s);
							r = first[dsu.find(label[mate[r]])];
							if (label[r] == -edgeLabel)
							{
								join = r;
								break;
							}
							label[r] = -edgeLabel;
						}
						for (int z: {x, y})
						{
							for (int v = first[dsu.find(z)];
								v != join;
								v = first[dsu.find(label[mate[v]])])
							{
								label[v] = edgeLabel;
								if (dsu.unite(v, join))
									first[dsu.find(join)] = join;
								q.push(v);
							}
						}
					}
				}
			}
		}
		return mt;
	}
	int getMate(int v)
	{
		assert(0 <= v && v < n);
		v++;
		int u = mate[v];
		assert(u == 0 || mate[u] == v);
		u--;
		return u;
	}
};
