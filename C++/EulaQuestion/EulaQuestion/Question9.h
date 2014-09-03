#include <iostream>

namespace Question9
{
	inline void Foo()
	{
		bool stop = false;
		for(int a = 1; a < 1000; ++a)
		{
			for(int b = 1; b < 1000; ++b)
			{
				if(a + b >= 1000)
				{
					break;
				}
				if(a + b <= 500) continue;

				int m = a * b;
				if(m % 1000 != 0) continue;
				int n = m / 1000;
				if(a + b == 500 + n)
				{
					std::cout << "a=" << a <<",b=" <<b << std::endl;
				}
			}
		}
	}
}