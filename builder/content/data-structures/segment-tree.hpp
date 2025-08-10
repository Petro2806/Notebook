int ZERO = 0;

template<typename T>
struct SegmentTree
{
	int n;
	vector<T> t;
	
	SegmentTree(int _n)
	{
		n = 1;
		while (n < _n) n *= 2;
		t.assign(2 * n - 1, ZERO);
	}
	
	void build(int v, int tl, int tr, const vector<T>& a)
	{
		if (tl + 1 == tr)
		{
			if (tl < SZ(a))
				t[v] = a[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(2 * v + 1, tl, tm, a);
		build(2 * v + 2, tm, tr, a);
		t[v] = combine(t[2 * v + 1], t[2 * v + 2]);
	}
	
	void build(const vector<T>& a)
	{
		build(0, 0, n, a);
	}
	
	void push(int v, int tl, int tr)
	{
		if (tl + 1 == tr)
			return;
		
	}
	
	// important
	T combine(const T& n1, const T& n2)
	{
		return n1 + n2;
	}
	
	void upd(int v, int tl, int tr, int l, int r, T x)
	{
		push(v, tl, tr);
		if (l <= tl && tr <= r)
		{
			//update this node t[v]
			t[v] = x;
			return;
		}
		if (r <= tl || tr <= l)
			return;
		int tm = (tl + tr) / 2;
		upd(2 * v + 1, tl, tm, l, r, x);
		upd(2 * v + 2, tm, tr, l, r, x);
		t[v] = combine(t[2 * v + 1], t[2 * v + 2]);
	}
	
	void upd(int l, int r, T x)
	{
		upd(0, 0, n, l, r, x);
	}
	
	T query(int v, int tl, int tr, int l, int r)
	{
		push(v, tl, tr);
		if (l <= tl && tr <= r)
			return t[v];
		if (r <= tl || tr <= l)
			return ZERO;
		int tm = (tl + tr) / 2;
		return combine(query(2 * v + 1, tl, tm, l, r), 
			query(2 * v + 2, tm, tr, l, r));
	}
	
	T query(int l, int r)
	{
		return query(0, 0, n, l, r);
	}
};
