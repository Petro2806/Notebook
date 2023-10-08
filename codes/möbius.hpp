void mobius()
{
	fill(pr, pr + N, 1);
	fill(mu, mu + N, 1);
	pr[1] = false;
	FOR (i, 2, N)
	{
		if (!pr[i]) 
			continue;
		mu[i] = mod - 1;
		for (int j = 2 * i; j < N; j += i)
		{
			pr[j] = false;
			if (j % (i * i) == 0) 
				mu[j] = 0;
			mu[j] = mult(mu[j], mod - 1);
		}
	}
}
