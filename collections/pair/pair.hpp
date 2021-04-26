#pragma once

#include <iostream>
#include <memory>
#include "../interfaces.h"

namespace collections
{
    template <typename FirstT, typename SecondT>
    class pair : public ipair<FirstT, SecondT>
    {
        using typename ipair<FirstT, SecondT>::first_t;
        using typename ipair<FirstT, SecondT>::second_t;

        first_t m_first;
        second_t m_second;

    public:
        virtual const first_t &first() const
        {
            return m_first;
        }

        virtual void first(const first_t &i_first)
        {
            m_first = i_first;
        }

        virtual const second_t &second() const
        {
            return m_second;
        }

        virtual void second(const second_t &i_second)
        {
            m_second = i_second;
        }

        inline friend std::ostream &operator<<(std::ostream &os, const pair &p)
        {
            return os << "( " << p.first() << " ; " << p.second() << " )";
        }
    };

    template <comparable_req KeyT, typename ValueT>
    class map_pair
    {
        using first_t = KeyT;
        using second_t = ValueT;

        first_t m_key{};
        mutable std::shared_ptr<second_t> m_value{nullptr};

    public:
        explicit map_pair(const ipair<first_t, second_t> &in_pair) : m_key{in_pair.first()} { value(in_pair.second()); }
        map_pair(const first_t &i_key) : m_key{i_key} {}
        map_pair(const first_t &i_key, const second_t &i_value) : m_key{i_key} { value(i_value); }

        const first_t &key() const { return m_key; }
        second_t &value() const
        {
            massert(m_value.get(), "second not set!");
            return *m_value;
        }
        // const second_t& value() const { massert(m_value.get(), "second not set!"); return *m_value; }
        void value(const second_t &v) { m_value = std::make_shared<second_t>(v); }

        inline friend bool operator==(const map_pair &p1, const map_pair &p2) { return p1.key() == p2.key(); }
        inline friend bool operator<(const map_pair &p1, const map_pair &p2) { return p1.key() < p2.key(); }
        inline friend std::ostream &operator<<(std::ostream &os, const map_pair &p)
        {
            return os << "( " << p.key() << " ; " << p.value() << " )";
        }
    };
}