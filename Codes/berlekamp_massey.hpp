vector<int> berlekampMassey(const vector<int>& a)
{
	vector<int> c = {1}, bp = {1};
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
		vector t = c;
		int coef = mult(d, binPow(b, mod - 2));
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
	c = vector(c.begin() + 1, c.end());
	for (int& ci : c)
		ci = mult(ci, mod - 1);
	return c;
}
