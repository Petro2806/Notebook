/**
 * Description: queryLcp returns the longest common prefix of substrings starting at $i$ and $j$.
 */
 
struct Lcp
{
	VI lcp;
	SuffixArray a;
	SparseTable st;

	void init(const SuffixArray& _a)
	{
		a = _a;
		lcp = lcpArray();
		st.init(SZ(lcp));
		st.build(lcp);
	}

	VI lcpArray()
	{
		lcp.resize(a.n - 1);
		int h = 0;
		FOR (i, 0, a.n)
		{
			if (h > 0)
				h--;
			if (a.rnk[i] == 0)
				continue;
			int j = a.sa[a.rnk[i] - 1];
			for (; j + h < a.n && i + h < a.n; h++)
			{
				if (a.s[j + h] != a.s[i + h])
					break;
			}
			lcp[a.rnk[i] - 1] = h;
		}
		return lcp;
	}
	int queryLcp(int i, int j)
	{
		if (i == a.n || j == a.n)
			return 0;
		assert(i != j); // return n - i ????
		i = a.rnk[i];
		j = a.rnk[j];
		if (i > j)
			swap(i, j);
		// query [i, j)
		return st.query(i, j);
	}
};
