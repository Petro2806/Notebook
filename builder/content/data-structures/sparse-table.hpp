/**
 * Description: Sparse table for minimum on the range $[l, r), l < r$.
 * You can push back an element in $O(\text{LOG})$ and query anytime.
 */

struct SparseTable
{
	VI t[LOG];
	
	void push_back(int v)
	{
		int i = SZ(t[0]);
		t[0].PB(v);
		FOR (j, 0, LOG - 1) 
			t[j + 1].PB(min(t[j][i], t[j][max(0, i - (1 << j))]));
	}
	// [l, r)
	int query(int l, int r)
	{
		assert(l < r && r <= SZ(t[0]));
		int i = 31 - __builtin_clz(r - l);
		return min(t[i][r - 1], t[i][l + (1 << i) - 1]);
	}
};
