/**
 * Description: Evaluates the polynomial $P(x)$ of degree $m$ at points $x_0, \dots, x_{n - 1}$.
 * Time: O(n \log^2 n + m \log m)
 */
VI multipointEval(const VI& p, const VI& x)
{
	int n = SZ(x);
	vector<VI> t;
	int _n = 1;
	while (_n < 2 * n)
		_n *= 2;
	t.resize(_n);
	
	function<void(int, int, int)> build = [&](int v, int tl, int tr)
	{
		if(tl + 1 == tr)
		{
			t[v] = {sub(0, x[tl]), 1};
			return;
		}
		int tm = (tl + tr) / 2;
		build(2 * v + 1, tl, tm);
		build(2 * v + 2, tm, tr);
		t[v] = mult(t[2 * v + 1], t[2 * v + 2]);
	};
	
	build(0, 0, n);
	VI ans(n);
	
	function<void(int, int, int, VI)> solve
		= [&](int v, int tl, int tr, VI q)
	{
		q = divide(q, t[v]).S;
		if (q.empty())
			return;
		if(tl + 1 == tr)
		{
			ans[tl] = q[0];
			return;
		}
		int tm = (tl + tr) / 2;	
		solve(2 * v + 1, tl, tm, q);
		solve(2 * v + 2, tm, tr, q);
	};
	
	solve(0, 0, n, p);
	return ans;
}
