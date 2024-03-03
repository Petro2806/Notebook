/**
 * Description: solves the system $A x = b$.
 * If there is no solution, returns $(\{\}, -1)$.
 * If the solution is unique, returns $(x, 1)$.
 * Otherwise, returns $(x, 2)$ with $x$ being any solution.
 * Time: O(n m \min (n, m))
 */
pair<VI, int> solveLinear(vector<VI> a, VI b)
{
	int n = SZ(a), m = SZ(a[0]);
	assert(SZ(b) == n);
	FOR(i, 0, n)
	{
		assert(SZ(a[i]) == m);
		a[i].PB(b[i]);
	}
	int p = 0;
	VI pivots;
	FOR(j, 0, m)
	{
		// with doubles, abs(a[p][j]) -> max
		if (a[p][j] == 0)
		{
			int l = -1;
			FOR(i, p, n)
				if (a[i][j] != 0)
					l = i;
			if (l == -1)
				continue;
			swap(a[p], a[l]);
		}
		int inv = binpow(a[p][j], mod - 2);
		FOR(i, p + 1, n)
		{
			int c = mult(a[i][j], inv);
			FOR(k, j, m + 1)
				updSub(a[i][k], mult(c, a[p][k]));
		}
		pivots.PB(j);
		p++;
		if (p == n)
			break;
	}
	FOR(i, p, n)
		if (a[i].back() != 0)
			return {{}, -1};
	VI x(m);
	RFOR(i, p, 0)
	{
		int j = pivots[i];
		x[j] = a[i].back();
		FOR(k, j + 1, m)
			updSub(x[j], mult(a[i][k], x[k]));
		x[j] = mult(x[j], binpow(a[i][j], mod - 2));
	}
	return {x, SZ(pivots) == m ? 1 : 2};
}
