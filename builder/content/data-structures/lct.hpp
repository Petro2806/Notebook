/**
 * Description: Link-Cut Tree. 
 * Calculate any path queries. Change \texttt{upd} to maintain what you need. 
 * Don't use \texttt{upd} in \texttt{push}:). Calculate non commutative functions in both ways and swap them in push.
 * \texttt{cnt} -- number of nodes in current splay tree.
 * Don't touch \texttt{rev}, \texttt{sub}, \texttt{vsub}. 
 * \texttt{v->access()} 
 * brings \texttt{v} to the top and pushes it; its left subtree will be 
 * the path from \texttt{v} to the root and its right subtree will be empty. 
 * Only then \texttt{sub} will be the number of nodes in the connected component
 * of \texttt{v} and \texttt{vsub} will be the number of nodes under \texttt{v}.
 * Change upd to calc sum in subtree of other functions.
 * Use \texttt{makeRoot} for arbitrary path queries.
 * Time: O(\log n)
 * Usage: FOR (i, 0, n) LCT[i] = new snode(i); link(LCT[u], LCT[v]);
 */
typedef struct Snode* sn;
struct Snode 
{ 
	sn p, c[2]; // parent, children
	bool rev = false; // subtree reversed or not (internal usage)
	int val, cnt; // value in node, # nodes in splay subtree
	int sub, vsub = 0; // vsub stores sum of virtual children
	
	Snode(int _val): val(_val)
	{
		p = c[0] = c[1] = 0;
		upd();
	}	
	friend int getCnt(sn v)
	{
		return v ? v->cnt : 0;
	}
	friend int getSub(sn v)
	{
		return v ? v->sub : 0;
	}
	void push()
	{
		if (!rev)
			return;
		swap(c[0], c[1]);
		rev = false;
		FOR (i, 0, 2)
			if (c[i])
				c[i]->rev ^= 1;
	}
	void upd()
	{
		FOR (i, 0, 2)
			if (c[i])
				c[i]->push();
		cnt = 1 + getCnt(c[0]) + getCnt(c[1]);
		sub = 1 + getSub(c[0]) + getSub(c[1]) + vsub;
	}
	//////// SPLAY TREE OPERATIONS
	int dir()
	{
		if (!p) return -2;
		FOR (i, 0, 2)
			if (p->c[i] == this)
				return i;
		// p is path-parent pointer
		// -> not in current splay tree
		return -1;
	}
	
	// checks if root of current splay tree
	bool isRoot()
	{
		return dir() < 0;
	}
	friend void setLink(sn p, sn v, int d)
	{
		if (v)
			v->p = p;
		if (d >= 0)
			p->c[d] = v;
	}
	void rot()
	{
		assert(!isRoot());
		int d = dir();
		sn pa = p;
		setLink(pa->p, this, pa->dir());
		setLink(pa, c[d ^ 1], d);
		setLink(this, pa, d ^ 1);
		pa->upd();
	}
	void splay()
	{
		while (!isRoot() && !p->isRoot())
		{
			p->p->push();
			p->push();
			push();
			dir() == p->dir() ? p->rot() : rot();
			rot();
		}
		if (!isRoot())
			p->push(), push(), rot();
		push();
		upd();
	}
	//////// BASE OPERATIONS
	// bring this to top of tree, propagate
	void access()
	{
		for (sn v = this, pre = 0; v; v = v->p)
		{
			v->splay();
			if (pre)
				v->vsub -= pre->sub;
			if (v->c[1])
				v->vsub += v->c[1]->sub;
			v->c[1] = pre;
			v->upd();
			pre = v;
		}
		splay();
		assert(!c[1]);
	}
	void makeRoot()
	{
		access();
		rev ^= 1;
		access();
		assert(!c[0] && !c[1]);
	}
	//////// QUERIES
	friend sn lca(sn u, sn v)
	{
		if (u == v)
			return u;
		u->access();
		v->access();
		if (!u->p)
			return 0;
		u->splay();
		return u->p ? u->p : u;
	}
	friend bool connected(sn u, sn v)
	{
		return lca(u, v);
	}
	//////// MODIFICATIONS
	void set(int v)
	{
		access();
		val = v;
		upd();
	}
	friend void link(sn u, sn v)
	{
		assert(!connected(u, v));
		v->makeRoot();
		u->access();
		setLink(v, u, 0);
		v->upd();
	}
	// cut v from it's parent in LCT
	// make sure about root or better use next function
	friend void cut(sn v)
	{
		v->access();
		assert(v->c[0]); // assert if not a root
		v->c[0]->p = 0;
		v->c[0] = 0;
		v->upd();
	}
	// u, v should be adjacent in tree
	friend void cut(sn u, sn v)
	{
		u->makeRoot();
		v->access();
		assert(v->c[0] == u && !u->c[0] && !u->c[1]);
		cut(v);
	}
};
