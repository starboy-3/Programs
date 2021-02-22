#include<cmath>
#include<cstdlib>
#include<numeric>

class Rational {
private:
  int numer;
  int denom;

public:
  Rational(int numerator = 0, int denominator = 1) {
      if (denominator < 0) {
          numer = -numerator;
          denom = -denominator;
      } else {
          numer = numerator;
          denom = denominator;
      }
      int gcdiv = std::abs(std::gcd(numer, denom));
      if (numer % gcdiv == 0 && denom % gcdiv == 0) {
          numer /= gcdiv;
          denom /= gcdiv;
      }
  }
//  unary + -
  Rational operator-() const {
      return Rational(-numer, denom);
  }
  Rational operator+() const {
      return *this;
  }
//  + - * /
  Rational operator+(const Rational& a) const {
      return Rational((numer * a.denom + a.numer * denom),
                      a.denom * denom);;
  }
  Rational operator-(const Rational& a) const {
      return Rational((numer * a.denom - a.numer * denom),
                      a.denom * denom);;
  }
  Rational operator*(const Rational a) const {
      return Rational((a.numer * numer),
                      (a.denom * denom));
  }
  Rational operator/(const Rational& a) const {
      return Rational((a.denom * numer),
                      (a.numer * denom));
  }
// post and pre ++ --
  Rational operator++(int) {
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      Rational oldValue(numer, denom);
      numer += denom;
      int gcd = std::abs(std::gcd(numer, denom));
      if ((numer % gcd == 0) && (denom % gcd == 0)) {
          numer /= gcd;
          denom /= gcd;
      }
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      return oldValue;
  }
  Rational& operator++() {
      numer += denom;
      int gcd = std::abs(std::gcd(numer, denom));
      if ((numer % gcd == 0) && (denom % gcd == 0)) {
          numer /= gcd;
          denom /= gcd;
      }
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      return *this;
  }
  Rational& operator--() {
      numer -= denom;
      int gcd = std::abs(std::gcd(numer, denom));
      if (numer % gcd == 0 && denom % gcd == 0) {
          numer /= gcd;
          denom /= gcd;
      }
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      return *this;
  }
  Rational operator--(int) {
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      Rational oldValue{numer, denom};
      numer -= denom;
      int gcd = std::abs(std::gcd(numer, denom));
      if ((numer % gcd == 0) && (denom % gcd == 0)) {
          numer /= gcd;
          denom /= gcd;
      }
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      return oldValue;
  }
//  +=    -=    /=   *=
  Rational& operator*=(const Rational& a) {
      numer = numer * a.numer;
      denom = denom * a.denom;
      int gcd = std::abs(std::gcd(numer, denom));
      if ((numer % gcd == 0) && (denom % gcd == 0)) {
          numer /= gcd;
          denom /= gcd;
      }
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      return *this;
  }
  Rational& operator/=(const Rational a) {
      numer = numer * a.denom;
      denom = a.numer * denom;
      int gcd = std::abs(std::gcd(numer, denom));
      if (numer % gcd == 0 && denom % gcd == 0) {
          numer = numer / gcd;
          denom = denom / gcd;
      }
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      return *this;
  }
  Rational& operator+=(const Rational& a) {
      numer = numer * a.denom + a.numer * denom;
      denom = denom * a.denom;
      int gcd = std::abs(std::gcd(numer, denom));
      if (numer % gcd == 0 && denom % gcd == 0) {
          numer = numer / gcd;
          denom = denom / gcd;
      }
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      return *this;
  }
  Rational& operator-=(const Rational& a) {
      numer = numer * a.denom - a.numer * denom;
      denom = denom * a.denom;
      int gcd = std::abs(std::gcd(numer, denom));
      if (numer % gcd == 0 && denom % gcd == 0) {
          numer = numer / gcd;
          denom = denom / gcd;
      }
      if (denom < 0) {
          numer = -numer;
          denom = -denom;
      }
      return *this;
  }
//  bool == !=
  bool operator==(const Rational& a) const {
      return (a.numer == numer && a.denom == denom);
  }
  bool operator!=(const Rational& a) const {
      return !(a.numer == numer && a.denom == denom);
  }
//  returning numerator and denominator
  int Numerator() const {
      return numer;
  }
  int Denominator() const {
      return denom;
  }
};

Rational operator+(int a, Rational b) {
    return Rational(a, 1) + b;
}
Rational operator-(int a, Rational b) {
    return Rational(a, 1) - b;
}
Rational operator*(int a, Rational b) {
    return Rational(a, 1) * b;
}
Rational operator/(int a, Rational b) {
    return Rational(a, 1) / b;
}
