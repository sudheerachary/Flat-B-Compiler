{
	int sum;
	int data[100];
}

{
	for i = 1, 100 {
		data[i] = i;
	}
	

	sum = 0;
	for j = 1, 100 {
		sum = sum + data[j];
 	}

	print "Sum value: ", sum;
}

