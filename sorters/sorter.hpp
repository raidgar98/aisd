#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <random>
#include <algorithm>
#include <chrono>
#include <cassert>

#include <boost/type_index.hpp>

template <typename Element>
using collection_t = std::vector<Element>;
template <typename Element>
using collection_ptr_t = std::shared_ptr<collection_t<Element>>;

namespace utils
{
	template <typename T>
	void create_random_data(collection_t<T> &out, const size_t count = 10)
	{
		std::random_device engine;
		std::uniform_int_distribution<int> range{0, 10};

		out.reserve(count);
		for (size_t i = 0; i < count; i++)
			out.emplace_back(range(engine));
	}

	template <typename T>
	void reference_sort(collection_t<T> &out)
	{
		std::sort(out.begin(), out.end());
	}

	template <typename T>
	void reverse(collection_t<T> &out)
	{
		std::reverse(out.begin(), out.end());
	}

	template <typename T>
	bool is_sorted(const collection_t<T> &in)
	{
		return std::is_sorted(in.begin(), in.end());
	}
};

namespace sorting_algorithms
{
	template < template<typename Element> typename Child, typename Element>
	struct abstract_sorter
	{
		using coll_t = collection_t<Element>;
		using coll_ptr_t = collection_ptr_t<Element>;

		explicit abstract_sorter(coll_t &input) : data{&input, [](coll_t*){ /* no destroying */}} {}
		explicit abstract_sorter(coll_ptr_t &input) : data{input} {}
		abstract_sorter() : data{new coll_t{}}
		{
			utils::create_random_data(*data);
		}

		inline friend std::ostream &operator<<(std::ostream &os, abstract_sorter &ss)
		{
			os << ss.get_class_name() << std::endl;
			ss.display(os);
			auto start = std::chrono::high_resolution_clock::now(); 
			ss.sort();
			os << std::endl << "sorting time: " 	<< std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() << "us" << std::endl;
			ss.display(os); 
			os << std::endl << "is sorted: " << (utils::is_sorted<int>(*ss.data) ? "TRUE" : "FALSE") << std::endl;
			return os;
		}

		inline friend std::ostream& operator<<(std::ostream& os, Child<Element>&& ss)
		{
			Child<Element> c{ss};
			os << c;
			return os;
		}

		void display(std::ostream &os = std::cout) const
		{
			os << "[ ";
			for (auto it = data->begin(); it != data->end(); it++)
			{
				if (it != data->begin())
					os << ",";
				os << " " << *it;
			}
			os << " ]";
		}

		virtual void sort() = 0;

	protected:
		coll_ptr_t data;

	private:
		static std::string get_class_name()
		{
			return boost::typeindex::type_id< Child<Element> >().pretty_name();
		}
	};
}