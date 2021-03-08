#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

template<typename T>
class Matrix {
private:
  using iterator = typename std::vector<std::vector<T>>::iterator;
  using const_iterator = typename std::vector<std::vector<T>>::const_iterator;
  std::vector<std::vector<T>> matt;

public:
  iterator begin() { return matt.begin(); }
  iterator end() { return matt.end(); }
  const_iterator begin() const { return matt.begin(); }
  const_iterator end() const { return matt.end(); }

  Matrix(const std::vector<std::vector<T>>& d) {
      matt = d;
  }

  const std::vector<T>& operator[](size_t i) const {
      return matt[i];
  }

  std::vector<T>& operator[](size_t i) {
      return matt[i];
  }

  std::pair<size_t, size_t> size() const {
      return {matt.size(), matt[0].size()};
  }

  Matrix<T>& operator+=(const Matrix<T>& B) {
      size_t n = matt.size();
      size_t m = matt[0].size();
      for (size_t i = 0; i < n; ++i) {
          for (size_t j = 0; j < m; ++j) {
              matt[i][j] += B[i][j];
          }
      }
      return *this;
  }

  template<typename H>
  Matrix<T>& operator*=(const H& scalar) {
      size_t n = matt.size();
      size_t m = matt[0].size();
      for (size_t i = 0; i < n; ++i) {
          for (size_t j = 0; j < m; ++j) {
              matt[i][j] *= scalar;
          }
      }
      return *this;
  }

  Matrix& transpose() {
      size_t n = matt.size();
      size_t m = matt[0].size();
      Matrix<T> transp(std::vector<std::vector<T>>(m, std::vector<T>(n)));
      for (size_t i = 0; i < n; ++i) {
          for (size_t j = 0; j < m; ++j) {
              transp[j][i] = matt[i][j];
          }
      }
      *this = transp;
      return *this;
  }

  Matrix transposed() const {
      auto res(*this);
      res.transpose();
      return res;
  }

  Matrix<T>& operator*=(const Matrix& other) {
      size_t n = matt.size();
      size_t m = matt[0].size();
      size_t n_other = other.size().first;
      size_t m_other = other.size().second;
      Matrix<T> res(std::vector<std::vector<T>>(n, std::vector<T>(m_other)));
      assert(m == n_other);
      for (size_t i = 0; i < n; ++i) {
          for (size_t j = 0; j < m_other; ++j) {
              for (size_t k = 0; k < n_other; ++k) {
                  res[i][j] += matt[i][k] * other[k][j];
              }
          }
      }
      *this = res;
      return *this;
  }
};

template<typename T>
Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B) {
    Matrix<T> res(A);
    res += B;
    return res;
}

template<typename T, typename H>
Matrix<T> operator*(const Matrix<T>& B, const H& scalar) {
    size_t n = B.size().first;
    size_t m = B.size().second;
    Matrix<T> res(B);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            res[i][j] *= scalar;
        }
    }
    return res;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& B, const Matrix<T>& A) {
    Matrix<T> res(B);
    res *= A;
    return res;
}

template<typename T, typename H>
Matrix<T> operator*(const H& scalar, const Matrix<T>& B) {
    return B * scalar;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& other) {
    for (size_t i = 0; i < other.size(); ++i) {
        if (i + 1 < other.size()) {
            out << other[i] << ' ';
        } else {
            std::cout << other[i];
        }
    }
    return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matt_) {
    size_t n = matt_.size().first;
    size_t m = matt_.size().second;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (j + 1 < m) {
                out << matt_[i][j] << '\t';
            } else if (i + 1 < n) {
                out << matt_[i][j] << '\n';
            } else if (i + 1 == n) {
                out << matt_[i][j];
            }
        }
    }
    return out;
}
