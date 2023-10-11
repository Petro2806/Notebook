void convAnd(VI& a, int k, bool inverse)
{
	FOR(i, 0, k)
		FOR(j, 0, 1 << k)
			if((j & (1 << i)) == 0)
			{
				if(inverse)
					a[j] -= a[j + (1 << i)];
				else
					a[j] += a[j + (1 << i)];				
			}
}
