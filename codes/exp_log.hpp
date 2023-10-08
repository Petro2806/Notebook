VI deriv(const VI& a, int k)
{
	VI res(k);
	FOR(i, 0, k)
		if(i + 1 < SZ(a))
			res[i] = mult(a[i + 1], i + 1);
	return res;
}

VI integr(const VI& a, int k)
{
	VI res(k);
	RFOR(i, k, 1)
		res[i] = mult(a[i - 1], inv[i]);
	res[0] = 0;
	return res;
}

VI log(const VI& a, int k)
{
	assert(a[0] == 1);	
	return integr(mult(deriv(a, k), inverse(a, k)), k);	
}

VI exp(VI a, int k)
{
	assert(a[0] == 0);
	
	VI Qk = {1};
	int pw = 1;
	while(pw <= k)
	{
		pw *= 2;
		
		Qk.resize(pw);
		VI lnQ = log(Qk, pw);
		
		FOR(i, 0, SZ(lnQ))
		{
			if(i < SZ(a))
				lnQ[i] = sub(a[i], lnQ[i]);
			else
				lnQ[i] = sub(0, lnQ[i]);
		}
		updAdd(lnQ[0], 1);		
		
		Qk = mult(Qk, lnQ);
	}
	Qk.resize(k);
	return Qk;
}

