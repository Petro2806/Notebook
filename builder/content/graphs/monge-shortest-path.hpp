/**
 * Description: Finds shortest paths from the vertex $0$ to all vertices in a DAG with $n$ vertices,
 * where the edges weights $c(i, j)$ satisfy the Monge property:
 * $\forall i, j, k, l, \quad 0 \le i < j < k < l < n \implies c(i, l) + c(j, k) \ge c(i, k) + c(j, l)$.
 * Time: O(n \log n)
 */

template<typename F>
VL mongeShortestPath(int n, const F& cost)
{
	VL dist(n, LINF);
	VI amin(n);
	dist[0] = 0;
	
	auto update = [&](int i, int k)
	{
		LL nd = dist[k] + cost(k, i);
		if (nd < dist[i])
		{
			dist[i] = nd;
			amin[i] = k;
		}
	};
	
	function<void(int, int)> solve = [&](int l, int r)
	{
		if (r - l == 1)
			return;
		int m = (l + r) / 2;
		FOR(k, amin[l], min(m, amin[r] + 1))
			update(m, k);
		solve(l, m);
		FOR(k, l + 1, m + 1)
			update(r, k);
		solve(m, r);
	};
	
	update(n - 1, 0);
	solve(0, n - 1);
	return dist;
}
