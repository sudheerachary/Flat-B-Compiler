{
	int flag;
}

{
	for i = 2, 10 {
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

