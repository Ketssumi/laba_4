#pragma once

#include <memory>
#include <stdexcept>

template <typename T>
class Array
{
private:
    std::shared_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity)
    {
        std::shared_ptr<T[]> new_data = std::shared_ptr<T[]>(new T[new_capacity]);

        for (size_t i = 0; i < size_; ++i)
        {
            new_data[i] = std::move(data_[i]);
        }

        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    Array() : size_(0), capacity_(10)
    {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
    }

    Array(size_t initial_capacity) : size_(0), capacity_(initial_capacity)
    {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
    }

    ~Array() = default;

    void add(const T &value)
    {
        if (size_ >= capacity_)
        {
            resize(capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void add(T &&value)
    {
        if (size_ >= capacity_)
        {
            resize(capacity_ * 2);
        }
        data_[size_++] = std::move(value);
    }

    void remove(size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }

        for (size_t i = index; i < size_ - 1; ++i)
        {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }

    T &operator[](size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T &operator[](size_t index) const
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    bool empty() const { return size_ == 0; }

    void clear()
    {
        size_ = 0;
    }
};