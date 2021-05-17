#pragma once

#include "list/list.hpp"
#include "map/map.hpp"
#include "collections.hpp"

#include "../algorithms/interfaces.hpp"

constexpr size_t test_count{ 10'000 };

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

void test_08(std::ostream &os)
{
	using namespace collections;
	using alist = array_list<uint32_t>;

	alist list1;
	alist list2;

	algs::helpers::generate_file_with_random_stuff("test_08_list_1.dat", 5);
	algs::helpers::generate_file_with_random_stuff("test_08_list_2.dat", 5);

	alist::read_file("test_08_list_1.dat", list1);
	alist::read_file("test_08_list_2.dat", list2);

	const auto list3 = alist::merge(list1, list2);

	os << "======= FILES =======" << std::endl;
	os << "========= L1 =========" << std::endl;
	for(const auto x : list1) os << x << std::endl;
	os << "========= L2 =========" << std::endl;
	for(const auto x : list2) os << x << std::endl;
	os << "========= L3 =========" << std::endl;
	for(const auto x : list3) os << x << std::endl;
}

template <template <typename Any> typename collection_t>
requires(collections::lista_req<collection_t>) void run_collection_tests(const std::string &msg)
{
	std::stringstream ss;
	if (!msg.empty())
		ss << "===== " << msg << " =======" << std::endl;

	test_01<collection_t>(ss);
	test_02<collection_t>(ss);
	if constexpr ( std::is_same_v<collection_t<int>, collections::array_list<int>> ) test_08(ss);

	std::cout << ss.str();
}

template <template <typename T1, typename T2> typename map_t>
requires collections::map_req<map_t> void test_05(std::ostream& out)
{
	using str = std::string;
	map_t<str, int> tabAso{7u, true};
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

template <template <typename T1, typename T2> typename map_t>
requires collections::map_req<map_t> void test_06(std::ostream& out)
{
	using str = std::string;
	map_t<str, int> tabAso{7u, true};
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

template <template <typename T1, typename T2> typename map_t>
requires collections::map_req<map_t> void test_07(std::ostream& os)
{
	using coll_t = map_t<int, std::string>;

	coll_t map;
	os << collections::map_adding<map_t>{map, test_count};
	os << collections::reading<coll_t>{map};
	os << collections::reading_foreach<coll_t>{map};
	os << collections::map_searching<map_t>(map);
	os << collections::map_ereasing<map_t>(map);
}

template <template <typename T1, typename T2> typename map_t>
requires collections::map_req<map_t> void run_map_tests(const std::string &msg)
{
	std::stringstream ss;
	if (!msg.empty()) ss << "===== " << msg << " =======" << std::endl;

	test_05<map_t>(ss);
	test_06<map_t>(ss);
	test_07<map_t>(ss);

	std::cout << ss.str();
}
