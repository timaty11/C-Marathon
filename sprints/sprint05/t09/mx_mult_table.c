#include <stdbool.h>

bool mx_isspace(char);

bool mx_isdigit(char);

void mx_printchar(char);

void mx_printint(int);

int mx_atoi(const char*);

int mx_strlen(const char*);

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		return 0;
	}

	int a = mx_atoi(argv[1]);
	int b = mx_atoi(argv[2]);

	if (a > 9 || a < 1 || b > 9 || b < 1 )
	{
		return 0;
	}

	if (a > b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	
	for (int i = a; i <= b; i++)
	{
		for (int j = a; j <= b; j++)
		{
			mx_printint(i * j);

			if (j < b)
			{	
				mx_printchar('\t');
			}
		}

		mx_printchar('\n');
	}

	return 0;
}

