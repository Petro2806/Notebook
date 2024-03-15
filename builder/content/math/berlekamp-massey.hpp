/**
 * Description: Finds a sequence of $d$ integers $c_1, \dots, c_d$
 * of the minimum length $d$ such that
 * $a_i = \sum_{j=1}^d c_j a_{i - j}$.
 */
VI berlekampMassey(const VI& a)
{
	VI c = {1}, bp = {1};
	int l = 0, b = 1, x = 1;
	FOR(j, 0, SZ(a))
	{
		assert(SZ(c) == l + 1);
		int d = a[j];
		FOR(i, 1, l + 1)
			updAdd(d, mult(c[i], a[j - i]));
		if (d == 0)
		{
			x++;
			continue;
		}
		VI t = c;
		int coef = mult(d, binpow(b, mod - 2));
		if (SZ(bp) + x > SZ(c))
			c.resize(SZ(bp) + x);
		FOR(i, 0, SZ(bp))
			updSub(c[i + x], mult(coef, bp[i]));
		if (2 * l > j)
		{
			x++;
			continue;
		}
		l = j + 1 - l;
		bp = t;
		b = d;
		x = 1;
	}
	c.erase(c.begin());
	for (int& ci : c)
		ci = mult(ci, mod - 1);
	return c;
}
