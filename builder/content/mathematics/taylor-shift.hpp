/**
 * Description: Finds the polynomial $A(x + c)$.
 * Time: O(n \log n)
 */
VI taylorShift(VI a, int c)
{
	int n = SZ(a);
	if (n == 0)
		return {};
	VI b(n);
	int pw = 1;
	FOR(i, 0, n)
	{
		// fact[i] = i!
		// invFact[i] = 1 / i!
		a[i] = mult(a[i], fact[i]);
		b[i] = mult(pw, invFact[i]);
		pw = mult(pw, c);
	}
	reverse(ALL(b));
	VI res = mult(a, b);
	res = {res.begin() + n - 1, res.end()};
	FOR(i, 0, n)
		res[i] = mult(res[i], invFact[i]);
	return res;
}
