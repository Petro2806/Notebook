/**
 * Description: Code finds a specific structure of the answer.
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
		auto [d, x, y] = gcdExt(a, c);
		
		if(b % d != 0)
			return -1;
		a /= d;
		b /= d;
		c /= d;
		
		b = (b * x % c + c) % c;
		m[i] = b;
		p[i] = c;
	}
	//specific structure where gcd(pi, pj) = 1
	LL res = m[n - 1];
	RFOR(i, n - 1, 0)
		res = res * p[i] + m[i];
	return res;
}
