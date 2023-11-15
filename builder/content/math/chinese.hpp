/**
 * Description: Calculate result \% mod ($modulo \ne p_i$).\\
 * Not tested on good tests
 * Time: O(n^2) 
 */
LL chinese(VI m, VI p)
{
	int n = SZ(m);
	FOR(i, 1, n)
	{
		LL a = 1;
		LL b = 0;
		RFOR(j, i, 0)
		{
			b = (b * p[j] + m[j]) % p[i];
			a = a * p[j] % p[i];
		}
		b = (m[i] - b + p[i]) % p[i];
		
		int c = p[i];
		int x, y;
		int d = gcd(a, c, x, y);
		
		if(b % d != 0)
			return -1;
		a /= d;
		b /= d;
		c /= d;
		
		b = b * x % c;
		m[i] = b;
		p[i] = c;
	}
	LL res = m[n - 1] % mod;
	RFOR(i, n - 1, 0)
	{
		res = mult(res, p[i]);
		res = add(res, m[i]);
	}
	return res;
}
