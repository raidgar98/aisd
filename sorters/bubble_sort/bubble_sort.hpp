#pragma once

#include "../sorter.hpp"
#include <algorithm>
#include <tuple>

namespace sorting_algorithms
{

	namespace bubble
	{
		template<typename T>
		class basic : public abstract_sorter< basic, T>
		{
			using abstract_sorter< basic, T >::abstract_sorter;

			virtual void sort() override
			{
				auto begin = this->data->begin();
				auto end = this->data->end();

				for (auto i = begin; i != end; ++i)
					for (auto j = begin; j < i; ++j)
						if (*i < *j)
							std::iter_swap(i, j);
			}
		};

		template<typename T>
		class reduced : public abstract_sorter< reduced , T>
		{
			using abstract_sorter<reduced, T>::abstract_sorter;

			virtual void sort() override
			{
				auto begin = this->data->begin();
				auto end = this->data->end();
				auto curr = begin; curr++;
				bool next_iter = false;

				do
				{
					next_iter = false;

					for (auto j = begin; j < end; ++j) 
						if (*curr < *j)
						{
							std::iter_swap(curr, j);
							next_iter = true;
						}
					curr++;
				}while(next_iter && curr != end);
			}
		};

		template<typename T>
		class two_way_reduced : public abstract_sorter< two_way_reduced , T>
		{
			using abstract_sorter<two_way_reduced, T>::abstract_sorter;
			using iterator_t = decltype( ((std::vector<T>*)(nullptr))->begin() );

			virtual void sort() override
			{
				auto begin = this->data->begin();
				auto end = this->data->end();
				auto curr = begin;
				auto rcurr = std::prev(end); 

				bool next_iter = false;

				auto min_max = [&]() -> std::tuple<iterator_t,iterator_t> {
					auto cur_max = rcurr;
					auto cur_min = curr;
					next_iter = false;

					for(auto j = curr; j < rcurr || j == rcurr; ++j)
					{
						next_iter = true;
						std::cout << *j << std::endl;
						if(*j < *cur_min) cur_min = j;
						if(*j > *cur_max) cur_max = j;
					}

					if(cur_min == cur_max) cur_max = end;
					return {cur_min, cur_max};
				};

				do
				{
					auto [min, max] = min_max();
					std::iter_swap(min, curr);
					std::advance(curr, 1);

					if(max != end)
					{
						std::iter_swap(max, rcurr);
						std::advance(rcurr, -1);
					}

					this->display();
					std::cout << std::endl;
					std::cout << "###################" << std::endl;

				}while(rcurr != curr && next_iter);
			}
		};
	}
}