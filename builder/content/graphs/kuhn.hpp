/**
 * Description: mateFor is $-1$ or mate. addEdge([0, $L$), [0, $R$)).
 * Time: 0.6s for $L, R \le 10^5, |E| \le 2 \cdot 10^5$
 */

mt19937 rng;

struct Graph
{
	int szL, szR;
	// edges from the left to the right, 0-indexed
	vector<VI> g;
	VI mateForL, usedL, mateForR;
	
	Graph(int L = 0, int R = 0): szL(L), szR(R), g(L), 
		mateForL(L), usedL(L), mateForR(R) {}
	
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
			
			bool ok = false;
			FOR(v, 0, szL)
			{
				if (mateForL[v] == -1)
				{
					if (kuhn(v))
					{
						ok = true;
						res++;
					}
				}
			}
			if (!ok) break;
		}
		return res;
	}
};
