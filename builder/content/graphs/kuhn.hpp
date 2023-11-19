/**
 * Time: 0.6s for $|V| = 10^5, |E| = 2*10^5$
 */
struct Graph
{
	int szL, szR;
	// edges from the left to the right, 0-indexed
	vector<VI> g;
	VI mateForR, mateForL, usedL;
	
	void init(int l, int r)
	{
		szL = l, szR = r;
		g.resize(L);
		mateForL.resize(L);
		usedL.resize(L);
		
		mateForR.resize(R);
	}
	
	void addEdge(int from, int to)
	{
		assert(0 <= from && from < szL);
		assert(0 <= to && to < szR);
		
		g[from].PB(to);
	}
	
	int iter;
	bool kuhn(int v)
	{
		if (usedL[v] == iter) return false;
		usedL[v] = iter;
		shuffle(ALL(g[v]), rng);
		for(int to : g[v])
		{
			if (mateForR[to] == -1)
			{
				mateForR[to] = v;
				mateForL[v] = to;
				return true;
			}
		}
		for(int to : g[v])
		{
			if (kuhn(mateForR[to]))
			{
				mateForR[to] = v;
				mateForL[v] = to;
				return true;
			}
		}
		return false;
	}
	int doKuhn()
	{
		fill(ALL(mateForR), -1);
		fill(ALL(mateForL), -1);
		fill(ALL(usedL), -1);
		
		int res = 0;
		iter = 0;
		
		while(true)
		{
			iter++;
			
			VI order(L);
			iota(ALL(order), 0);
			shuffle(ALL(order), rng);

			bool ok = false;
			for(int v : order)
			{
				if (mateForL[v] == -1)
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
