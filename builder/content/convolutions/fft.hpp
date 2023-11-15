/**
 * Description: $GEN^{\frac{LEN}{2}} = mod - 1$.
 * Comments for complex.\\
 * $mod = 9223372036737335297, GEN = 3^{\frac{mod - 1}{LEN}}, LEN \le 2^{24}$.
 */
const int mod = 998244353;

int add(int a, int b)
{
	return a + b < mod ? a + b : a + b - mod;
}
int sub(int a, int b)
{
	return a - b >= 0 ? a - b : a - b + mod;
}
int mult(int a, int b)
{
	return (LL) a * b % mod;
}
int binpow(int a, int n)
{
	int res = 1;
	while(n)
	{
		if(n & 1)
			res = mult(res, a);
		a = mult(a, a);
		n /= 2;
	}
	return res;
}

const int LEN = 1 << 23;
const int GEN = 31;
const int IGEN = binpow(GEN, mod - 2);

//void init()
//{
//	db phi = (db)2 * acos(-1.) / LEN;
//	FOR(i, 0, LEN)
//		pw[i] = com(cos(phi * i), sin(phi * i));	
//}

void fft(VI& a, bool inv)
{
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
		int ml = binpow(inv ? IGEN : GEN, LEN / len);
		//int diff = inv ? LEN - LEN / len : LEN / len;
		for(int i = 0; i < SZ(a); i += len)
		{
			int pw = 1;
			//int pos = 0;
			FOR(j, 0, len / 2)
			{
				int v = a[i + j];
				int u = mult(a[i + j + len / 2], pw);
				// * pw[pos]
				
				a[i + j] = add(v, u);
				a[i + j + len / 2] = sub(v, u);
			
				pw = mult(pw, ml);
				//pos = (pos + diff) % LEN;
			}
		}
	}
	if(inv)
	{
		int m = binpow(SZ(a), mod - 2);
		FOR(i, 0, SZ(a))
			a[i] = mult(a[i], m);
	}
}

VI mult(VI a, VI b)
{
	int sz = 0;
	int sum = SZ(a) + SZ(b) - 1;
	while((1 << sz) < sum) sz++;
	a.resize(1 << sz);
	b.resize(1 << sz);
	
	fft(a, false);
	fft(b, false);
	
	FOR(i, 0, SZ(a))
		a[i] = mult(a[i], b[i]);
	
	fft(a, true);
	a.resize(sum);
	return a;
}


