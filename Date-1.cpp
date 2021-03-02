#include <iostream>
#include <stdexcept>
#include <tuple>
#include <vector>

class Date {
private:
  int day, month, year;

  Date& DaysBefore(int daysbefore) {
      int jdn = JDN(day, month, year) - daysbefore;
      *this = ToGregor(jdn);
      return *this;
  }
  int JDN(int day, int month, int year) const {
      int a1 = (14 - month) / 12;
      int y1 = year + 4800 - a1;
      int m1 = month + 12 * a1 - 3;
      int jdn1 = day + ((153 * m1 + 2) / 5) + 365 * y1 +
          y1 / 4 - y1 / 100 + y1 / 400 - 32045;
      return jdn1;
  }
  Date ToGregor(int JDN) {
      int a = JDN + 32044;
      int b = (4 * a + 3) / 146097;
      int c = a - (146097 * b) / 4;
      int d = (4 * c + 3) / 1461;
      int e = c - (1461 * d) / 4;
      int m = (5 * e + 2) / 153;
      int day_ = e - (153 * m + 2) / 5 + 1;
      int month_ = m + 3 - 12 * (m / 10);
      int year_ = 100 * b + d - 4800 + (m / 10);
      return {day_, month_, year_};
  }
  Date& DaysAfter(int daysafter) {
      int jdn = JDN(day, month, year) + daysafter;
      *this = ToGregor(jdn);
      return *this;
  }
  int dofm(int m) const {
      std::vector<int> dayofmonth{31,
                                  (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? 29 : 28,
                                  31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
      return dayofmonth[m];
  }

public:
  Date(int d, int m, int y) {
      year = y;
      if (1 > m || m > 12 || 1 > d || d > dofm(m - 1) || 1970 > y || y > 2099) {
          throw std::invalid_argument("Enter a valid date, you stupid");
      }
      day = d;
      month = m;
  }
  int GetDay() const {
      return day;
  }
  int GetMonth() const {
      return month;
  }
  int GetYear() const {
      return year;
  }
  Date operator+(int d) const {
      return Date(day, month, year).DaysAfter(d);
  }
  Date operator-(int d) const {
      return Date(day, month, year).DaysBefore(d);
  }
  Date& operator++() {
      return (*this).DaysAfter(1);
  }
  Date& operator--() {
      return (*this).DaysBefore(1);
  }
  int operator-(const Date& other) const {
      if (std::tie(year, month, day) >
          std::make_tuple(other.GetYear(), other.GetMonth(), other.GetDay())) {
          return (*this).DateDiff(other);
      } else {
          return -(other).DateDiff(*this);
      }
  }
  int DateDiff(const Date& other) const {
      return abs(JDN(day, month, year) - JDN(other.GetDay(), other.GetMonth(), other.GetYear()));
  }
};
