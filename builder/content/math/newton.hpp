VI newton(VI a, int k)
{
	//c_n= a_n + sum(i = 0, n - 1) c_i * c_(n-1-i)
	//Q = A + x * Q * Q
	//F(Q) = Q - x * Q * Q - A
	//F'(Q) = 1 - 2 * x * Q	
	
	
	VI Qk = {a[0]};
	int pw = 1;
	while(pw <= k)
	{
		assert(SZ(Qk) == pw);
		pw *= 2;
		
		VI F1(pw); 		
		F1[0] = 1;
		FOR(i, 0, pw / 2)
			F1[i + 1] = sub(0, mult(2, Qk[i]));
		//F' = 1 - 2 * x * Q
		

		VI F = mult(Qk, Qk);
		F.resize(pw);
		RFOR(i, pw, 1)
			F[i] = sub(0, F[i - 1]);
		F[0] = 0; // F = -x * Q*Q
			
		FOR(i, 0, pw / 2)
			F[i] = add(F[i], Qk[i]);
			//F = Q - x * Q * Q
		FOR(i, 0, min(pw, SZ(a)))
			F[i] = sub(F[i], a[i]);
			//F = Q - x * Q * Q - A
		
			
		F = mult(F, inverse(F1, pw));
		F.resize(pw);
		
		FOR(i, 0, pw)
			F[i] = sub(0, F[i]);//-F/F'
		FOR(i, 0, pw / 2)
			F[i] = add(F[i], Qk[i]);//Q - F/F'		

		//new Qk = Qk - F(Qk) / F'(Qk) mod(x ^ pw)
		Qk = F;
	}
	Qk.resize(k);
	return Qk;
}
