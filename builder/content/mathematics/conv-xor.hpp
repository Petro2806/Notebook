/**
 * Description: $c_k = \sum_{i \oplus j = k} a_i b_j$.
 */
void convXor(VI& a, int k)
{
	FOR(i, 0, k)
		FOR(j, 0, 1 << k)
			if((j & (1 << i)) == 0)
			{
				int u = a[j];
				int v = a[j + (1 << i)];
				a[j] = add(u, v);
				a[j + (1 << i)] = sub(u, v);
			}
}
VI multXor(VI a, VI b, int k)
{
	convXor(a, k);
	convXor(b, k);
	FOR(i, 0, 1 << k)
		a[i] = mult(a[i], b[i]);
	convXor(a, k);
	int d = inv(1 << k);
	FOR(i, 0, 1 << k)
		a[i] = mult(a[i], d);
	return a;
}	
