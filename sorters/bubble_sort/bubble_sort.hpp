#pragma once

#include "../sorter.hpp"
#include <algorithm>

namespace sorters
{

	class base_bubble_sorter : public abstract_sorter<base_bubble_sorter, int>
	{
		using abstract_sorter::abstract_sorter;

		virtual void sort() override
		{
			utils::reference_sort(*data);
		}
	};

}