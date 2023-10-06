// to speed up change candidates to at least 4 random values rng() % (a - 3) + 2;
// use __int128 in mult

VI candidates = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 47};
bool MillerRabin(LL a)
{
	if (a == 1)
		return false;
	if (a == 2 || a == 3)
		return true;
	LL d = a - 1;
	int s = __builtin_ctzll(d);
	d >>= s;
	
	for (LL b : candidates)
	{
		if (b >= a)
			break;
		b = binpow(b, d, a);
		if (b == 1)
			continue;
		bool ok = false;
		FOR (i, 0, s)
		{
			if (b + 1 == a)
			{
				ok = true;
				break;
			}
			b = mult(b, b, a);
		}
		if (!ok) 
			return false;
	}
	return true;
}
