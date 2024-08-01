struct DSU
{
	int n;
	VI p, sz;
	
	DSU(int _n = 0) 
	{
		n = _n;
		p.resize(n);
		iota(ALL(p), 0);
		sz.assign(n, 1);
	}
	int find(int v)
	{
		if (v == p[v])
			return v;
		return p[v] = find(p[v]);
	}
	bool unite(int u, int v)
	{
		u = find(u);
		v = find(v);
		if (u == v) 
			return false;
		if (sz[u] > sz[v])
			swap(u, v);
		p[u] = v;
		sz[v] += sz[u];
		return true;
	}
};
