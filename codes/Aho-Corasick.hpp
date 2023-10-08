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
	Node A[MAX];
	int sz;
	void init()
	{
		A[0].init();
		sz = 1;
	}
	int addStr(const string& s)
	{
		int x = 0;
		FOR (i, 0, SZ(s))
		{
			int c = s[i] - 'A'; // change to [0 AL)
			if (A[x].nxt[c] == -1)
			{
				A[x].nxt[c] = sz;
				A[sz].init();
				A[sz].c = c;
				A[sz].p = x;
				sz++;
			}
			x = A[x].nxt[c];
		}
		return x;
	}
	int go(int x, int c)
	{
		if (A[x].g[c] != -1)
			return A[x].g[c];
			
		if (A[x].nxt[c] != -1)
			A[x].g[c] = A[x].nxt[c];
		else if (x != 0)
			A[x].g[c] = go(getLink(x), c);
		else
			A[x].g[c] = 0;
			
		return A[x].g[c];
	}
	int getLink(int x)
	{
		if (A[x].link != -1)
			return A[x].link;
		if (x == 0 || A[x].p == 0)
			return 0;
		return A[x].link = go(getLink(A[x].p), A[x].c);
	}
} A;
