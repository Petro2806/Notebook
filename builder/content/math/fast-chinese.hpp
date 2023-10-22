/**
 * Description: $x \% p_i = m_i, lcm(p) < 10^{18}, p < 10^9$. \\
 * no solution -> return -1
 * Time: O(nlog)
 */
LL FastChinese(VI m, VI p)
{
	assert(SZ(m) == SZ(p));
	LL aa = p[0];
	LL bb = m[0];
	FOR(i, 1, SZ(m))
	{
		int b = (m[i] - bb % p[i] + p[i]) % p[i];
		int a = aa % p[i];
		int c = p[i];
		
		int x, y;
		int d = gcd(a, c, x, y);
		if(b % d != 0)
			return -1;
		a /= d;
		b /= d;
		c /= d;
		b = b * (LL)x % c;
		
		bb = aa * b + bb;
		aa = aa * c;
	}
	return bb;
}
