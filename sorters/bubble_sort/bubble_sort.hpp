#pragma once

#include "../sorter.hpp"
#include <algorithm>

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

					for (auto j = begin; j < end; ++j) if (*curr < *j)
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

			virtual void sort() override
			{
				throw; // not implemented
				auto begin = this->data->begin();
				auto end = this->data->end();
				auto curr = begin; curr++;
				bool next_iter = false;

				do
				{
					next_iter = false;

					for (auto j = begin; j < end; ++j) if (*curr < *j)
					{
						std::iter_swap(curr, j);
						next_iter = true;
					}
					curr++;
				}while(next_iter && curr != end);
			}
		};
	}
}