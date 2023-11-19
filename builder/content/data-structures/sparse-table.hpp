struct SparseTable
{
	VI t[LOG];
	VI lg;
	int n;
	
	void init(int _n)
	{
		n = _n;
		lg.resize(n + 1);
		FOR(i, 2, n + 1)
			lg[i] = lg[i / 2] + 1;
			
		FOR(j, 0, LOG)
			t[j].assign(n, INF);
	}
	
	void build(const VI& v)
	{	
		FOR (i, 0, SZ(v)) t[0][i] = v[i];
		
		FOR (j, 1, LOG)
		{
			int len = 1 << (j - 1);
			FOR (i, 0, n - (1 << j) + 1)
			{
				t[j][i] = min(t[j - 1][i], 
				t[j - 1][i + len]);
			}
		}
	}
	// [l, r)
	int query(int l, int r)
	{
		int i = lg[r - l];
		return min(t[i][l], t[i][r - (1 << i)]);
	}
};
