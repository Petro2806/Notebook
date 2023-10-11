void convXor(VI& a, int k)
{
	FOR(i, 0, k)
		FOR(j, 0, 1 << k)
			if((j & (1 << i)) == 0)
			{
				int u = a[j];
				int v = a[j + (1 << i)];
				a[j] = u + v;
				a[j + (1 << i)] = u - v;
			}
}
