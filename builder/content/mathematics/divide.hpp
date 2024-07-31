/**
 * Description: Finds $Q(x)$ and $R(x)$ such that $A(x) = Q(x) B(x) + R(x)$ and $\deg R < \deg B$.
 * Time: O(n \log n)
 */
void removeLeadingZeros(VI& a)
{
	while(SZ(a) > 0 && a.back() == 0)
		a.pop_back();
}
pair<VI, VI> divide(VI a, VI b)
{
	removeLeadingZeros(a);
	removeLeadingZeros(b);
	int n = SZ(a), m = SZ(b);
	assert(m > 0);
	if(m > n)
		return {{}, a};
	reverse(ALL(a));
	reverse(ALL(b));
	VI q = b;
	q.resize(n - m + 1);
	q = mult(a, inverse(q, n - m + 1));
	q.resize(n - m + 1);
	reverse(ALL(a));
	reverse(ALL(b));
	reverse(ALL(q));
	VI r = mult(b, q);
	FOR(i, 0, n)
		r[i] = sub(a[i], r[i]);
	removeLeadingZeros(r);
	return {q, r};
}
