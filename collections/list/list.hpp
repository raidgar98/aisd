#pragma once

#include <iostream>
#include <cstring>
#include <memory>
// #include <cassert>

template <typename Any>
constexpr void massert(const bool expr, const Any msg = "assert")
{
    if (!expr)
    {
        std::cout << "assertion message: `" << msg << '`' << std::endl;
        throw msg;
    }
}

namespace collections
{

    constexpr size_t c_growth_factor{10u};
    constexpr size_t c_shrink_factor{c_growth_factor};
    constexpr size_t c_shrink_level{2};

    template <typename ElementT>
    struct ilist
    {
        using value_type = ElementT;
        using elem_t = std::shared_ptr<ElementT>;
        using index_t = uint32_t;

        virtual void dodaj(const ElementT &) = 0;
        virtual ElementT usun(const index_t) = 0;
        virtual void wstaw(const index_t, const ElementT &) = 0;
        virtual index_t szukaj(const ElementT &) = 0;
        virtual ElementT &odczytaj(const index_t) = 0;
        virtual const ElementT &odczytaj(const index_t) const = 0;
        virtual index_t rozmiar() const = 0;
        virtual ~ilist() {}
    };

    template <typename ElementT>
    class array_list : public ilist<ElementT>
    {
        using elem_t = typename ilist<ElementT>::elem_t;
        using index_t = typename ilist<ElementT>::index_t;

        std::unique_ptr<elem_t[]> m_data{};
        index_t m_size{0};
        index_t m_max_size{0};

    public:

        struct iterator_t
        {
            friend class array_list<ElementT>;

            using difference_type = size_t;
            using value_type = ElementT;
            using pointer = elem_t;
            using reference = ElementT&;

            reference operator*() { return **m_ptr; }
            const reference operator*() const { return **m_ptr; }

            reference operator->() { return **m_ptr; }
            const reference operator->() const { return **m_ptr; }

            void operator++() { (++m_ptr); }
            void operator++(int) { (m_ptr++); }

            void operator--() { (--m_ptr); }
            void operator--(int) { (m_ptr--); }

            inline friend bool operator!=(const iterator_t& me, const iterator_t& you) { return me.m_ptr != you.m_ptr; }
            inline friend bool operator==(const iterator_t& me, const iterator_t& you) { return me.m_ptr == you.m_ptr; }

        private:
            explicit iterator_t(elem_t* e) : m_ptr{e} {}
            elem_t* m_ptr;
        };

        array_list() { resize(c_growth_factor); }
        explicit array_list(const index_t preallocate) { resize(preallocate); }
        explicit array_list(const std::initializer_list<ElementT> &init)
        {
            resize(init.size());
            for (const auto &val : init)
                insert(m_size, val);
        }

        virtual void dodaj(const ElementT &e) override { insert(m_size, e); }
        virtual void wstaw(const index_t i, const ElementT &e) override { insert(i, e); }
        virtual index_t szukaj(const ElementT &e) override { return lookup(e); }
        virtual ElementT usun(const index_t i) override { return *erease(i); }
        virtual ElementT &odczytaj(const index_t i) override { return get(i); }
        virtual const ElementT &odczytaj(const index_t i) const override { return get(i); }
        virtual index_t rozmiar() const override { return m_size; }

        iterator_t begin() const { return iterator_t{ m_data.get() }; }
        iterator_t end() const { return iterator_t{ m_data.get() + m_size + 1 }; }

    private:
        ElementT &get(const index_t pos)
        {
            check_range(pos);
            return *m_data[pos];
        }

        const ElementT &get(const index_t pos) const
        {
            check_range(pos);
            return *m_data[pos];
        }

        index_t lookup(const ElementT &e) const
        {
            for (index_t i = 0; i < m_size; i++)
                if (get(i) == e)
                    return i;
            massert(false, "no match");
            return index_t{}; // never will be executed
        }

        elem_t erease(const index_t pos)
        {
            massert(m_size > 0, "array_list is empty");
            check_range(pos);
            if (m_size * c_shrink_level <= m_max_size)
                resize(m_max_size - c_shrink_factor);

            elem_t result = m_data[pos];
            m_data[pos].reset();

            if (pos != m_size - 1)
                for (index_t i = pos; i < m_size - 1; ++i)
                    m_data[i] = m_data[i + 1];

            m_size--;
            return result;
        }

        void insert(const index_t pos, const ElementT &e)
        {
            check_range(pos, true);
            if (0 == m_max_size or m_max_size == m_size)
                resize(m_max_size + c_growth_factor);

            elem_t to_write{construct(e)};
            if (pos == m_size) [[likely]]
                m_data[pos] = to_write;
            else
            {
                for (index_t i = m_size; i > pos; --i)
                    m_data[i] = m_data[i - 1];
                m_data[pos] = to_write;
            }

            m_size++;
        }

        void check_range(const index_t pos, const bool equal = false) const
        {
            massert(
                pos < m_size or
                (
                    equal and
                    pos == m_size
                ),
                "position not in range");
        }

        static elem_t construct(const ElementT &e) { return std::make_shared<ElementT>(e); }

        void resize(const index_t objects)
        {
            massert(objects >= m_size, "there should be enough space for all objects");
            elem_t *new_array = new elem_t[objects + 1]; // extra one is for end()
            for (index_t i = 0; i < m_size; ++i)
                new_array[i] = m_data[i];
            m_data.reset(new_array);
            m_max_size = objects;
        }
    };

    template<typename ElementT>
    class linked_list : public ilist<ElementT>
    {

    };
}