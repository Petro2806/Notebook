/**
 * Description: Finds the smallest $x \ge 0$ such that $(ax + b) \mod m \ge c$. Returns $-1$, if the solution does not exist.
 * Time: O(\log m).
 */
int modInequality(LL m, LL a, LL b, LL c)
{
	a %= m;
	b %= m;
	if (b >= c)
		return 0;
	if (a == 0)
		return -1;
	if (c + a < m)
		return (c - b + a - 1) / a;
	int k = modInequality(a, m, c - b - 1, c + a - m);
	if (k == -1)
		return -1;
	return (k * m + c - b + a - 1) / a;
}
