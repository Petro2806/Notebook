const int mod = 998244353;

int add(int a, int b)
{
	return a + b < mod ? a + b : a + b - mod;
}

void updAdd(int& a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

int sub(int a, int b)
{
	return a - b >= 0 ? a - b : a - b + mod;
}

void updSub(int& a, int b)
{
	a -= b;
	if (a < 0)
		a += mod;
}

int mult(int a, int b)
{
	return (LL)a * b % mod;
}

int binpow(int a, LL n)
{
	int res = 1;
	while (n)
	{
		if (n & 1)
			res = mult(res, a);
		a = mult(a, a);
		n /= 2;
	}
	return res;
}

int inv[N], fact[N], ifact[N];

void init()
{
	inv[1] = 1;
	FOR(i, 2, N)
	{
		inv[i] = mult(mod - mod / i, inv[mod % i]);
	}
	fact[0] = ifact[0] = 1;
	FOR(i, 1, N)
	{
		fact[i] = mult(fact[i - 1], i);
		ifact[i] = mult(ifact[i - 1], inv[i]);
	}
}

int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return mult(fact[n], mult(ifact[n - k], ifact[k]));
}
