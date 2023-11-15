int dfsSZ(int v, int par = -1)
{
	sz[v] = 1;
	for (auto to : g[v])
	{
		if (to != par && !usedC[to])
			sz[v] += dfsSZ(to, v);
	}
	return sz[v];
}

void build(int cent)
{
	dfsSZ(cent, -1);
	int szAll = sz[cent];
	int pr = cent;
	while (true)
	{
		int v = -1;
		for (auto to : g[cent])
		{
			if (to == pr || usedC[to]) 
				continue;
			if (sz[to] * 2 > szAll)
			{
				v = to;
				break;
			}
		}
		if (v == -1)
			break;
		pr = cent;
		cent = v;
	}
	usedC[cent] = true;
	
	// here calculate f(cent)
		
	for (auto to : g[cent])
	{
		if (!usedC[to])
		{
			build(to);
		}
	}
}
