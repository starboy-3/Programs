#include <deque>
#include <iostream>

template<typename T, typename Container = std::deque<T>>
class Queue {
private:
  Container queue;

public:
  Queue() = default;
  void front() const {
      return queue.front();
  }
  T& front() {
      T& fr = queue.front();
      return fr;
  }
  void pop() {
      queue.pop_front();
  }
  void push(const T& n) {
      queue.push_back(n);
  }
  size_t size() const {
      return queue.size();
  }
  bool empty() const {
      return queue.empty();
  }
  bool operator==(const Queue& other) const {
      return (queue == other.queue);
  }
  bool operator!=(const Queue& other) const {
      return !(queue == other.queue);
  }
};
