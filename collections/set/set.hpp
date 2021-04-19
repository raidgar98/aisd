#pragma once

#include <iostream>
#include <memory>
#include "../list/list.hpp"


namespace collections
{
    template<comparable_req T>
    class flat_unordered_set : 
        public iset<T>,
        protected array_list<T>
    {
        virtual bool insert_proxy(const uint32_t, const T& e) override
        {
            return this->insert(array_list<T>::rozmiar(), e);
        }

        array_list<T>* get_as_array() const { return (array_list<T>*)this; }

    public:

        using array_list<T>::rozmiar;
        using array_list<T>::begin;
        using array_list<T>::end;

        template<typename ... Args>
        explicit flat_unordered_set(Args&& ... argv) : array_list<T>{ std::forward<Args>(argv)... } {}

        virtual bool istnieje(const T& e) const override
        {
            return !(this->lookup_noexcept(e) == array_list<T>::c_not_found);
        }

        virtual const T& odczytaj(const T& e) const
        {
            return this->get(this->lookup(e));
        }

        virtual bool wstaw(const T& e) override 
        {
            return insert_proxy(0u, e);
        }

        virtual T usun(const T& e) override
        {
            const size_t idx = this->lookup(e);
            return get_as_array()->usun(idx);
        }

        inline friend std::ostream& operator<<(std::ostream& os, const flat_unordered_set<T>& ss)
        {
            return os << *ss.get_as_array();
        }

    };

}