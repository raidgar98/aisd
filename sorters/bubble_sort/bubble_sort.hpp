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
				auto curr = begin;
				bool next_iter = false;

				do
				{
					next_iter = false;
					auto checker = curr;
					for (auto j = std::next(curr); j < end; ++j, ++checker) 
					{
						if (*j < *curr)
						{
							std::iter_swap(curr, j);
							next_iter = true;
						}else if( !(*checker < *j)) 
						{
							next_iter = true;
						}
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

				auto it = curr;

				bool forward = true;
				bool prime = true;
				bool apply = false;

				auto min = begin;
				auto max = rcurr;

				// this->display();

				do
				{
					if(*it < *min) min = it;
					else if(*max < *it) max = it;

					if(!prime && (it == curr || it == rcurr))
					{
						bool max_swapped = false;
						std::iter_swap(min, curr);
						if(rcurr != min && curr != max)
						{
							std::iter_swap(max, rcurr);
							max_swapped = true;
						}
						
						apply = false;
						prime = true;
						
						curr++;
						if(curr != rcurr && max_swapped) rcurr--;
						else if(!*curr < *rcurr) std::iter_swap(curr, rcurr);
						
						min = curr;
						max = rcurr;

						if(forward)
						{
							forward = false;
							it = rcurr;
						}
						else
						{
							forward = true;
							it = curr;
						}
					}else{
						it = (forward ? std::next(it) : std::prev(it));
						prime = false;
					}
				}while(curr != rcurr);
			}
		};
	}
}