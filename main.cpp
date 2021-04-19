#include "sorters/bubble_sort/bubble_sort.hpp"
#include "sorters/insertion_sort/insertion_sort.hpp"
#include <cassert>
#include <thread>
#include <sstream>

#include "collections/list/list.hpp"
#include "collections/map/map.hpp"
#include "collections/collections.hpp"

constexpr size_t test_count{ 10'000 };

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

template <template <typename X> typename collection_t>
requires(collections::lista_req<collection_t>) void test_01(std::ostream &os)
{
	collection_t<std::string> list;

	os << "======= Dodawanie ==========" << std::endl;
	list.dodaj("a");
	list.dodaj("b");
	list.dodaj("c");

	os << "======= Odczytywanie ==========" << std::endl;
	os << list << std::endl;

	os << "====== Usuwanie ==========" << std::endl;
	list.usun(1);
	os << list << std::endl;

	os << "========Wstawianie ========" << std::endl;
	list.wstaw(1, "g");
	os << list << std::endl;

	os << "======== Szukanie =========" << std::endl;
	os << "(g) jest pod indeksem " << list.szukaj("g") << std::endl;

	os << "======== Usuwanie 2 =========" << std::endl;
	list.usun(2);
	os << list << std::endl;
}

template <template <typename X> typename collection_t>
requires(collections::lista_req<collection_t>) void test_02(std::ostream &os)
{
	using coll_t = collection_t<int>;

	coll_t list;
	os << collections::adding<coll_t>{list, test_count};
	os << collections::reading<coll_t>{list};
	os << collections::reading_foreach<coll_t>{list};
	os << collections::searching<coll_t>(list);
	os << collections::ereasing<coll_t>(list);
}

template <template <typename Any> typename collection_t>
requires(collections::lista_req<collection_t>) void run_collection_tests(const std::string &msg)
{
	std::stringstream ss;
	if (!msg.empty())
		ss << "===== " << msg << " =======" << std::endl;

	// test_01<collection_t>(ss);
	test_02<collection_t>(ss);

	std::cout << ss.str();
}

template <template <collections::comparable_req T1, typename T2> typename map_t>
requires collections::map_req<map_t> static void test_05(std::ostream& out)
{
	using str = std::string;
	map_t<str, int> tabAso{7u};
	out << "====== Wstawianie ========" << std::endl;
	str k{"A"};
	int v{1};
	k = "A";
	v = 1;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "B";
	v = 2;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "C";
	v = 3;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "D";
	v = 4;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "F";
	v = 99;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "G";
	v = 10;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "E";
	v = 5;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "H";
	v = 8;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "I";
	v = 9;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	out << "====== Odczyt ========" << std::endl;
	k = "A";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "B";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "C";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "D";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "E";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "F";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "G";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "H";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "I";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	out << "====== Wstawianie ========" << std::endl;
	k = "A";
	v = 10;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "H";
	v = 11;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "I";
	v = 12;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	out << "====== Odczyt ========" << std::endl;
	k = "A";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "B";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "C";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "D";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "E";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "F";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "G";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "H";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
	k = "I";
	out << k << " : " << tabAso.odczytaj(k) << std::endl;
}

template <template <collections::comparable_req T1, typename T2> typename map_t>
requires collections::map_req<map_t> static void test_06(std::ostream& out)
{
	using str = std::string;
	map_t<str, int> tabAso{7u};
	out << "====== Wstawianie ========" << std::endl;
	str k;
	int v;
	k = "A";
	v = 1;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "B";
	v = 2;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "C";
	v = 3;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "D";
	v = 4;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "E";
	v = 5;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "H";
	v = 8;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "I";
	v = 9;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	out << "====== Odczyt ForEach ========" << std::endl;

	for (const auto& para : tabAso) out << para << std::endl;

	out << "====== Wstawianie ========" << std::endl;
	k = "A";
	v = 10;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "H";
	v = 11;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	k = "I";
	v = 12;
	tabAso.wstaw(k, v);
	out << "Wstawiam: [" << k << ":" << v << "]" << std::endl;
	out << "====== Odczyt ForEach========" << std::endl;

	for (const auto& para : tabAso) out << para << std::endl;
}

template <template <collections::comparable_req T1, typename T2> typename map_t>
requires collections::map_req<map_t> static void test_07(std::ostream& os)
{
	using coll_t = map_t<int, std::string>;

	coll_t map;
	os << collections::adding<coll_t>{map, test_count};
	os << collections::reading<coll_t>{map};
	os << collections::reading_foreach<coll_t>{map};
	os << collections::searching<coll_t>(map);
	os << collections::ereasing<coll_t>(map);
}

template <template <collections::comparable_req T1, typename T2> typename map_t>
requires collections::map_req<map_t> void run_map_tests(const std::string &msg)
{
	std::stringstream ss;
	if (!msg.empty()) ss << "===== " << msg << " =======" << std::endl;

	// test_05<map_t>(ss);
	// test_06<map_t>(ss);
	test_07<map_t>(ss);

	std::cout << ss.str();
}

int main()
{
	std::jthread coll_0{[&]() { run_collection_tests<collections::array_list>("array_list"); }};
	std::jthread coll_1{[&]() { run_collection_tests<collections::linked_list>("linked_list"); }};
	std::jthread coll_2{[&]() { run_map_tests<collections::flat_unordered_map>("flat_map"); }};
}