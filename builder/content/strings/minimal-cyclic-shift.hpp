/**
 * Description: $s_{shift}, s_{shift + 1}, \dots$ is lexicographically smallest cyclic shift. 
 * If more than one answer it finds the minimum value of $shift$.
 * Time: $O(n)$ time and memory complexity.
 */

int minimalCyclicShift(VI s)
{
	int n = SZ(s);
	s.resize(2 * n);
	FOR(i, 0, n)
		s[n + i] = s[i];
		
	int shift = 0;
	VI f(2 * n);
	FOR(i, 1, 2 * n)
	{
		int j = f[i - 1 - shift];
		while(j > 0 && s[shift + j] != s[i])
		{
			if(s[shift + j] > s[i])
				shift = i - j;
			j = f[j - 1];
		}
		if(j == 0 && s[shift] != s[i])
		{
			if(s[shift] > s[i])
				shift = i;
		}
		else
			j++;
		f[i - shift] = j;
	}
	return shift;
}
