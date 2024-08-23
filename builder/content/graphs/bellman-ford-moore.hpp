/**
 * Description: Computes shortest paths from a single source vertex to all of the other vertices in a weighted directed graph.
 * Time: O(n m)
 */
VL spfa(const vector<vector<pair<int, LL>>>& g, int n, int s)
{
	VL dist(n, LINF);
	dist[s] = 0;
	queue<int> q;
	q.push(s);
	VI inQueue(n);
	inQueue[s] = true;
	VI cnt(n);
	bool negCycle = false;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		cnt[v]++;
		negCycle |= cnt[v] > n;
		inQueue[v] = false;
		for (auto [to, w] : g[v])
		{
			LL newDist = dist[v] + w;
			if (newDist < dist[to])
			{
				dist[to] = newDist;
				if (!inQueue[to])
				{
					q.push(to);
					inQueue[to] = true;
				}
			}
		}
		if (negCycle)
			break;
	}
	return dist;
}
