/**
 * Description: uncomment in split for explicit
 *  key or in merge for implicit priority.
 */

mt19937 rng;

struct Node
{
	int l, r;	
	int x;	
	int y;	
	int cnt;	
	int par;	
	int rev;	
	int mn;		
	
	void init(int value)
	{
		l = r = -1;
		x = value;
		y = rng();
		cnt = 1;
		par = -1;
		rev = 0;
		mn = value;
	}
};

struct Treap
{
	int n;
	vector<Node> a;
	void init(int _n)
	{
		n = _n;
		a.resize(n);
	}
	int sz = 0;
	
	int getCnt(int v)
	{
		if (v == -1) 
			return 0;
		return a[v].cnt;
	}
	int getMn(int v)
	{
		if (v == -1)	
			return INF;
		return a[v].mn;
	}
	int newNode(int val)
	{
		assert(sz < n);
		a[sz].init(val);
		return sz++;
	}
	void upd(int v)
	{
		if (v == -1) 
			return;
		a[v].cnt = getCnt(a[v].l) + 
		getCnt(a[v].r) + 1;
		
		a[v].mn = min(a[v].x, 
		min(getMn(a[v].l), getMn(a[v].r)));
	}
	void reverse(int v)
	{
		if (v == -1) 
			return;
		a[v].rev ^= 1;
	}
	void push(int v)
	{
		if (v == -1 || a[v].rev == 0) 
			return;
		reverse(a[v].l);
		reverse(a[v].r);
		swap(a[v].l, a[v].r);
		a[v].rev = 0;
	}
	PII split(int v, int cnt)
	{
		if (v == -1) 
			return {-1, -1};
		push(v);
		int left = getCnt(a[v].l);
		PII res;
		// if (val <= a[v].x)
		if (cnt <= left)
		{
			if (a[v].l != -1) 
				a[a[v].l].par = -1;
			res = split(a[v].l, cnt);
			a[v].l = res.second;
			if (res.second != -1) 
				a[res.second].par = v;
			res.second = v;
		}
		else
		{
			if (a[v].r != -1) 
				a[a[v].r].par = -1;
			// split(v, val)
			res = split(a[v].r, cnt - left - 1);
			a[v].r = res.first;
			if (res.first != -1) 
				a[res.first].par = v;
			res.first = v;
		}
		upd(v);
		return res;
	}
	int merge(int v, int u)
	{
		if (v == -1) return u;
		if (u == -1) return v;
		int res;
		// if (rng() % (getCnt(v) + getCnt(u)) < getCnt(v))
		if (a[v].y > a[u].y)
		{
			push(v);
			if (a[v].r != -1)
				a[a[v].r].par = -1;
			res = merge(a[v].r, u);
			a[v].r = res;
			if (res != -1) 
				a[res].par = v;
			res = v;
		}
		else
		{
			push(u);
			if (a[u].l != -1) 
				a[a[u].l].par = -1;
			res = merge(v, a[u].l);
			a[u].l = res;
			if (res != -1) 
				a[res].par = u;
			res = u;
		}
		upd(res);
		return res;
	}
	int getIdx(int v, int from = -1)
	{
		if (v == -1) 
			return 0;
		int x = getIdx(a[v].par, v);
		if (from == -1 || a[v].r == from)
			x += getCnt(a[v].l) + 1;
		push(v);
		return x;
	}
};
