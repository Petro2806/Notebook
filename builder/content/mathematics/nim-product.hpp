/**
 * Description: The Nim sum $\oplus$: $a \oplus b := \text{mex} (\{a' \oplus b | a' < a\} \cup \{a \oplus b' | b' < b\})$.
 * The Nim product $\otimes$: $a \otimes b := \text{mex} \{(a' \otimes b) \oplus (a \otimes b') \oplus (a' \otimes b') | a' < a, b' < b\}$.
 * Let $A$ be the set consisting of integers between $0$ (inclusive) and $2^{2^n}$ (exclusive) (where $n$ is an integer).
 * Then the algebraic structure whose addition is $\oplus$ and multiplication is $\otimes$ forms a field. Such a field is called \textbf{Nimber}.
 */
typedef unsigned long long ULL;

const int S = 8;

ULL small[1 << S][1 << S];

template <bool isPre = false>
ULL nimProduct(ULL a, ULL b, int p = 64)
{
	if (min(a, b) <= 1)
		return a * b;
	if (!isPre && p <= S)
		return small[a][b];
	p >>= 1;
	ULL a1 = a >> p, a2 = a & ((1ULL << p) - 1);
	ULL b1 = b >> p, b2 = b & ((1ULL << p) - 1);
	ULL c = nimProduct<isPre>(a1, b1, p);
	ULL d = nimProduct<isPre>(a2, b2, p);
	ULL e = nimProduct<isPre>(a1 ^ a2, b1 ^ b2, p);
	return nimProduct<isPre>(c, 1ULL << (p - 1), p) ^ d ^ ((d ^ e) << p);
}

void init()
{
	FOR(i, 0, 1 << S)
		FOR(j, 0, 1 << S)
			small[i][j] = nimProduct<true>(i, j, S);
}
