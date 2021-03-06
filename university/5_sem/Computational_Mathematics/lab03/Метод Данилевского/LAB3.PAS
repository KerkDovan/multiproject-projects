{���᫥��� ᮡ�⢥���� �ᥫ � ᮡ�⢥���� ����஢}
{�ணࠬ�� ����ᠭ� ��� ��������஢ Turbo Pascal/Borland Pascal ��� Borland inc.}
uses Crt;

type
	MatrType = array[1..3, 1..3] of Real;     {���, ����뢠�騩 ������ [3x3]}
	VectorType = array[1..3] of Real;        {����� �� 3-� ������⮢}

const
	{��室��� �����}
	MyMatr:MatrType =
		((1, 2, -1),
			(3, 0, 2),
			(4, -2, 5));

	{�����筠� �����}
	EM:MatrType =
		((1, 0, 0),
			(0, 1, 0),
			(0, 0, 1));

	{ࠧ��୮��� �������� ������}
	N : integer = 3;

{���᫥��� �ࠪ�����᪮�� �������� � �窥 X
(�ᯮ������ � �襭�� �ࠢ����� P(lambda)=0 ��⮤�� ���⮭�)}
Function F(X : Real; P : VectorType) : Real;
{�室�� ��ࠬ����:
	X - ���祭�� X,
	P - �����樥��� p1,..,pn (�������� ������ �஡�����).
	��室��� ��ࠬ���:
	F - ���祭�� �ࠪ�����᪮�� �������� � �窥 X.}
begin
	F := (-1) * (Sqr(X) * X - P[1] * Sqr(X) - P[2] * X - P[3]);
end;

{���᫥��� ���祭�� �ந������� ��ࢮ�� ���浪�
	�� �ࠪ�����᪮�� �������� � �窥 X
(�ᯮ������ � �襭�� �ࠢ����� D(lambda)=0 ��⮤�� ���⮭�)}
Function dF(X : Real; P : VectorType) : Real;
{�室�� ��ࠬ����:
	X - ���祭�� X,
	P - �����樥��� p1,..,pn (�������� ������ �஡�����).
	��室��� ��ࠬ���:
	dF - ���祭�� �ந������� ��ࢮ�� ���浪� ��
		 �ࠪ�����᪮�� �������� � �窥 X.}
begin
	dF := (-1) * (3 * Sqr(X) - 2 * P[1] * X - P[2]);
end;

{㬭������ ������ �� ������}
Procedure MxM(A, B : MatrType; var X : MatrType);
{�室�� ��ࠬ����:
	A,B - ��६������� ������.
	��室��� ��ࠬ���:
	X - ����� - १���� ����樨 㬭������.}
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

{㬭������ ������ �� �����}
Procedure MxV(A: MatrType; V: VectorType; var X: VectorType);
{�室�� ��ࠬ����:
	A - ����� (���� �����⥫�),
	V - ����� (��ன �����⥫�),
	X - �����, � ���஬ �࠭���� १����� ���᫥���}
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


Procedure Lab3(Matr : MatrType; var L : VectorType; var X, Ax, Lx : MatrType);
(*�室�� ��ࠬ����:
	 Matr:MatrType    -  �����⭠� �����, ��� ���ன
						 ��室���� ᮡ�⢥��� ���祭��;
	 ��室�� ��ࠬ����:
	 L:VectorType     -  ���ᨢ [1..N] ᮡ�⢥���� �ᥫ;
	 X:MatrType       -  ��㬥�� ���ᨢ, ��ப� ���ண� ᮤ�ঠ�
						  ᮡ�⢥��� ������
	 Ax,Lx:MatrType - ������, ��ப� ������ ᮤ�ঠ� १����� �஢�ન 
						  A*x(i) � L(i)*x(i) ᮮ⢥��⢥���*)

var
	i, j, k, h : integer;   	{�ᯮ����⥫�� ��६����}
	P : MatrType;        		{����� �஡�����}
	Pvec : VectorType;   		{����� �����樥�⮢ (p1,p2,p3)}
	A, B, A1, B1 : real;    	{�࠭��� ���ࢠ��� (��⮤ ���⮭�)}
	E : real;            		{�筮��� ���᫥��� (��⮤ ���⮭�)}
	lam0, lam1 : real;    		{�ᯮ����⥫�� ��६���� (��⮤ ���⮭�)}
	S : MatrType;        		{���ᮡ����� ����� S=M(n-1)*...*M1}
	M, M1 : MatrType;     		{������, �ᯮ��㥬� � �८�ࠧ������ �������}
	Yi : VectorType;     		{ᮡ�⢥��� ����� ������ �஡�����,
									ᮮ⢥�����騩 i-�� ᮡ�⢥����� ���}
	Xi : VectorType;      		{i-� ᮡ�⢥��� ����� ��室��� ������}
	Axi, Lxi : VectorType; 		{������ � १���⠬� �஢�ન �ࠢ��쭮�� ���᫥���
						  			i-�� ᮡ�⢥����� ����� ��室��� ������}

	{४��ᨢ��� ��楤�� ���᫥���
		������ �஡����� � ���ᮡ����� ������ S}
	procedure Frob(A : MatrType; Num : integer);
	var i, j : integer;
	begin
		if Num - 1 > 0 then
		begin
	
			M := EM;
			M1 := EM;
			for i := 1 to N do
			begin
				{���᫥��� ����� M(n-1),...,M1}
				if i = Num - 1 then
					M[Num - 1, i] := 1 / A[Num, Num - 1]
				else
					M[Num - 1, i] := -A[Num, i] / A[Num, Num - 1];
				{���᫥��� ����� M(n-1)^-1,...,M1^-1}
				M1[Num - 1, i] := A[Num, i];
			end;

			{���᫥��� ���ᮡ����� ������ S}
			MxM(S, M, S);
			{�८�ࠧ������ �������}
			MxM(A, M, A);
			MxM(M1, A, A);
			P := A;
			Frob(A, Num - 1);
		end;
	end;

	Begin
		clrscr;
		{��宦����� ������ �஡�����}
		S := EM;
		Frob(Matr, N);

		{�뤥����� ����� p=(p1,p2,p3)}
		for i := 1 to N do
			Pvec[i] := P[1, i];

		{�襭�� �ࠢ����� P(lambda)=0 � �ᯮ�짮������ ��⮤� ���⮭�
		��� ��宦����� ᮡ�⢥���� �ᥫ}
		A := -5; B := 5;                   {���ࢠ� ��� ���᪠ ��୥�}
		h := 10;                         {������⢮ 㧫��}
		E := 0.0001;                     {�筮��� �襭��}
		j := 1;

		for i := 0 to h do
			{�⤥����� ��୥�}
			if F((A + i * (B - A) / h), Pvec) *
				F((A + (i + 1) * (B - A) / h), Pvec) < 0 then
			begin
				{[A1, B1] - ���ࢠ�,  �� ���஬ ��室���� ��७�}
				A1 := A + i * (B - A) / h;
				B1 := A + (i + 1) * (B - A) / h;
				{��⮤ ���⮭�}
				lam1 := (A1 + B1) / 2;
				repeat
					lam0 := lam1;
					lam1 := lam0 - F(lam0, Pvec) / dF(lam0, Pvec);
				until Abs(lam1 - lam0) < E;
				{���ᥭ�� ���������� i-�� ᮡ�⢥�����
				�᫠ � ���ᨢ ᮡ�⢥���� �ᥫ}
				L[j] := lam1;
				j := j + 1;
			end;

		{��宦����� ᮡ�⢥���� ����஢}
		for i := 1 to N do
		begin
			{��宦����� i-�� ᮡ�⢥����� ����� ������ �஡�����}
			Yi[N] := 1;
			for j := N - 1 downto 1 do
				Yi[j] := L[i] * Yi[j + 1];
			{��宦����� i-�� ᮡ�⢥����� ����� ��室��� ������
			��⥬ 㬭������ ���ᮡ����� ������ S=M(n-1) * ... * M1
			�� ᮮ⢥�����騩 ᮡ�⢥��� ����� ������ �஡�����}
			MxV(S, Yi, Xi);
			for j := 1 to N do
				X[i, j] := Xi[j];

			{�஢�ઠ �ࠢ��쭮�� ���᫥��� ᮡ�⢥���� ����஢}
			MxV(Matr, Xi, Axi);
			for j := 1 to N do 
			begin
				Ax[i, j] := Axi[j];
				Lx[i, j] := L[i] * Xi[j];
			end;
		
		end;

	End;

var
	(* ��室�� �����:      *)
	X : MatrType;     {����� ᮡ�⢥���� ����஢}
	L : VectorType;   {����� ᮡ�⢥���� �ᥫ}
	Ax, Lx : MatrType;
	(* �ᯮ����⥫�� ��६���� *)
	{N:Integer;      {�����୮��� ������}
	i, j : Integer;
Begin
	N := 3;
	Lab3(MyMatr, L, X, Ax, Lx); {���᫥��� ᮡ�⢥���� �ᥫ � ����஢}
	{�뢮� १���⮢}
	WriteLn('����⢥��� �᫠:');
	for i := 1 to N do
		WriteLn('L(', i, ') = ', L[i]:1:5);
	Writeln;
	WriteLn('����⢥��� ������:');
	for i := 1 to N do
	begin
		write('x(', i, ') = ');
		for j := 1 to N do
			Write(X[i, j]:1:5, ' ');
		writeln;
	end;
	Writeln;
	Writeln('�஢�ઠ A * x(i)=L(i) * x(i):');
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
End.
