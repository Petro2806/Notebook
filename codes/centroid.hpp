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
			if (to == pr || usedc[to]) 
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
	usedc[cent] = true;
		
	for (auto to : g[cent])
	{
		if (!usedc[to])
		{
			build(to);
		}
	}
}
