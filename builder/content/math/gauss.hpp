/**
 * Description: a[i].back() is right side element
 * Time: $O(m^2*n)$
 */
VI Gauss(vector<VI> a)
{
	int n = SZ(a);
	if(n == 0)
		return {};
	int m = SZ(a[0]) - 1;//number of variables
	assert(n >= m);
	
	int vars = m;
	FOR(i, 0, m)
	{
		if (a[i][i] == 0)
		{
			//for double find row 
			//with max abs value
			int row = -1;
			FOR(k, i + 1, n)
			{
				if (a[k][i] != 0)
					row = k;
			}
			if(row == -1)
			{
				//variable i can be any
				vars--;
				continue;
			}
			swap(a[i], a[row]);
		}
		int d = inv(a[i][i]);
		FOR(k, i + 1, n)
		{
			int c = mult(a[k][i], d);
			FOR(j, 0, m + 1)
				updSub(a[k][j], mult(c, a[i][j]));
		}
	}
	FOR(i, vars, n)
		if(a[i].back() != 0)
			cout << "No solution\n";
	VI x(m);
	RFOR(i, m, 0)
	{
		x[i] = a[i].back();
		FOR(j, i + 1, m)
			updSub(x[i], mult(a[i][j], x[j]));
		x[i] = mult(x[i], inv(a[i][i]));
	}
	return x;
}
