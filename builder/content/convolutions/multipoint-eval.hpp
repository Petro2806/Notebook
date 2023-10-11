int x[LEN];
VI P[2 * LEN];

void build(int v, int tl, int tr)
{
	if(tl + 1 == tr)
	{
		P[v] = {sub(0, x[tl]), 1};
		return;
	}
	int tm = (tl + tr) / 2;
	build(2 * v + 1, tl, tm);
	build(2 * v + 2, tm, tr);
	
	P[v] = mult(P[2 * v + 1], P[2 * v + 2]);
}
int ans[LEN];
void solve(int v, int tl, int tr, const VI& Q) 
//Q != Q % P[0] -> wa
{
	if(SZ(Q) == 0)
		return;
	if(tl + 1 == tr)
	{
		ans[tl] = Q[0];
		return;
	}
	int tm = (tl + tr) / 2;	
	solve(2 * v + 1, tl, tm, 
	modulo(Q, P[2 * v + 1]).S);
	solve(2 * v + 2, tm, tr, 
	modulo(Q, P[2 * v + 2]).S);
}
