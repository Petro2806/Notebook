/**
 * Description: solves the system $A x = b$.
 * If there is no solution, returns a pair of two empty vectors.
 * Otherwise, returns the pair $(x, \text{basis})$ with $x$ being any solution
 * and $\text{basis}$ being the basis for the \textit{nullspace} -- the set of solutions of $A x = 0$.
 * Time: O(n m \min (n, m))
 */
pair<VI, vector<VI>> solveLinear(vector<VI> a, VI b)
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
		// when working with floating-point numbers
		// a[p][j] should be the largest element in the
		// column by absolute value
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
			return {};
	VI x(m);
	RFOR(i, p, 0)
	{
		int j = pivots[i];
		x[j] = a[i].back();
		FOR(k, j + 1, m)
			updSub(x[j], mult(a[i][k], x[k]));
		x[j] = mult(x[j], binpow(a[i][j], mod - 2));
	}
	vector<VI> basis;
	FOR(q, 0, m)
	{
		if (find(ALL(pivots), q) != pivots.end())
			continue;
		VI d(m);
		d[q] = 1;
		RFOR(i, p, 0)
		{
			int j = pivots[i];
			FOR(k, j + 1, m)
				updSub(d[j], mult(a[i][k], d[k]));
			d[j] = mult(d[j], binpow(a[i][j], mod - 2));
		}
		basis.PB(d);
	}
	return {x, basis};
}
