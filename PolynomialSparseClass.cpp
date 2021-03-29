#include <cmath>
#include <iostream>
#include <map>
#include <vector>

template<class T>
class Polynomial {
private:
    std::map<size_t, T> coefs;

    const T pow(const T& value, const T& degree) const {
        T res = static_cast<T>(1);
        for (T i = static_cast<T>(1); i <= degree; ++i) {
            res *= value;
        }
        return res;
    }

public:
    Polynomial(const std::map<size_t, T> other) {
        for (const auto& [key, value] : other) {
            if (value != T(0)) {
                coefs[key] = value;
            }
        }
    }
    Polynomial(const std::vector<T>& new_coefs) {
        for (size_t i = 0; i < new_coefs.size(); ++i) {
            if (new_coefs[i] != T(0)) {
                coefs[i] = new_coefs[i];
            }
        }
    }

    Polynomial(const T& value = T(0)) {
        if (value != T(0)) {
            coefs[0] = value;
        }
    }
    template<typename Iter>
    Polynomial(Iter first, Iter last) {
        size_t pos = 0;
        while (first != last) {
            if (*first != T(0)) {
                coefs[pos] = *first;
            }
            ++pos;
            ++first;
        }
    }
    void Normalize() {
        while (!coefs.empty() && coefs.back() == static_cast<T>(0)) {
            coefs.pop_back();
        }
    }
    friend bool operator==(Polynomial<T> p, const Polynomial<T>& other) {
        return (p.coefs == other.coefs);
    }

    friend bool operator!=(Polynomial<T> p, const Polynomial<T>& other) {
        return !(p.coefs == other.coefs);
    }
    int Degree() const {
        if (coefs.empty()) {
            return -1;
        }
        auto it = coefs.end();
        --it;
        return (*it).first;
    }
    std::map<size_t, T> Container() const {
        return coefs;
    }
    Polynomial<T>& operator+=(const Polynomial<T>& other) {
        for (const auto& [deg, coef] : other.coefs) {
            coefs[deg] += coef;
            if (coefs[deg] == T(0)) {
                coefs.erase(deg);
            }
        }
        return *this;
    }
    friend Polynomial<T> operator+(Polynomial<T> p, const Polynomial<T>& other) {
        Polynomial<T> tmp(p.coefs);
        tmp += other;
        return tmp;
    }
    Polynomial<T>& operator-=(const Polynomial<T>& other) {
        for (const auto& [deg, coef] : other.coefs) {
            coefs[deg] -= coef;
            if (coefs[deg] == T(0)) {
                coefs.erase(deg);
            }
        }
        return *this;
    }
    friend Polynomial<T> operator-(Polynomial<T> p, const Polynomial<T>& other) {
        Polynomial<T> tmp(p.coefs);
        tmp -= other;
        return tmp;
    }

    Polynomial<T>& operator*=(const Polynomial<T>& other) {
        int deg = Degree();
        int other_deg = other.Degree();
        if (deg == -1 || other_deg == -1) {
            *this = Polynomial<T>(0);
            return *this;
        }
        std::vector<T> new_coefs(deg + other_deg + 1);
        for (const auto& [cur_deg, cur_value] : coefs) {
            for (const auto& [deg, value] : other.coefs) {
                new_coefs[cur_deg + deg] += cur_value * value;
            }
        }
        *this = Polynomial<T>(new_coefs);
        return *this;
    }

    friend Polynomial<T> operator* (Polynomial<T> p, const Polynomial<T>& other) {
        Polynomial<T> tmp_now(p.coefs);
        tmp_now *= other;
        return tmp_now;
    }
    T operator[](const int& pos) const {
        if (coefs.count(pos)) {
            return coefs.at(pos);
        } else {
            return T(0);
        }
    }

    const T operator() (const T& value) const {
        T res = T{0};
        for (const auto& [deg, coef] : coefs) {
            res += coef * pow(value, static_cast<T>(deg));
        }
        return res;
    }
    constexpr typename std::map<size_t, T>::iterator begin() noexcept {
        return coefs.begin();
    }
    constexpr typename std::map<size_t, T>::const_iterator begin() const noexcept {
        return coefs.begin();
    }
    constexpr typename std::map<size_t, T>::iterator end() noexcept {
        return coefs.end();
    }
    constexpr typename std::map<size_t, T>::const_iterator end() const noexcept {
        return coefs.end();
    }
    const Polynomial<T> operator^(int degree) const {
        if (degree == -1) {
            return Polynomial<T>();
        }
        if (degree == 0) {
            return Polynomial<T>(1);
        }
        Polynomial<T> res(coefs);
        for (int i = 2; i <= degree; ++i) {
            res *= Polynomial<T>(*this);
        }
        return res;
    }
    const Polynomial<T> operator&(const Polynomial<T>& other) const {
        Polynomial<T> res(0);
        for (const auto& [deg, coef] : coefs) {
            res += (other^deg) * coef;
        }
        return res;
    }
    Polynomial<T> GetByDeg(T coef, size_t deg = 0) const {
        std::vector<T> res(deg + 1);
        res[deg] = coef;
        return Polynomial<T>(res);
    }

    Polynomial<T> operator/(const Polynomial<T>& other) const {
        Polynomial<T> tmp(coefs);
        std::vector<T> res(Degree() + 1);
        while (tmp.Degree() >= other.Degree()) {
            T s = tmp.coefs[tmp.Degree()] / other.coefs.at(other.Degree());
            res[tmp.Degree() - other.Degree()] = s;;
            tmp = tmp - (other * GetByDeg(s, tmp.Degree() - other.Degree()));
        }
        Polynomial<T> fres(res);
        return  fres;
    }

    Polynomial<T> operator%(const Polynomial<T>& other) const {
        // a % b = a - b * ceil(a / b)
        Polynomial<T> tmp = *this / other;
        tmp *= other;
        auto res = (*this - tmp);
        return res;
    }
};

template<class T>
T abs(const T& value) {
    T res(value);
    if (res < T(0)) {
        res *= -1;
    }
    return res;
}
template<class T>
Polynomial<T> GCD(Polynomial<T> f, Polynomial<T> g) {
    while (g.Degree() != -1) {
        auto rem = f % g;
        f = g;
        g = rem;
    }
    f = f / f[f.Degree()];
    return f;
}

template<class T>
Polynomial<T> operator,(const Polynomial<T>& left, const Polynomial<T>& other) {
    if (left.Degree() == -1 || other.Degree() == -1) {
        return T(0);
    }
    Polynomial<T> tmp_left(left.Container());
    Polynomial<T> tmp_right(other.Container());
    auto res = GCD(tmp_left, tmp_right);
    return res;
}

template<class T>
std::ostream& operator << (std::ostream& out, const Polynomial<T>& p) {
    int deg = p.Degree();
    if (deg == -1) {
        out << "0";
        return out;
    }
    for (int i = deg; i > 0; --i) {
        T value = p[i];
        if (value == T(0)) {
            continue;
        }
        if (value > T(0)) {
            if (i != deg) {
                out << "+";
            }
        } else {
            out << "-";
        }
        if (abs(value) != T(1)) {
            out << abs(value) << "*";
        }
        out << "x";
        if (i > 1) {
            out << "^" << i;
        }
    }
    if (deg != 0 && p[0] > T(0)) {
        out << "+";
    }
    if (p[0] != T(0)) {
        out << p[0];
    }
    return out;
}
