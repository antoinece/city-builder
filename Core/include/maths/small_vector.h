#ifndef COREMATHS_SMALLVECTOR_H
#define COREMATHS_SMALLVECTOR_H

#include <stdexcept>
#include <iostream>

namespace core
{
    template <typename T, size_t N>
    class SmallVector {
    private:
        T data_[N];
        size_t size_;

    public:
        SmallVector() : size_(0) {}

        void push_back(const T& value) {
            if (size_ >= N) {
                throw std::overflow_error("SmallVector overflow");
            }
            data_[size_++] = value;
        }

        void pop_back() {
            if (size_ == 0) {
                throw std::underflow_error("SmallVector is empty");
            }
            --size_;
        }

        T& at(size_t index) {
            if (index >= size_) {
                throw std::out_of_range("Index out of range");
            }
            return data_[index];
        }

        const T& at(size_t index) const {
            if (index >= size_) {
                throw std::out_of_range("Index out of range");
            }
            return data_[index];
        }

        size_t size() const {
            return size_;
        }

        bool empty() const {
            return size_ == 0;
        }

        void clear() {
            size_ = 0;
        }

        // Overload the stream insertion operator for easy output
        friend std::ostream& operator<<(std::ostream& os, const SmallVector& vec) {
            for (size_t i = 0; i < vec.size_; ++i) {
                os << vec.data_[i] << " ";
            }
            return os;
        }
    };
}

#endif // COREMATHS_SMALLVECTOR_H