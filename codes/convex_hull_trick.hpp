struct Line
{
	LL a, b, xLast;
	Line() {}
	Line(LL _a, LL _b): a(_a), b(_b) {}
	bool operator<(const Line& l) const
	{
		return MP(a, b) < MP(l.a, l.b);
	}
	bool operator<(int x) const
	{
		return xLast < x;
	}
	LL getY(int x) const
	{
		return a * x + b;
	}
	LL intersect(const Line& l) const
	{
		assert(a < l.a);
		LL dA = l.a - a, dB = b - l.b, x = dB / dA;
		if (dB < 0 && dB % dA != 0)
			x--;
		return x;
	}
};

struct ConvexHull: set<Line, less<>>
{
	bool needErase(iterator it, const Line& l)
	{
		LL x = it->xLast;
		if (it->getY(x) > l.getY(x))
			return false;
		if (it == begin())
			return it->a >= l.a;
		x = prev(it)->xLast + 1;
		return it->getY(x) < l.getY(x);
	}
	void add(LL a, LL b)
	{
		Line l(a, b);
		auto it = lower_bound(l);
		if (it != end())
		{
			LL x = it == begin() ? -INF : prev(it)->xLast;
			if ((it == begin() || prev(it)->getY(x) >= l.getY(x)) && it->getY(x + 1) >= l.getY(x + 1))
				return;
		}
		while (it != end() && needErase(it, l))
			it = erase(it);
		while (it != begin() && needErase(prev(it), l))
			erase(prev(it));
		if (it != begin())
		{
			auto itP = prev(it);
			Line lIt = *itP;
			lIt.xLast = itP->intersect(l);
			erase(itP);
			if (lIt.xLast > -INF)
			{
				if (lIt.xLast >= INF)
				{
					while (it != end())
						it = erase(it);
					lIt.xLast = INF;
				}
				insert(lIt);
			}
		}
		l.xLast = it == end() ? INF : l.intersect(*it);
		assert(l.xLast <= INF);
		insert(l);
 	}
	LL getMaxY(LL x)
	{
		return lower_bound(x)->getY(x);
	}
};
