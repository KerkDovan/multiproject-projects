#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <deque>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <unordered_map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <valarray>
#include <vector>
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define sqr(x)     ((x) * (x))
#define eq(x, y)   (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)      int((x).size())
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(), (x).rend()
#define let        const auto
#define fst        first
#define snd        second
#define mp         make_pair
#define eb         emplace_back
#define ef         emplace_front
#define mt         make_tuple
#define eps        1e-8
#define inf        int(1e9)
#define linf       llong(4e18)

using namespace std;

struct debug_t {
  template<typename T>
  debug_t& operator << (const T& o) {
#   ifdef LOCAL_DEBUG
    cout<<o<<flush;
#   endif
    return *this;
  }
} debug;

#define TIMESTAMP(msg) debug << "[" msg "] Time = " << clock() * 1.0 / CLOCKS_PER_SEC << '\n'
#define DBG(x) debug << "[" #x "] = " << x << '\n'
#define DOUT(x) debug << x << '\n'
#define _ << " " <<

#ifdef __GNUC__
# define DECLARE_VECTOR(len, bytes, type, name)                                \
    typedef signed type   name##len##v    __attribute__((vector_size(bytes))); \
    typedef unsigned type u##name##len##v __attribute__((vector_size(bytes)));

  DECLARE_VECTOR(16, 16, char, char)
  DECLARE_VECTOR(32, 32, char, char)
  DECLARE_VECTOR(8,  16, short, short)
  DECLARE_VECTOR(16, 32, short, short)
  DECLARE_VECTOR(4,  16, int, int)
  DECLARE_VECTOR(8,  32, int, int)
  DECLARE_VECTOR(2,  16, long long, llong)
  DECLARE_VECTOR(4,  32, long long, llong)

# undef DECLARE_VECTOR
#endif

typedef unsigned char       uchar;
typedef basic_string<uchar> ustring;
typedef long long           llong;
typedef unsigned long long  ullong;
typedef long double         ldouble;
typedef vector<int>         vi;
typedef vector<vi>          vvi;
typedef vector<double>      vd;
typedef vector<vd>          vvd;
typedef pair<int,int>       pii;

const double EPS = 1e-6;

struct Point {
  double x,y;
  Point operator + (const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator - (const Point& p) const { return {x - p.x, y - p.y}; }
  Point operator * (double m) const { return {x * m, y * m}; }
  double operator * (const Point& p) const { return x * p.y - y * p.x; }
  double operator % (const Point& p) const { return x * p.x + y * p.y; }
  Point rotate() const { return {-y, x}; }
  Point rotate(double cosa, double sina) const { return *this * cosa + rotate() * sina; }
  Point rotate(double angle) const { return rotate(cos(angle), sin(angle)); }
  double angle_to(const Point& to) const { return atan2(*this * to, *this % to); }
};

bool line_intersection(Point A, Point B, Point C, Point D, Point& O) {
  double s1 = (C - A) * (D - A);
  double s2 = (D - B) * (C - B);
  double s = s1 + s2;
  if( fabs(s) <= eps )
    return false;
  O = A + (B - A) * (s1 / s);
  return true;
}

double s(const Point& a, const Point& b, const Point& c) {
  return (c - a) * (b - a);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
# ifndef LOCAL_PROJECT
    freopen("i.in", "r", stdin);
    freopen("i.out", "w", stdout);
# endif

  Point a, b, c, p, a1, b1, c1;
  int testCount;
  cin >> testCount;
  for (int test = 0; test < testCount; ++test) {
    int test_num;
    cin >> test_num;
    cout << test_num << ' ';
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    double angle_a, angle_b, angle_c;
    Point ac = c - a, ab = b - a, ba = a - b, bc = c - b, ca = a - c, cb = b - c;
    angle_a = ab.angle_to(ac);
    angle_b = bc.angle_to(ba);
    angle_c = ca.angle_to(cb);
    double left = 0.0, right = min({ angle_a, angle_b, angle_c });
    while (true) {
      double d = (right - left) / 3.0;
      
      double ltry[2] = { left + d, right - d };
      double s1[2];
      for (int i = 0; i < 2; ++i) {
        Point abr, bcr, car;
        abr = ab.rotate(ltry[i]);
        bcr = bc.rotate(ltry[i]);
        car = ca.rotate(ltry[i]);
        line_intersection(b, bcr, c, ca.rotate(ltry[i]), a1);
        line_intersection(a, abr, c, ca.rotate(ltry[i]), b1);
        line_intersection(c, car, b, bc.rotate(ltry[i]), c1);
        s1[i] = s(a1, b1, c1);
      }
      if (s1[0] < s1[1])
        right = ltry[1];
      else
        left = ltry[0];
      if (right - left <= EPS)
        break;
    }
    line_intersection(a, ab.rotate(left), b, bc.rotate(left), p);
    cout << p.x << ' ' << p.y << '\n';
  }

  TIMESTAMP("end");
  return 0;
}
