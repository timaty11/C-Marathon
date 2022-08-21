#include <stdbool.h>

bool mx_isspace(char);

bool mx_isdigit(char);

void mx_printchar(char);

void mx_printint(int);

int mx_atoi(const char*);

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		return 0;
	}
		
	for (int i = 1; i < argc; i++)
	{
		int n = mx_atoi(argv[i]);

		for (int j = 31; j >= 0; j--)
		{
			int k = n >> j;

			if (k & 1)
			{
				mx_printchar('1');
			}
				
			else
			{
				mx_printchar('0');
			}
		}
		
		mx_printchar('\n');
	}

	return 0;
}

