/**
 * Description: Multiplies polynomials modulo arbitrary \texttt{mod} (or without modulo).
 * Add the modulo parameter to the modular arithmetics functions (\texttt{int add(int a, int b, int m = mod)}).
 * \texttt{LEN} must be $2^{24}$.
 * Change signature of the fft function into \texttt{void fft(VI\& a, bool inverse, int nttMod, int GEN)}.
 * \texttt{GEN} will not be a constant anymore.
 * You must add \texttt{nttMod} inside the \texttt{fft} function 10 times in 8 lines of code.
 * Change signature of the original \texttt{mult} function into \texttt{VI mult(VI a, VI b, int nttMod, int GEN)}.
 * You must add \texttt{nttMod} inside the original \texttt{mult} function 4 times in 4 lines of code.
 */
VI mult(const VI& a, const VI& b)
{
	int n = SZ(a), m = SZ(b);
	if (n == 0 || m == 0)
		return {};
	const int mods[3] = {754974721, 167772161, 469762049};
	const int invs[3] = {190329765, 58587104, 187290749};
	const int gens[3] = {362, 2, 40};
	vector<VI> fa(3, VI(n)), fb(3, VI(m));
	vector<VI> c(3);
	FOR(i, 0, 3)
	{
		FOR(j, 0, n)
			fa[i][j] = a[j] % mods[i];
		FOR(j, 0, m)
			fb[i][j] = b[j] % mods[i];
		c[i] = mult(fa[i], fb[i], mods[i], gens[i]);
	}
	__int128 modsProd = (__int128)mods[0] * mods[1] * mods[2];
	VI res(n + m - 1);
	FOR(i, 0, n + m - 1)
	{
		__int128 cur = 0;
		FOR(j, 0, 3)
		{
			cur += (__int128)mods[(j + 1) % 3] * mods[(j + 2) % 3]
				* mult(invs[j], c[j][i], mods[j]);
		}
		res[i] = cur % modsProd % mod;
	}
	return res;
}
