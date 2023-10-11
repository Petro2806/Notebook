VI prefixFunction(const string& s)
{
	int n = SZ(s);
	VI p(n);
	p[0] = 0;
	FOR (i, 1, n)
	{
		int j = p[i - 1];
		while(j != 0 && s[i] != s[j]) 
			j = p[j - 1];

		if (s[i] == s[j]) j++;
		p[i] = j;
	}
	return p;
}
