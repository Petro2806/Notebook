/**
 * Description: Run \texttt{dfsSZ(root, -1, 0)} and \texttt{dfsHLD(root, -1, root)} to build the HLD.
 * Each vertex $v$ has an index tin[$v$]. To update on the path, use the process as defined in \texttt{get()}.
 * The values are stored in the vertices.
 * */

VI g[N];     
int sz[N];   
int h[N];    
int p[N];    
int top[N];  
int tin[N];
int tout[N];
int t = 0;

void dfsSZ(int v, int par, int hei)
{
	sz[v] = 1;
	h[v] = hei;
	p[v] = par;
	for (auto& to : g[v])
	{
		if (to == par) 
			continue;
		dfsSZ(to, v, hei + 1);
		sz[v] += sz[to];
		if (g[v][0] == par || sz[g[v][0]] < sz[to])
			swap(g[v][0], to);
	}
}
void dfsHLD(int v, int par, int tp)
{
	tin[v] = t++;
	top[v] = tp;
	FOR (i, 0, SZ(g[v]))
	{
		int to = g[v][i];
		if (to == par)
			continue;
		if (i == 0) 
			dfsHLD(to, v, tp);
		else 
			dfsHLD(to, v, to);
	}
	tout[v] = t - 1;
}
LL get(int u, int v)
{
	LL res = 0;
	while(true)
	{
		int tu = top[u];
		int tv = top[v];
		if (tu == tv)
		{
			int t1 = tin[u];
			int t2 = tin[v];
			if (t1 > t2)
				swap(t1, t2);
			// query [t1, t2] both inclusive
			res += query(t1, t2);
			break;
		}
		if (h[tu] < h[tv])
		{
			swap(tu, tv);
			swap(u, v);
		}
		res += query(tin[tu], tin[u]);
		u = p[tu];
	}
	return res;
}
