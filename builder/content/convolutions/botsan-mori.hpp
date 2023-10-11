// c - coefficients c[1], .., c[k] but 0-index
// a - initial values a[0], a[1], ..., a[k-1]
int botsanMori(VI c, VI a, LL n) {
	int k = SZ(c);
	assert(SZ(a) == k);
	VI q(k + 1);
	q[0] = 1;
	FOR(i, 0, k) 
		q[i + 1] = sub(0, c[i]);
	
	VI p = mult(a, q);
	p.resize(k);
	while (n) {
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
	return mult(p[0], binPow(q[0], mod - 2));
}
