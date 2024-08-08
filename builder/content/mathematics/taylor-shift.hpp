/**
 * Description: Finds the coefficients of polynomial $A(x + c)$.
 * Time: O(n \log n)
 */
VI taylorShift(VI a, int c)
{
	int n = SZ(a);
	VI b(n);
	int pw = 1;
	FOR(i, 0, n)
	{
		a[i] = mult(a[i], fact[i]);
		b[i] = mult(pw, ifact[i]);
		pw = mult(pw, c);
	}
	reverse(ALL(b));
	VI res = mult(a, b);
	res = {res.begin() + n - 1, res.end()};
	FOR(i, 0, n)
		res[i] = mult(res[i], ifact[i]);
	return res;
}
