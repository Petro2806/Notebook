/**
 * Description: $[\frac{A(x)}{B(x)}]$ and $A(x)$ modulo $B(x)$.
 */
void removeLeadingZeros(VI& a)
{
	while(SZ(a) > 0 && a.back() == 0)
		a.pop_back();
}
pair<VI, VI> modulo(VI a, VI b)
{
	removeLeadingZeros(a);
	removeLeadingZeros(b);
	//be careful with this case
	assert(SZ(a) != 0 && SZ(b) != 0);
	
	int n = SZ(a), m = SZ(b);
	if(m > n)
		return MP(VI{}, a);
	
	reverse(ALL(a));
	reverse(ALL(b));
	
	VI d = b;
	d.resize(n - m + 1);
	d = mult(a, inverse(d, n - m + 1));
	d.resize(n - m + 1);
	
	reverse(ALL(a));
	reverse(ALL(b));
	reverse(ALL(d));
	
	VI res = mult(b, d);
	res.resize(SZ(a));
	FOR(i, 0, SZ(a))
		res[i] = sub(a[i], res[i]);
	
	removeLeadingZeros(d);
	removeLeadingZeros(res);
	return MP(d, res);
}
