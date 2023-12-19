vector<Pt> vertices;

struct Edge
{
	// cross(vertices[j] - vertices[i], l.n) > 0
	int i, j;
	Line l;
	Edge(int _i, int _j, const Line& _l):
		i(_i), j(_j), l(_l)
	{
		assert(0 <= i && i < SZ(vertices));
		assert(0 <= j && j < SZ(vertices));
		assert(i != j);
	}
	Edge(int _i, int _j): Edge(_i, _j,
		{vertices[_i], vertices[_j]}) {}
};

vector<Edge> edges;

struct Comparator
{
	static int vertexIdx;
	db getY(const Line& l) const
	{
		return -(l.n.x * vertices[vertexIdx].x
			+ l.c) / l.n.y;
	}
	bool operator()(int i, int j) const
	{
		auto [u1, v1, l1] = edges[i];
		auto [u2, v2, l2] = edges[j];
		if (u1 == vertexIdx && u2 == vertexIdx)
			return sgn(cross(l1.n, l2.n)) > 0;
		if (v1 == vertexIdx && v2 == vertexIdx)
			return sgn(cross(l1.n, l2.n)) < 0;
		int dy = sgn(getY(l1) - getY(l2));
		assert(dy != 0);
		return dy < 0;
	}
};
int Comparator::vertexIdx;

DSU dsu;

// Returns the dual graph to the planar graph
// given by `vertices` and `edges`. Vertex
// `dsu.find(i)` in the dual graph corresponds to
// the face under `edges[i]`
vector<unordered_set<int>> buildDualGraph()
{
	const db ROT_ANGLE = 4;
	int n = SZ(vertices), m = SZ(edges);
	for (Pt& p : vertices)
		p = rot(p, ROT_ANGLE);
	VI idxesVertices(n), invIdxes(n);
	iota(ALL(idxesVertices), 0);
	sort(ALL(idxesVertices), [](int i, int j)
	{
		return vertices[i].x < vertices[j].x;
	});
	vector<Pt> sortedVertices(n);
	FOR(i, 0, n)
	{
		sortedVertices[i] =
			vertices[idxesVertices[i]];
		invIdxes[idxesVertices[i]] = i;
	}
	vertices = sortedVertices;
	vector<VI> edgesL(n), edgesR(n);
	FOR(k, 0, m)
	{
		auto& [i, j, l] = edges[k];
		i = invIdxes[i];
		j = invIdxes[j];
		l.n = rot(l.n, ROT_ANGLE);
		if (i > j)
		{
			swap(i, j);
			l.n = l.n * (-1);
			l.c *= -1;
		}
		edgesL[j].PB(k);
		edgesR[i].PB(k);
	}
	vertices.PB({-INF, INF});
	vertices.PB({INF, INF});
	edges.PB({n, n + 1});
	dsu.init(m + 1);
	set<int, Comparator> s;
	s.insert(m);
	vector<PII> edgesDual;
	FOR(i, 0, n)
	{
		Comparator::vertexIdx = i;
		Comparator comparator;
		int upper = -1, lower = -1;
		if (!edgesL[i].empty())
		{
			assert(i > 0);
			sort(ALL(edgesL[i]), comparator);
			auto it	=
				s.lower_bound(edgesL[i][0]);
			lower = edgesL[i][0];
			for (int e : edgesL[i])
			{
				assert(*it == e);
				assert(next(it) != s.end());
				edgesDual.PB({e, *next(it)});
				it = s.erase(it);
			}
			assert(it != s.end());
			upper = *it;
		}
		if (!edgesR[i].empty())
		{
			assert(i + 1 < n);
			sort(ALL(edgesR[i]), comparator);
			if (upper == -1)
			{
				upper =
					*s.lower_bound(edgesR[i][0]);
			}
			int prv = -1;
			for (int e : edgesR[i])
			{
				s.insert(e);
				if (prv != -1)
					edgesDual.PB({e, prv});
				prv = e;
			}
			edgesDual.PB({upper,
				edgesR[i].back()});
			dsu.unite(edgesL[i].empty() ? upper :
				lower, edgesR[i][0]);
		}
		else
		{
			assert(upper != -1 && lower != -1);
			dsu.unite(upper, lower);
		}
	}
	vector<unordered_set<int>> dualGraph;
	dualGraph.resize(m + 1);
	for (auto& [u, v] : edgesDual)
	{
		u = dsu.find(u);
		v = dsu.find(v);
		dualGraph[u].insert(v);
		dualGraph[v].insert(u);
	}
	return dualGraph;
}
