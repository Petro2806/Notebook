/**
 * Description: Calculate $a^{-1} \% x^k$.
 */
VI inverse(const VI& a, int k)
{
	assert(SZ(a) == k && a[0] != 0);
	if(k == 1)
		return {binpow(a[0], mod - 2)};  
	
	VI ra = a;
	FOR(i, 0, SZ(ra))
		if(i & 1)
			ra[i] = sub(0, ra[i]);    
	
	int nk = (k + 1) / 2;
	VI t = mult(a, ra);
	t.resize(k);
	
	FOR(i, 0, nk)
		t[i] = t[2 * i];
  
	t.resize(nk);
	t = inverse(t, nk);
	t.resize(k);
  
	RFOR(i, nk, 1)
	{
		t[2 * i] = t[i];
		t[i] = 0;
	}
	
	VI res = mult(ra, t);
	res.resize(k);
	return res;
}
