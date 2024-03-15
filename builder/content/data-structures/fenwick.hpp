struct Fenwick
{
	int n;
	vector<LL> t;
	
	void init(int _n)
	{
		n = _n;
		t.clear();
		t.assign(n, 0);
	}
	
	void upd(int i, int x)
	{
		for (; i < n; i |= i + 1)
			t[i] += x;
	}
	
	LL query(int i)
	{
		LL ans = 0;
		for (; i >= 0; i = (i & (i + 1)) - 1)
			ans += t[i];
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
			if (j < n && sum + t[j] < x)
			{
				sum += t[j];
				i = j;
			}
			lg--;
		}
		return i + 1;
	}
};
