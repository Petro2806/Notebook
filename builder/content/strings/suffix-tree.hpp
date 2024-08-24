/**
 * Description: Ukkonen's algorithm for building a suffix tree.
 * Cast your string to vector.
 * Don't forget about delimiters.
 * \texttt{a[v].g[c]} is a transition in format $(u, (l, r))$,
 * that goes from $v$ to $u$ and the string spelled out by this transition is the substring $s_{l..r}$.
 * For transitions that go to leaves, $r = \text{INF}$.
 * For the root node which has number $0$, \texttt{link == -1}. For leaves, \texttt{link == -2}.
 * For all other nodes, \texttt{link} is maintained explicitly.
 * Time: O(n)
 */

struct SuffixTree
{
	struct Node
	{
		map<int, pair<int, PII>> g;
		int link;
		Node(): link(-2) {}
	};
	VI s;
	vector<Node> a;
	pair<bool, int> testAndSplit(int v, int l, int r, int c)
	{
		if (v == -1)
			return {true, -1};
		if (l <= r)
		{
			auto [nv, nlr] = a[v].g[s[l]];
			auto [nl, nr] = nlr;
			if (c == s[nl + r - l + 1])
				return {true, v};
			int newNode = SZ(a);
			a.PB(Node());
			a[v].g[s[l]] = {newNode, {nl, nl + r - l}};
			a[newNode].g[s[nl + r - l + 1]] = {nv, {nl + r - l + 1, nr}};
			return {false, newNode};
		}
		return {a[v].g.count(c), v};
	}
	PII canonize(int v, int l, int r)
	{
		if (v == -1 && l <= r)
		{
			v = 0;
			l++;
		}
		if (r < l)
			return {v, l};
		auto [nv, nlr] = a[v].g[s[l]];
		auto [nl, nr] = nlr;
		while (nr - nl <= r - l)
		{
			l += nr - nl + 1;
			v = nv;
			if (l <= r)
			{
				tie(nv, nlr) = a[v].g[s[l]];
				tie(nl, nr) = nlr;
			}
		}
		return {v, l};
	}
	PII update(int v, int l, int r)
	{
		int oldu = 0;
		auto [endPoint, u] = testAndSplit(v, l, r - 1, s[r]);
		while (!endPoint)
		{
			int newNode = SZ(a);
			a.PB(Node());
			a[u].g[s[r]] = {newNode, {r, INF}};
			if (oldu != 0)
				a[oldu].link = u;
			oldu = u;
			tie(v, l) = canonize(a[v].link, l, r - 1);
			tie(endPoint, u) = testAndSplit(v, l, r - 1, s[r]);
		}
		if (oldu != 0)
			a[oldu].link = v;
		return {v, l};
	}
	void build(const VI& _s)
	{
		s = _s;
		// Add the symbol that was not present in `s`
		s.PB(-1);
		a.reserve(2 * SZ(s));
		a = {Node()};
		a[0].link = -1;
		int v = 0, l = 0;
		FOR(i, 0, SZ(s))
		{
			tie(v, l) = update(v, l, i);
			tie(v, l) = canonize(v, l, i);
		}
	}
};
