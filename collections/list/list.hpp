#pragma once

#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include <memory>
#include <iomanip>
#include "../interfaces.h"

namespace collections
{

    constexpr size_t c_growth_factor{10u};
    constexpr double c_shrink_level{2.5};

    template <typename ElementT>
    class array_list : public ilist<ElementT>
    {
    protected:
        using elem_t = typename ilist<ElementT>::elem_t;
        using index_t = typename ilist<ElementT>::index_t;

    private:
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
            using reference = ElementT &;

            reference operator*() { return **m_ptr; }
            const reference operator*() const { return **m_ptr; }

            reference operator->() { return **m_ptr; }
            const reference operator->() const { return **m_ptr; }

            void operator++() { (++m_ptr); }
            void operator++(int) { (m_ptr++); }

            void operator--() { (--m_ptr); }
            void operator--(int) { (m_ptr--); }

            inline friend bool operator==(const iterator_t &me, const iterator_t &you) { return me.m_ptr == you.m_ptr; }
            inline friend bool operator!=(const iterator_t &me, const iterator_t &you) { return !(me.m_ptr == you.m_ptr); }

            void swap(iterator_t& x) { std::swap(*m_ptr, *x.m_ptr); }

        private:
            explicit iterator_t(elem_t *e) : m_ptr{e} {}
            elem_t *m_ptr;
        };

        array_list() { resize(c_growth_factor); }
        array_list(const index_t preallocate, bool) { resize(preallocate); }
        explicit array_list(const std::initializer_list<ElementT> &init)
        {
            resize(init.size());
            for (const auto &val : init)
                insert(m_size, val);
        }

        virtual void dodaj(const ElementT &e) override { insert_proxy(m_size, e); }
        virtual void wstaw(const index_t i, const ElementT &e) override { insert_proxy(i, e); }
        virtual index_t szukaj(const ElementT &e) override { return lookup(e); }
        virtual ElementT usun(const index_t i) override { return *erease(i); }
        virtual ElementT &odczytaj(const index_t i) override { return get(i); }
        virtual const ElementT &odczytaj(const index_t i) const override { return get(i); }
        virtual index_t rozmiar() const override { return m_size; }

        void wyczy????(){ reset(); }

        iterator_t begin() const { return iterator_t{m_data.get()}; }
        iterator_t end() const { return iterator_t{m_data.get() + m_size}; }

        static void read_file(const std::string_view& filename, array_list<index_t>& dst)
        {
            std::shared_ptr<std::ifstream> file{ new std::ifstream{filename.data()}, [](std::ifstream* ptr){ if(ptr) { ptr->close(); delete ptr; } }};
            massert(file->good(), "can't open file");
            std::string line;
            bool set = false;
            while(std::getline(*file, line)) if(line.size())
            {
                const index_t num = static_cast<index_t>(std::stoul(line));
                if(!set)
                {
                    dst.resize(num);
                    set = true;
                }else dst.dodaj( num );
            }
        }

        static array_list<index_t> merge(const array_list<index_t>& in_1, const array_list<index_t>& in_2)
        {
            array_list<index_t> result{}; result.resize(in_1.rozmiar() + in_2.rozmiar());
            for(const auto& x : in_1) result.dodaj(x);
            for(const auto& x : in_2) result.dodaj(x);
            return result;
        }

    protected:

        constexpr static index_t c_not_found{ std::numeric_limits<index_t>::max() };

        virtual bool insert_proxy(const index_t i, const ElementT& e)
        {
            insert(i, e);
            return true;
        }

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

        index_t lookup_noexcept(const ElementT &e) const noexcept
        {
            for (index_t i = 0; i < m_size; i++)
                if (get(i) == e)
                    return i;
            return c_not_found;
        }

        index_t lookup(const ElementT &e) const
        {
            const index_t result{ lookup_noexcept(e) };
            massert( result != c_not_found, "no match" );
            return result;
        }

        elem_t erease(const index_t pos)
        {
            massert(m_size > 0, "array_list is empty");
            check_range(pos);
            if (m_size * c_shrink_level < m_max_size)
                resize(m_max_size - m_size);

            elem_t result = m_data[pos];
            m_data[pos].reset();

            if (pos != m_size - 1)
                for (index_t i = pos; i < m_size - 1; ++i)
                    m_data[i] = m_data[i + 1];

            m_size--;
            return result;
        }

        bool insert(const index_t pos, const ElementT &e)
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
            return true;
        }

        void check_range(const index_t pos, const bool equal = false) const
        {
            massert(
                pos < m_size or
                    (equal and
                     pos == m_size),
                "position not in range");
        }

        static elem_t construct(const ElementT &e) { return std::make_shared<ElementT>(e); }

        void reset()
        {
            m_data.reset(new elem_t[c_growth_factor + 1]);
            m_max_size = c_growth_factor;
            m_size = 0;
        }

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

    namespace node_ns
    {
        template <typename ElementT>
        struct node : public std::enable_shared_from_this<node<ElementT>>
        {
            std::unique_ptr<ElementT> value{};
            std::shared_ptr<node<ElementT>> m_prev{};
            std::shared_ptr<node<ElementT>> m_next{};

            node() = default;
            node(const ElementT &e) : value{std::make_unique<ElementT>(e)} {}
        };
    }

    template <typename ElementT>
    class linked_list : public ilist<ElementT>
    {
        using index_t = typename ilist<ElementT>::index_t;
        using node = typename node_ns::node<ElementT>;
        using node_ptr = typename std::shared_ptr<node>;

        node_ptr m_end = std::make_shared<node>();
        node_ptr m_begin{m_end->shared_from_this()};
        index_t m_size{0u};

    public:
        struct iterator_t
        {
            friend class linked_list<ElementT>;

            using value_type = ElementT;
            using reference = ElementT &;

            reference operator*() { return *m_ptr.lock()->value; }
            const reference operator*() const { return *m_ptr.lock()->value; }

            reference operator->() { return *m_ptr.lock()->value; }
            const reference operator->() const { return *m_ptr.lock()->value; }

            void operator++() {  next(); }
            void operator++(int) { next(); }

            void operator--() { prev(); }
            void operator--(int) { prev(); }

            inline friend bool operator!=(const iterator_t &me, const iterator_t &you) { return me.m_ptr.lock() != you.m_ptr.lock(); }
            inline friend bool operator==(const iterator_t &me, const iterator_t &you) { return me.m_ptr.lock() == you.m_ptr.lock(); }
            
            void swap(iterator_t& x) { std::swap(*m_ptr, *x.m_ptr); }
            
        private:
            void next()
            {
                massert(m_ptr.lock()->m_next.get(), "out of range"); 
                m_ptr = m_ptr.lock()->m_next->weak_from_this();
            }

            void prev()
            {
                massert(m_ptr.lock()->m_prev.get(), "out of range"); 
                m_ptr = m_ptr.lock()->m_prev->weak_from_this();
            }

            iterator_t(node& n) : m_ptr{ n.weak_from_this() } {}
            std::weak_ptr<node> m_ptr;
        };

        template <typename U>
        friend std::ostream &operator<<(std::ostream &, const linked_list<U> &);

        linked_list() = default;
        explicit linked_list(const std::initializer_list<ElementT> &init)
        {
            for (const auto &v : init)
                insert(*m_end, v);
        }
        virtual void dodaj(const ElementT & e) override { insert(*m_end, e); }
        virtual ElementT usun(const index_t idx) override { return erease(idx); }
        virtual void wstaw(const index_t idx, const ElementT & e) override { insert(idx, e); }
        virtual index_t szukaj(const ElementT & pat) override { return lookup(pat); }
        virtual ElementT &odczytaj(const index_t idx) override { return *get(idx).value; }
        virtual const ElementT &odczytaj(const index_t idx) const override { return *get(idx).value; }
        virtual index_t rozmiar() const override { return m_size; }

        iterator_t begin() const { return iterator_t{*m_begin}; }
        iterator_t end() const { return iterator_t{*m_end}; }

    private:
        void insert(const index_t &i, const ElementT &value)
        {
            insert(get(i), value);
        }

        void insert(node &n, const ElementT &value)
        {
            node_ptr new_node = std::make_shared<node>(value);
            if (m_size == 0) [[unlikely]]
            {
                m_begin = new_node;
                m_begin->m_next = m_end;
                m_end->m_prev = new_node;
            }
            else
            {
                insert_switcher(n.m_prev, new_node, n.shared_from_this());
            }

            m_size++;
        }

        void insert_switcher(node_ptr i_prev, node_ptr i_new, node_ptr i_next)
        {
            i_prev->m_next = i_new;

            i_new->m_prev = i_prev;
            i_new->m_next = i_next;

            i_next->m_prev = i_new;
        }

        ElementT erease(const index_t i) 
        { 
            return erease(get(i).shared_from_this()); 
        }

        ElementT erease(node_ptr x)
        {
            massert(m_size > 0, "list is empmty");

            if (x->m_prev.get())
                x->m_prev->m_next = x->m_next;
            if (x->m_next.get())
                x->m_next->m_prev = x->m_prev;

            x->m_prev.reset();
            x->m_next.reset();

            m_size--;

            return *x->value;
        }

        index_t lookup(const ElementT& pattern) const
        {
            return lookup_impl(pattern, 0, *m_begin);
        }

        index_t lookup_impl(const ElementT& pattern, const index_t idx, node& n) const
        {
            massert( n.shared_from_this() != m_end, "not found" );
            if(*n.value == pattern) return idx;
            else return lookup_impl( pattern, idx+1, *n.m_next );
        }

        node &get(const index_t pos) const
        {
            massert(m_size, "list is empty");
            massert(pos < m_size, "out of range");
            return ( pos < m_size / 2 ? get_impl(pos, 0, *m_begin) : get_impl_prev(pos, m_size, *m_end));
        }

        node &get_impl(const index_t pos, const index_t curr, node &n) const
        {
            if (curr == pos) return n;
            else return get_impl(pos, curr + 1, *(n.m_next));
        }

        node &get_impl_prev(const index_t pos, const index_t curr, node &n) const
        {
            if(curr == pos) return n;
            else return get_impl_prev(pos, curr - 1, *(n.m_prev));
        }
    };
}