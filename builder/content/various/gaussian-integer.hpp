/**
 * Description: Works for int.
 *
 */
LL closest(LL u, LL d)
{
	if(2 * u + d >= 0)
		return (2 * u + d) / (2 * d);
	return -((-2 * u + d) / (2 * d));	
}
struct num : complex<LL>
{	
	num(LL a, LL b = 0) : complex(a, b) {}
	num(complex a) : complex(a) {}
	num inv()
	{
		return num(real(), -imag());
	}
	num operator% (num x)
	{
		num prod = *this * x.inv();
		LL D = (x * x.inv()).real();
		
		LL m = closest(prod.real(), D);
		LL n = closest(prod.imag(), D);
	
		return *this - x * num(m, n);
	}
	bool operator != (num b)
	{
		FOR(it, 0, 4)
		{
			if(real() == b.real() && imag() == b.imag())
				return false;
			b = b * num(0, 1);
		}
		return true;
	}
};

