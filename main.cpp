#include "sorters/bubble_sort/bubble_sort.hpp"
#include "sorters/insertion_sort/insertion_sort.hpp"
#include <cassert>
#include <thread>
#include <sstream>

#include "collections/collections.hpp"
/*
constexpr uint32_t test_count{10'000'000};

template <typename T>
void test()
{
	// using namespace ch = std::chrono::high_resolution_clock;
	auto start = std::chrono::high_resolution_clock::now();
	for (uint32_t _ = 0; _ < test_count; _++)
		assert(static_cast<bool>(T{}));
	std::stringstream ss{};
	ss
		<< "[ "
		<< std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()
		<< " us ] "
		<< T{}.uname()
		<< ": done\n";
	std::cout << ss.str();
}

int main_2()
{
	std::vector<std::shared_ptr<std::thread>> threads{{std::make_shared<std::thread>(test<sorting_algorithms::bubble::basic<int>>),
													   std::make_shared<std::thread>(test<sorting_algorithms::bubble::reduced<int>>),
													   std::make_shared<std::thread>(test<sorting_algorithms::bubble::two_way_reduced<int>>),
													   std::make_shared<std::thread>(test<sorting_algorithms::insert::basic<int>>)}};

	for (auto &th : threads)
		th->join();
	return 0;
}

using string = std::string;
template <typename Any>
using Lista = typename collections::linked_list<Any>;
*/

template< template<typename X> typename collection_t>
requires(collections::lista_req<collection_t>)
void test_01()
{
	collection_t<std::string> list;

	std::cout << "======= Dodawanie ==========" << std::endl;
	list.dodaj("a");
	list.dodaj("b");
	list.dodaj("c");

	std::cout << "======= Odczytywanie ==========" << std::endl;
	std::cout << list << std::endl;

	std::cout << "====== Usuwanie ==========" << std::endl;
	list.usun(1);
	std::cout << list << std::endl;

	std::cout << "========Wstawianie ========" << std::endl;
	list.wstaw(1, "g");
	std::cout << list << std::endl;

	std::cout << "======== Szukanie =========" << std::endl;
	std::cout << "(g) jest pod indeksem " << list.szukaj("g") << std::endl;

	std::cout << "======== Usuwanie 2 =========" << std::endl;
	list.usun(2);
	std::cout << list << std::endl;
}

template< template<typename X> typename collection_t>
requires(collections::lista_req<collection_t>)
void test_02(const std::string& message)
{
	const size_t N = 10'000;
	using coll_t = collection_t<int>;
	if(!message.empty()) std::cout << "===== " << message << " =======" << std::endl;

	coll_t list;
	std::cout << collections::adding<coll_t>{list, N};
	std::cout << collections::reading<coll_t>{list};
	std::cout << collections::reading_foreach<coll_t>{list};
	std::cout << collections::searching<coll_t>(list);
	std::cout << collections::ereasing<coll_t>(list);
}

int main()
{
	test_01<collections::linked_list>();
	test_01<collections::array_list>();
	test_02<collections::linked_list>("Lista Wskaźnikowa");
	test_02<collections::array_list>("Lista Tablicowa");
}