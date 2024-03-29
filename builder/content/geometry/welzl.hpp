/**
 * Description: Returns the smallest enclosing circle of points in $v$
 * Time: O(n) \text{(expected)}
 **/
pair<Pt, db> welzl(vector<Pt> v)
{
	int n = SZ(v), k = 0, idxes[2];
	mt19937 rng;
	shuffle(ALL(v), rng);
	Pt c = v[0];
	db r = 0;
	while (true)
	{
		FOR(i, k, n)
		{
			if (sgn(abs(v[i] - c) - r) > 0)
			{
				swap(v[i], v[k]);
				if (k == 0)
					c = v[0];
				else if (k == 1)
					c = (v[0] + v[1]) / 2;
				else
					c = circumCenter(v[0], v[1],	v[2]);
				r = abs(v[0] - c);
				if (k < i)
				{
					if (k < 2)
						idxes[k++] = i;
					shuffle(v.begin() + k, v.begin() + i + 1, rng);
					break;
				}
			}
			while (k > 0 && idxes[k - 1] == i)
				k--;
			if (i == n - 1)
				return {c, r};
		}
	}
}
