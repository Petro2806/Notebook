#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define RFOR(i, a, b) for(int i = (a) - 1; i >= (b); i--)
#define SZ(a) int(a.size())
#define ALL(a) a.begin(), a.end()
#define PB push_back
#define MP make_pair
#define F first
#define S second

typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef double db;



#include "../builder/content/math/gcd.hpp"
#include "../builder/content/math/fast-chinese.hpp"
#include "../builder/content/math/chinese.hpp"

namespace Algotester
{
	LL Mult(LL a, LL b, LL mod)
	{
		return (__int128) a * b % mod;
	}
	LL Bpow(LL a, LL n, LL mod)
	{
		LL res = 1;
		while(n)
		{
			if(n & 1)
				res = Mult(res, a, mod);
			a = Mult(a, a, mod);
			n /= 2;
		}
		return res;
	}
	LL Phi(LL n)
	{
		LL res = n;
		for(LL p = 2; p * p <= n; p++)
		{
			if(n % p != 0)
				continue;
			res -= res / p;
			while(n % p == 0)
				n /= p;
		}
		if(n != 1)
			res -= res / n;
		return res;
	}
	LL Chinese2(vector<LL> A, vector<LL> P)
	{
		int N = SZ(A);
		bool ok = 1;
		LL aa = P[0];
		LL bb = A[0];
		FOR(j, 1, N)
		{
			LL b = (A[j] - bb % P[j] + P[j]) % P[j];
			LL a = aa % P[j];
			LL c = P[j];
			LL g = gcd(a , c);
			if (b % g != 0)
			{
				ok = 0;
				break;
			}
			a /= g;
			b /= g;
			c /= g;
			b = Mult(b, Bpow(a , Phi(c) - 1, c), c);
			bb = aa * b + bb;
			aa = aa * c;
		}
		if (ok)
		{
			LL res = bb;
			return res;
		}
		else	
			//cout<<"No solutions"<<endl;
			return -1;
	}
};

mt19937 rng(47);

LL rand(LL l, LL r)
{
	return rng() % (r - l) + l;
}

void testFast()
{
	LL A = 10000;
	LL B = 10000000000000LL;
	LL C = 100LL;
	LL D = 10000000000LL;
	
	FOR(i, 0, A)
	{
		LL n = rand(0, B);
		
		int sz = rand(1, C);
		vector<LL> ost(sz), mod(sz);
		LL lcm = 1;
		FOR(j, 0, sz)
		{
			mod[j] = rand(1, D);
			ost[j] = n % mod[j];
			
			__int128 val = lcm * (__int128) (mod[j] / gcd(lcm, mod[j]));
			if(val > 1e18)
			{
				sz = j;
				ost.resize(sz);
				mod.resize(sz);
				break;
			}
			lcm = lcm * (mod[j] / gcd(lcm, mod[j]));
		}
		LL AT = Algotester::Chinese2(ost, mod);
		LL FST = fastChinese(ost, mod);
		//cout << n << " " << AT << " " << ST << " " << lcm << " " << n % lcm << endl;
		
		n %= lcm;
		
		assert(AT == n);
		assert(FST == n);
	}	
}
void testIntP()
{
	LL A = 10000;
	LL B = 10000000000000LL;
	LL C = 100LL;
	LL D = 100000000LL;
	
	FOR(i, 0, A)
	{
		LL n = rand(0, B);
		
		int sz = rand(1, C);
		vector<int> ost(sz), mod(sz);
		vector<LL> ostLL(sz), modLL(sz);
		LL lcm = 1;
		FOR(j, 0, sz)
		{
			mod[j] = modLL[j] = rand(1, D);
			ost[j] = ostLL[j] = n % mod[j];
			
			__int128 val = lcm * (__int128) (mod[j] / gcd(lcm, mod[j]));
			if(val > 1e18)
			{
				sz = j;
				ost.resize(sz);
				mod.resize(sz);
				ostLL.resize(sz);
				modLL.resize(sz);
				break;
			}
			lcm = lcm * (mod[j] / gcd(lcm, mod[j]));
		}
		LL AT = Algotester::Chinese2(ostLL, modLL);
		LL ST = chinese(ost, mod);
		LL FST = fastChinese(ostLL, modLL);
		
		n %= lcm;
		
		assert(AT == n);
		assert(ST == n);
		assert(FST == n);
	}	
}


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	

	
	
	



	return 0;
}
