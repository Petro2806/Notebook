/**
 * Description: works for cyclic graphs. $par$ - parent in dfs. $p$ - parent in dsu. $val$ - vertex with min sdom in dsu.
 * $dom$ - immidiate dominator. $sdom$ - semidominator, min vertex with alternate path.
 * $bkt$ - vertices with this sdom. 
 * $dom[root] = -1$. $dom[v] = -1$ if $v$ is unreachable.
 * Time: $O(n)$
 **/


struct Graph
{
	int n;
	vector<VI> g, gr, bkt;
	VI par, used, p, val, sdom, dom, tin;
	int T;
	VI ord;
	
	void init(int _n)
	{
		n = _n;
		g.resize(n);
		gr.resize(n);
		bkt.resize(n);
		par.resize(n);
		used.resize(n);
		p.resize(n);
		val.resize(n);
		sdom.resize(n);
		dom.resize(n);
		tin.resize(n);
	}
	
	void addEdge(int u, int v)
	{
		g[u].PB(v);
		gr[v].PB(u);
	}
	
	int find(int v)
	{
		if (p[v] == v) 
			return v;
		int y = find(p[v]);
		if (p[y] == y) 
			return v;
		if (tin[sdom[val[p[v]]]] < tin[sdom[val[v]]])
			val[v] = val[p[v]];
		p[v] = y;
		return y;
	}
	int get(int v)
	{
		find(v);
		// return vertex with min sdom
		return val[v]; 
	}
	
	
	void dfs(int v, int pr)
	{
		tin[v] = T++;
		used[v] = true;
		ord.PB(v);
		par[v] = pr;
		for (auto to : g[v])
		{
			if (!used[to])
				dfs(to, v);
		}
	}
	
	void build(int s)
	{
		FOR (i, 0, n)
		{
			used[i] = false;
			sdom[i] = i;
			dom[i] = -1;
			p[i] = i;
			val[i] = i;
			bkt[i].clear();
		}
		ord.clear();
		T = 0;
	
		dfs(s, -1);
		
		RFOR(i, SZ(ord), 0)
		{
			int v = ord[i];
			for (auto from : gr[v])
			{
				// don't consider unreachable vertices
				if (!used[from])
					continue; 
				// find min sdom 
				if (tin[sdom[v]] > tin[sdom[get(from)]]) 
				{   
					sdom[v] = sdom[get(from)];
				}
			}
			if (v != s) 
				bkt[sdom[v]].PB(v);
			for (auto y : bkt[v])
			{
				int u = get(y);
				// if sdoms equals then this is dom
				// else we will find it later
				if (sdom[y] == sdom[u])
					dom[y] = sdom[y]; 
				else dom[y] = u; 
			}
			// add vertex to dsu
			if (par[v] != -1) 
				p[v] = par[v]; 
		}
	
		for (auto v : ord)
		{
			if (v == s || dom[v] == -1)
				continue;
			if (dom[v] != sdom[v]) dom[v] = dom[dom[v]];
		}
	}
	
};
