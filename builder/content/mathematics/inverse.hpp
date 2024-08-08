/**
 * Description: $\frac{1}{A(x)}$ modulo $x^n$.
 * Time: O(n \log n)
 */
VI inverse(const VI& a, int n)
{
	assert(SZ(a) == n && a[0] != 0);
	if(n == 1)
		return {binpow(a[0], mod - 2)};
	
	VI ra = a;
	FOR(i, 0, SZ(ra))
		if(i & 1)
			ra[i] = sub(0, ra[i]);
	
	int nn = (n + 1) / 2;
	VI t = mult(a, ra);
	t.resize(n);
	
	FOR(i, 0, nn)
		t[i] = t[2 * i];
  
	t.resize(nn);
	t = inverse(t, nn);
	t.resize(n);
  
	RFOR(i, nn, 1)
	{
		t[2 * i] = t[i];
		t[i] = 0;
	}
	
	VI res = mult(ra, t);
	res.resize(n);
	return res;
}
