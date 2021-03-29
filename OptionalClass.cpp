#include <cstdint>
#include <utility>

struct BadOptionalAccess {
};

template<typename T>
class Optional {
private:
  alignas(T) unsigned char data[sizeof(T)];
  bool defined = false;

public:
  Optional() = default;
  Optional(const Optional& elem) {
      if (elem.defined) {
          new(data) T(elem.value());
          defined = true;
      }
  }
  Optional(T && elem) {
      new(data) T(std::move(elem));
      defined = true;
  }
  Optional(const T& other) {
      new(data) T(other);
      defined = true;
  }
  Optional& operator=(const Optional& elem) {
      if (defined) {
          if (elem.defined) {
              value() = elem.value();
          } else {
              reset();
          }
      } else if (elem.defined) {
          new(data) T(elem.value());
          defined = true;
      }
      return *this;
  }
  Optional& operator=(const T& elem) {
      if (defined) {
          value() = elem;
      } else {
          new(data) T(elem);
          defined = true;
      }
      return *this;
  }
  Optional& operator=(T && elem) {
      if (defined) {
          value() = std::move(elem);
      } else {
          new(data) T(std::move(elem));
          defined = true;
      }
      return *this;
  }
  bool has_value() const {
      return defined;
  }
  T& operator*() {
      return *reinterpret_cast<T*>(data);
  }
  const T& operator*() const {
      return *reinterpret_cast<const T*>(data);
  }
  T* operator->() {
      return reinterpret_cast<T*>(data);
  }
  const T* operator->() const {
      return reinterpret_cast<const T*>(data);
  }
  T& value() {
      if (!defined) {
          throw BadOptionalAccess();
      }
      return *reinterpret_cast<T*>(data);
  }
  const T& value() const {
      if (!defined) {
          throw BadOptionalAccess();
      }
      return *reinterpret_cast<const T*>(data);
  }
  void reset() {
      if (defined) {
          value().~T();
          defined = false;
      }
  }
  ~Optional() {
      reset();
  }
};
