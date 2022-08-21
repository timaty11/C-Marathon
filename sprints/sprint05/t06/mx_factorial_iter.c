int mx_factorial_iter(int n)
{
	if (n < 0 )
	{
		return 0;
	}

	long int res = 1;

	for (long int i = 1; i <= n; i++)
	{
		long int tmp = res * i;

		if (tmp > 2147483647)
		{
			i = 0;
		}

		res *= i;
	}

	return res;
}

