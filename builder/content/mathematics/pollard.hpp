/** 
 * Description: Uses the Miller-Rabin test. 
 * \texttt{rho} finds a divisor of $n$. 
 * Use \texttt{\_\_int128} in \texttt{mult}.
 * Time: $O(n^{1/4} \cdot \log n)$.
 **/
 
LL f(LL x, LL c, LL n)
{
	return add(mult(x, x, n), c, n);
}

LL rho(LL n)
{
	const int iter = 47 * pow(n, 0.25);
	while (true)
	{
		LL x0 = rng() % n;
		LL c = rng() % n;
		LL x = x0;
		LL y = x0;
		LL g = 1;
		FOR (i, 0, iter)
		{
			x = f(x, c, n);
			y = f(y, c, n);
			y = f(y, c, n);
			g = gcd(abs(x - y), n);
			if (g != 1)
				break;
		}
		if (g > 1 && g < n)
			return g;
	}
}
VI primes = {2, 3, 5, 7, 11, 13, 17, 19, 23};

VL factorize(LL n)
{
	VL ans;
	
	for (auto p : primes)
	{
		while (n % p == 0)
		{
			ans.PB(p);
			n /= p;
		}
	}
	queue<LL> q;
	q.push(n);
	
	while (!q.empty())
	{
		LL x = q.front();
		q.pop();
		if (x == 1)
			continue;
		if (millerRabin(x))
			ans.PB(x);
		else
		{
			LL y = rho(x);
			q.push(y);
			q.push(x / y);
		}
	}
	return ans;
}
