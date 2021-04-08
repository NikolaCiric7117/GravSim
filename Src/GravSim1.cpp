#include <time.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>

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
 private:
  Vector3D position;
  Vector3D velocity;
  Vector3D acceleration;

  string name;
  string orbits;

  double mass;
  double diameter;
  double Perhelion;
  double Aphelion;
  double distFromSun;
  double trueAnomly;

 public:
  Body(string name)
      : name(name),
        orbits(),
        mass(),
        diameter(),
        Perhelion(),
        Aphelion(),
        position(),
        velocity(),
        acceleration(), distFromSun(), trueAnomly() {}

  Vector3D getPosition() const { return position; }
  Vector3D getVelocity() const { return position; }
  Vector3D getAcceleration() const { return acceleration; }
  string getName() const { return name; }
  double getMass() const { return mass; }
  double getDiameter() const { return diameter; }

  friend ostream& operator<<(ostream& s, const Body b) {
    return s << b.name << " " << b.position << " " << b.acceleration << " "
             << b.velocity << " " << endl;
  }

  friend istream& operator>>(istream& s, Body& b) {
    string linebuff;
    getline(s, linebuff);
    istringstream line(linebuff);
    line >> b.name >> b.orbits >> b.mass >> b.diameter >> b.Perhelion >>
        b.Aphelion;
    return s;
  }

  static void setPosition(vector<Body*> bodies) {  
    JulianDate currentTime;
    double dayNumber = currentTime.getJDay() - 2451543.5;
    for (auto b: bodies) {
      string name = b->name;
      if (b->name == "mercury") {
        double N = 48.3313 + 3.24587E-5 * dayNumber;
        double i = 7.0047 + 5.00E-8 * dayNumber;
        double w = 29.1241 + 1.01444E-5 * dayNumber;
        double a = 0.387098;
        double e = 0.205635 + 5.59e-10 * dayNumber;
        double M = 168.6562 + 4.0923344368 * dayNumber;
        if (M < 0) {
          while (M < 0) {
            M = M + 360;
          }
        }
        if (M > 360) {
          while (M > 360) {
            M = M - 360;
          }
        }
        double E =
            M + e * (sin(M) * (180 / M_PI)) * (1 + e * (cos(M) * (180 / M_PI)));
        double x = a * (cos(E) - e);
        double y = a * sqrt(1 - (e * e)) * sin(E);

        b->distFromSun = sqrt(x * x + y * y);
        b->trueAnomly = atan2(y, x);
        b->position.x = b->distFromSun * cos(b->trueAnomly);
        b->position.y = b->distFromSun * sin(b->trueAnomly);

      } else if (b->name == "venus") {
        double N = 76.6799 + 2.46590E-5 * dayNumber;
        double i = 3.3946 + 2.75E-8 * dayNumber;
        double w = 54.8910 + 1.38374E-5 * dayNumber;
        double a = 0.723330;
        double e = 0.006773 - 1.302e-9 * dayNumber;
        double M = 48.0052 + 1.6021302244 * dayNumber;
        if (M < 0) {
          while (M < 0) {
            M = M + 360;
          }
        }
        if (M > 360) {
          while (M > 360) {
            M = M - 360;
          }
        }
        double E =
            M + e * (sin(M) * (180 / M_PI)) * (1 + e * (cos(M) * (180 / M_PI)));
        double x = a * (cos(E) - e);
        double y = a * sqrt(1- e * e) * sin(E);

        b->distFromSun = sqrt((x * x) + (y * y));
        b->trueAnomly = atan2(y, x);
        b->position.x =
            b->distFromSun * cos(b->trueAnomly);
        b->position.y =
            b->distFromSun * sin(b->trueAnomly);
       
      } else if (b->name == "mars") {
        double N = 49.5574 + 2.11081E-5 * dayNumber;
        double i = 1.8497 - 1.78E-8 * dayNumber;
        double w = 286.5016 + 2.92961E-5 * dayNumber;
        double a = 1.523688;
        double e = 0.093405 + 2.516E-9 * dayNumber;
        double M = 18.6021 + 0.5240207766 * dayNumber;
        if (M < 0) {
          while (M < 0) {
            M = M + 360;
          }
        }
        if (M > 360) {
          while (M > 360) {
            M = M - 360;
          }
        }
        double E =
            M + e * (sin(M) * (180 / M_PI)) * (1 + e * (cos(M) * (180 / M_PI)));
        double x = a * (cos(E) - e);
        double y = a * sqrt(1-e * e) * sin(E);

        b->distFromSun = sqrt(x * x + y * y);
        b->trueAnomly = atan2(y, x);
        b->position.x =
            b->distFromSun * cos(b->trueAnomly);
        b->position.y =
            b->distFromSun * sin(b->trueAnomly);
       
      } else if (b->name == "jupiter") {
        double N = 100.4542 + 2.76854E-5 * dayNumber;
        double i = 1.3030 - 1.557E-7 * dayNumber;
        double w = 273.8777 + 1.64505E-5 * dayNumber;
        double a = 5.20256;
        double e = 0.048498 + 4.469E-9 * dayNumber;
        double M = 19.8950 + 0.0830853001 * dayNumber;
        if (M < 0) {
          while (M < 0) {
            M = M + 360;
          }
        }
        if (M > 360) {
          while (M > 360) {
            M = M - 360;
          }
        }
        double E =
            M + e * (sin(M) * (180 / M_PI)) * (1 + e * (cos(M) * (180 / M_PI)));
        double x = a * (cos(E) - e);
        double y = a * sqrt(1-e * e) * sin(E);

        b->distFromSun = sqrt(x * x + y * y);
        b->trueAnomly = atan2(y, x);
        b->position.x =
            b->distFromSun * cos(b->trueAnomly);
        b->position.y =
            b->distFromSun * sin(b->trueAnomly);
        
      } else if (b->name == "saturn") {
        double N = 113.6634 + 2.38980E-5 * dayNumber;
        double i = 2.4886 - 1.081E-7 * dayNumber;
        double w = 339.3939 + 2.97661E-5 * dayNumber;
        double a = 9.55475;
        double e = 0.055546 - 9.499E-9 * dayNumber;
        double M = 316.9670 + 0.0334442282 * dayNumber;
        if (M < 0) {
          while (M < 0) {
            M = M + 360;
          }
        }
        if (M > 360) {
          while (M > 360) {
            M = M - 360;
          }
        }
        double E =
            M + e * (sin(M) * (180 / M_PI)) * (1 + e * (cos(M) * (180 / M_PI)));
        double x = a * (cos(E) - e);
        double y = a * sqrt(1-e * e) * sin(E);

        b->distFromSun = sqrt(x * x + y * y);
        b->trueAnomly = atan2(y, x);
        b->position.x =
            b->distFromSun * cos(b->trueAnomly);
        b->position.y =
            b->distFromSun * sin(b->trueAnomly);
        
      } else if (b->name == "uranus") {
        double N = 74.0005 + 1.3978E-5 * dayNumber;
        double i = 0.7733 + 1.9E-8 * dayNumber;
        double w = 96.6612 + 3.0565E-5 * dayNumber;
        double a = 19.18171 - 1.55E-8 * dayNumber;
        double e = 0.047318 + 7.45E-9 * dayNumber;
        double M = 142.5905 + 0.011725806 * dayNumber;
        if (M < 0) {
          while (M < 0) {
            M = M + 360;
          }
        }
        if (M > 360) {
          while (M > 360) {
            M = M - 360;
          }
        }
        double E =
            M + e * (sin(M) * (180 / M_PI)) * (1 + e * (cos(M) * (180 / M_PI)));
        double x = a * (cos(E) - e);
        double y = a * sqrt(1-e * e) * sin(E);

        b->distFromSun = sqrt(x * x + y * y);
        b->trueAnomly = atan2(y, x);
        b->position.x =
            b->distFromSun * cos(b->trueAnomly);
        b->position.y =
            b->distFromSun * sin(b->trueAnomly);
        
      } else if (b->name == "neptune") {
        double N = 131.7806 + 3.0173E-5 * dayNumber;
        double i = 1.7700 - 2.55E-7 * dayNumber;
        double w = 272.8461 - 6.027E-6 * dayNumber;
        double a = 30.05826 + 3.313E-8 * dayNumber;
        double e = 0.008606 + 2.15E-9 * dayNumber;
        double M = 260.2471 + 0.005995147 * dayNumber;
        if (M < 0) {
          while (M < 0) {
            M = M + 360;
          }
        }
        if (M > 360) {
          while (M > 360) {
            M = M - 360;
          }
        }
        double E =
            M + e * (sin(M) * (180 / M_PI)) * (1 + e * (cos(M) * (180 / M_PI)));
        double x = a * (cos(E) - e);
        double y = a * sqrt(1-e * e) * sin(E);

        b->distFromSun = sqrt(x * x + y * y);
        b->trueAnomly = atan2(y, x);
        b->position.x =
            b->distFromSun * cos(b->trueAnomly);
        b->position.y =
            b->distFromSun * sin(b->trueAnomly);
        
      }
    }
    
  }
  };

class Solarsystem {
  private:
   vector<Body*> bodies;

  public:
   Solarsystem() {
     
      Body* sun = new Body("sun");
      Body* mercury = new Body("mercury");
      Body* venus = new Body("venus");
      Body* earth = new Body("earth");
      Body* mars = new Body("mars");
      Body* jupiter = new Body("jupiter");
      Body* saturn = new Body("saturn");
      Body* uranus = new Body("uranus");
      Body* neptune = new Body("neptune");

      bodies.push_back(sun);
      bodies.push_back(mercury);
      bodies.push_back(venus);
      bodies.push_back(earth);
      bodies.push_back(mars);
      bodies.push_back(jupiter);
      bodies.push_back(saturn);
      bodies.push_back(uranus);
      bodies.push_back(neptune);

      Body::setPosition(bodies);
      

   }


  ~Solarsystem() {
    for (auto b : bodies) {
      delete b;
    }
  }

  friend ostream& operator<<(ostream& s, const Solarsystem& Sol) {
    for (auto b : Sol.bodies) {
      s << " " << *b << " ";
    }
    return s;
  }
};

int main() {
  ///========testing purposes=========== //

  bool flag = true;

  /*
    cout << "press choise one to display the current soloar system";
    int choice;
    cin >> choice;
    if (choice == 1)  {
      Solarsystem s;
      cout << s;
    }
    */
  Solarsystem s;
  cout << s;

  ///========testing purposes=========== //
}