/**
 * Description: Let $P(x)$ be the polynomial of degree at most $n - 1$.
 * Given $P(0), P(1), \dots, P(n - 1)$.
 * Computes $P(c), P(c + 1), \dots, P(c + m - 1)$.
 * Time: O((n + m) \log (n + m))
 */
VI shiftEvalValues(VI a, int c, int m)
{
	int n = SZ(a);
	VI q(n);
	FOR(i, 0, n)
	{
		q[i] = mult(a[i], mult(ifact[i], ifact[n - i - 1]));
		if ((n - i) % 2 == 0)
			q[i] = sub(0, q[i]);
	}
	VI s(n + m - 1);
	FOR(i, 0, SZ(s))
		s[i] = binpow(sub(add(c, i), n - 1), mod - 2);
	VI res = mult(q, s);
	res = {res.begin() + n - 1, res.begin() + n + m - 1};
	int prod = 1;
	FOR(i, 0, n)
	{
		int cur = sub(c, i);
		if (cur != 0)
			prod = mult(prod, cur);
	}
	FOR(i, 0, m)
	{
		int j = add(c, i);
		res[i] = j < n ? a[j] : mult(res[i], prod);
		int r = add(c, i + 1);
		if (r != 0)
			prod = mult(prod, r);
		int l = sub(add(c, i), n - 1);
		if (l != 0)
			prod = mult(prod, binpow(l, mod - 2));
	}
	return res;
}
