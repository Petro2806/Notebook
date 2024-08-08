/**
 * Description: Computes the $n$-th term of a given linearly
 * recurrent sequence with polynomial coefficients
 * $\sum_{j=0}^d P_j(i) \cdot a_{i + d - j} = 0$.
 * The first $d$ terms $a_0, a_1, \dots, a_{d - 1}$ are given.
 * Let $m$ be the maximum degree of $P_j$.
 * Time: O(d^2 \sqrt{n m} \log {n m} + d^3 \sqrt{n m})
 */
VI add(const VI& a, const VI& b)
{
	int n = SZ(a), m = SZ(b);
	VI c(max(n, m));
	FOR(i, 0, n)
		updAdd(c[i], a[i]);
	FOR(i, 0, m)
		updAdd(c[i], b[i]);
	return c;
}

int evalPoly(const VI& p, int x)
{
	int res = 0;
	RFOR(i, SZ(p), 0)
		res = add(mult(res, x), p[i]);
	return res;
}

VI mult(const vector<VI>& a, const VI& b)
{
	int n = SZ(a);
	VI c(n);
	FOR(i, 0, n)
		FOR(j, 0, n)
			updAdd(c[i], mult(a[i][j], b[j]));
	return c;
}

vector<VI> mult(const vector<VI>& a, const vector<VI>& b)
{
	int n = SZ(a);
	vector<VI> c(n, VI(n));
	FOR(i, 0, n)
		FOR(k, 0, n)
			FOR(j, 0, n)
				updAdd(c[i][j], mult(a[i][k], b[k][j]));
	return c;
}

typedef vector<vector<VI>> PolyMatr;

PolyMatr mult(const PolyMatr& a, const PolyMatr& b)
{
	int n = SZ(a);
	PolyMatr c(n, vector<VI>(n));
	FOR(i, 0, n)
		FOR(k, 0, n)
			FOR(j, 0, n)
				c[i][j] = add(c[i][j], mult(a[i][k], b[k][j]));
	return c;
}

int findNthOfPRecursive(const vector<VI>& p, VI a, int n)
{
	int d = SZ(p) - 1;
	assert(SZ(a) == d);
	if (n < d)
		return a[n];
	auto polyMatrProd = [](const PolyMatr& polyMatr, int k, VI u)
	{
		int h = SZ(polyMatr);
		
		auto shiftEvalMatrs =
			[&](const vector<vector<VI>>& matrices, int c, int m)
		{
			int cnt = SZ(matrices);
			vector<vector<VI>> res(m, vector<VI>(h, VI(h)));
			FOR(i, 0, h)
			{
				FOR(j, 0, h)
				{
					VI b(cnt);
					FOR(l, 0, cnt)
						b[l] = matrices[l][i][j];
					b = shiftEvalValues(b, c, m);
					FOR(l, 0, m)
						res[l][i][j] = b[l];
				}
			}
			return res;
		};
		
		int m = 0;
		FOR(i, 0, h)
			FOR(j, 0, h)
				m = max(m, SZ(polyMatr[i][j]) - 1);
		int s = 1;
		while ((LL)m * s * s < k)
			s *= 2;
		int invS = binpow(s, mod - 2);
		vector<vector<VI>> matrices(m + 1, vector<VI>(h, VI(h)));
		FOR(l, 0, m + 1)
		{
			FOR(i, 0, h)
				FOR(j, 0, h)
					matrices[l][i][j] = evalPoly(polyMatr[i][j], l * s);
		}
		for (int r = 1; r < s; r *= 2)
		{
			auto sh = shiftEvalMatrs(matrices, r * m + 1, SZ(matrices) - 1);
			matrices.insert(matrices.end(), ALL(sh));
			sh = shiftEvalMatrs(matrices, mult(r, invS), SZ(matrices));
			FOR(l, 0, SZ(matrices))
				matrices[l] = mult(sh[l], matrices[l]);
		}
		int l = 0;
		for (; l + s <= k; l += s)
			u = mult(matrices[l / s], u);
		vector<VI> matr(h, VI(h));
		for (; l < k; l++)
		{
			FOR(i, 0, h)
				FOR(j, 0, h)
					matr[i][j] = evalPoly(polyMatr[i][j], l);
			u = mult(matr, u);
		}
		return u;
	};

	PolyMatr polyMatr(d, vector<VI>(d));
	FOR(i, 0, d - 1)
		polyMatr[i][i + 1] = p[0];
	FOR(i, 0, d)
	{
		polyMatr[d - 1][i] = p[d - i];
		for (int& coef : polyMatr[d - 1][i])
			coef = sub(0, coef);
	}
	PolyMatr denom = {{p[0]}};
	a = polyMatrProd(polyMatr, n - d + 1, a);
	const VI& x = polyMatrProd(denom, n - d + 1, {1});
	return mult(binpow(x[0], mod - 2), a.back());
}
