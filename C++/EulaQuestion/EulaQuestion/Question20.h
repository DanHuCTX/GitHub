namespace Question20
{
	int foo(int n)
	{
		double product = 0.1;
		for(int i = 1; i <= n; ++i)
		{
			product *= i;
			while(product >= 1073741824)
			{
				product /= 10;
			}
		}

		return 0;
	}
}