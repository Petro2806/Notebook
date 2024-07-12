/**
 * Description: Finds $\min \{(ax + b) \mod m \ | \ 0 \le x < n\}$.
 * Time: O(\log m).
 */
int minModLinear(LL n, LL m, LL a, LL b)
{
	LL res = m;
	while (n > 0)
	{
		a %= m;
		b = (b % m + m) % m;
		res = min(res, b);
		n = (a * (n - 1) + b) / m;
		b -= m * n;
		swap(a, m);
	}
	return res;
}
