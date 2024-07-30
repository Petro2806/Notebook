int lowerBound(LL x)
{
	LL sum = 0;
	int i = -1;
	int lg = 31 - __builtin_clz(n);
	while (lg >= 0)
	{
		int j = i + (1 << lg);
		if (j < n && sum + t[j] < x)
		{
			sum += t[j];
			i = j;
		}
		lg--;
	}
	return i + 1;
}
