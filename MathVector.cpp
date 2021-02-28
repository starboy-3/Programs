#include <iostream>
#include <vector>

template<typename T>
class MathVector {
private:
  std::vector<T> data;

public:
  // Zero vector of size n
  MathVector() = default;
  MathVector(size_t n) {
      data.resize(n);
  }
  template<typename Iter>
  MathVector(Iter first, Iter last) {
      while (first != last)
          data.push_back(*first++);
  }
  size_t Dimension() const {
      return data.size();
  }
  T& operator[](size_t i) {
      return data[i];
  }
  const T& operator[](size_t i) const {
      return data[i];
  }
  MathVector<T>& operator*=(const T& scalar) {
      for (size_t i = 0; i < data.size(); ++i) {
          data[i] *= scalar;
      }
      return *this;
  }
  MathVector<T>& operator+=(const MathVector<T>& other) {
      for (size_t i = 0; i < data.size(); ++i) {
          data[i] += other[i];
      }
      return *this;
  }
  MathVector<T> operator+(const MathVector<T>& other) const {
      MathVector<T> sum(data.size());
      for (size_t i = 0; i < data.size(); ++i) {
          sum[i] = data[i] + other[i];
      }
      return sum;
  }
  MathVector<T> operator*(const T& scalar) const {
      MathVector<T> tmp(data.begin(), data.end());
      tmp *= scalar;
      return tmp;
  }
  friend MathVector<T> operator*(const T& scalar, const MathVector<T>& v) {
      MathVector<T> multip(v);
      for (size_t i = 0; i < v.Dimension(); ++i) {
          multip[i] *= scalar;
      }
      return multip;
  }
};

// Output format: (1, 2, 3, 4, 5)
template<typename T>
std::ostream& operator<<(std::ostream& out, const MathVector<T>& v) {
    out << '(';
    for (size_t i = 0; i != v.Dimension(); ++i) {
        if (i > 0)
            out << ", ";
        out << v[i];
    }
    out << ')';
    return out;
}
