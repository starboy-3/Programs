#include <cstddef>
#include <memory>

template <typename T>
class SharedPtr {
private:
  int* global_counter = nullptr;
  T* pointer = nullptr;
  void update(int cnt = 1) {
      if (pointer != nullptr) {
          if (global_counter == nullptr) {
              global_counter = new int(cnt);
          } else {
              *global_counter += cnt;
              if (*global_counter == 0) {
                  delete global_counter;
                  delete pointer;
                  global_counter = nullptr;
                  pointer = nullptr;
              }
          }
      } else {
          delete global_counter;
          global_counter = nullptr;
      }
  }

public:
  SharedPtr() = default;
  SharedPtr(T* ptr)
      : pointer(ptr) {
      global_counter = new int(1);
  }
  SharedPtr(const SharedPtr<T>& rhs) {
      global_counter = rhs.global_counter;
      pointer = rhs.pointer;
      update();
  }
  SharedPtr(SharedPtr&& rhs) {
      global_counter = rhs.global_counter;
      pointer = rhs.pointer;
      rhs.global_counter = nullptr;
      rhs.pointer = nullptr;
  }
  SharedPtr& operator= (T* ptr) {
      update(-1);
      pointer = ptr;
      global_counter = nullptr;
      update();
      return *this;
  }
  SharedPtr& operator= (const SharedPtr& rhs) {
      if (pointer == rhs.pointer) {
          return *this;
      }
      update(-1);
      pointer = rhs.pointer;
      global_counter = rhs.global_counter;
      update();
      return *this;
  }
  SharedPtr& operator= (SharedPtr&& rhs) {
      if (this == &rhs) {
          return *this;
      }
      update(-1);
      pointer = rhs.pointer;
      global_counter = rhs.global_counter;
      rhs.pointer = nullptr;
      rhs.global_counter = nullptr;
      return *this;
  }
  ~SharedPtr() {
      update(-1);
  }
  T& operator*() {
      return *pointer;
  }
  const T& operator*() const {
      return *pointer;
  }
  T* operator->() const {
      return pointer;
  }
  void reset(T* ptr) {
      update(-1);
      pointer = ptr;
      global_counter = nullptr;
      update();
  }
  void swap(SharedPtr& rhs) noexcept {
      std::swap(pointer, rhs.pointer);
      std::swap(global_counter, rhs.global_counter);
  }
  T* get() const noexcept {
      return pointer;
  }
  explicit operator bool() const noexcept {
      return (pointer != nullptr);
  }
};
