uses Crt;

type
	MatrType = array[1..3, 1..3] of Real;     
	VectorType = array[1..3] of Real;        

const
	
	MyMatr:MatrType =
		((1, 2, -1),
		(3, 0, 2),
		(4, -2, 5));

	
	EM:MatrType =
		((1, 0, 0),
		(0, 1, 0),
		(0, 0, 1));
	
	N : integer = 3;

function F(X : Real; P : VectorType) : Real;
begin
	F := (-1) * (Sqr(X) * X - P[1] * Sqr(X) - P[2] * X - P[3]);
end;

function dF(X : Real; P : VectorType) : Real;
begin
	dF := (-1) * (3 * Sqr(X) - 2 * P[1] * X - P[2]);
end;

procedure MxM(A, B : MatrType; var X : MatrType);
var
	i, j, k : integer;
	s : real;
begin
	for i := 1 to N do
		for j := 1 to N do
		begin
			S := 0;
			for k := 1 to N do
				s := s + A[i, k] * B[k, j];
			X[i, j] := s;
		end;
end;

procedure MxV(A: MatrType; V: VectorType; var X: VectorType);
var
	i, j : integer;
	s : real;
begin
	for i := 1 to N do
	begin
		s := 0;
		for j := 1 to N do
			s := s + A[i, j] * v[j];
		X[i] := s;
	end;
end;

procedure Lab3(Matr : MatrType; var L : VectorType; var X, Ax, Lx : MatrType);
var
	i, j, k, h : integer;   	
	P : MatrType;        		
	Pvec : VectorType;   		
	A, B, A1, B1 : real;    	
	E : real;            		
	lam0, lam1 : real;    		
	S : MatrType;        		
	M, M1 : MatrType;     		
	Yi : VectorType;     		
	Xi : VectorType;      		
	Axi, Lxi : VectorType; 		

	procedure Frob(A : MatrType; Num : integer);
	var i, j : integer;
	begin
		if Num - 1 > 0 then
		begin
	
			M := EM;
			M1 := EM;
			for i := 1 to N do
			begin
				
				if i = Num - 1 then
					M[Num - 1, i] := 1 / A[Num, Num - 1]
				else
					M[Num - 1, i] := -A[Num, i] / A[Num, Num - 1];
				
				M1[Num - 1, i] := A[Num, i];
			end;

			
			MxM(S, M, S);
			
			MxM(A, M, A);
			MxM(M1, A, A);
			P := A;
			Frob(A, Num - 1);
		end;
	end;

	begin
		clrscr;
		
		S := EM;
		Frob(Matr, N);

		for i := 1 to N do
			Pvec[i] := P[1, i];

		A := -5; B := 5;                   
		h := 10;                         
		E := 0.0001;                     
		j := 1;

		for i := 0 to h do
		begin
			A1 := A + (i + 0) * (B - A) / h;
			B1 := A + (i + 1) * (B - A) / h;
		
			if F(A1, Pvec) * F(B1, Pvec) < 0 then
			begin
				
				lam1 := (A1 + B1) / 2;
				repeat
					lam0 := lam1;
					lam1 := lam0 - F(lam0, Pvec) / dF(lam0, Pvec);
				until Abs(lam1 - lam0) < E;
				
				L[j] := lam1;
				j := j + 1;
			end;
		end;
		
		for i := 1 to N do
		begin
			
			Yi[N] := 1;
			for j := N - 1 downto 1 do
				Yi[j] := L[i] * Yi[j + 1];
			
			MxV(S, Yi, Xi);
			for j := 1 to N do
				X[i, j] := Xi[j];
			
			MxV(Matr, Xi, Axi);
			for j := 1 to N do 
			begin
				Ax[i, j] := Axi[j];
				Lx[i, j] := L[i] * Xi[j];
			end;
		
		end;

	end;

var
	X : MatrType;     
	L : VectorType;   
	Ax, Lx : MatrType;
	i, j : Integer;
begin
	N := 3;
	Lab3(MyMatr, L, X, Ax, Lx); 
	
	WriteLn('‘®ЎбвўҐ­­лҐ зЁб« :');
	for i := 1 to N do
		WriteLn('L(', i, ') = ', L[i]:1:5);
	Writeln;
	WriteLn('‘®ЎбвўҐ­­лҐ ўҐЄв®ал:');
	for i := 1 to N do
	begin
		write('x(', i, ') = ');
		for j := 1 to N do
			Write(X[i, j]:1:5, ' ');
		writeln;
	end;
	Writeln;
	Writeln('Џа®ўҐаЄ  A * x(i)=L(i) * x(i):');
	for i := 1 to N do
	begin
		write('A * x(', i, ')    = ');
		for j := 1 to N do
			write(Ax[i, j]:2:4, ' ');
		writeln;
		write('L(', i, ') * x(', i, ') = ');
		for j := 1 to N do
			write(Lx[i, j]:2:4, ' ');
		writeln;
	end;

	readln;
end.
