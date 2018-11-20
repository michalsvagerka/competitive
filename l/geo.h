#include "lib.h"
#include "random.h"
#include "int128.h"

constexpr double PI = 3.14159265358979323846;
template <typename T> struct Segment;

template <typename T> struct Point : public pair<T,T> {
    Point(T a=0,T b=0) : pair<T,T>(a,b) {}
    Point(const pair<T,T> &p) : pair<T,T>(p.x,p.y) {}
    Point(const Point<T>&p) = default;
    Point<T>& operator=(const Point<T>&p) = default;

    T squaredDistance(const Point<T>&o) const { return Segment<T>{*this,o}.squaredLength(); }
    double distance(const Point<T>&o) const { return Segment<T>{*this,o}.length(); }
};

template <typename T> ostream& operator<<(ostream&o, const Point<T>&p) { o << p.x << ' ' << p.y; return o; }

template <typename T> T ccw(const Point<T>&a, const Point<T>&b, const Point<T>&c) { return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x); }
template <typename T> T area(const Point<T>&a,const Point<T>&b,const Point<T>&c) { return abs(ccw(a,b,c)); }
template <typename T> double cosangle(const Point<T>&a, const Point<T> &b, const Point<T> &c) {
    return ((b.x-a.x)*(c.x-a.x) + (b.y-a.y)*(c.y-a.y)) / a.distance(b) / a.distance(c);
}

template <typename T> bool acuteAngle(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
    return ((b.x-a.x)*(c.x-a.x) + (b.y-a.y)*(c.y-a.y)) > 0;
}
template <typename T> bool obtuseAngle(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
    return ((b.x-a.x)*(c.x-a.x) + (b.y-a.y)*(c.y-a.y)) < 0;
}
template <typename T> bool rightAngle(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
    return ((b.x-a.x)*(c.x-a.x) + (b.y-a.y)*(c.y-a.y)) == 0;
}
template <typename T> double angle(const Point<T>&a, const Point<T> &b, const Point<T> &c) {
    return acos(cosangle(a,b,c));
}
template <typename T> int orientation(const Point<T>&a, const Point<T>&b, const Point<T>&c) { auto o = ccw(a,b,c); return (o>1e-6)-(o<-1e-6); }
template <typename T> bool collinear(const Point<T>&a, const Point<T>&b, const Point<T>&c) { return orientation(a,b,c) == 0; }

template <typename T> struct Segment : public pair<Point<T>,Point<T>> {
    using pair<Point<T>,Point<T>>::x;
    using pair<Point<T>,Point<T>>::y;
    explicit Segment(Point<T> a={0,0}, Point<T> b={0,0}) : pair<Point<T>,Point<T>>(a,b) {}
    Segment(const Segment<T>&) = default;
    Segment<T>& operator=(const Segment<T>&) = default;
    inline T dx() const { return x.x - y.x; }
    inline T dy() const { return x.y - y.y; }
    T squaredLength() const { return dx()*dx()+dy()*dy(); }
    double length() const { return sqrt(squaredLength()); }
    
    bool contains(const Point<T> &q) const {
        return collinear(x,q,y) && ((q.x <= max(x.x, y.x) && q.x >= min(x.x, y.x)) && (q.y <= max(x.y, y.y) && q.y >= min(x.y, y.y)));
    }
    
    double distance(const Point<T>&p) const {
        double u = ((p.x-y.x) * dx() + (p.y-y.y) * dy()) / double(dx()*dx()+dy()*dy());
        if (u > 1) u = 1;
        if (u < 0) u = 0;
        return Point<double>(p.x,p.y).distance({y.x + u * dx(), y.y + u * dy()});
    }
    
    bool intersect(const Segment<T>&s) const {
        return (orientation(x, y, s.x) != orientation(x, y, s.y) && orientation(s.x, s.y, x) != orientation(s.x, s.y, y))
               || contains(s.x) || contains(s.y) || s.contains(x) || s.contains(y);
    }
};

template <typename T> struct Line : public pair<Point<T>,Point<T>> {
    using pair<Point<T>,Point<T>>::x;
    using pair<Point<T>,Point<T>>::y;
    Line(Point<T> a = {0, 0}, Point<T> b = {0, 0}) : pair<Point<T>, Point<T>>(a, b) {}
    explicit Line(const Segment<T> &s) : pair<Point<T>, Point<T>>(s.x, s.y) {}
    Line(const Line<T> &p) = default;
    Line<T> &operator=(const Line<T> &p) = default;
    inline T dx() const { return x.x - y.x; }
    inline T dy() const { return x.y - y.y; }
    inline T c() const { return x.y * y.x - x.x * y.y; }

    double distance(const Point<T> &p) const {
        ll px = dx(), py = dy(), dL = px * px + py * py;
        return abs(py * p.x - px * p.y + y.x * x.y - y.y * x.x) / sqrt(dL);
    }

    Point<double> project(const Point<T> &p) const {
        double u = ((p.x - y.x) * dx() + (p.y - y.y) * dy()) / double(dx() * dx() + dy() * dy());
        return {y.x + u * dx(), y.y + u * dy()};
    }

    bool parallel(const Line<T> &l) const {
        return abs(l.dx() * dy()-l.dy() * dx()) < 1e-6;
    }

    Point<double> intersection(const Line<T> &l) {
        double det = l.dx() * dy()-l.dy() * dx();
        if (abs(det) < 1e-6) /// det == 0
            return {1e300, 1e300}; /// no intersection
        else {
            double c1 = c(), c2 = l.c();
            double x = -(c2 * dx() - l.dx() * c1) / det;
            double y = -(-l.dy() * c1 + c2 * dy()) / det;
            return {x, y};
        }
    };
};

template <typename T> T cramer(const std::array<T, 9> &X) {
    return X[0] * X[4] * X[8] + X[1] * X[5] * X[6] + X[2] * X[3] * X[7] - X[0] * X[5] * X[7] - X[1] * X[3] * X[8] - X[2] * X[4] * X[6];
}


template <typename T> struct Circle {
    Point<T> center;
    T sqRadius;


    bool contains(const Point<T>&p) const {
        return p.squaredDistance(center) <= sqRadius;
    }

// Checking intersection of two circles be like
/// sqrt(d) <= sqrt(a) + sqrt(b)
/// d <= a + b + 2sqrt(ab)
//  d - (a+b) <= 2sqrt(ab)
//  (d - (a+b))^2 <= 4ab
// but d, a & b are already squared distances, so this fits into ll only if coords <= 3e4
// so for exactness, int128 is needed


    //    bool intersect(const Circle<T>&o) const {
//        return o.center.squaredDistance(center) <= (radius+o.radius)*(radius+o.radius);
//    }
//    bool contains(const Circle<T>&o) const {
//        return radius>=o.radius && o.center.squaredDistance(center) <= (radius-o.radius)*(radius-o.radius);
//    }
//    bool touches(const Circle<T>&o) const {
//        T dist = center.squaredDistance(o.center);
//        return dist == (radius-o.radius)*(radius-o.radius) || dist == (radius+o.radius)*(radius+o.radius);
//    }

    Circle(const Point<T> &c, T r) : center(c), sqRadius(r) {}
    explicit Circle(const Point<T> &p) : center(p), sqRadius(0) {}
    explicit Circle(const Point<T> &a, const Point<T> &b) : center((a.x+b.x)/2, (a.y+b.y)/2), sqRadius(a.squaredDistance(b)/4) {}
    explicit Circle(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
        T la = a.squaredDistance({0,0}), lb = b.squaredDistance({0,0}), lc = c.squaredDistance({0,0});
        T x = cramer<T>({ la, a.y, 1, lb, b.y, 1, lc, c.y, 1 }) / 2;
        T y = cramer<T>({ a.x, la, 1, b.x, lb, 1, c.x, lc, 1 }) / 2;
        T s = cramer<T>({ a.x, a.y, 1, b.x, b.y, 1, c.x, c.y, 1 });
        center.x = x / s;
        center.y = y / s;
        sqRadius = center.squaredDistance(a);
    }

    static Circle minimumEnclosing(vector<Point<T>> p, bool randomize = true) {
        if (randomize) shuffle(p.begin(), p.end(), rng);
        vector<Point<T>> V;
        return welzl(p.begin(), p.end(), V);
    }

private:
    static Circle welzl(typename vector<Point<T>>::const_iterator it, typename vector<Point<T>>::const_iterator itend, vector<Point<T>> &p) {
        if (it == itend || p.size() == 3) {
            if (p.size() == 1) return Circle{p[0]};
            else if (p.size() == 2) return Circle{p[0], p[1]};
            else if (p.size() == 3) return Circle(p[0], p[1], p[2]);
            else return {Point<T>{0,0}, 0};
        } else {
            Circle d = welzl(next(it), itend, p);
            if (d.contains(*it)) return d;
            else {
                p.push_back(*it);
                d = welzl(next(it), itend, p);
                p.pop_back();
                return d;
            }
        }
    }
};

template <typename T> struct Polygon : public vector<Point<T>> {
    using vector<Point<T>>::vector;
    using vector<Point<T>>::at;
    using vector<Point<T>>::front;
    using vector<Point<T>>::back;

    T doubleSignedArea() const {
        if (this->empty()) return T(0);
        T area = back().x*front().y - back().y*front().x;
        for (int i = 0; i < this->size()-1; ++i) area += (at(i).x * at(i+1).y - at(i+1).x * at(i).y);
        return area;
    }

    double circumference() const {
        if (this->empty()) return T(0);
        T res = back().distance(front());
        for (int i = 0; i < this->size()-1; ++i) res += at(i).distance(at(i+1));
        return res;
    }
};

template <typename T> Polygon<T> convexhull(const vector<Point<T>> &v) {
    ui N = (ui)v.size(); vector<Point<T>> w(N+1); int lo = 0;
    for (int i = 0; i<N; ++i) if (v[i].y < v[lo].y || (v[i].y == v[lo].y && v[i].x < v[lo].x)) lo = i;
    Point<T> o = v[lo];
    for (int i = 0; i<N; ++i) w[i+1] = {v[i].x-o.x,v[i].y-o.y};
    swap(w[1],w[lo+1]);

//    sort(w.begin()+2,w.end(),[](Point<T>&a,Point<T>&b) {
//        if (a.y==0&&a.x>0) return true;
//        if (b.y==0&&b.x>0) return false;
//        if (a.y>0&&b.y<0) return true;
//        return !(a.y<0&&b.y>0) && (a.x*b.y-a.y*b.x)>0;
//    });

    sort(w.begin()+2,w.end(),[](Point<T>&a,Point<T>&b) {
        if (a.y==0) return b.y != 0 || a.x < b.x;
        if (b.y==0) return false;
        auto disc = (a.x*b.y-a.y*b.x);
        return disc > 0 || (disc == 0 && a.y < b.y);
    });
    w[0] = w[N];
    ui M=1;
    for (int i=2;i<=N;++i) {
        while(ccw(w[M-1],w[M],w[i]) <= 0) if (M>1) --M; else if (i == N) break; else ++i;
        ++M; swap(w[M],w[i]);
    }
    Polygon<T> res(M);
    for (int i=0;i<M;++i) res[i] = {w[i+1].x+o.x,w[i+1].y+o.y};
    return res;
}

