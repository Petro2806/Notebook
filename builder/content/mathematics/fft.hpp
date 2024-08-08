/**
 * Description: Number-theoretic transform. If you need complex-valued FFT, use the commented out code.
 * Time: O(n \log n)
 */
const int LEN = 1 << 23;
const int GEN = 31;

/*typedef complex<db> com;
com pw[LEN];
void init()
{
	db phi = (db)2 * PI / LEN;
	FOR(i, 0, LEN)
		pw[i] = com(cos(phi * i), sin(phi * i));	
}*/

void fft(VI& a, bool inverse)
{
	const int IGEN = binpow(GEN, mod - 2);
	int lg = __builtin_ctz(SZ(a));
	FOR(i, 0, SZ(a))
	{
		int k = 0;
		FOR(j, 0, lg)
			k |= ((i >> j) & 1) << (lg - j - 1);
		if(i < k)
			swap(a[i], a[k]);
	}
	for(int len = 2; len <= SZ(a); len *= 2)
	{
		// int diff = inv ? LEN - LEN / len : LEN / len;
		int ml = binpow(inverse ? IGEN : GEN, LEN / len);
		for(int i = 0; i < SZ(a); i += len)
		{
			// int pos = 0;
			int pw = 1;
			FOR(j, 0, len / 2)
			{
				int u = a[i + j];
				int v = mult(a[i + j + len / 2], pw); // * pw[pos]
				a[i + j] = add(u, v);
				a[i + j + len / 2] = sub(u, v);
				// pos = (pos + diff) % LEN;
				pw = mult(pw, ml);
			}
		}
	}
	if (inverse)
	{
		int m = binpow(SZ(a), mod - 2);
		FOR(i, 0, SZ(a))
			// a[i] /= SZ(a);
			a[i] = mult(a[i], m); 
	}
}

VI mult(VI a, VI b)
{
	int n = SZ(a), m = SZ(b);
	if (n == 0 || m == 0)
		return {};
	int sz = 1, szRes = n + m - 1;
	while(sz < szRes)
		sz *= 2;
	a.resize(sz);
	b.resize(sz);
	
	fft(a, false);
	fft(b, false);
	
	FOR(i, 0, sz)
		a[i] = mult(a[i], b[i]);
	
	fft(a, true);
	a.resize(szRes);
	return a;
}

