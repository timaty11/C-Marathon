int mx_strlen(const char *s)
{
	int size = 0;
	for(int i = 0; s[i] != '\0'; i++)
	{
		size++;
	}
	return size;
}

