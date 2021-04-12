#include "sorters/bubble_sort/bubble_sort.hpp"
#include "sorters/insertion_sort/insertion_sort.hpp"
#include <cassert>
#include <thread>
#include <sstream>

#include "collections/collections.hpp"

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
using Lista = typename collections::array_list<Any>;

void Test1()
{

	Lista<string> l;
	std::cout << "======= Dodawanie ==========" << std::endl;
	l.dodaj("a");
	l.dodaj("b");
	l.dodaj("c");
	for (int i = 0; i < l.rozmiar(); i++)
	{
		string v = l.odczytaj(i);
		std::cout << i << " : " << v << std::endl;
	}
	std::cout << "====== Usuwanie ==========" << std::endl;
	l.usun(1);
	for (int i = 0; i < l.rozmiar(); i++)
	{
		string v = l.odczytaj(i);
		std::cout << i << " : " << v << std::endl;
	}
	std::cout << "========Wstawianie ========" << std::endl;
	l.wstaw(1, "g");
	for (int i = 0; i < l.rozmiar(); i++)
	{
		string v = l.odczytaj(i);
		std::cout << i << " : " << v << std::endl;
	}
	std::cout << "======== Szukanie =========" << std::endl;
	std::cout << "(g) jest pod indeksem " << l.szukaj("g") << std::endl;
	std::cout << "======== Usuwanie 2 =========" << std::endl;
	l.usun(2);
	for (int i = 0; i < l.rozmiar(); i++)
	{
		string v = l.odczytaj(i);
		std::cout << i << " : " << v << std::endl;
	}
}

void Test2()
{
	const size_t N = 1'000;
	using ari = Lista<int>;
	{
		ari list;
		std::cout << "===== Lista Tablicowa =======" << std::endl;
		std::cout << collections::adding<ari>{list, N};
		std::cout << collections::reading<ari>{list};
		std::cout << collections::reading_foreach<ari>{list};
		std::cout << collections::searching<ari>(list);
		std::cout << collections::ereasing<ari>(list);
	}
	// {
	// 	Lista<int> l;
	// 	std::cout << "===== Lista Wskaznikowa =======" << std::endl;
	// 	std::cout << "Czas dodawania:" + CzasDodawania(l, n) << std::endl;
	// 	std::cout << "Czas odczytu  :" + CzasOdczytu(l) << std::endl;
	// 	std::cout << "Czas szukania:" + CzasSzukania(l) << std::endl;
	// 	std::cout << "Czas usuwania :" + CzasUsuwania(l) << std::endl;
	// }
	// Console.ReadKey();
}

int main()
{
	Lista<int> list{{1, 2, 3, 4, 5, 6}};
	list.wstaw(4, 10);
	std::cout << list << ": " << list.rozmiar() << std::endl;
	list.usun(1);
	std::cout << list << ": " << list.rozmiar() << std::endl;

	Test1();
	Test2();
}