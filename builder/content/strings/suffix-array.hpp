/**
 * Description: Cast your string to an array.
 * Don't forget about delimiters.
 * No need to add anything at the end.
 * $\text{sa}$ represents permutations of positions if you sort all suffixes.
 * $\text{rnk} = \text{sa}^{-1}$.
 */

struct SuffixArray
{
	int n;
	VI s;
	VI sa, rnk;	
	
	void init(const VI& _s)
	{
		n = SZ(_s);
		s = _s;
		sa = suffixArray();
		rnk.resize(n);
		FOR (i, 0, n)
			rnk[sa[i]] = i;
	}
	
	void countSort(VI& p, const VI& c)
	{
		VI cnt(n);
		FOR (i, 0, n)
			cnt[c[i]]++;
		VI pos(n);
		FOR (i, 1, n)
			pos[i] = pos[i - 1] + cnt[i - 1];
		VI p2(n);
		for (auto x : p)
		{
			int i = c[x];
			p2[pos[i]++] = x;
		}
		p = p2;
	}
	
	VI suffixArray()
	{
		// strictly smaller than any other element
		s.PB(-INF);
		n++;
		VI p(n), c(n);
		iota(ALL(p), 0);
		sort(ALL(p), [&](int i, int j)
		{
			return s[i] < s[j];
		});
		int x = 0;
		c[p[0]] = 0;
		FOR (i, 1, n)
		{
			if (s[p[i]] != s[p[i - 1]])
				x++;
			c[p[i]] = x;
		}
		int k = 0;
		while ((1 << k) < n)
		{
			FOR (i, 0, n)
				p[i] = (p[i] - (1 << k) + n) % n;
			countSort(p, c);
			VI c2(n);
			PII pr = {c[p[0]], c[(p[0] + (1 << k)) % n]};
			FOR (i, 1, n)
			{
				PII nx = {c[p[i]], c[(p[i] + (1 << k)) % n]};
				c2[p[i]] = c2[p[i - 1]];
				if (pr != nx)
					c2[p[i]]++;
				pr = nx;
			}
			c = c2;
			k++;
		}
		p.erase(p.begin());
		s.pop_back();
		n--;
		return p;
	}
};
