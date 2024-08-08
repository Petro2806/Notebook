/**
 * Description: $\exp(A(x))$ modulo $x^n$.
 * Time: O(n \log n)
 */
VI exp(const VI& a, int n)
{
	assert(SZ(a) == n && a[0] == 0);
	VI q = {1};
	for (int k = 2; k <= 2 * n; k *= 2)
	{
		q.resize(k);
		VI lnQ = log(q, k);
		FOR(i, 0, k)
		{
			if(i < n)
				lnQ[i] = sub(a[i], lnQ[i]);
			else
				lnQ[i] = sub(0, lnQ[i]);
		}
		lnQ[0] = add(lnQ[0], 1);
		q = mult(q, lnQ);
	}
	q.resize(n);
	return q;
}
