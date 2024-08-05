db goldenSectionSearch(db l, db r)
{
	const db c = (-1 + sqrt(5)) / 2;
	const int M = 474;
	db m1 = r - c * (r - l), fm1 = f(m1),
		m2 = l + c * (r - l), fm2 = f(m2);
	FOR(i, 0, M)
	{
		if (fm1 < fm2)
		{
			r = m2;
			m2 = m1;
			fm2 = fm1;
			m1 = r - c * (r - l);
			fm1 = f(m1);
		}
		else
		{
			l = m1;
			m1 = m2;
			fm1 = fm2;
			m2 = l + c * (r - l);
			fm2 = f(m2);
		}
	}
	return (l + r) / 2;
}
