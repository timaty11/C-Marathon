int mx_strlen(const char *s);

void mx_printchar(char);

void mx_printint(int);

void mx_printstr(const char*);

int main(int argc, char const *argv[])
{
	mx_printstr(argv[0]);
	mx_printchar('\n');
	mx_printint(argc);
	mx_printchar('\n');
	return 0;
}

