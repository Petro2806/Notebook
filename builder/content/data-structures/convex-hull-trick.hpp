/**
 * Description: $\text{add}(a, b)$ adds a straight line $y = a x + b$.
 * \texttt{getMaxY(p)} finds the maximum $y$ at $x = p$.
 **/
 
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
	__int128 getY(__int128 x) const
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
			LL x = it == begin() ? -LINF : 
					prev(it)->xLast;
			if ((it == begin() 
				|| prev(it)->getY(x) >= l.getY(x)) 
				&& it->getY(x + 1) >= l.getY(x + 1))
				return;
		}
		while (it != end() && needErase(it, l))
			it = erase(it);
		while (it != begin() && needErase(prev(it), l))
			erase(prev(it));
		if (it != begin())
		{
			auto itP = prev(it);
			Line itL = *itP;
			itL.xLast = itP->intersect(l);
			erase(itP);
			insert(itL);
		}
		l.xLast = it == end() ? LINF : l.intersect(*it);
		insert(l);
 	}
	LL getMaxY(LL p)
	{
		return lower_bound(p)->getY(p);
	}
};
