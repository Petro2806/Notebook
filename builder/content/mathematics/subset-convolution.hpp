/**
* Description: $c[S] = \sum_{T \subseteq S} a[T] \cdot b[S \setminus T]$.
* Time: $O(n^2 \cdot 2^n)$, ~1.5s for $n = 20$.
*/

vector<VI> rankedMobius(VI a, int n)
{
	vector<VI> res(n + 1, VI(1 << n));
	FOR(mask, 0, 1 << n)
		res[__builtin_popcount(mask)][mask] = a[mask];
	FOR(sz, 0, n + 1)
		convOr(res[sz], n, false); 
	return res;
}
VI subsetConvolution(VI a, VI b, int n)
{
	auto f = rankedMobius(a, n);
	auto g = rankedMobius(b, n);
	
	vector<VI> conv(n + 1, VI(1 << n));	
	FOR(sz, 0, n + 1)
	{
		FOR(i, 0, sz + 1) 
			FOR(mask, 0, 1 << n)
				updAdd(conv[sz][mask], mult(f[i][mask], g[sz - i][mask]));
		convOr(conv[sz], n, true);
	}
	VI res(1 << n);
	FOR(mask, 0, 1 << n)
		res[mask] = conv[__builtin_popcount(mask)][mask];
	return res;
}
