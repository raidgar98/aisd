#pragma once

#include <chrono>
#include <iomanip>
#include <type_traits>
#include <concepts>

using namespace std::chrono_literals;
namespace collections
{
    template <typename U>
    inline std::ostream &operator<<(std::ostream &os, const array_list<U> &arr)
    {
        os << "[ ";
        for(auto it = arr.begin(); it != arr.end(); it++)
        {
            if (it != arr.begin()) os << ", ";
            os << *it;
        }
        return os << " ]";
    }

    template <typename U>
    inline std::ostream &operator<<(std::ostream &os, const linked_list<U> &arr)
    {
        os << "[ ";
        for (uint32_t i = 0; i < arr.m_size; i++)
        {
            if (i > 0)
                os << ", ";
            os << *arr.get(i).value;
        }
        return os << " ]";
    }

    using time_point_t = decltype(std::chrono::system_clock::now());
    using duration_t = typename time_point_t::duration;
    
    inline std::ostream& operator<<(std::ostream& os, const duration_t& dur)
    {
        return os << std::fixed << std::setprecision(2) << dur.count() / 1'000'000.0 << " ms";
    }

    struct scope_timer
    {
        static time_point_t get_time() noexcept { return std::chrono::system_clock::now(); }

        scope_timer(duration_t& result) : m_result{result}, m_start{ get_time() } {}
        ~scope_timer() { m_result = ( get_time() - m_start ); }

    private:
        duration_t& m_result;
        const time_point_t m_start;
    };

    template<typename coll_t>
    struct adding
    {
        size_t elements;
        duration_t duration;

        adding(coll_t& list, const size_t n) 
            : elements{n}
        {
            scope_timer _{duration};
            for(size_t i = 0; i < elements; ++i) list.dodaj( i );
        }

        inline friend std::ostream& operator<<(std::ostream& os, const adding<coll_t>& ss)
        {
            return os << "adding " << ss.elements << " elements took: " << ss.duration << std::endl;
        }
    };

    template<typename coll_t>
    struct reading
    {
        duration_t duration;

        reading(coll_t& list) 
        {
            scope_timer _{duration};
            for(size_t i = 0; i < list.rozmiar(); ++i) list.odczytaj( i );
        }

        inline friend std::ostream& operator<<(std::ostream& os, const reading<coll_t>& ss)
        {
            return os << "reading all elements took: " << ss.duration << std::endl;
        }
    };

    template<typename coll_t>
    struct reading_foreach
    {
        duration_t duration;

        reading_foreach(coll_t& list) 
        {
            scope_timer _{duration};
            for(const auto& _ : list) _;
        }

        inline friend std::ostream& operator<<(std::ostream& os, const reading_foreach<coll_t>& ss)
        {
            return os << "reading all elements in foreach took: " << ss.duration << std::endl;
        }
    };

    template<typename coll_t>
    struct searching
    {
        duration_t duration;

        searching(coll_t& list) 
        {
            const typename coll_t::value_type val = list.rozmiar() / 2u;
            scope_timer _{duration};
            list.szukaj( val );
        }

        inline friend std::ostream& operator<<(std::ostream& os, const searching<coll_t>& ss)
        {
            return os << "searching of middle element took: " << ss.duration << std::endl;
        }
    };

    template<typename coll_t>
    struct ereasing
    {
        duration_t duration;

        ereasing(coll_t& list) 
        {
            scope_timer _{duration};
            do{ list.usun( ( list.rozmiar() == 1 ? 0 : 1 ) ); }while(list.rozmiar());
        }

        inline friend std::ostream& operator<<(std::ostream& os, const ereasing<coll_t>& ss)
        {
            return os << "clearing whole collection took: " << ss.duration << std::endl;
        }
    };

    template<template<typename K, typename V> typename map_t, typename key_t>
    requires map_req<map_t> 
    struct adding<map_t<key_t, std::string>>
    {
        size_t elements;
        duration_t duration;

        adding(map_t<key_t, std::string>& list, const size_t n) 
            : elements{n}
        {
            scope_timer _{duration};
            for(size_t i = 0; i < elements; ++i) list.wstaw( i, std::to_string(i) );
        }

        inline friend std::ostream& operator<<(std::ostream& os, const adding<map_t<key_t, std::string>>& ss)
        {
            return os << "adding " << ss.elements << " elements took: " << ss.duration << std::endl;
        }
    };

    template<template<typename K, typename V> typename map_t, typename key_t>
    requires map_req<map_t> 
    struct searching<map_t<key_t, std::string>>
    {
        duration_t duration;

        searching(map_t<key_t, std::string>& map) 
        {
            const size_t val = map.rozmiar() / 2u;
            scope_timer _{duration};
            map.istnieje( val );
        }

        inline friend std::ostream& operator<<(std::ostream& os, const searching<map_t<key_t, std::string>>& ss)
        {
            return os << "searching of middle element took: " << ss.duration << std::endl;
        }
    };

    template<template<typename K, typename V> typename map_t, typename key_t>
    requires map_req<map_t> 
    struct ereasing<map_t<key_t, std::string>>
    {
        duration_t duration;

        ereasing(map_t<key_t, std::string>& map) 
        {
            scope_timer _{duration};
            do{ map.usun( (*map.begin()).key() ); }while(map.rozmiar());
        }

        inline friend std::ostream& operator<<(std::ostream& os, const ereasing<map_t<key_t, std::string>>& ss)
        {
            return os << "clearing whole collection took: " << ss.duration << std::endl;
        }
    };

}