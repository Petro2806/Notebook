/**
 * Description: $ax + by = d, gcd(a, b) = \|d\| \rightarrow (d, x, y)$.\\
 * Minimizes $\|x\| + \|y\|$. And minimizes $\|x - y\|$ for $a > 0$, $b > 0$.
 */
tuple<int, int, int> gcdExt(int a, int b)
{
	int x1 = 1, y1 = 0;
	int x2 = 0, y2 = 1;
	while (b)
	{
		int k = a / b;
		x -= k * x2;
		y -= k * y2;
		a %= b;
		swap(a, b);
		swap(x, x2);
		swap(y, y2);
	}
	return {a, x1, y1};
}
