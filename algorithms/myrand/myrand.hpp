#pragma once

#include <iostream>
#include <functional>
#include <limits>
#include <memory>
#include <iomanip>
#include "../interfaces.hpp"
#include "../../collections/set/set.hpp"

namespace algs
{
    struct rand_no_dups : public helpers::std_random_generator
    {
        rand_no_dups(const num_t start, const num_t stop, const num_t count) : std_random_generator{start, stop}, data{count, true} {reroll(count);}

        virtual num_t operator()() override
        {
            if(m_idx == data.rozmiar()) reroll();
            return data.odczytaj(m_idx++);
        }

        num_t left() const { return data.rozmiar() - m_idx; }

        void reroll(const num_t count = ~0u)
        {
            const num_t size{ ( count == ~0u ? data.size() : count ) };
            massert(size <= range.b - range.a, "not possible to create of unique range, range too narrow");
            while(data.rozmiar() != size) data.dodaj( std_random_generator::operator() );
            m_idx = 0;
        }

    private:

        num_t m_idx{ 0 };
        collections::flat_set<num_t> data;
    };
}