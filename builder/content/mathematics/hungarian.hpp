/**
 * Description: Finds a maximum matching that has the minimum weight in a weighted bipartite graph.
 * Time: O(n^2 m)
 */
LL hungarian(const vector<VL>& a)
{
	int n = SZ(a), m = SZ(a[0]);
	assert(n <= m);
	VL u(n + 1), v(m + 1);
	VI p(m + 1, n), way(m + 1);
	FOR(i, 0, n)
	{
		p[m] = i;
		int j0 = m;
		VL minv(m + 1, LINF);
		VI used(m + 1);
		while (p[j0] != n)
		{
			used[j0] = true;
			int i0 = p[j0], j1 = -1;
			LL delta = LINF;
			FOR(j, 0, m)
			{
				if (!used[j])
				{
					LL cur = a[i0][j] - u[i0] - v[j];
					if (cur < minv[j])
					{
						minv[j] = cur;
						way[j] = j0;
					}
					if (minv[j] < delta)
					{
						delta = minv[j];
						j1 = j;
					}
				}
			}
			assert(j1 != -1);
			FOR(j, 0, m + 1)
			{
				if (used[j])
				{
					u[p[j]] += delta;
					v[j] -= delta;
				}
				else
					minv[j] -= delta;
			}
			j0 = j1;
		}
		while (j0 != m)
		{
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		}
	}
	VI ans(n + 1);
	FOR(j, 0, m)
		ans[p[j]] = j;
	LL res = 0;
	FOR(i, 0, n)
		res += a[i][ans[i]];
	assert(res == -v[m]);
	return res;
}
