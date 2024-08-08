/**
 * Description: queryLcp returns the longest common prefix of substrings starting at $i$ and $j$.
 */
struct LCP
{
	int n;
	VI s, sa, rnk, lcp;
	SparseTable st;

	LCP(VI _s): n(SZ(_s)), s(_s)
	{
		sa = suffixArray(s);
		rnk.resize(n);
		FOR (i, 0, n)
			rnk[sa[i]] = i;
		lcpArray();
		FOR (i, 0, n - 1)
			st.PB(lcp[i]);
	}

	void lcpArray()
	{
		lcp.resize(n - 1);
		int h = 0;
		FOR (i, 0, n)
		{
			if (h > 0)
				h--;
			if (rnk[i] == 0)
				continue;
			int j = sa[rnk[i] - 1];
			for (; j + h < n && i + h < n; h++)
			{
				if (s[j + h] != s[i + h])
					break;
			}
			lcp[rnk[i] - 1] = h;
		}
	}
	int queryLcp(int i, int j)
	{
		if (i == n || j == n)
			return 0;
		assert(i != j); // return n - i ????
		i = rnk[i];
		j = rnk[j];
		if (i > j)
			swap(i, j);
		// query [i, j)
		return st.query(i, j);
	}
};
