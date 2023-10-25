const int AL = 26;

struct Node
{
	int p;
	int c;
	int g[AL];
	int nxt[AL];
	int link;
	
	void init()
	{
		c = -1;
		p = -1;
		fill(g, g + AL, -1);
		fill(nxt, nxt + AL, -1);
		link = -1;
	}
};

struct AC
{
	Node A[N];
	int sz;
	void init()
	{
		A[0].init();
		sz = 1;
	}
	int addStr(const string& s)
	{
		int v = 0;
		FOR (i, 0, SZ(s))
		{
			int c = s[i] - 'a'; // change to [0 AL)
			if (A[v].nxt[c] == -1)
			{
				A[v].nxt[c] = sz;
				A[sz].init();
				A[sz].c = c;
				A[sz].p = v;
				sz++;
			}
			v = A[v].nxt[c];
		}
		return v;
	}
	int go(int v, int c)
	{
		if (A[v].g[c] != -1)
			return A[v].g[c];
			
		if (A[v].nxt[c] != -1)
			A[v].g[c] = A[v].nxt[c];
		else if (v != 0)
			A[v].g[c] = go(getLink(v), c);
		else
			A[v].g[c] = 0;
			
		return A[v].g[c];
	}
	int getLink(int v)
	{
		if (A[v].link != -1)
			return A[v].link;
		if (v == 0 || A[v].p == 0)
			return 0;
		return A[v].link=go(getLink(A[v].p), A[v].c);
	}
} A;
