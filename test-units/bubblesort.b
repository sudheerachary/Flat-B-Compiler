{
	int n, temp;
	int A[100];
	int j;
	int i;
}

{ 
	read n;
	for i = 0, n {
		read A[i];
	}
	for i = 0, n-1 {
		for j = 0, n-i-1 {
			if A[j] > A[j+1] {
				temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
			}
		}
	} 
	for j = 0, n {
		print A[j];
	}
}