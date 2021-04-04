#include <cmath>
#include <iostream>

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

int main() {
  ///========testing purposes=========== //
  Vector3D a;
  Vector3D b(1, 3, 5);
  Vector3D c(4, 4, 6);

  Vector3D d = b + c;
  Vector3D e = b - c;
  Vector3D f = b * c;
  Vector3D g = b / c;

  Vector3D j = 1.56 * b;
  Vector3D k = b * 1.56;
  Vector3D i = 1.56 / b;
  Vector3D z = b / 1.56;

  cout << b.dot(c) << endl;
  cout << b.mag() << endl;
  cout << b.dist(c) << endl;
  cout << b.normalize() << endl;
  cout << b.perpendicular() << endl;
  cout << b.cross(c) << endl;
  cout << b.anglebetween(c) << endl;

  cout << endl;
  cout << endl;

  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  cout << d << endl;
  cout << e << endl;
  cout << f << endl;
  cout << g << endl;
  cout << j << endl;
  cout << k << endl;
  cout << i << endl;
  cout << z << endl;
  ///========testing purposes=========== //
}