#include <iostream>
#include <vector>
#include <map>
#include <set>

namespace Question21
{
	inline
	void Divisors(int n, std::vector<int>& vec)
	{
		for(int i = 1; i <= n / 2; ++i)
		{
			if(n % i == 0) vec.push_back(i);
		}
	}

	inline
	int foo(int n)
	{
		std::map<int, int> number2d;
		for(int i = 2; i < n; ++i)
		{
			std::vector<int> vec;
			Divisors(i, vec);
			int sum = 0;
			for(int k:vec)
			{
				sum += k;
			}
			number2d[i] = sum;
		}

		int sum = 0;
		std::set<int> skips;
		for(std::map<int, int>::const_iterator citor = number2d.begin();
			citor != number2d.end();
			++citor)
		{
			int n1 = citor->first;
			if(skips.find(n1) != skips.end())
			{
				continue;
			}

			int n2 = citor->second;

			if(number2d[n2] == n1 && n1 != n2)
			{
				sum += (n1 + n2);
				skips.insert(n2);
			}
		}
		
		return sum;
	}
}
