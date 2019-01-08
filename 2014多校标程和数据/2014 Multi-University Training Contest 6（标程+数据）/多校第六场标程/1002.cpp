#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <map>
#include <queue>
#include <vector>

const double INF = 1E100;
const double EPS = 1E-8;
const double PI = acos(-1.0);

inline int sgn(double x) {
  return x < -EPS ? -1 : x > EPS;
}
inline double sqr(double x) {
  return x * x;
}

class Segment;
class Circle;

class Point {
 public:
  double x, y;
  explicit Point(double x = 0, double y = 0) : x(x), y(y) {}

  bool operator < (const Point& o) const;

  void input();
  double norm2() const;
  double norm() const;
  Point normalize(double length) const;
  Point RotLeft() const;
  Point RotRight() const;

  double DistToPoint(const Point &a) const;
  double DistToLine(const Point &a, const Point &b) const;
  double DistToSegment(const Segment& s) const;
};

enum Relation {INTERSECT, AWAY, CUT};

class Segment {
 public:
  Point a, b;
  Segment() {}
  Segment(Point a, Point b): a(a), b(b) {}

  bool cross(const Segment &v) const;
  bool OnSegment(const Point& p) const;

  Point GetFoot(const Point& p) const;
  Point NearestPointOnSegment(const Point& p) const;

  Relation GetRelation(const Segment& v) const;
  Relation GetRelationLine(const Circle& v) const;
  void GetCrossPoint(const Segment &v, std::vector<Point>& points) const;
  void GetCrossPoint(const Circle &v, std::vector<Point>& points) const;
};

class Circle {
 public:
  Point o;
  double r;

  Circle() {}
  Circle(const Point &o, const double& r) : o(o), r(r) {}

  Relation GetRelation(const Circle& v) const;
  void GetCrossPoint(const Segment& v, std::vector<Point>& cross_point) const;
  void GetCrossPointLine(const Segment& v, std::vector<Point>& cross_point) const;
  void GetCrossPoint(const Circle& v, std::vector<Point>& cross_point) const;
  Point NearestPointOnCircle(const Point& p) const;
};

bool operator == (const Point &a, const Point &b) {
  return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
}
Point operator + (Point a, Point b) {return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) {return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double d) {return Point(a.x * d, a.y * d);}
Point operator * (double d, Point a) {return Point(a.x * d, a.y * d);}
Point operator / (Point a, double d) {return Point(a.x / d, a.y / d);}

double det(Point a, Point b) {return a.x * b.y - a.y * b.x;}
double dot(Point a, Point b) {return a.x * b.x + a.y * b.y;}

double Point::norm2() const {return dot(*this, *this);}
double Point::norm() const {return sqrt(norm2());}
Point Point::normalize(double length = 1) const {
  return *this / norm() * length;
}
Point Point::RotLeft() const {return Point(-y, x);}
Point Point::RotRight() const {return Point(y, -x);}
void Point::input() {scanf("%lf%lf", &x, &y);}

bool Point::operator < (const Point& o) const {
  int flag = sgn(x - o.x);
  return flag ? flag < 0 : sgn(y - o.y) < 0;
}
double Point::DistToPoint(const Point &a) const {
  return (*this - a).norm();
}
double Point::DistToLine(const Point &a, const Point &b) const {
  Point p = *this;
  return fabs(det(p - a, p - b) / (a - b).norm());
}
double Point::DistToSegment(const Segment& s) const {
  Point p = *this;
  Point a = s.a;
  Point b = s.b;
  if (sgn(dot(p - b, a - b)) < 0 || sgn(dot(p - a, b - a)) < 0)
      return std::min(p.DistToPoint(a), p.DistToPoint(b));
  return p.DistToLine(a, b);
}

bool Segment::cross(const Segment &v) const {
  Segment u = *this;
  int d1 = sgn(det(u.b - u.a, v.a - u.a));
  int d2 = sgn(det(u.b - u.a, v.b - u.a));
  int d3 = sgn(det(v.b - v.a, u.a - v.a));
  int d4 = sgn(det(v.b - v.a, u.b - v.a));
  if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return true;
  return (d1 == 0 && sgn(dot(v.a - u.a, v.a - u.b)) <= 0
      || d2 == 0 && sgn(dot(v.b - u.a, v.b - u.b)) <= 0
      || d3 == 0 && sgn(dot(u.a - v.a, u.a - v.b)) <= 0
      || d4 == 0 && sgn(dot(u.b - v.a, u.b - v.b)) <= 0);
}
Relation Segment::GetRelationLine(const Circle& v) const {
  double dist = v.o.DistToLine(a, b);
  if (sgn(dist - v.r) < 0) {
    return INTERSECT;
  }
  if (sgn(dist - v.r) == 0) {
    return CUT;
  }
  return AWAY;
}
bool Segment::OnSegment(const Point &p) const {
    return sgn(det(p - a, p - b)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}
void Segment::GetCrossPoint(
    const Segment &v, std::vector<Point>& cross_point) const {
  cross_point.clear();
  const Segment& u = *this;
  if (!u.cross(v)) {
    return;
  }
  double a1 = det(v.b - v.a, u.a - v.a);
  double a2 = det(v.b - v.a, u.b - v.a);
  cross_point.push_back(Point((u.a.x * a2 - u.b.x * a1) / (a2 - a1),
                              (u.a.y * a2 - u.b.y * a1) / (a2 - a1)));
}
void Segment::GetCrossPoint(
    const Circle &v, std::vector<Point>& cross_point) const {
  return v.GetCrossPoint(*this, cross_point);
}
Point Segment::GetFoot(const Point& p) const {
  return a + ((b - a) * (dot(b - a, p - a) / (b - a).norm2()));
}
Point Segment::NearestPointOnSegment(const Point& p) const {
  const Segment& u = *this;
  Point foot = u.GetFoot(p);
  if (u.OnSegment(foot)) {
    return foot;
  }
  return p.DistToPoint(u.a) < p.DistToPoint(u.b) ? u.a : u.b;
}

Relation Circle::GetRelation(const Circle& v) const {
  double d = o.DistToPoint(v.o);
  if (sgn(d - r - v.r) > 0) return AWAY;
  if (sgn(d - r - v.r) == 0) return CUT;
  double l = fabs(r - v.r);
  if (sgn(d - l) == 0) return CUT;
  if (sgn(d - l) < 0) return AWAY;
  return INTERSECT;
}
void Circle::GetCrossPoint(
    const Segment& v, std::vector<Point>& cross_point) const {
  std::vector<Point> temp;
  GetCrossPointLine(v, temp);
  cross_point.clear();
  for (int i = 0; i < temp.size(); ++ i) {
    if (v.OnSegment(temp[i])) {
      cross_point.push_back(temp[i]);
    }
  }
}
void Circle::GetCrossPointLine(
    const Segment& v, std::vector<Point>& cross_point) const {
  cross_point.clear();
  const Circle& u = *this;
  Relation relation = v.GetRelationLine(u);
  if (relation == AWAY) {
    return;
  }
  Point a = v.GetFoot(o);
  double d = o.DistToLine(v.a, v.b);
  d = sqrt(r * r - d * d);
  if (sgn(d) == 0) {
    cross_point.push_back(a);
    return;
  }
  Point p;
  p = Point(a - ((v.b - v.a).normalize() * d));
  cross_point.push_back(p);
  p = Point(a + ((v.b - v.a).normalize() * d));
  cross_point.push_back(p);
}
void Circle::GetCrossPoint(
    const Circle& v, std::vector<Point>& cross_point) const {
  cross_point.clear();
  int relation = GetRelation(v);
  if (relation == AWAY) {
    return;
  }
  double d = o.DistToPoint(v.o);
  double l = (d + (sqr(r) - sqr(v.r)) / d) / 2;
  double h = sqrt(sqr(r) - sqr(l));
  Point p1 = o + ((v.o - o).normalize(l) + ((v.o - o).RotLeft().normalize(h)));
  Point p2 = o + ((v.o - o).normalize(l) + ((v.o - o).RotRight().normalize(h)));
  if (relation == CUT) {
    cross_point.push_back(p1);
  } else {
    cross_point.push_back(p1);
    cross_point.push_back(p2);
  }
}
Point Circle::NearestPointOnCircle(const Point& p) const {
  std::vector<Point> cross_point;
  GetCrossPointLine(Segment(o, p), cross_point);
  return p.DistToPoint(cross_point[0]) < p.DistToPoint(cross_point[1]) ? 
      cross_point[0] : cross_point[1];
}

class StraightRoad : public Segment {
 public:
  double v;
  void input() {
    a.input();
    b.input();
    scanf("%lf", &v);
    v /= 60;
  }
};

class CircleRoad : public Circle {
 public:
  double v;
  void input() {
    o.input();
    scanf("%lf%lf", &r, &v);
    v /= 60;
  }
};

bool StraightRoadCompare(const Point& a, const Point& b) {
  return a < b;
}
bool CircleRoadCompare(const Point& a, const Point& b) {
  return atan2(a.y, a.x) < atan2(b.y, b.x);
}

std::map<Point, int> point_id;
std::map<int, Point> point_reflection;
int point_counter;

int GetId(const Point& p) {
  if (!point_id.count(p)) {
    point_id[p] = point_counter;
    point_reflection[point_counter ++] = p;
  }
  return point_id[p];
}

const int N = 18;
const int M = 35;
const int P = 2000;

std::vector<Point> packages;
std::vector<StraightRoad> straight_roads;
std::vector<CircleRoad> circle_roads;
std::vector<double> urgency;

bool visit[P];
double min_dist[P];
double cost[N][N];
double dp[1 << N][N], sum_of_urgency[1 << N];
double v_walk, t_wait;
int n, m, size;

using std::pair;
using std::make_pair;
typedef pair<int, double> Edge;

std::vector<Edge> edges[P];

void AddEdge(int u, int v, double w) {
  edges[u].push_back(make_pair(v, w));
  edges[v].push_back(make_pair(u, w));
}

void Initialize() {
  for (int i = 0; i < N; ++ i) {
    for (int j = 0; j < N; ++ j) {
      cost[i][j] = INF;
    }
  }
  for (int i = 0; i < M * M; ++ i) {
    edges[i].clear();
  }
  for (int i = 0; i < 1 << N; ++ i) {
    for (int j = 0; j < N; ++ j) {
      dp[i][j] = INF;
    }
  }
  packages.clear();
  straight_roads.clear();
  circle_roads.clear();
  urgency.clear();
  point_id.clear();
  point_reflection.clear();
  point_counter = 0;
}

std::queue<int> queue;
void AddToQueue(int id, double w) {
  assert(id < size);
  min_dist[id] = w;
  visit[id] = true;
  queue.push(id);
}

void GetShortestPath(const Point& start) {
  for (int i = 0; i < size; ++ i) {
    min_dist[i] = INF;
    visit[i] = false;
  }
  while (!queue.empty()) {
    queue.pop();
  }
  for (int i = 0; i < straight_roads.size(); ++ i) {
    const StraightRoad& sr = straight_roads[i];
    const Point& p = sr.NearestPointOnSegment(start);
    AddToQueue(GetId(p), start.DistToPoint(p) / v_walk + t_wait);
  }
  for (int i = 0; i < circle_roads.size(); ++ i) {
    const CircleRoad& cr = circle_roads[i];
    if (start == cr.o) {
      for (int j = 0; j < size; ++ j) {
        if (sgn(cr.o.DistToPoint(point_reflection[j]) - cr.r) == 0) {
          AddToQueue(GetId(point_reflection[j]), cr.r / v_walk + t_wait);
        }
      }
    } else {
      const Point& p = cr.NearestPointOnCircle(start);
      AddToQueue(GetId(p), start.DistToPoint(p) / v_walk + t_wait);
    }
  }

  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    visit[u] = false;
    for (int i = 0; i < edges[u].size(); ++ i) {
      int v = edges[u][i].first;
      double w = edges[u][i].second;
      if (min_dist[u] + w < min_dist[v]) {
        min_dist[v] = min_dist[u] + w;
        if (!visit[v]) {
          visit[v] = true;
          queue.push(v);
        }
      }
    }
  }
}

int main() {
  int test_count;
  assert(scanf("%d", &test_count) == 1);
  assert(1 <= test_count && test_count <= 10);
  while (test_count --) {
    Initialize();

    assert(scanf("%d%d%lf%lf", &n, &m, &v_walk, &t_wait) == 4);
    assert(1 <= n && n <= 15);
    assert(1 <= m && m <= 30);
    v_walk /= 60;

    n ++;
    packages.resize(n);
    urgency.resize(n);
    packages[0].input();
    urgency[0] = 0; 
    for (int i = 1; i < n; ++ i) {
      packages[i].input();
      scanf("%lf", &urgency[i]);
    }

    char type[10];
    for (int i = 0; i < m; ++ i) {
      assert(scanf("%s", type) == 1);
      if (*type == 'L') {
        StraightRoad sr;
        sr.input();
        straight_roads.push_back(sr);
      } else {
        CircleRoad cr;
        cr.input();
        circle_roads.push_back(cr);
      }
    }

    std::vector<Point> event_points;
    for (int i = 0; i < straight_roads.size(); ++ i) {
      const StraightRoad& sr = straight_roads[i];
      event_points.clear();
      event_points.push_back(sr.a);
      event_points.push_back(sr.b);

      for (int j = 0; j < n; ++ j) {
        Point p = sr.NearestPointOnSegment(packages[j]);
        event_points.push_back(p);
      }
      for (int j = 0; j < straight_roads.size(); ++ j) {
        if (i == j) {
          continue;
        }
        std::vector<Point> cross_point;
        sr.GetCrossPoint(straight_roads[j], cross_point);
        for (int k = 0; k < cross_point.size(); ++ k) {
          event_points.push_back(cross_point[k]);
        }
      }
      for (int j = 0; j < circle_roads.size(); ++ j) {
        std::vector<Point> cross_point;
        sr.GetCrossPoint(circle_roads[j], cross_point);
        for (int k = 0; k < cross_point.size(); ++ k) {
          event_points.push_back(cross_point[k]);
        }
      }

      std::sort(event_points.begin(), event_points.end(), StraightRoadCompare);
      event_points.resize(unique(event_points.begin(), event_points.end()) -
          event_points.begin());

      for (int j = 0; j + 1 < event_points.size(); ++ j) {
        int x = GetId(event_points[j]);
        int y = GetId(event_points[j + 1]);
        AddEdge(x, y, event_points[j].DistToPoint(event_points[j + 1]) / sr.v);
      }
    }

    for (int i = 0; i < circle_roads.size(); ++ i) {
      const CircleRoad& cr = circle_roads[i];
      event_points.clear();
      
      for (int j = 0; j < n; ++ j) {
        if (cr.o == packages[j]) {
          continue;
        }
        Point p = cr.NearestPointOnCircle(packages[j]);
        event_points.push_back(p);
      }
      for (int j = 0; j < straight_roads.size(); ++ j) {
        std::vector<Point> cross_point;
        cr.GetCrossPoint(straight_roads[j], cross_point);
        for (int k = 0; k < cross_point.size(); ++ k) {
          event_points.push_back(cross_point[k]);
        }
      }
      for (int j = 0; j < circle_roads.size(); ++ j) {
        if (i == j) {
          continue;
        }
        std::vector<Point> cross_point;
        cr.GetCrossPoint(circle_roads[j], cross_point);
        for (int k = 0; k < cross_point.size(); ++ k) {
          event_points.push_back(cross_point[k]);
        }
      }

      std::sort(event_points.begin(), event_points.end(), CircleRoadCompare);
      event_points.resize(unique(event_points.begin(), event_points.end()) -
          event_points.begin());
      if (event_points.size() > 1) {  // Connect the first and last points on the circle
        event_points.push_back(event_points[0]);
      }
      for (int j = 0; j + 1 < event_points.size(); ++ j) {
        int x = GetId(event_points[j]);
        int y = GetId(event_points[j + 1]);
        double d = event_points[j].DistToPoint(event_points[j + 1]);
        double w = cr.r * acos(1 - d * d / 2 / cr.r / cr.r);
        AddEdge(x, y, w / cr.v);
      }
    }

    size = point_counter;
    for (int src = 0; src < n; ++ src) {
      GetShortestPath(packages[src]);
      for (int dest = 0; dest < n; ++ dest) {
        if (src == dest) {
          continue;
        }
        cost[src][dest] = packages[src].DistToPoint(packages[dest]) / v_walk;

        for (int r = 0; r < straight_roads.size(); ++ r) {
          Point p = straight_roads[r].NearestPointOnSegment(packages[dest]);
          double w = min_dist[GetId(p)] + p.DistToPoint(packages[dest]) /
              v_walk;
          cost[src][dest] = std::min(cost[src][dest], w);
        }
        for (int r = 0; r < circle_roads.size(); ++ r) {
          const CircleRoad& cr = circle_roads[r];
          if (packages[dest] == cr.o) {
            for (int i = 0; i < size; ++ i) {
              if (sgn(point_reflection[i].DistToPoint(cr.o) - cr.r) == 0) {
                Point p = point_reflection[i];
                double w = min_dist[GetId(p)] + p.DistToPoint(packages[dest]) /
                    v_walk;
                cost[src][dest] = std::min(cost[src][dest], w);
              }
            }
          } else {
            Point p = cr.NearestPointOnCircle(packages[dest]);
            double w = min_dist[GetId(p)] + p.DistToPoint(packages[dest]) /
                v_walk;
            cost[src][dest] = std::min(cost[src][dest], w);
          }
        }
      }
    }

    for (int mask = 0; mask < 1 << n; ++ mask) {
      sum_of_urgency[mask] = 0;
      for (int u = 0; u < n; ++ u) {
        if (1 << u & mask) {
          sum_of_urgency[mask] += urgency[u];
        }
      }
    }

    int full_mask = (1 << n) - 1;
    dp[1][0] = 0;
    for (int mask = 1; mask < 1 << n; ++ mask) {
      for (int u = 0; u < n; ++ u) {
        if (!(1 << u & mask)) {
          continue;
        }
        for (int v = 0; v < n; ++ v) {
          if (1 << v & mask) {
            continue;
          }
          dp[mask | 1 << v][v] = std::min(dp[mask | 1 << v][v],
              dp[mask][u] + cost[u][v] * sum_of_urgency[full_mask ^ mask]);
        }
      }
    }
    double answer = INF;
    for (int u = 1; u < n; ++ u) {
      answer = std::min(answer, dp[full_mask][u]);
    }
    printf("%.2f\n", answer);
  }
  return 0;
}
