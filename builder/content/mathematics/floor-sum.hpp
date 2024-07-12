/**
 * Description: Computes $\sum_{i=0}^{n-1} \left\lfloor \frac{a \cdot i + b}{m} \right\rfloor$.
 * Time: O(\log m).
 */
LL floorSum(LL n, LL m, LL a, LL b)
{
	LL ans = 0;
	while (true)
	{
		ans += (a / m) * n * (n - 1) / 2 + (b / m) * n;
		a %= m;
		b %= m;
		if (a == 0)
			return ans;
		LL k = (a * (n - 1) + b) / m;
		b = a * n - m * k + b;
		n = k;
		swap(a, m);
	}
}
