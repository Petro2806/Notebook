/**
 * Description: computes the $n$-th term of a given linearly
 * recurrent sequence $a_i = \sum_{j=1}^d c_j a_{i - j}$.
 * The problem reduces to determining $[x^n] P(x)/Q(x)$.
 * \Large{$\frac{P(x)}{Q(x)}=\frac{P(x)Q(-x)}{Q(x)Q(-x)}=\frac{U_\text{e}(x^2)}{V(x^2)} + x \frac{U_\text{o}(x^2)}{V(x^2)}$.
 * \begin{displaymath}
\left[x^n\right]\frac{P(x)}{Q(x)} = \left\{ \begin{array}{ll}
\left[x^\frac{n}{2}\right]\frac{U_\text{e}(x)}{V(x)}, & \textrm{if $n$ is even,} \\
\left[x^\frac{n-1}{2}\right]\frac{U_\text{o}(x)}{V(x)}, & \textrm{else.}
\end{array} \right.
\end{displaymath}}
 * Time: $O(d \log d \log n)$.
 */
int bostanMori(const VI& c, VI a, LL n) {
	int k = SZ(c);
	assert(SZ(a) == k);
	int m = 1 << (33 - __builtin_clz(k));
	assert(m >= 2 * k + 1);
	VI q(k + 1);
	q[0] = 1;
	FOR(i, 0, k) 
		q[i + 1] = sub(0, c[i]);
	VI p = mult(a, q);
	p.resize(m);
	FOR(i, k, m)
		p[i] = 0;
	q.resize(m);
	VI qMinus;
	while (n)
	{
		qMinus = q;
		for (int i = 1; i <= k; i += 2)
			qMinus[i] = sub(0, qMinus[i]);
		fft(qMinus, false);
		fft(p, false);
		fft(q, false);
		FOR(i, 0, m)
			p[i] = mult(p[i], qMinus[i]);
		fft(p, true);
		FOR(i, 0, m)
			q[i] = mult(q[i], qMinus[i]);
		fft(q, true);
		FOR(i, 0, k)
			p[i] = p[2 * i + (n & 1)];
		FOR(i, k, m)
			p[i] = 0;
		FOR(i, 0, k + 1) 
			q[i] = q[2 * i];
		FOR(i, k + 1, m)
			q[i] = 0;
		n >>= 1;
	}
	return mult(p[0], binpow(q[0], mod - 2));
}
