/**
 * Description: Returns the indices of tangent points from $p$.
 * $p$ must be strictly outside the polygon.
 **/
PII tangentsToConvexPolygon(const vector<Pt>& v, const Pt& p)
{
	int n = SZ(v), i = 0;
	if (n == 2)
		return {0, 1};
	while (sgn(orient(p, v[i], v[(i + 1) % n]))
		* sgn(orient(p, v[i], v[(i + n - 1) % n])) > 0)
		i++;
	int s1 = 1, s2 = -1;
	if (sgn(orient(p, v[i], v[(i + 1) % n])) == s1 
		|| sgn(orient(p, v[i], v[(i + n - 1) % n])) == s2)
		swap(s1, s2);
	PII res;
	int l = i, r = i + n - 1;
	while (r - l > 1)
	{
		int m = (l + r) / 2;
		if (sgn(orient(p, v[i], v[m % n])) != s1
			&& sgn(orient(p, v[m % n], v[(m + 1) % n])) != s1)
			l = m;
		else
			r = m;
	}
	res.F = r % n;
	l = i;
	r = i + n - 1;
	while (r - l > 1)
	{
		int m = (l + r) / 2;
		if (sgn(orient(p, v[i], v[m % n])) == s2
			|| sgn(orient(p, v[m % n], v[(m + 1) % n])) != s2)
			l = m;
		else
			r = m;
	}
	res.S = r % n;
	return res;
}
