int lg[MAX + 1];

struct SparseTable
{
	int t[MAX][LOG];
	
	void init(const VI& v)
	{
		lg[1] = 0;
		FOR (i, 2, MAX + 1) lg[i] = lg[i / 2] + 1;
		FOR (i, 0, MAX) FOR (j, 0, LOG) t[i][j] = INF;
		FOR (i, 0, SZ(v)) t[i][0] = v[i];
		
		FOR (j, 1, LOG)
		{
			int len = 1 << (j - 1);
			FOR (i, 0, MAX - (1 << j))
			{
				t[i][j] = min(t[i][j - 1], 
				t[i + len][j - 1]);
			}
		}
	}
	
	int query(int l, int r)
	{
		int i = lg[r - l + 1];
		return min(t[l][i], t[r - (1 << i) + 1][i]);
	}
} st;
