int gcd(int a, int b, int& x, int& y)
{
	x = 1, y = 0;
	int x2 = 0, y2 = 1;
	while (b)
	{
		int k = a / b;
		x -= k * x2;
		y -= k * y2;
		a %= b;
		swap(a, b);
		swap(x, x2);
		swap(y, y2);
	}
	return a;
}
