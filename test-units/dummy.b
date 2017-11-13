{
	int a[100], b[100];
	int c;
	int d;
	int test;
	int i;
	int k;
	int j;
}
{
	c = 6;
	b[c] = c;
	a[c] = b[c] + a[c];
	a[c] = 9;
	read a[c];
	a[c] = a[c]*2;
	print a[3];
	if c>5
	{
		test=5;
		print "hello world1";
	}
	else
	{
		test = 6;
		print "oyaa";
	}
	print test;
	i=2;
	k=9;
	for j = 2*i+2 , k+3
	{
		print j;
		print "In for loop";
	}
}