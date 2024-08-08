/**
 * Description: Solves the system $A x = b$.
 * Returns $(v, w)$ such that every solution $x$ can be represented as
 * $v + c_1 w_1 + c_2 w_2 + \dots + c_k w_k$, where $v$ is arbitrary solution,
 * $c_i$ are scalars and $w$ is basis.
 * If there is no solution, returns an empty pair.
 * If the solution is unique, then $w$ is empty.
 * Time: O(n m \min (n, m))
 */
pair<VI, vector<VI>> solveLinearSystem(vector<VI> a, VI b)
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
			return {};
	VI v(m);
	RFOR(i, p, 0)
	{
		int j = pivots[i];
		v[j] = a[i].back();
		FOR(k, j + 1, m)
			updSub(v[j], mult(a[i][k], v[k]));
		v[j] = mult(v[j], binpow(a[i][j], mod - 2));
	}
	vector<VI> w;
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
		w.PB(d);
	}
	return {v, w};
}
