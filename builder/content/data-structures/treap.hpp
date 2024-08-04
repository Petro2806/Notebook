/**
 * Description: uncomment in split for explicit
 * key or in merge for implicit priority.
 * Minimum and reverse queries.
 */


mt19937 rng;

struct Node
{
	int l, r;	
	int x, y;
	int cnt, par;
	int rev, mn;
	
	Node(int value)
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
	vector<Node> t;
	
	int getCnt(int v)
	{
		if (v == -1) 
			return 0;
		return t[v].cnt;
	}
	int getMn(int v)
	{
		if (v == -1)	
			return INF;
		return t[v].mn;
	}
	int newNode(int val)
	{
		t.PB({val});
		return SZ(t) - 1;
	}
	void upd(int v)
	{
		if (v == -1) 
			return;
		// important!
		t[v].cnt = getCnt(t[v].l) + 
		getCnt(t[v].r) + 1;
		
		t[v].mn = min(t[v].x, min(getMn(t[v].l), getMn(t[v].r)));
	}
	void reverse(int v)
	{
		if (v == -1) 
			return;
		t[v].rev ^= 1;
	}
	void push(int v)
	{
		if (v == -1 || t[v].rev == 0) 
			return;
		reverse(t[v].l);
		reverse(t[v].r);
		swap(t[v].l, t[v].r);
		t[v].rev = 0;
	}
	PII split(int v, int cnt)
	{
		if (v == -1) 
			return {-1, -1};
		push(v);
		int left = getCnt(t[v].l);
		PII res;
		// elements a[v].x == val will be in right part
		// if (val <= a[v].x)
		if (cnt <= left)
		{
			if (t[v].l != -1) 
				t[t[v].l].par = -1;
			// res = split(a[v].l, val);
			res = split(t[v].l, cnt);
			t[v].l = res.S;
			if (res.S != -1) 
				t[res.S].par = v;
			res.S = v;
		}
		else
		{
			if (t[v].r != -1) 
				t[t[v].r].par = -1;
			// res = split(a[v].r, val);
			res = split(t[v].r, cnt - left - 1);
			t[v].r = res.F;
			if (res.F != -1) 
				t[res.F].par = v;
			res.F = v;
		}
		upd(v);
		return res;
	}
	int merge(int v, int u)
	{
		if (v == -1) return u;
		if (u == -1) return v;
		int res;
		// if ((int)(rng() % (getCnt(v) + getCnt(u))) < getCnt(v))
		if (t[v].y > t[u].y)
		{
			push(v);
			if (t[v].r != -1)
				t[t[v].r].par = -1;
			res = merge(t[v].r, u);
			t[v].r = res;
			if (res != -1) 
				t[res].par = v;
			res = v;
		}
		else
		{
			push(u);
			if(t[u].l != -1) 
				t[t[u].l].par = -1;
			res = merge(v, t[u].l);
			t[u].l = res;
			if (res != -1) 
				t[res].par = u;
			res = u;
		}
		upd(res);
		return res;
	}
	// returns index of element [0, n)
	int getIdx(int v, int from = -1)
	{
		if (v == -1) 
			return 0;
		int x = getIdx(t[v].par, v);
		push(v);
		if (from == -1 || t[v].r == from)
			x += getCnt(t[v].l) + (from != -1);
		return x;
	}
};
