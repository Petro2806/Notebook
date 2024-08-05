/**
 * Description: solve can be called again if needed, but it searches for the solution from scratch.
 * Time: solve() works in less than $O(1.84^n \cdot n^2)$.
 */

struct ThreeSAT
{
	int n;
	VI ans;
	vector<vector<VI>> hasRule;
	
	void init(int _n)
	{		
		n = _n;
		hasRule.assign(2 * n, vector<VI>(2 * n, VI(2 * n, 0)));
	}
	//(x_a == valA) || (x_b == valB) || (x_c == valC)
	void addRule(int a, int valA, int b, int valB, int c, int valC)
	{
		a = 2 * a + valA;
		b = 2 * b + valB;
		c = 2 * c + valC;
		
		hasRule[a][b][c] = hasRule[a][c][b] = true;
		hasRule[b][a][c] = hasRule[b][c][a] = true;
		hasRule[c][a][b] = hasRule[c][b][a] = true;
	}
	VI findRule(int k)
	{
		FOR(i, 0, 2 * n)
			FOR(j, 0, 2 * n)
				FOR(t, 0, 2)
					if(hasRule[2 * k + t][i][j])
						return {2 * k + t, i, j};
		return {};		
	}
	
	VI fixed;
	bool add(int k, int t)
	{
		if(ans[k] != -1)
			return ans[k] == t;	
		
		ans[k] = t;
		fixed.PB(k);		
		FOR(i, 0, n)
		{
			if(ans[i] == -1)
				continue;
			int xi = 2 * i + ans[i];
			int xk = 2 * k + t;
			FOR(j, 0, n)	
				FOR(tj, 0, 2)
					if(hasRule[xi ^ 1][xk ^ 1][2 * j + tj] && !add(j, tj))
						return false;
		}
		return true;
	}
	
	bool check()
	{
		int var = 0;
		while(var < n && ans[var] != -1)
			var++;
		if(var == n)
			return true;
				
		VI rule = findRule(var);
		FOR(i, 0, 3)
		{
			fixed.clear();
			bool ok = add(rule[i] / 2, rule[i] % 2);
			FOR(j, 0, i)
				ok &= add(rule[j] / 2, (rule[j] % 2) ^ 1);

			VI curFixed = fixed;			
			if(ok && check())
				return true;
				
			for(int v : curFixed)
				ans[v] = -1;			
		}
		return false;
	}
	
	VI solve()
	{
		ans.assign(n, -1);
		FOR(var, 0, n)
		{
			if(findRule(var).empty())
				add(var, 0);
		}
		if(!check())
			return {};
		return ans;
	}
};
