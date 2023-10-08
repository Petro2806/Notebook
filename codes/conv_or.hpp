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
