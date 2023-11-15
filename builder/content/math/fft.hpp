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
	return (LL)a * b % mod;
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

void fft(VI& a, bool inv)
{
	int lg = 0;
	while((1 << lg) < SZ(a)) lg++;
	FOR(i, 0, SZ(a))
	{
		int x = 0;
		FOR(j, 0, lg)
			x |= ((i >> j) & 1) << (lg - j - 1);
		if(i < x)
			swap(a[i], a[x]);
	}
	for(int len = 2; len <= SZ(a); len *= 2)
	{
		int ml = binpow(inv ? IGEN : GEN, LEN / len);
		for(int i = 0; i < SZ(a); i += len)
		{
			int pw = 1;
			FOR(j, 0, len / 2)
			{
				int v = a[i + j];
				int u = mult(a[i + j + len / 2], pw);
				
				a[i + j] = add(v, u);
				a[i + j + len / 2] = sub(v, u);
			
				pw = mult(pw, ml);
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
	
	fft(a, 0);
	fft(b, 0);
	
	FOR(i, 0, SZ(a))
		a[i] = mult(a[i], b[i]);
	
	fft(a, 1);
	a.resize(sum);
	return a;
}


