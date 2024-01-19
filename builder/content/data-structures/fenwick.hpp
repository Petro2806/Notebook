struct Fenwick
{
	int n;
	vector<LL> v;
	
	void init(int _n)
	{
		n = _n;
		v.clear();
		v.assign(n, 0);
	}
	
	void upd(int i, int x)
	{
		for (; i < n; i |= (i + 1))
			v[i] += x;
	}
	
	LL query(int i)
	{
		LL ans = 0;
		for (; i >= 0; i = (i & (i + 1)) - 1)
			ans += v[i];
		return ans;
	}
	
	// returns n if sum(a) < x
	int lowerBound(LL x)
	{
		LL sum = 0;
		int i = -1;
		int lg = 31 - __builtin_clz(n);
		while (lg >= 0)
		{
			int j = i + (1 << lg);
			if (j < n && sum + v[j] < x)
			{
				sum += v[j];
				i = j;
			}
			lg--;
		}
		return i + 1;
	}
};
