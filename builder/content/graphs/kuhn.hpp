/**
 * Time: 0.6s for $|V| = 10^5, |E| = 2*10^5$
 */
struct Graph
{
	int L, R;
	//edges from left to right in 0 indexing
	vector<VI> g;   
	VI mt, P, U;
	
	void init(int l, int r)
	{
		L = l, R = r;
		g.resize(L);
		P.resize(L);
		U.resize(L);
		
		mt.resize(R);
	}
	
	void addEdge(int from, int to)
	{
		assert(0 <= from && from < L);
		assert(0 <= to && to < R);
		
		g[from].PB(to);
	}
	
	int iter;
	bool kuhn(int v)
	{
		if (U[v] == iter) return false;
		U[v] = iter;
		random_shuffle(ALL(g[v]));
		for(int to : g[v])
		{
			if (mt[to] == -1)
			{
				mt[to] = v;
				P[v] = to;
				return true;
			}
		}
		for(int to : g[v])
		{
			if (kuhn(mt[to]))
			{
				mt[to] = v;
				P[v] = to;
				return true;
			}
		}
		return false;
	}
	int doKuhn()
	{
		fill(ALL(mt), -1);
		fill(ALL(P), -1);
		fill(ALL(U), -1);
		
		int res = 0;
		iter = 0;
		VI order(L);
		iota(ALL(order), 0);
		random_shuffle(ALL(order));
		
		while(true)
		{
			iter++;
			bool ok = false;
			for(int v : order)
			{
				if (P[v] == -1)
					if (kuhn(v))
					{
						ok = true;
						res++;
					}
			}
			if (!ok) break;
		}
		return res;
	}
};
