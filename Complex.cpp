#include <cmath>
#include <iostream>

class Complex {
private:
  double re, im;

public:
  Complex(double first = 0, double second = 0) {
      re = first;
      im = second;
  }
  const Complex operator/(const Complex a) const {
      return Complex((re * a.re + a.im * im) / (a.re * a.re + a.im * a.im),
                     (a.re * im - re * a.im) / (a.re * a.re + a.im * a.im));
  }
  const Complex operator/(double a) const {
      return Complex(re / a, im / a);
  }
  const Complex operator+() const {
      return Complex(re, im);
  }
  const Complex operator-() const {
      return Complex(-re, -im);
  }
  const Complex operator+(double a) const {
      return Complex(a + re, im);
  }
  const Complex operator+(const Complex a) const {
      return Complex(a.re + re, im + a.im);
  }
  const Complex operator-(double a) const {
      return Complex(re - a, im);
  }
  const Complex operator-(const Complex a) const {
      return Complex(re - a.re, im - a.im);
  }
  Complex operator*(double a) const {
      return Complex(a * re, a * im);
  }
  Complex operator*(const Complex a) const {
      return Complex(a.re * re - a.im * im, re * a.im + im * a.re);
  }
  bool operator==(const Complex& a) const {
      return (a.im == im && a.re == re);
  }
  bool operator!=(const Complex& a) const {
      return !(a.im == im && a.re == re);
  }
  double Re() const {
      return re;
  }
  double Im() const {
      return im;
  }
};

Complex operator*(double x, const Complex z) {
    return z * x;
}
Complex operator+(double x, const Complex z) {
    return z + x;
}
Complex operator-(double x, const Complex z) {
    return Complex(x - z.Re(), -z.Im());
}
Complex operator/(double x, const Complex a) {
    return Complex(x, 0) / a;
}
double Abs(const Complex& a) {
    return std::pow(a.Re() * a.Re() + a.Im() * a.Im(), 0.5);
}
