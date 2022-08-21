char *mx_strchr(const char*, int);

int mx_strncmp(const char*, const char*, int);

unsigned long mx_strlen(const char*);

char *mx_strstr(const char*, const char*);

int mx_count_substr(const char *str, const char *sub)
{
	int lenght = mx_strlen(sub);
	int result = 0;
	const char *p = str;
	for (int i = 0; i < lenght; i++)
    {
		if (p[i] != sub[i])
        {
            break;
        }
		else if (p[i] == sub[i] && i == lenght - 1)
        {
            result++;
        }
	}
	for (; *p; )
    {
		p = mx_strstr(p, sub);
		if (p == '\0')
        {
            break;
        }
		result++;
	}
	return result;
}

