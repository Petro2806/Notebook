/**
 * Description: d1[i] - half-length of odd length palindrome with center in i.
 * d2[i] - half-length of even length palindrome if i is right center of it.
 * 
 **/

int d1[N], d2[N];

void manacher(const string& s)
{
    int n = SZ(s);
    int l = -1;
    int r = -1;
    FOR (i, 0, n)
    {
        if (i <= r)
            d1[i] = min(r - i + 1, 
            	d1[l + (r - i)]);
        while (i + d1[i] < n && i - d1[i] >= 0 
        	&& s[i + d1[i]] == s[i - d1[i]])
						d1[i]++;
        if (i + d1[i] - 1 > r)
        {
            r = i + d1[i] - 1;
            l = i - (d1[i] - 1);
        }
    }
    l = -1;
    r = -1;
    FOR (i, 0, n)
    {
        if (i <= r)
            d2[i] = min(r - i + 1, 
            	d2[l + (r - i) + 1]);
        while (i + d2[i] < n 
        	&& i - (d2[i] + 1) >= 0 
        	&& s[i + d2[i]] == s[i - (d2[i] + 1)])
						d2[i]++; 
        if (i + d2[i] > r)
        {
            r = i + d2[i] - 1;
            l = i - d2[i];
        }
    }
}
