#include <stdio.h>
#include <string.h>
inline
bool IsPalindrome(int n)
{
	char buffer[1024] = {0};
	sprintf(buffer, "%d", n);
	const char* p = buffer;
	const char* q = buffer + (strlen(buffer) - 1);

	while(p < q)
	{
		if(*p++ != *q--) return false;
	}

	return true;
}

inline
int FindBiggest()
{
	int biggest = -1;
	
	for(int m = 999; m >= 100; m--)
	{
		for(int n = 999; n >= 100; n--)
		{
			int k = m * n;
			if(IsPalindrome(k) && k > biggest)
			{
				biggest = k;
			}
		}
	}
	

	return biggest;
}