const db phi = (3. - sqrt(5.0)) / 2.;
db get(db L, db R)
{
	db M1, M2, v1, v2;
	M1 = L + (R - L) * phi;
	M2 = R - (R - L) * phi;
	v1 = f(M1);
	v2 = f(M2);
	FOR (i, 0, 74)
	{
 	   	if (v1 > v2) // for minimum
		{
			L = M1;
			M1 = M2;
			v1 = v2;
			M2 = R - (R - L) * phi;
			v2 = f(M2);
		}
		else
		{
			R = M2;
			M2 = M1;
			v2 = v1;
			M1 = L + (R - L) * phi;
			v1 = f(M1);
		}
	}
	return L; // or f(L);
}
