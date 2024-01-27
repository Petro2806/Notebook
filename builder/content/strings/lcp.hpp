VI lcpArray(const string& s, const VI& sa) 
{
	int n = SZ(s);
	VI rnk(n);
	FOR (i, 0, n)
		rnk[sa[i]] = i;
	VI lcp(n - 1);
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
	return lcp;
}
