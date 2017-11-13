{
	int a, b, N;
	int c, i;
}

{
	a = 0;
	b = 1;
	N = 20;
	for i = 1, N {
		c = a+b;
		print c;
		a = b;
		b = c;
	}
}