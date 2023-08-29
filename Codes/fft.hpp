const int mod = 998244353;

int add(int a, int b)
{
	return (a + b < mod) ? (a + b) : (a + b - mod);
}
int sub(int a, int b)
{
	return (a - b < 0) ? (a - b + mod) : (a - b);
}
int mult(int a, int b)
{
	return a * (LL) b % mod;
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

const int LEN = 1 << 20;
const int GEN = 646;
int PW[LEN];

void init()
{
	PW[0] = 1;
	FOR(i, 1, LEN)
		PW[i] = mult(PW[i - 1], GEN);
}
void fft(VI& a, bool invert)
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
		int diff = LEN / len;
		if(invert) diff = LEN - diff;
		for(int i = 0; i < SZ(a); i += len)
		{
			int pos = 0;
			FOR(j, 0, len / 2)
			{
				int v = a[i + j];
				int u = mult(a[i + j + len / 2], PW[pos]);
				
				a[i + j] = add(v, u);
				a[i + j + len / 2] = sub(v, u);
			
				pos += diff;
				if(pos >= LEN)
					pos -= LEN;
			}
		}
	}
	if(invert)
	{
		int m = binpow(SZ(a), mod - 2);
		FOR(i, 0, SZ(a))
			a[i] = mult(a[i], m);
	}
}

void mult(VI& a, VI b)
{
	int sz = 0;
	while((1 << sz) < SZ(a) + SZ(b) - 1) sz++;
	a.resize(1 << sz);
	b.resize(1 << sz);
	
	fft(a, 0);
	fft(b, 0);
	
	FOR(i, 0, SZ(a))
		a[i] = mult(a[i], b[i]);
	
	fft(a, 1);
}


