int mx_factorial_rec(int n)
{
	if (n < 0)
	{
		return 0;
	}

	if (n == 0)
	{
		return 1;
	}

	if (n % 1 != 0)
	{
		return 0;
	}

	long int tmp = (long int)n * (long int)n - 1;

	if (tmp > 2147483647)
	{
		n = 0;
	}

	if (n == 1)
	{
		return 1;
	}
	
	return n * mx_factorial_rec(n - 1);
}

