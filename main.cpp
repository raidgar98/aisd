#include "sorters/bubble_sort/bubble_sort.hpp"
#include "sorters/insertion_sort/insertion_sort.hpp"
#include <cassert>
#include <thread>
#include <sstream>

constexpr uint32_t test_count{ 10'000'000 };

template<typename T>
void test()
{
	// using namespace ch = std::chrono::high_resolution_clock;
	auto start = std::chrono::high_resolution_clock::now(); 
	for(uint32_t _ = 0; _ < test_count; _++) 
		assert(static_cast<bool>(T{})); 
	std::stringstream ss{}; ss
		<< "[ " 
		<< std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()
		<< " us ] " 
		<< T{}.uname() 
		<< ": done\n";
	std::cout << ss.str();
}

int main()
{
	std::vector<std::shared_ptr<std::thread>> threads{{ 
		std::make_shared<std::thread>(test<sorting_algorithms::bubble::basic<int>>),
		std::make_shared<std::thread>(test<sorting_algorithms::bubble::reduced<int>>),
		std::make_shared<std::thread>(test<sorting_algorithms::bubble::two_way_reduced<int>>),
		std::make_shared<std::thread>(test<sorting_algorithms::insert::basic<int>>)
	}};

	for(auto& th : threads) th->join();
	return 0;
}