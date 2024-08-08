/**
 * Description: $\log(A(x))$ modulo $x^n$.
 * Time: O(n \log n)
 */
VI deriv(const VI& a)
{
	int n = SZ(a);
	VI res(max(0, n - 1));
	FOR(i, 0, n - 1)
		res[i] = mult(a[i + 1], i + 1);
	return res;
}

VI integr(const VI& a)
{
	int n = SZ(a);
	VI res(n + 1);
	RFOR(i, n, 1)
		res[i] = mult(a[i - 1], inv[i]);
	res[0] = 0;
	return res;
}

VI log(const VI& a, int n)
{
	assert(SZ(a) == n && a[0] == 1);
	VI res = integr(mult(deriv(a), inverse(a, n)));
	res.resize(n);
	return res;
}
