const int AL = 26;

struct Node
{
	int to[AL];
	int link;
	int len;
	Node(int _link, int _len)
	{
		fill(to, to + AL, -1);
		link = _link;
		len = _len;
	}
};
struct PalTree
{
	string s;
	vector<Node> a;
	int last;
	
	PalTree(string t = ""): s(t), a({{-1, -1}, {0, 0}}), last(1) {}
	void add(int idx)
	{
		// change to [0, AL)
		int ch = s[idx] - 'a';
		
		int cur = last;
		while (cur != -1)
		{
			int pos = idx - a[cur].len - 1;
			if (pos >= 0 && s[pos] == s[idx])
				break;
			cur = a[cur].link;
		}
		if (a[cur].to[ch] == -1)
		{
			a[cur].to[ch] = SZ(a);
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
			a.PB(Node(link, a[cur].len + 2));
		}
		last = a[cur].to[ch];
	}
};

