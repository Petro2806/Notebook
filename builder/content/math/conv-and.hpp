/**
 * Description: $c_{i \land j} += a_i * b_j$.
 */
void convAnd(VI& a, int k, bool inverse)
{
	FOR(i, 0, k)
		FOR(j, 0, 1 << k)
			if((j & (1 << i)) == 0)
			{
				if(inverse)
					updSub(a[j], a[j + (1 << i)]);
				else
					updAdd(a[j], a[j + (1 << i)]);				
			}
}
VI multAnd(VI a, VI b, int k)
{
	convAnd(a, k, false);
	convAnd(b, k, false);
	FOR(i, 0, 1 << k)
		a[i] = mult(a[i], b[i]);
	convAnd(a, k, true);
	return a;
}
