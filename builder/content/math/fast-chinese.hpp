/**
 * Description: $x \% p_i = m_i, \text{lcm}(p) \le 10^{18}, p \le 10^9$
 * $\rightarrow x$ or -1. \\
 * Not tested on good tests
 * Time: O(n\log(\text{lcm}(p_i)))
 */
LL fastChinese(VI m, VI p)
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
