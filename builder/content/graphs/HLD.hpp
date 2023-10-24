/**
 * Description: run dfsSZ and dfsHLD to build HLD.
 * Vertex v has index tin[v]. To update on path use process as in get(). 
 * */

VI g[N];     
int sz[N];   
int h[N];    
int p[N];    
int top[N];  
int tin[N];
int tout[N];
int t = 0;

void dfsSZ(int v, int par = -1, int hei = 0)
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
void dfsHLD(int v, int par = -1, int tp = 0)
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
LL get(int x, int y)
{
	LL res = 0;
	while(true)
	{
		int tx = top[x];
		int ty = top[y];
		if (tx == ty)
		{
			int t1 = tin[x];
			int t2 = tin[y];
			if (t1 > t2)
				swap(t1, t2);
			res += query(t1, t2);
			break;
		}
		if (h[tx] < h[ty])
		{
			swap(tx, ty);
			swap(x, y);
		}
		res += query(tin[tx], tin[x]);
		x = p[tx];
	}
	return res;
}
