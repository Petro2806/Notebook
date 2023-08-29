VI inverse(VI a, int k)
{
	a.resize(k);
	if(k == 1)
		return {binpow(a[0], mod - 2)};	
	
	VI ra = a;
	FOR(i, 0, SZ(ra))
		if(i & 1)
			ra[i] = sub(0, ra[i]);		
	
	int nk = (k + 1) / 2;
	VI t = mult(a, ra);	
	FOR(i, 0, nk)
		if(2 * i < SZ(t))
			t[i] = t[2 * i];

	t = inverse(t, nk);
	
	t.resize(k);
	RFOR(i, nk, 1)
		if(2 * i < SZ(t))
		{
			t[2 * i] = t[i];
			t[i] = 0;
		}
		
	return mult(ra, t);
}
