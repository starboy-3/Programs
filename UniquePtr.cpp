#include <algorithm>
#include <cstddef>
#include <memory>
#include <tuple>

template<typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
private:
  std::tuple<T*, Deleter> data;
  T* GetPtr() const {
      return std::get<0>(data);
  }
  Deleter GetDeleter() const {
      return std::get<1>(data);
  }
  T*& GetPtr() {
      return std::get<0>(data);
  }
  Deleter& GetDeleter() {
      return std::get<1>(data);
  }

public:
  UniquePtr(T* ptr = nullptr, const Deleter& deleter = Deleter()) :
      data(std::make_tuple(ptr, deleter)) {}
  UniquePtr(UniquePtr&& other) : data(other.data) {
      other.GetPtr() = nullptr;
  }
  ~UniquePtr() {
      GetDeleter()(GetPtr());
  }
  UniquePtr(const UniquePtr& other) = delete;
  UniquePtr& operator=(const UniquePtr& other) = delete;
  UniquePtr& operator=(std::nullptr_t) {
      GetDeleter()(GetPtr());
      GetPtr() = nullptr;
      return *this;
  }
  UniquePtr& operator=(UniquePtr&& other) {
      if (GetPtr() != other.GetPtr()) {
          GetDeleter()(GetPtr());
          data = other.data;
          other.GetPtr() = nullptr;
      }
      return *this;
  }
  void swap(UniquePtr& other) {
      std::swap(data, other.data);
  }
  T* get() const {
      return GetPtr();
  }
  T& operator*() const {
      return *GetPtr();
  }
  T* operator->() const {
      return GetPtr();
  }
  T* release() {
      T* old_d = GetPtr();
      GetPtr() = nullptr;
      return old_d;
  }
  void reset(T* ptr) {
      if (GetPtr() != ptr) {
          GetDeleter()(GetPtr());
          GetPtr() = ptr;
      }
  }
  explicit operator bool() {
      return GetPtr() != nullptr;
  }
  Deleter& get_deleter() {
      return GetDeleter();
  }
  const Deleter& get_deleter() const {
      return GetDeleter();
  }
};
