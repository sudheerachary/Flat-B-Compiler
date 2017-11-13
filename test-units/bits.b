{
	int r, tmp, N;
}
{
	read N;
	tmp = N;
	while tmp != 0 {
		r = tmp%2;
		tmp = tmp/2;
		print r;
	}
	print "bits of ", N;
}