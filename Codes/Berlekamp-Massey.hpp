
vector<int> berlekampMassey(vector<int> x)
{
  vector<int> ls, cur;
  int lf = 0, ld = 0;
  FOR(i, 0, SZ(x))
  {
    int t = 0;
    FOR(j, 0, SZ(cur))
    {
      updAdd(t, mult(x[i - j - 1], cur[j]));
    }
    if (t == x[i])
      continue;
    if (cur.empty())
    {
      cur.resize(i + 1);
      lf = i;
      ld = sub(t, x[i]);
      continue;
    }
    int k = mult(sub(t, x[i]), binPow(ld, mod - 2));
    vector<int> c(i - lf - 1);
    c.push_back(k);
    for (auto const &j : ls)
    {
      int curr = mult(sub(0, j), k);
      c.push_back(curr);
    }
    if (c.size() < cur.size())
      c.resize(cur.size());
    FOR(j, 0, SZ(cur))
    {
      updAdd(c[j], cur[j]);
    }
    if (i - lf + ls.size() >= cur.size())
    {
		ls = cur;
		lf = i;
		ld = sub(t, x[i]);
    }
    cur = c;
  }
  return cur;
}
