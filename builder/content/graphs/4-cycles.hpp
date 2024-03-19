/**
 * Description: Sort $d$ and add breaks to speed up.
 * With breaks works 0.5s for m = $5 \cdot 10^5$.
 * Time: O(\sum_{uv \in E} \min(\deg(u), \deg(v))) = O(m \cdot \sqrt{m})
 */

LL rect(int n)
{
	LL cnt4 = 0;
	vector<PII> d(n);
	FOR (v, 0, n) d[v] = MP(SZ(g[v]), v);
	VI L(n);
	FOR (v, 0, n)
	{
		for (auto u : g[v])
			if (d[u] < d[v])
				for (auto y : g[u])
					if (d[y] < d[v])
						cnt4 += L[y], L[y]++;
		for (auto u : g[v])
			if (d[u] < d[v])
				for (auto y : g[u])
					L[y] = 0;
	}
	return cnt4;
}
