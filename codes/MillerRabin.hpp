mt19937 rng;

bool MillerRabin(LL a, int k = 4)
{
	if (a == 2 || a == 3)
		return true;
	LL d = a - 1;
	int s = __builtin_ctzll(d);
	d >>= s;
	
	FOR (it, 0, k)
	{
		LL b = rng() % (a - 3) + 2;
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
