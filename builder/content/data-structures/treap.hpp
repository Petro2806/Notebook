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
	Node A[MAX];
	int sz = 0;
	
	int getCnt(int v)
	{
		if (v == -1) 
			return 0;
		return A[v].cnt;
	}
	int getMn(int v)
	{
		if (v == -1)	
			return INF;
		return A[v].mn;
	}
	int newNode(int val)
	{
		A[sz].init(val);
		return sz++;
	}
	void upd(int v)
	{
		if (v == -1) 
			return;
		A[v].cnt = getCnt(A[v].l) + getCnt(A[v].r) + 1;
		A[v].mn = min(A[v].x, min(getMn(A[v].l), getMn(A[v].r)));
	}
	void reverse(int v)
	{
		if (v == -1) 
			return;
		A[v].rev ^= 1;
	}
	void push(int v)
	{
		if (v == -1 || A[v].rev == 0) 
			return;
		reverse(A[v].l);
		reverse(A[v].r);
		swap(A[v].l, A[v].r);
		A[v].rev = 0;
	}
	PII split(int v, int cnt)
	{
		if (v == -1) 
			return {-1, -1};
		push(v);
		int left = getCnt(A[v].l);
		PII res;
		// if (val <= A[v].x)
		if (cnt <= left)
		{
			if (A[v].l != -1) 
				A[A[v].l].par = -1;
			res = split(A[v].l, cnt);
			A[v].l = res.second;
			if (res.second != -1) 
				A[res.second].par = v;
			res.second = v;
		}
		else
		{
			if (A[v].r != -1) 
				A[A[v].r].par = -1;
			// split(v, val)
			res = split(A[v].r, cnt - left - 1);
			A[v].r = res.first;
			if (res.first != -1) 
				A[res.first].par = v;
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
		if (A[v].y > A[u].y)
		{
			push(v);
			if (A[v].r != -1)
				A[A[v].r].par = -1;
			res = merge(A[v].r, u);
			A[v].r = res;
			if (res != -1) 
				A[res].par = v;
			res = v;
		}
		else
		{
			push(u);
			if (A[u].l != -1) 
				A[A[u].l].par = -1;
			res = merge(v, A[u].l);
			A[u].l = res;
			if (res != -1) 
				A[res].par = u;
			res = u;
		}
		upd(res);
		return res;
	}
	int getIdx(int v, int from = -1)
	{
		if (v == -1) 
			return 0;
		int x = getIdx(A[v].par, v);
		if (from == -1 || A[v].r == from)
			x += getCnt(A[v].l) + 1;
		push(v);
		return x;
	}
};
