struct Node
{
	int to[AL];
	int link;
	int len;
	void clear()
	{
		fill(to, to + AL, -1);
		link = -1;
		len = -1;
	}
};
struct PalTree
{
	string s;
	vector<Node> a;
	int sz;
	int last;
	
	void init(string t)
	{
		a.resize(2 * SZ(t));
		a[0].clear();
		a[1].clear();
		a[1].len = 0;
		a[1].link = 0;
		sz = 2;
		last = 1;
		s = t;
	}
	void add(int idx)
	{
		int ch = s[idx] - 'a';
		
		int cur = last;
		while (cur != -1)
		{
			int pos = idx - a[cur].len - 1;
			if (pos >= 0 && s[pos] == s[idx])
				break;
			cur = a[cur].link;
		}
		assert(cur != -1);
		if (a[cur].to[ch] == -1)
		{
			a[cur].to[ch] = sz;
			a[sz].clear();
			a[sz].len = a[cur].len + 2;
			int link = a[cur].link;
			while (link != -1)
			{
				int pos = idx - a[link].len - 1;
				if (pos >= 0 && s[pos] == s[idx])
					break;
				link = a[link].link;
			}
			if (link == -1)
				link = 1;
			else
				link = a[link].to[ch];
			a[sz].link = link;
			sz++;
		}
		last = a[cur].to[ch];
	}
};
