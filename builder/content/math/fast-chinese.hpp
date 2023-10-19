/**
 * Description: $x \% P_i = A_i, lcm(P) < 10^{18}, P < 10^9$. \\
 * no solution -> return -1
 */
LL FastChinese(VI A, VI P)
{
	assert(SZ(A) == SZ(P));
	LL aa = P[0];
	LL bb = A[0];
	
	FOR(i, 1, SZ(A))
	{
		int b = (A[i] - bb % P[i] + P[i]) % P[i];
		int a = aa % P[i];
		int c = P[i];
		
		int x, y;
		int d = gcd(a, c, x, y);
		
		if(b % d != 0)
			return -1;
		
		a /= d;
		b /= d;
		c /= d;
		
		b = b * x % c;

		
		bb = aa * b + bb;
		aa = aa * c;
	}
	return bb;
}
