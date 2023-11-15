/**
 * Description: Function \textit{build} calculates the products of $x - x_i$. \\
 * Function \textit{solve} calculates the values of $q(x)$ in $x_0, \dots, x_{n - 1}$.\\
 * 1. Call $build(0, 0, n)$. 2. Call $solve(0, 0, n, q)$.
 */
int x[LEN];
VI p[2 * LEN];

void build(int v, int tl, int tr)
{
	if(tl + 1 == tr)
	{
		p[v] = {sub(0, x[tl]), 1};
		return;
	}
	int tm = (tl + tr) / 2;
	build(2 * v + 1, tl, tm);
	build(2 * v + 2, tm, tr);
	
	p[v] = mult(p[2 * v + 1], p[2 * v + 2]);
}
int ans[LEN];
void solve(int v, int tl, int tr, const VI& q) 
//q != q % p[0] -> wa
{
	if(SZ(q) == 0)
		return;
	if(tl + 1 == tr)
	{
		ans[tl] = q[0];
		return;
	}
	int tm = (tl + tr) / 2;	
	solve(2 * v + 1, tl, tm, 
	modulo(q, p[2 * v + 1]).S);
	
	solve(2 * v + 2, tm, tr, 
	modulo(q, p[2 * v + 2]).S);
}
