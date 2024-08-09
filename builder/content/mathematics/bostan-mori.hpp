/**
 * Description: Computes the $n$-th term of a given linearly
 * recurrent sequence $a_i = \sum_{j=1}^d c_j a_{i - j}$.
 * The first $d$ terms $a_0, a_1, \dots, a_{d - 1}$ are given.
 * 
 * The problem reduces to determining $[x^n] P(x)/Q(x)$.
 * 
 * $\dfrac{P(x)}{Q(x)}=\dfrac{P(x)Q(-x)}{Q(x)Q(-x)}=\dfrac{U_\text{e}(x^2)}{V(x^2)} + x \cdot \dfrac{U_\text{o}(x^2)}{V(x^2)}$.
 * Time: $O(d \log d \log n)$.
 */
int bostanMori(const VI& c, VI a, LL n)
{
	int k = SZ(c);
	assert(SZ(a) == k);
	VI q(k + 1);
	q[0] = 1;
	FOR(i, 0, k) 
		q[i + 1] = sub(0, c[i]);
	VI p = mult(a, q);
	p.resize(k);
	while (n)
	{
		VI qMinus = q;
		for (int i = 1; i <= k; i += 2)
			qMinus[i] = sub(0, qMinus[i]);
		VI newP = mult(p, qMinus);
		VI newQ = mult(q, qMinus);
		FOR(i, 0, k) 
			p[i] = newP[2 * i + (n & 1)];
		FOR(i, 0, k + 1) 
			q[i] = newQ[2 * i];
		n >>= 1;
	}
	return mult(p[0], binpow(q[0], mod - 2));
}
