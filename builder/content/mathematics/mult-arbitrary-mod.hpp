/**
 * Description: Multiplies polynomials modulo arbitrary mod.
 * Add the modulo parameter to the modular arithmetics functions (int add(int a, int b, int m = mod)).
 * Add the parameters to fft function: void fft(VI\& a, bool inv, int nttMod, int LEN, int GEN, int IGEN).
 * LEN, GEN, IGEN will not be constants anymore.
 * You must add nttMod inside the fft function 8 times in 7 lines of code.
 * Add the parameters to the original mult function: VI mult(VI a, VI b, int nttMod, int LEN, int GEN, int IGEN).
 * You must add nttMod inside the original mult function 4 times in 4 lines of code.
 */
VI mult(const VI& a, const VI& b)
{
	if (a.empty() || b.empty())
		return {};
	const int mods[3] = {754974721, 897581057, 998244353};
	const int lens[3] = {1 << 24, 1 << 23, 1 << 23};
	const int gens[3] = {362, 45, 31};
	
	vector fa(3, VI(SZ(a))), fb(3, VI(SZ(b)));
	vector<VI> c(3);
	FOR(i, 0, 3)
	{
		FOR(j, 0, SZ(a))
			fa[i][j] = a[j] % mods[i];
		FOR(j, 0, SZ(b))
			fb[i][j] = b[j] % mods[i];
		c[i] = mult(fa[i], fb[i], mods[i], lens[i], gens[i], binpow(gens[i], mods[i] - 2, mods[i]));
	}
	__int128 modsProd = (__int128)mods[0] * mods[1] * mods[2];
	VI res(SZ(a) + SZ(b) - 1);
	FOR(i, 0, SZ(res))
	{
		res[i] = (((__int128)mods[1] * mods[2] * mult(59724183, c[0][i], mods[0])
			+ (__int128)mods[2] * mods[0] * mult(127597251, c[1][i], mods[1])
			+ (__int128)mods[0] * mods[1] * mult(777368488, c[2][i], mods[2])) % modsProd) % mod;
	}
	return res;
}
