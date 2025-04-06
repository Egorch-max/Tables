#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <functional>
#include <stdexcept>

template <class T>

class _table_interface

{

public:

    virtual ~_table_interface() = default;

    virtual void clear() = 0;

    virtual bool erase(size_t key) = 0;

    virtual bool insert(size_t key, const T& value) = 0;

    virtual T* find(size_t key) = 0;

    virtual const T* find(size_t key) const = 0;

    virtual T& operator[](size_t key) = 0;

    virtual const T& operator[](size_t key) const = 0;

    virtual size_t size() const = 0;

    virtual bool empty() const = 0;
};

// ====================== unordered_table ======================

template <class T>

class unordered_table : public _table_interface<T>
{
    std::vector<std::pair<size_t, T>> data;

public:
    bool insert(size_t key, const T& value) override
    {
        if (find(key))
        {
            return false;
        }

        data.emplace_back(key, value);

        return true;
    }

    bool erase(size_t key) override
    {
        auto it = std::find_if(data.begin(), data.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != data.end())
        {
            *it = std::move(data.back());

            data.pop_back();

            return true;
        }

        return false;
    }

    T* find(size_t key) override
    {
        auto it = std::find_if(data.begin(), data.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != data.end()) 
        {
            return &it->second;
        }
        return nullptr;
    }

    const T* find(size_t key) const override
    {
        auto it = std::find_if(data.begin(), data.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != data.end())
        {
            return &it->second;
        }
        return nullptr;
    }

    T& operator[](size_t key) override
    {
        auto it = std::find_if(data.begin(), data.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != data.end())
        {
            return it->second;
        }

        throw std::out_of_range("Key not found");
    }

    const T& operator[](size_t key) const override
    {
        auto it = std::find_if(data.begin(), data.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != data.end())
        {
            return it->second;
        }

        throw std::out_of_range("Key not found");
    }

    void clear() override
    {
        data.clear();
    }

    size_t size() const override
    {
        return data.size();
    }

    bool empty() const override
    {
        return data.empty();
    }
};

// ====================== ordered_table ======================

template <class T>

class ordered_table : public _table_interface<T>
{
    std::vector<std::pair<size_t, T>> data;

public:
    bool insert(size_t key, const T& value) override
    {
        auto it = std::lower_bound(data.begin(), data.end(), key,[](const auto& item, size_t k)
            {
                return item.first < k;
            }
        );

        if (it != data.end() && it->first == key)
        {
            return false;
        }

        data.emplace(it, key, value);

        return true;
    }

    bool erase(size_t key) override
    {
        auto it = std::lower_bound(data.begin(), data.end(), key,[](const auto& item, size_t k)
            {
                return item.first < k;
            }
        );

        if (it != data.end() && it->first == key)
        {
            data.erase(it);

            return true;
        }

        return false;
    }

    T* find(size_t key) override
    {
        auto it = std::lower_bound(data.begin(), data.end(), key,[](const auto& item, size_t k)
            {
                return item.first < k;
            }
        );

        if (it != data.end() && it->first == key)
        {
            return &it->second;
        }
        return nullptr;
    }

    const T* find(size_t key) const override
    {
        auto it = std::lower_bound(data.begin(), data.end(), key,[](const auto& item, size_t k)
            {
                return item.first < k;
            }
        );

        if (it != data.end() && it->first == key)
        {
            return &it->second;
        }
        return nullptr;
    }

    T& operator[](size_t key) override
    {
        auto it = std::lower_bound(data.begin(), data.end(), key,[](const auto& item, size_t k)
            {
                return item.first < k;
            }
        );

        if (it != data.end() && it->first == key)
        {
            return it->second;
        }

        throw std::out_of_range("Key not found");
    }

    const T& operator[](size_t key) const override
    {
        auto it = std::lower_bound(data.begin(), data.end(), key,[](const auto& item, size_t k)
            {
                return item.first < k;
            }
        );

        if (it != data.end() && it->first == key)
        {
            return it->second;
        }

        throw std::out_of_range("Key not found");
    }

    void clear() override
    {
        data.clear();
    }

    size_t size() const override
    {
        return data.size();
    }

    bool empty() const override
    {
        return data.empty();
    }
};

// ====================== hash_table ======================

template <class T>

class hash_table : public _table_interface<T>
{
    static const size_t DEFAULT_BUCKETS = 1000;

    std::vector<std::list<std::pair<size_t, T>>> buckets;

    size_t item_count = 0;

    size_t hash(size_t key) const
    {
        return std::hash<size_t>{}(key) % buckets.size();
    }

public:
    hash_table() : buckets(DEFAULT_BUCKETS) {}

    bool insert(size_t key, const T& value) override
    {
        auto& bucket = buckets[hash(key)];

        if (std::any_of(bucket.begin(), bucket.end(),[key](const auto& item)
            {
                return item.first == key;
            }))
        {
            return false;
        }

        bucket.emplace_back(key, value);

        item_count++;

        return true;
    }

    bool erase(size_t key) override
    {
        auto& bucket = buckets[hash(key)];

        auto it = std::find_if(bucket.begin(), bucket.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != bucket.end())
        {
            bucket.erase(it);

            item_count--;

            return true;
        }

        return false;
    }

    T* find(size_t key) override
    {
        auto& bucket = buckets[hash(key)];

        auto it = std::find_if(bucket.begin(), bucket.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != bucket.end()) 
        {
            return &it->second;
        }
        return nullptr;
    }

    const T* find(size_t key) const override
    {
        const auto& bucket = buckets[hash(key)];

        auto it = std::find_if(bucket.begin(), bucket.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != bucket.end()) 
        {
            return &it->second;
        }
        return nullptr;
    }

    T& operator[](size_t key) override
    {
        auto& bucket = buckets[hash(key)];

        auto it = std::find_if(bucket.begin(), bucket.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != bucket.end())
        {
            return it->second;
        }

        throw std::out_of_range("Key not found");
    }

    const T& operator[](size_t key) const override
    {
        const auto& bucket = buckets[hash(key)];

        auto it = std::find_if(bucket.begin(), bucket.end(),[key](const auto& item)
            {
                return item.first == key;
            }
        );

        if (it != bucket.end())
        {
            return it->second;
        }

        throw std::out_of_range("Key not found");
    }

    void clear() override
    {
        for (auto& bucket : buckets)
        {
            bucket.clear();
        }

        item_count = 0;
    }

    size_t size() const override
    {
        return item_count;
    }

    bool empty() const override
    {
        return item_count == 0;
    }
};