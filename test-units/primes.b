{
	int i, j, flag;
	int N;
}

{
	N = 20;
	for i = 2, N {
		flag = 0;
		for j = 2, i {
			if i%j == 0 {
				flag = 1;
			} 
		}
		if flag == 0 {
			print i;
		}
	}
}