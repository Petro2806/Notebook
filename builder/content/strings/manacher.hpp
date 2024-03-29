/**
 * Description: $s[i - d0_i, i + d0_i - 1]$, $s[i - d1_i + 1, i + d1_i - 1]$ are palindromes.
 **/

vector<VI> manacher(const string& s)
{
	int n = SZ(s);
	vector<VI> d(2);
	FOR (t, 0, 2)
	{
		d[t].resize(n);
		int l = -1;
		int r = -1;
		FOR (i, 0, n)
		{
			if (i <= r)
				d[t][i] = min(r - i + 1, d[t][l + (r - i) + 1 - t]);
			while (i + d[t][i] < n 	&& i + t - d[t][i] - 1 >= 0 
				&& s[i + d[t][i]] == s[i + t - d[t][i] - 1])
							d[t][i]++;
			if (i + d[t][i] - t > r)
			{
				r = i + d[t][i] - 1;
				l = i - d[t][i] + t;
			}
		}
	}
	return d;
}

