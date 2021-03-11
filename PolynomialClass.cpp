#include <cmath>
#include <iostream>
#include <vector>

template<typename T>
class Polynomial {
public:
  using const_iterator = typename std::vector<T>::const_iterator;

private:
  std::vector<T> coeffs;

public:
  Polynomial& DeleteZeros() {
      while (!coeffs.empty() && coeffs.back() == T(0)) {
          coeffs.pop_back();
      }
      return *this;
  }
  const_iterator begin() const { return coeffs.begin(); }
  const_iterator end() const { return coeffs.end(); }
  Polynomial(const std::vector<T>& data) {
      coeffs = data;
      (*this).DeleteZeros();
  }
  Polynomial(const T& lambda = T(0)) {
      coeffs.push_back(lambda);
      (*this).DeleteZeros();
  }
  template<typename A>
  Polynomial(A beg_iter, A end_iter) {
      for (A it = beg_iter; it != end_iter; ++it) {
          coeffs.push_back(*it);
      }
      (*this).DeleteZeros();
  }
  const std::vector<T>& GetCoeffs() const {
      return coeffs;
  }
  Polynomial& operator-=(const Polynomial& other) {
      if (coeffs.size() < other.coeffs.size()) {
          coeffs.resize(other.coeffs.size(), T(0));
      }
      for (size_t i = 0; i < std::min(other.coeffs.size(), coeffs.size()); ++i) {
          coeffs[i] -= other.coeffs[i];
      }
      (*this).DeleteZeros();
      return *this;
  }
  friend Polynomial operator-(const Polynomial& first, const Polynomial& other) {
      Polynomial diff(first);
      diff -= other;
      diff.DeleteZeros();
      return diff;
  }
  Polynomial& operator+=(const Polynomial& other) {
      if (coeffs.size() < other.coeffs.size()) {
          coeffs.resize(other.coeffs.size(), T(0));
      }
      for (size_t i = 0; i < std::min(other.coeffs.size(), coeffs.size()); ++i) {
          coeffs[i] += other.coeffs[i];
      }
      (*this).DeleteZeros();
      return *this;
  }
  friend Polynomial operator+(const Polynomial& first, const Polynomial& other) {
      Polynomial sum(first);
      sum += other;
      return sum;
  }
  friend bool operator==(const Polynomial& first, const Polynomial& other) {
      return (first.coeffs == other.coeffs);
  }
  friend bool operator!=(const Polynomial& first, const Polynomial& other) {
      return !(first.coeffs == other.coeffs);
  }
  int Degree() const {
      if (coeffs.empty()) {
          return -1;
      }
      return coeffs.size() - 1;
  }
  T operator[](size_t i) const {
      if (i >= coeffs.size()) {
          return 0;
      }
      return coeffs[i];
  }
  Polynomial& operator*=(const Polynomial& other) {
      std::vector<T> res(coeffs.size() + other.coeffs.size(), T(0));
      for (size_t i = 0; i < coeffs.size(); ++i) {
          for (size_t j = 0; j < other.coeffs.size(); ++j) {
              res[i + j] += coeffs[i] * other.coeffs[j];
          }
      }
      coeffs = res;
      (*this).DeleteZeros();
      return *this;
  }
  friend Polynomial operator*(const Polynomial& first, const Polynomial& other) {
      Polynomial res(first);
      res *= other;
      return res;
  }
  T operator()(const T value) const {
      T function_val = T(0);
      T cum = T(1);
      for (size_t i = 0; i < coeffs.size(); ++i) {
          function_val += coeffs[i] * cum;
          cum *= value;
      }
      return function_val;
  }
  friend Polynomial operator&(const Polynomial& first, const Polynomial& second) {
      Polynomial<Polynomial<T>> composition(first.begin(), first.end());
      return composition(second);
  }
  Polynomial<T> CreatePolynom(size_t deg = 0, T coef = T(0)) const {
      std::vector<T> res(deg + 1);
      res[deg] = coef;
      return Polynomial<T>(res);
  }
  Polynomial<T> operator/(const Polynomial<T>& other) const {
      Polynomial<T> divisor(coeffs);
      std::vector<T> res(coeffs.size());
      while (other.Degree() <= divisor.Degree()) {
          T s = divisor.coeffs.back() / other.coeffs.back();
          res[divisor.Degree() - other.Degree()] = s;;
          divisor = divisor - (other * CreatePolynom(divisor.Degree() - other.Degree(), s));
      }
      return res;
  }
  Polynomial<T> operator%(const Polynomial<T>& other) const {
      Polynomial<T> div = (*this / other);
      div *= other;
      return (*this - div);
  }
  Polynomial operator,(Polynomial b) const {
      auto a = *this;
      while (b.Degree() != -1) {
          auto r = a % b;
          a = b;
          b = r;
      }
      a = a / a.coeffs.back();
      a.DeleteZeros();
      return a;
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& polynom) {
    int n = polynom.GetCoeffs().size();
    bool afterfirsttime = false;
    if (n == 0) {
        out << 0;
    }
    for (int degree = n - 1; degree >= 0; --degree) {
        T coeff = polynom.GetCoeffs()[degree];
        if (coeff == T(0)) {
            continue;
        }
        if (coeff == T(1) || coeff == T(-1)) {
            if (degree == 0) {
                if (afterfirsttime && coeff == T(1)) {
                    out << "+";
                }
                out << coeff;
            } else {
                if (afterfirsttime && coeff == T(1)) {
                    out << "+";
                } else if (coeff == T(-1)) {
                    out << "-";
                }
            }
        } else if (coeff != T(1) && coeff != T(-1)) {
            if (afterfirsttime && coeff > T(0)) {
                out << "+";
            }
            out << coeff;
            if (degree != 0) {
                out << '*';
            }
        }
//        printing "x" with degree
        if (degree >= 2) {
            out << "x^" << degree;
        } else if (degree == 1) {
            out << "x";
        }
        afterfirsttime = true;
    }
    return out;
}
