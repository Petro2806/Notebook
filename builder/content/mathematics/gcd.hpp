/**
 * Description: $ax + by = d$, $\gcd(a, b) = |d| \rightarrow (d, x, y)$.\\
 * Minimizes $|x| + |y|$. And minimizes $|x - y|$ for $a > 0$, $b > 0$.
 */
tuple<LL, LL, LL> gcdExt(LL a, LL b)
{
	LL x1 = 1, y1 = 0;
	LL x2 = 0, y2 = 1;
	while (b)
	{
		LL k = a / b;
		x1 -= k * x2;
		y1 -= k * y2;
		a %= b;
		swap(a, b);
		swap(x1, x2);
		swap(y1, y2);
	}
	return {a, x1, y1};
}
