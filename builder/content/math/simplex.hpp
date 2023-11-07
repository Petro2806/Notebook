/**
 * Description: $c^T x \to \max$, $Ax \le b$, $x \ge 0$.
 */
typedef vector<db> VD;

struct Simplex
{
	void pivot(int l, int e)
	{
		assert(0 <= l && l < m);
		assert(0 <= e && e < n);
		assert(abs(a[l][e]) > EPS);
		b[l] /= a[l][e];
		FOR(j, 0, n)
			if (j != e)
				a[l][j] /= a[l][e];
		a[l][e] = 1 / a[l][e];
		FOR(i, 0, m)
		{
			if (i != l)
			{
				b[i] -= a[i][e] * b[l];
				FOR(j, 0, n)
					if (j != e)
						a[i][j] -= a[i][e] * a[l][j];
				a[i][e] *= -a[l][e];
			}
		}
		v += c[e] * b[l];
		FOR(j, 0, n)
			if (j != e)
				c[j] -= c[e] * a[l][j];
		c[e] *= -a[l][e];
		swap(nonBasic[e], basic[l]);
	}
	void findOptimal()
	{
		VD delta(m);
		while (true)
		{
			int e = -1;
			FOR(j, 0, n)
				if (c[j] > EPS && (e == -1 || nonBasic[j] < nonBasic[e]))
					e = j;
			if (e == -1)
				break;
			FOR(i, 0, m)
				delta[i] = a[i][e] > EPS ? b[i] / a[i][e] : LINF;
			int l = min_element(ALL(delta)) - delta.begin();
			if (delta[l] == LINF)
			{
				// unbounded
				assert(false);
			}
			pivot(l, e);
		}
	}
	void initializeSimplex(const vector<VD>& _a, const VD& _b, const VD& _c)
	{
		m = SZ(_b);
		n = SZ(_c);
		nonBasic.resize(n);
		iota(ALL(nonBasic), 0);
		basic.resize(m);
		iota(ALL(basic), n);
		a = _a;
		b = _b;
		c = _c;
		v = 0;
		int k = min_element(ALL(b)) - b.begin();
		if (b[k] > -EPS)
			return;
		nonBasic.PB(n);
		iota(ALL(basic), n + 1);
		FOR(i, 0, m)
			a[i].PB(-1);
		c.assign(n, 0);
		c.PB(-1);
		n++;
		pivot(k, n - 1);
		findOptimal();
		if (v < -EPS)
		{
			// infeasible
			assert(false);
		}
		int l = find(ALL(basic), n - 1) - basic.begin();
		if (l != m)
		{
			int e = -1;
			while (abs(a[l][e]) < EPS)
				e++;
			pivot(l, e);
		}
		n--;
		int p = find(ALL(nonBasic), n) - nonBasic.begin();
		assert(p < n + 1);
		nonBasic.erase(nonBasic.begin() + p);
		FOR(i, 0, m)
			a[i].erase(a[i].begin() + p);
		c.assign(n, 0);
		FOR(j, 0, n)
		{
			if (nonBasic[j] < n)
				c[j] = _c[nonBasic[j]];
			else
				nonBasic[j]--;
		}
		FOR(i, 0, m)
		{
			if (basic[i] < n)
			{
				v += _c[basic[i]] * b[i];
				FOR(j, 0, n)
					c[j] -= _c[basic[i]] * a[i][j];
			}
			else
				basic[i]--;
		}
	}
	pair<VD, db> simplex(const vector<VD>& _a, const VD& _b, const VD& _c)
	{
		initializeSimplex(_a, _b, _c);
		assert(SZ(a) == m);
		FOR(i, 0, m)
			assert(SZ(a[i]) == n);
		assert(SZ(b) == m);
		assert(SZ(c) == n);
		assert(SZ(nonBasic) == n);
		assert(SZ(basic) == m);
		findOptimal();
		VD x(n);
		FOR(i, 0, m)
			if (basic[i] < n)
				x[basic[i]] = b[i];
		return {x, v};
	}
private:
	int m, n;
	VI nonBasic, basic;
	vector<VD> a;
	VD b;
	VD c;
	db v;
};
