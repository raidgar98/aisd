#pragma once

#include "../set/set.hpp"
#include "../pair/pair.hpp"

namespace collections
{
    template<comparable_req KeyT, typename ValueT>
    class flat_unordered_map : public imap<KeyT, ValueT>
    {
        using typename imap<KeyT, ValueT>::key_t;
        using typename imap<KeyT, ValueT>::value_t;
        using value_type = map_pair<key_t, value_t>;

        flat_unordered_set<value_type> m_storage;
    public:

        template<typename ... Args>
        explicit flat_unordered_map(Args&& ... argv) : m_storage{ std::forward<Args>(argv)... } {}

        virtual value_t& odczytaj(const key_t& key) override
        {
            return m_storage.odczytaj( value_type{ key } ).value();
        }

        virtual const value_t& odczytaj(const key_t& key) const override
        {
            return m_storage.odczytaj( value_type{ key } ).value();
        }

        virtual const value_t& usun(const key_t& key) override
        {
            return m_storage.usun(value_type{key}).value();
        }

        virtual void wstaw(const key_t& k, const value_t& v) override
        {
            m_storage.wstaw( value_type{ k, v } );
        }

        virtual void wstaw(const ipair<key_t, value_t>& pair) override
        {
            m_storage.wstaw( value_type{ pair } );
        }

        virtual size_t rozmiar() const override { return m_storage.rozmiar(); }

        virtual bool istnieje(const key_t& k) const override { return m_storage.istnieje(value_type{k}); }

        auto begin() { return m_storage.begin(); }
        auto end() { return m_storage.end(); }

    };
}