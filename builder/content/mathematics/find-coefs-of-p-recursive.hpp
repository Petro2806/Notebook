/**
 * Description: Finds the polynomials $P_j$ such that
 * $\sum_{j=0}^d P_j(i) \cdot a_{i + d - j} = 0$.
 * Returns an empty vector if unable to find such polynomials.
 * The first $k$ terms $a_0, a_1, \dots, a_{k - 1}$ are given.
 * Time: O(k^3)
 */
vector<VI> findCoefsOfPRecursive(const VI& a, int d)
{
	int m = (SZ(a) - d) / (d + 1) - 1;
	if (m < 0)
		return {};
	int n = (m + 1) * (d + 1);
	vector<VI> matr(SZ(a) - d, VI(n));
	FOR(i, 0, SZ(a) - d)
	{
		FOR(j, 0, d + 1)
		{
			int pw = 1;
			FOR(k, 0, m + 1)
			{
				matr[i][(m + 1) * j + k] = mult(pw, a[i + d - j]);
				pw = mult(pw, i);
			}
		}
	}
	auto [v, w] = solveLinearSystem(matr, VI(SZ(a) - d));
	if(w.empty())
		return {};
	vector<VI> p(d + 1);
	FOR(j, 0, d + 1)
	{
		p[j] = {w[0].begin() + (m + 1) * j, w[0].begin() + (m + 1) * (j + 1)};
		removeLeadingZeros(p[j]);
	}
	return p;
}
