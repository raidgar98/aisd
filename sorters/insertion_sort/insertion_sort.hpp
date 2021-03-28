#pragma once

#include "../sorter.hpp"

namespace sorting_algorithms
{
	namespace insert
	{
		template<typename T>
		class basic : public abstract_sorter< basic, T >
		{
			virtual void sort() override
			{
				using coll_t = typename abstract_sorter<basic, T>::coll_t;

				auto& dat = *this->data;
				coll_t output; 
				output.reserve(dat.size());

				while(!dat.empty())
				{
					const T& elem = dat.back();
					auto it = output.begin();
					for(; it != output.end(); it++) if(elem < *it ) break;
					output.insert(it, elem);
					dat.pop_back();
				}

				dat = std::move(output);
			}
		};
	}
}