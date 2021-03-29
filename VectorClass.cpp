#include <memory>
#include <utility>

// using T = int; можно удалить template ниже, если работать только с вектором интов

template<typename T>
class Vector {
private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T *data_ = nullptr;

  T *Allocate(size_t capacity) {
      void *new_data = operator new(sizeof(T) * capacity);
      return reinterpret_cast<T *>(new_data);
  }

  void Deallocate() {
      std::destroy_n(data_, size());
      operator delete(data_);
      size_ = 0;
      capacity_ = 0;
      data_ = nullptr;
  }

public:
  Vector() noexcept = default;

  explicit Vector(size_t cnt) :
      capacity_{cnt}, data_{Allocate(capacity())} {
      try {
          std::uninitialized_value_construct_n(begin(), capacity());
          size_ = cnt;
      } catch (...) {
          Deallocate();
          throw;
      }
  }

  Vector(const Vector& other) :
      capacity_{other.size()}, data_{Allocate(capacity())} {
      try {
          std::uninitialized_copy(other.begin(), other.end(), data_);
          size_ = other.size();
      } catch (...) {
          Deallocate();
          throw;
      }
  }

  ~Vector() {
      Deallocate();
  }

  Vector &operator=(const Vector &other) {
      Vector temp(other);
      swap(temp);
      return *this;
  }

  T& operator[](size_t pos) {
      return data_[pos];
  }

  const T& operator[](size_t pos) const {
      return const_cast<const T&>(data_[pos]);
  }

  void swap(Vector &other) noexcept {
      std::swap(size_, other.size_);
      std::swap(capacity_, other.capacity_);
      std::swap(data_, other.data_);
  }

  size_t size() const noexcept {
      return size_;
  }

  size_t capacity() const noexcept {
      return capacity_;
  }

  void clear() noexcept {
      std::destroy_n(data_, size());
      size_ = 0;
  }

  T *begin() noexcept {
      return data_;
  }

  const T *begin() const {
      return data_;
  }

  T *end() noexcept {
      return begin() + size();
  }

  const T *end() const {
      return begin() + size();
  }

  void reserve(size_t new_capacity) {
      if (new_capacity <= capacity()) {
          return;
      }
      auto new_data = Allocate(new_capacity);
      try {
          std::uninitialized_copy(begin(), end(), new_data);
          std::swap(data_, new_data);
          std::destroy_n(new_data, size());
          operator delete(new_data);
          capacity_ = new_capacity;
      } catch (...) {
          operator delete(new_data);
          throw;
      }
  }

  void pop_back() {
      std::destroy_at(end() - 1);
      --size_;
  }

  void push_back(const T &other) {
      if (size() == capacity()) {
          const auto new_cap = !capacity() ? static_cast<size_t>(1) : capacity() * 2;
          auto new_data = Allocate(new_cap);

          try {
              new(new_data + size()) T(other);
          } catch (...) {
              operator delete(new_data);
              throw;
          }

          try {
              std::uninitialized_copy(begin(), end(), new_data);
              std::swap(data_, new_data);
              std::destroy_n(new_data, size());
              operator delete(new_data);
              capacity_ = new_cap;
              ++size_;
          } catch (...) {
              std::destroy_at(new_data + size());
              operator delete(new_data);
              throw;
          }
      } else {
          new(end()) T(other);
          ++size_;
      }
  }

  void resize(size_t length) {
      if (length <= size()) {
          std::destroy_n(begin() + length, size() - length);
      } else if (length <= capacity()) {
          std::uninitialized_value_construct_n(end(), length - size());
      } else {
          auto new_data = Allocate(length);

          try {
              std::uninitialized_value_construct_n(new_data + size(), length - size());
          } catch (...) {
              operator delete(new_data);
              throw;
          }

          try {
              std::uninitialized_copy(begin(), end(), new_data);
              std::swap(data_, new_data);
              std::destroy_n(new_data, size());
              operator delete(new_data);
              capacity_ = length;
          } catch (...) {
              std::destroy_n(new_data + size(), length - size());
              operator delete(new_data);
              throw;
          }
      }
      size_ = length;
  }
};
