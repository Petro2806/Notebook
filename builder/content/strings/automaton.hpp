/**
 * To count number of occurances of string
 * calculate sum of cnt on link subtree
 */

const int AL = 26;

struct Node
{
	int g[AL];
	int link;
	int len;
	int cnt;
	Node()
	{
		fill(g, g + AL, -1);
		link = -1;
		len = -1;
		cnt = 1;
	}
};

struct Automaton
{
	vector<Node> a;
	int head;
	void init(int n)
	{
		a.reserve(2 * n);
		a.PB(Node());
		head = 0;
	}
	void add(char c)
	{
		// change to [0 AL)
		int ch = c - 'a';
		int nhead = SZ(a);
		a.PB(Node());
		a[nhead].len = a[head].len + 1;
		int cur = head;
		head = nhead;
		while (cur != -1 && a[cur].g[ch] == -1)
		{
			a[cur].g[ch] = head;
			cur = a[cur].link;
		}
		if (cur == -1)
		{
			a[head].link = 0;
			return;
		}
		int p = a[cur].g[ch];
		if (a[p].len == a[cur].len + 1)
		{
			a[head].link = p;
			return;
		}
		int q = SZ(a);
		a.PB(Node());
		a[q] = a[p];
		a[q].cnt = 0;
		a[q].len = a[cur].len + 1;
		a[p].link = a[head].link = q;
		while (cur != -1 && a[cur].g[ch] == p)
		{
			a[cur].g[ch] = q;
			cur = a[cur].link;
		}
	}
};
