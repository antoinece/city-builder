#ifndef COREMATHS_STACK_H
#define COREMATHS_STACK_H

#include <array>
#include <stdexcept>
#include <vector>


namespace core
{

    template <typename T, std::size_t Size>

    class FixedStack {

    public:

        FixedStack() : top_index_(-1) {}

        void push(const T& value) {
            if (top_index_ >= Size - 1) {
                throw std::overflow_error("Stack overflow");
            }
            data_[++top_index_] = value;
        }

        void pop() {
            if (top_index_ < 0) {
                throw std::underflow_error("Stack underflow");
            }
            --top_index_;
        }

        T& top() {
            if (top_index_ < 0) {
                throw std::underflow_error("Stack is empty");
            }
            return data_[top_index_];
        }

        [[nodiscard]] bool IsEmpty() const {

            return top_index_ == -1;
        }

        [[nodiscard]] bool IsFull() const {

            return top_index_ == Size - 1;
        }

    private:

        std::array<T, Size> data_;

        int top_index_;

    };


    template <typename T>
    class Stack {

    public:

        void push(const T& value) {
            
            data_.push_back(value);
        }

        void pop() {
            if (data_.empty()) {
                throw std::underflow_error("Stack underflow");
            }
            data_.pop_back();
        }

        T& top() {
            if (data_.empty()) {
                throw std::underflow_error("Stack is empty");
            }
            return data_.back();
        }

        [[nodiscard]] bool IsEmpty() const {

            return data_.empty();
        }

    private:

        std::vector<T> data_;
    };


}


#endif
