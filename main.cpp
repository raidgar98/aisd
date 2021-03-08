#include "sorters/bubble_sort/bubble_sort.hpp"

int main()
{
	std::cout << sorting_algorithms::bubble::basic<int>{} << std::endl;
	std::cout << sorting_algorithms::bubble::reduced<int>{} << std::endl;
	std::cout << sorting_algorithms::bubble::two_way_reduced<int>{} << std::endl;
	return 0;
}