#include <time.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Vector3D {
 public:
  double x;
  double y;
  double z;

  Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

  friend ostream& operator<<(ostream& s, const Vector3D& vec) {
    return s << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  }

  friend Vector3D operator+(Vector3D& left, Vector3D& right) {
    return Vector3D(left.x + right.x, left.y + right.y, left.z + right.z);
  }

  friend Vector3D operator-(Vector3D& left, Vector3D& right) {
    return Vector3D(left.x - right.x, left.y - right.y, left.z - right.z);
  }

  friend Vector3D operator*(Vector3D& left, Vector3D& right) {
    return Vector3D(left.x * right.x, left.y * right.y, left.z * right.z);
  }
  friend Vector3D operator/(Vector3D& left, Vector3D& right) {
    return Vector3D(left.x / right.x, left.y / right.y, left.z / right.z);
  }

  friend Vector3D operator*(double val, Vector3D& vec) {
    return Vector3D(val * vec.x, val * vec.y, val * vec.z);
  }

  friend Vector3D operator*(Vector3D& vec, double val) {
    return Vector3D(val * vec.x, val * vec.y, val * vec.z);
  }

  friend Vector3D operator/(double val, Vector3D& vec) {
    return Vector3D(val / vec.x, val / vec.y, val / vec.z);
  }

  friend Vector3D operator/(Vector3D& vec, double val) {
    return Vector3D(val / vec.x, val / vec.y, val / vec.z);
  }

  double dot(Vector3D& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
  double mag() const { return sqrt(x * x + y * y + z * z); }

  double dist(Vector3D& vec) const {
    return sqrt(pow(vec.x - x, 2) + pow(vec.y - y, 2) + pow(vec.z - z, 2));
  }
  Vector3D normalize() const {
    return Vector3D(this->x / this->mag(), this->y / this->mag(),
                    this->z / this->mag());
  }
  Vector3D perpendicular() const { return Vector3D(-y, x, z); }

  Vector3D cross(Vector3D& vec) const {
    return Vector3D((y * vec.z) - (z * vec.y), (z * vec.x) - (x * vec.z),
                    (x * vec.y) - (y * vec.x));
  }
  double anglebetween(Vector3D& vec) const {
    return acos((this->dot(vec)) / (this->mag() * vec.mag()));
  }
};

class JulianDate {
 private:
  static int EPOCH;
  int mon;
  int day;
  int year;
  int hour;
  int min;
  int second;
  double jday;  

 public:
  time_t theTime = time(NULL);
  struct tm* aTime = localtime(&theTime);
  JulianDate(int year, int mon, int day, int hour, int min, int second)
      : year(year), mon(mon), day(day), hour(hour), min(min), second(second) {
    jday = ((1461 * (year + 4800 + (mon - 14) / 12)) / 4 +
            (367 * (mon - 2 - 12 * ((mon - 14) / 12))) / 12 -
            (3 * ((year + 4900 + (year - 14) / 12) / 100)) / 4 + day -
            32075) +
           (((hour + 12.0) / 24)) + (min / 1440.0) + (second / 86400.0);
      }

  JulianDate() {
    year = aTime->tm_year + 1900;
    mon = aTime->tm_mon + 1;
    day = aTime->tm_mday;
    hour = aTime->tm_hour;
    min = aTime->tm_min;
    second = aTime->tm_sec;
    jday = ((1461 * (year + 4800 + (mon - 14) / 12)) / 4 +
            (367 * (mon - 2 - 12 * ((mon - 14) / 12))) / 12 -
            (3 * ((year + 4900 + (year - 14) / 12) / 100)) / 4 + day - 32075) +
           (((hour + 12.0) / 24)) + (min / 1440.0) + (second / 86400.0);
  }

  int getYear() const { return year; }
  int getMonth() const { return mon; }
  int getDay() const { return day; }

  int getHour() const { return hour; }

  int getMin() const { return min; }

  int getSec() const { return second; }

  double getJDay() const { return jday; }

  double JD(JulianDate b) {
    double JDN = ((1461 * (b.year + 4800 + (b.mon - 14) / 12)) / 4 +
                  (367 * (b.mon - 2 - 12 * ((b.mon - 14) / 12))) / 12 -
                  (3 * ((b.year + 4900 + (b.year - 14) / 12) / 100)) / 4 +
                  b.day - 32075) +
                 (((b.hour + 12.0) / 24)) + (b.min / 1440.0) +
                 (b.second / 86400.0);

    return JDN;
  }

  friend double operator-(JulianDate left, JulianDate right) {
    return left.JD(left) - right.JD(right);
  }

  friend JulianDate operator+(JulianDate left, int a) {
    left.day = left.day + a;
    double JD2 = left.JD(left);

    int l = JD2 + 68569.5;
    int n = (4 * l) / 146097;
    l = l - (146097 * n + 3) / 4;
    int i = (4000 * (l + 1)) / 1461001;
    l = l - (1461 * i) / 4 + 31;
    int j = (80 * l) / 2447;
    int d = (l - (2447 * j) / 80);
    l = j / 11;
    int m = j + 2 - (12 * l);
    int y = 100 * (n - 49) + i + l;
    return JulianDate(y, m, d, left.hour, left.min, left.second);
  }

  friend ostream& operator<<(ostream& s, const JulianDate& J) {
    return s << "\nyear: " << J.year << "\nmonth: " << J.mon
             << "\nday: " << J.day << "\nhour: " << J.hour
             << "\nminute: " << J.min << "\nsecond: " << J.second << '\n';
  }
};

class Body {
  private :
   Vector3D position;
   Vector3D velocity;
   Vector3D acceleration;

   string name;
   string orbits;


   double mass;
   double diameter;
   double Perhelion;
   double Aphelion;
   

  public:
   Body()
       : name(),
         orbits(),
         mass(),
         diameter(),
         Perhelion(),
         Aphelion(),
         position(),
         velocity(),
         acceleration() {}

   Vector3D getPosition()const  { return position; }
   Vector3D getVelocity() const { return position; }
   Vector3D getAcceleration()const { return acceleration; }
   string getName() const{ return name; }
   double getMass() const { return mass; }
   double getDiameter() const { return diameter; }

   friend ostream& operator<<(ostream& s, const Body b) {
     return s << b.name << " " << b.position << " " << b.acceleration << " " << b.velocity << " " << endl;
   }

   friend istream& operator>>(istream& s, Body& b) {
     string linebuff;
     getline(s, linebuff);
     istringstream line(linebuff);
     line >> b.name >> b.orbits >> b.mass >> b.diameter >> b.Perhelion >> b.Aphelion;
     return s;
   }
};

int main() {
  ///========testing purposes=========== //
  
  

  ///========testing purposes=========== //
}