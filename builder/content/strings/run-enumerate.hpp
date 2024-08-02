/**
 * Description: Enumerate all tuples $(len, l, r)$ with minimum period of $s[l, r)$ is $len$, and $r - l \ge 2 \cdot len$. 
 * Also $l$ and $r$ are maximal, that tuples $(len, l - 1, r)$ and $(len, l, r + 1)$ do not satisfy privious condition.
 * 
 * Number of the runs is $\le |s|$. Other properties at the end of the function.
 * Time: $O(nlogn)$, where $n = |s|$.
 */
struct run
{
	int len, l, r;
	bool operator<(const run& p) const
	{
		if(len != p.len) 
			return len < p.len;
		if(l != p.l) 
			return l < p.l;
		return r < p.r;
	}
	bool operator==(const run& p) const
	{
		return !(*this < p) && !(p < *this);
	}
};
vector<run> runEnumerate(VI s) 
{
	int n = SZ(s);
	LCP lcp(s); reverse(ALL(s));
	LCP rev(s); reverse(ALL(s));
	
	vector<run> runs;
	FOR(inv, 0, 2)
	{
		VI st = {n};
		auto pop = [&](int i)
		{
			int j = st.back();
			int dist = j - i;
			int distPrev = st[SZ(st) - 2] - j;
			int distMn = min(dist, distPrev);
			
			int len = lcp.queryLcp(i, j);
			if((len >= distMn && dist < distPrev) || 
				(len < distMn && ((s[i + len] < s[j + len]) ^ inv)))
				return true;
			return false;
		};
		
		RFOR(i, n, 0)
		{
			while (SZ(st) > 1 && pop(i))
				st.pop_back();
			int j = st.back();
			int dist = j - i;
			st.PB(i);
			
			int x = rev.queryLcp(n - i, n - j);
			int y = lcp.queryLcp(i, j);
			if (x < dist && x + y >= dist) 
				runs.push_back({dist, i - x, j + y});
		}
	}
	sort(runs.begin(), runs.end());
	runs.resize(unique(ALL(runs)) - runs.begin());
	
	//LL sumLen = 0, sumCnt = 0, sum = 0;
	//for(auto [len, l, r] : runs)
	//	sumLen += len, sumCnt += (r - l) / len, sum += r - l;
	//assert(SZ(runs) <= SZ(s));
	//assert(sumLen <= LOG * SZ(s));
	//assert(sumCnt <= 2 * SZ(s));
	//assert(sum <= 2 * LOG * SZ(s));
    return runs;
}
