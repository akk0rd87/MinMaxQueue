#pragma once
#include <deque>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

template <class T>
class MinMaxQueue {
public:
    void push(T&& Value) {
        const std::unique_lock<std::shared_mutex> lock(mtx);

        list.emplace_back(std::forward<T>(Value));
        const auto last = &list.back();

        if (min.empty()) {
            min.push_back(last);
        }
        else {
            const auto& currentMin = min.back();
            min.push_back(*currentMin < *last ? currentMin : last);
        }

        if (max.empty()) {
            max.push_back(last);
        }
        else {
            const auto& currentMax = max.back();
            max.push_back(*last < *currentMax ? currentMax : last);
        }

        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::shared_mutex> lock(mtx);
        cv.wait(lock, [this] { return !list.empty(); });

        const auto t = std::move(list.back());
        list.pop_back();
        min.pop_back();
        max.pop_back();
        return t;
    }

    const T& getMin() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        cv.wait(lock, [this] { return !list.empty(); });

        return *min.back();
    }

    const T& getMax() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        cv.wait(lock, [this] { return !list.empty(); });

        return *max.back();
    }

    std::size_t size() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return list.size();
    }

private:
    std::deque<T> list;
    std::deque<T*> min;
    std::deque<T*> max;
    mutable std::shared_mutex mtx;
    mutable std::condition_variable_any cv;
};