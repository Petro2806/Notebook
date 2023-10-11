struct DSU
{
	int n;
	VI p;
	VI sz;
	
	void init(int _n)
	{
		n = _n;
		sz.assign(n, 1);
		p.resize(n);
		iota(ALL(p), 0);
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
