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
	vector<Node> a;
	int sz;
	void init(int n)
	{
		a.resize(n);
		a[0].init();
		sz = 1;
	}
	int addStr(const string& s)
	{
		int v = 0;
		FOR (i, 0, SZ(s))
		{
			// change to [0 AL)
			int c = s[i] - 'a'; 
			if (a[v].nxt[c] == -1)
			{
				a[v].nxt[c] = sz;
				a[sz].init();
				a[sz].c = c;
				a[sz].p = v;
				sz++;
			}
			v = a[v].nxt[c];
		}
		return v;
	}
	int go(int v, int c)
	{
		if (a[v].g[c] != -1)
			return a[v].g[c];
			
		if (a[v].nxt[c] != -1)
			a[v].g[c] = a[v].nxt[c];
		else if (v != 0)
			a[v].g[c] = go(getLink(v), c);
		else
			a[v].g[c] = 0;
			
		return a[v].g[c];
	}
	int getLink(int v)
	{
		if (a[v].link != -1)
			return a[v].link;
		if (v == 0 || a[v].p == 0)
			return 0;
		return a[v].link=go(getLink(a[v].p), a[v].c);
	}
};
