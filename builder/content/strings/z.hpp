VI zFunction(const string& s)
{
	int n = SZ(s);
	VI z(n);

	int l = 0;
	int r = 0;
	FOR (i, 1, n)
	{
		z[i] = 0;
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);

		while(i + z[i] < n && s[i + z[i]] == s[z[i]])
			z[i]++;
		if(i + z[i] - 1 > r)
		{
			r = i + z[i] - 1;
			l = i;
		}
	}
	return z;
}
