/**
 * Description: $c_k = \sum_{i \text{ OR } j = k} a_i b_j$.
 */
void convOr(VI& a, int k, bool inverse)
{
	FOR(i, 0, k)
		FOR(j, 0, 1 << k)
			if((j & (1 << i)) == 0)
			{
				if(inverse)
					updSub(a[j + (1 << i)], a[j]);
				else
					updAdd(a[j + (1 << i)], a[j]);				
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
