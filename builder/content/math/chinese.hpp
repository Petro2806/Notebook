/**
 * Description: $result < 10^{18}, P < 10^9$.
 * Time: O(n^2) 
 */
LL Chinese(VI A, VI P)
{
	int n = SZ(A);
	FOR(i, 1, n)
	{
		LL a = 1;
		LL b = 0;
		RFOR(j, i, 0)
		{
			b = (b * P[j] + A[j]) % P[i];
			a = a * P[j] % P[i];
		}
		b = (A[i] - b + P[i]) % P[i];
		
		
		int c = P[i];
		int x, y;
		int d = gcd(a, c, x, y);
		
		if(b % d != 0)
			return -1;
		
		a /= d;
		b /= d;
		c /= d;
		
		b = b * x % c;
		A[i] = b;
		P[i] = c;
	}
	LL res = A[n - 1];
	RFOR(i, n - 1, 0)
	{
		res *= P[i];
		res += A[i];
	}
	return res;
}
