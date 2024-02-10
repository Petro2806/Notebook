/**
 * Description: $n = am + b, \frac{n}{m} = a, n \% m = b$.
 * use \_\_gcd instead of gcd.\\
 * If $g = gcd(\dots)$ than $\frac{a_i}{g}$ is the new coordinates with respect to $g$.
 */
LL closest(LL u, LL d)
{
	if(u >= 0)
		return (2 * u + d) / (2 * d);
	return -closest(-u, d);
}
struct num : complex<LL>
{	
	num(LL a, LL b = 0) : complex(a, b) {}
	num(complex a) : complex(a) {}
	num inv()
	{
		return num(real(), -imag());
	}
	num operator/ (num x)
	{
		num prod = *this * x.inv();
		LL D = (x * x.inv()).real();
		
		LL m = closest(prod.real(), D);
		LL n = closest(prod.imag(), D);
	
		return num(m, n);
	}
	num operator% (num x)
	{
		return *this - x * (*this / x);
	}
	bool operator == (num b)
	{
		FOR(it, 0, 4)
		{
			if(real() == b.real() && imag() == b.imag())
				return true;
			b = b * num(0, 1);
		}
		return false;
	}
	bool operator != (num b)
	{
		return !(*this == b);
	}
};
