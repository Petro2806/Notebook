int Z[MAX];	
	
void Zf(const string& s)
{
	int n = SZ(s);

	int l = 0;
	int r = 0;
	FOR (i, 1, n)
	{
		Z[i] = 0;
		if (i <= r)
			Z[i] = min(r - i + 1, Z[i - l]);

		while(i + Z[i] < n && s[i + Z[i]] == s[Z[i]])
			Z[i]++;
		if(i + Z[i] - 1 > r)
		{
			r = i + Z[i] - 1;
			l = i;
		}
	}
}
