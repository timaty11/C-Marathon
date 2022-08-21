void mx_printchar(char);

void mx_printint(int n)
{
	if (n < 0)
	{
		n = -n;
		mx_printchar('-');
	}

	char arr[11];
	int i = 0;

	for (; n != 0; n /= 10, i++)
	{
		arr[i] = (char)(n % 10) + 48;
	}

	for (; i >= 0; i--)
	{
		mx_printchar(arr[i]);
	}	
}

