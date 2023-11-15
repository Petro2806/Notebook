/**
 * Description: $c_{i \lor j} += a_i * b_j$.
 */
void convOr(VI& a, int k, bool inverse)
{
	FOR(i, 0, k)
		FOR(j, 0, 1 << k)
			if((j & (1 << i)) == 0)
			{
				if(inverse)
					a[j + (1 << i)] -= a[j];
				else
					a[j + (1 << i)] += a[j];				
			}
}
VI multOr(VI a, VI b, int k)
{
	convOr(a, k, false);
	convOr(b, k, false);
	FOR(i, 0, 1 << k)
		a[i] = mult(a[i], b[i]);
	convOr(a, k, true);
	return a;
}
