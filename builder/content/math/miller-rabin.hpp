/**
 * Description: to speed up change candidates to at least 4 random values rng() % (a - 3) + 2;
 * 
 * use \_\_int128 in mult
 * 
 **/

VI candidates = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 47};
bool millerRabin(LL n)
{
	if (n == 1)
		return false;
	if (n == 2 || n == 3)
		return true;
	LL d = n - 1;
	int s = __builtin_ctzll(d);
	d >>= s;
	
	for (LL b : candidates)
	{
		if (b >= n)
			break;
		b = binpow(b, d, n);
		if (b == 1)
			continue;
		bool ok = false;
		FOR (i, 0, s)
		{
			if (b + 1 == n)
			{
				ok = true;
				break;
			}
			b = mult(b, b, n);
		}
		if (!ok) 
			return false;
	}
	return true;
}
