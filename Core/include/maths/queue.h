#ifndef COREMATHS_QUEUE_H
#define COREMATHS_QUEUE_H
#include <array>
#include <vector>
#include <stdexcept>
 
namespace core
{

    template <typename T, std::size_t Size>
    class FixedQueue {

    private:
        std::array<T, Size> data_;
        std::size_t front_index_;
        std::size_t back_index_;
        std::size_t count_;

    public:

        FixedQueue() : front_index_(0), back_index_(0), count_(0) {}

        void enqueue(const T& value) {
            if (count_ >= Size) {
                throw std::overflow_error("Queue overflow");
            }

            data_[back_index_] = value;
            back_index_ = (back_index_ + 1) % Size;
            ++count_;
        }

        void dequeue() {
            if (count_ == 0) {
                throw std::underflow_error("Queue underflow");
            }

            front_index_ = (front_index_ + 1) % Size;
            --count_;
        }

        T& front() {
            if (count_ == 0) {
                throw std::underflow_error("Queue is empty");
            }

            return data_[front_index_];
        }

        [[nodiscard]] bool IsEmpty() const {

            return count_ == 0;
        }

        [[nodiscard]] bool IsFull() const {

            return count_ == Size;
        }


    };



    template <typename T>
    class Queue {

    public:

        void enqueue(const T& value) {

            data_.push_back(value);
        }

        void dequeue() {
            if (data_.empty()) {
                throw std::underflow_error("Queue underflow");
            }

            data_.erase(data_.begin());
        }

        T& front() {
            if (data_.empty()) {
                throw std::underflow_error("Queue is empty");
            }

            return data_.front();
        }

        [[nodiscard]] bool IsEmpty() const {

            return data_.empty();
        }

    private:
        std::vector<T> data_;
    };
}

#endif