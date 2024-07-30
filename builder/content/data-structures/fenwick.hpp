struct Fenwick
{
	int n;
	vector<LL> t;
	
	Fenwick(int _n = 0)
	{
		n = _n;
		t.clear();
		t.assign(n, 0);
	}
	void upd(int i, LL x)
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
};
