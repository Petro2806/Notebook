
const int AL = 26;
struct Node
{
	int g[AL];
	int link;
	int len;
	int cnt;
	void init()
	{
		fill(g, g + AL, -1);
		link = -1;
		len = -1;
	}
};
struct Automaton
{
	Node A[MAX * 2];
	int sz;
	int head;
	void init()
	{
		sz = 1;
		head = 0;
		A[0].init();
	}
	void add(char c)
	{
		int ch = c - 'a'; // change to [0 AL)
		int nhead = sz++;
		A[nhead].init();
		A[nhead].len = A[head].len + 1;
		int cur = head;
		head = nhead;
		while (cur != -1 && A[cur].g[ch] == -1)
		{
			A[cur].g[ch] = head;
			cur = A[cur].link;
		}
		if (cur == -1)
		{
			A[head].link = 0;
			return;
		}
		int p = A[cur].g[ch];
		if (A[p].len == A[cur].len + 1)
		{
			A[head].link = p;
			return;
		}
		int q = sz++;
		A[q] = A[p];
		A[q].len = A[cur].len + 1;
		A[p].link = A[head].link = q;
		while (cur != -1 && A[cur].g[ch] == p)
		{
			A[cur].g[ch] = q;
			cur = A[cur].link;
		}
	}
};
