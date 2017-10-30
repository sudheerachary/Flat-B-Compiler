{
	int data[100];
	int i, sum;
}

{
	i = 0;

L1:	data[i] = i; 
	i = i + 1;
	goto L1 if i < 100;
	

	sum = 0;
	i = 0;
L2:	sum = sum + data[i];
	i = i + 1;
	goto L2 if i < 100;

	for i = 1, 10 {
		a = a+b;
	}

	while i < 20 {
		j = j+1;
	}
	print "Sum value: ", sum;
}

