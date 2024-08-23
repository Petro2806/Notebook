/**
 * Description: Finds faces in a planar graph.
 * Use \texttt{addVertex()} and \texttt{addEdge()} for initializing the graph
 * and \texttt{addQueryPoint()} for initializing the queries.
 * After initialization, call \texttt{findFaces()} before using other functions.
 * \texttt{getIncidentFaces(i)} returns the pair of faces $(u, v)$ (possibly $u = v$)
 * such that the $i$-th edge lies on the boundary of these faces.
 * \texttt{getFaceOfQueryPoint(i)} returns the face where the $i$-th query point lies.
 */
namespace PlanarGraph
{
struct IndexedPt
{
	Pt p;
	int index;
	bool operator<(const IndexedPt& q) const
	{
		return p.x < q.p.x;
	}
};
struct Edge
{
	// cross(vertices[j].p - vertices[i].p, l.n) > 0
	int i, j;
	Line l;
};
vector<IndexedPt> vertices, queryPoints;
vector<Edge> edges;
struct Comparator
{
	using is_transparent = void;
	static IndexedPt vertex;
	db getY(const Line& l) const
	{
		return -(l.n.x * vertex.p.x + l.c) / l.n.y;
	}
	bool operator()(int i, int j) const
	{
		auto [u1, v1, l1] = edges[i];
		auto [u2, v2, l2] = edges[j];
		if (u1 == vertex.index && u2 == vertex.index)
			return sgn(cross(l1.n, l2.n)) > 0;
		if (v1 == vertex.index && v2 == vertex.index)
			return sgn(cross(l1.n, l2.n)) < 0;
		int dy = sgn(getY(l1) - getY(l2));
		assert(dy != 0);
		return dy < 0;
	}
	bool operator()(int i, const Pt& p) const
	{
		int dy = sgn(getY(edges[i].l) - p.y);
		assert(dy != 0);
		return dy < 0;
	}
} comparator;
IndexedPt Comparator::vertex;
DSU dsu;
VI upperFace, queryAns;

void addVertex(const Pt& p)
{
	vertices.PB({p, SZ(vertices)});
}
void addEdge(int i, int j, const Line& l)
{
	assert(0 <= i && i < SZ(vertices));
	assert(0 <= j && j < SZ(vertices));
	assert(i != j);
	assert(vertices[i].index == i);
	assert(vertices[j].index == j);
	edges.PB({i, j, l});
}
void addEdge(int i, int j)
{
	addEdge(i, j, {vertices[i].p, vertices[j].p});
}
void addQueryPoint(const Pt& p)
{
	queryPoints.PB({p, SZ(queryPoints)});
}
void findFaces()
{
	int n = SZ(vertices), m = SZ(edges);
	const db ROT_ANGLE = 4;
	for (auto& p : vertices)
		p.p = rot(p.p, ROT_ANGLE);
	for (auto& p : queryPoints)
		p.p = rot(p.p, ROT_ANGLE);
	vector<VI> edgesL(n), edgesR(n);
	FOR(k, 0, m)
	{
		auto& [i, j, l] = edges[k];
		l.n = rot(l.n, ROT_ANGLE);
		if (vertices[i].p.x > vertices[j].p.x)
		{
			swap(i, j);
			l.n = l.n * (-1);
			l.c *= -1;
		}
		edgesL[j].PB(k);
		edgesR[i].PB(k);
	}
	sort(ALL(vertices));
	sort(ALL(queryPoints));
	// when choosing INF, remember that we rotate the plane
	addVertex({-INF, INF});
	addVertex({INF, INF});
	addEdge(n, n + 1);
	dsu.init(m + 1);
	set<int, Comparator> s;
	s.insert(m);
	upperFace.resize(m);
	int ptr = 0;
	queryAns.resize(SZ(queryPoints));
	for (const IndexedPt& vertex : vertices)
	{
		int i = vertex.index;
		while (ptr < SZ(queryPoints)
			&& (i >= n || queryPoints[ptr] < vertex))
		{
			const auto& [pt, j] = queryPoints[ptr++];
			Comparator::vertex = {pt, -1};
			queryAns[j] = *s.lower_bound(pt);
		}
		if (i >= n)
			break;
		Comparator::vertex = vertex;
		int upper = -1, lower = -1;
		if (!edgesL[i].empty())
		{
			sort(ALL(edgesL[i]), comparator);
			auto it	= s.lower_bound(edgesL[i][0]);
			lower = edgesL[i][0];
			for (int e : edgesL[i])
			{
				assert(*it == e);
				assert(next(it) != s.end());
				upperFace[e] = *next(it);
				it = s.erase(it);
			}
			assert(it != s.end());
			upper = *it;
		}
		if (!edgesR[i].empty())
		{
			sort(ALL(edgesR[i]), comparator);
			if (upper == -1)
			{
				upper =	*s.lower_bound(edgesR[i][0]);
			}
			int prv = -1;
			for (int e : edgesR[i])
			{
				s.insert(e);
				if (prv != -1)
				{
					upperFace[prv] = e;
				}
				prv = e;
			}
			upperFace[edgesR[i].back()] = upper;
			dsu.unite(edgesL[i].empty() ? upper : lower, edgesR[i][0]);
		}
		else if (lower != -1 && upper != -1)
		{
			dsu.unite(upper, lower);
		}
	}
}
PII getIncidentFaces(int i)
{
	return {dsu.find(i), dsu.find(upperFace[i])};
}
int getFaceOfQueryPoint(int i)
{
	return dsu.find(queryAns[i]);
}
};
