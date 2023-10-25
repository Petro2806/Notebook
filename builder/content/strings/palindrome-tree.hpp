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
	vector<Node> A;
	int sz;
	int last;
	
	void init(string t)
	{
		A.resize(2 * SZ(t));
		A[0].clear();
		A[1].clear();
		A[1].len = 0;
		A[1].link = 0;
		sz = 2;
		last = 1;
		s = t;
	}
	void add(int idx)
	{
		int cur = last;
		while (cur != -1)
		{
			int pos = idx - A[cur].len - 1;
			if (pos >= 0 && s[pos] == s[idx])
				break;
			cur = A[cur].link;
		}
		assert(cur != -1);
		if (A[cur].to[s[idx] - 'a'] == -1)
		{
			A[cur].to[s[idx] - 'a'] = sz;
			A[sz].clear();
			A[sz].len = A[cur].len + 2;
			int link = A[cur].link;
			while (link != -1)
			{
				int pos = idx - A[link].len - 1;
				if (pos >= 0 && s[pos] == s[idx])
					break;
				link = A[link].link;
			}
			if (link == -1)
				link = 1;
			else
				link = A[link].to[s[idx] - 'a'];
			A[sz].link = link;
			sz++;
		}
		last = A[cur].to[s[idx] - 'a'];
	}
} pt;
