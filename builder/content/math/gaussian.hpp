/**
 * Description: if there is no solution, returns an empty vector.
 * Otherwise, returns any solution.
 */
VI solveLinearSystem(vector<VI> a, VI b)
{
	int n = SZ(b), m = SZ(a[0]);
	FOR(i, 0, n)
		a[i].PB(b[i]);
	int p = 0;
	VI pivots;
	FOR(j, 0, m)
	{
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
	return x;
}
