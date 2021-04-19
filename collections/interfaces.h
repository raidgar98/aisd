#pragma once

#include <string>
#include <concepts>

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

    template <template <typename T> typename coll_t>
    concept lista_req =
        std::derived_from<coll_t<int>, ilist<int>> &&
            std::is_constructible_v<coll_t<int>>;
    /*
    // requires(coll_t<std::string> coll, const coll_t<std::string> ccoll)
    // {
    //     typename coll_t<std::string>::value_type;
    //     { coll_t{ { std::string{}, std::string{}, std::string{} } } };
    //     { coll.dodaj( std::string{""} ) } -> std::same_as<void>;
    //     { coll.usun( 1u ) } -> std::same_as<std::string>;
    //     { coll.wstaw( 1u, std::string{""} ) } -> std::same_as<void>;
    //     { coll.szukaj( std::string{""} ) } -> std::same_as<uint32_t>;
    //     { coll.odczytaj( 1u ) } -> std::same_as<std::string&>;
    //     { ccoll.odczytaj( 1u ) } -> std::same_as<const std::string&>;
    //     { coll.rozmiar() } -> std::same_as<uint32_t>;
    //     { *coll.begin() } -> std::same_as<std::string&>;
    //     { *coll.end() } -> std::same_as<std::string&>;
    // };
    */

    template <typename FirstT, typename SecondT>
    struct ipair
    {
        using first_t = FirstT;
        using second_t = SecondT;

        virtual const first_t &first() const = 0;
        virtual void first(const first_t &) = 0;

        virtual const second_t &second() const = 0;
        virtual void second(const second_t &) = 0;

        virtual ~ipair() {}
    };

    template <template <typename T1, typename T2> typename pair_t>
    concept pair_req =
        std::derived_from<pair_t<int, int>, ipair<int, int>> &&
        std::is_constructible_v<pair_t<int, int>, int, int>;

    template<typename X>
    concept comparable_req = requires(const X& x1, const X& x2) { { x1 == x2 } -> std::same_as<bool>; };

    template<typename X>
    concept less_comparable_req = requires(const X& x1, const X& x2) { { x1 < x2 } -> std::same_as<bool>; };

    template<comparable_req T>
    struct iset
    {
        using value_type = T;

        virtual bool istnieje(const value_type&) const = 0;
        virtual bool wstaw(const value_type&) = 0;
        virtual value_type usun(const value_type&) = 0;

        virtual ~iset() {}
    };

    template<comparable_req KeyT, typename ValueT>
    struct imap
    {
        using key_t = KeyT;
        using value_t = ValueT;

        virtual value_t& odczytaj(const key_t&) = 0;
        virtual const value_t& odczytaj(const key_t&) const = 0;
        virtual const value_t& usun(const key_t&) = 0;
        virtual void wstaw(const key_t&, const value_t&) = 0;
        virtual void wstaw(const ipair<key_t, value_t>&) = 0;
        virtual size_t rozmiar() const = 0;
        virtual bool istnieje(const key_t& k) const = 0;

        virtual ~imap() {}
    };

    template <template <comparable_req T1, typename T2> typename map_t>
    concept map_req = 
        std::derived_from< map_t<int, int>, imap<int, int> > &&
        std::is_constructible_v<map_t<int, int>>;
}