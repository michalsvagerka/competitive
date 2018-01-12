#include "lib.h"
/*
auto polar = [](pii&a,pii&b) {
    if (a.y==0&&a.x>0) return true;
	if (b.y==0&&b.x>0) return false;
	if (a.y>0&&b.y<0) return true;
	return !(a.y<0&&b.y>0) && ((ll)a.x*b.y-(ll)a.y*b.x)>0;
};
*/
typedef pair<ll,ll> pll;

ll ccw(const pll&a, const pll&b, const pll&c) { return (ll)(b.x-a.x)*(c.y-a.y) - (ll)(b.y-a.y)*(c.x-a.x); }
ll area(const pll&a,const pll&b,const pll&c) { return abs(ccw(a,b,c)); }
int orientation(const pll&a, const pll&b, const pll&c) { auto o = ccw(a,b,c); return (o>0)-(o<0); }
bool collinear(const pll&a, const pll&b, const pll&c) { return orientation(a,b,c) == 0; }
bool onSegment(const pll&p, const pll&q, const pll&r) {
    return collinear(p,q,r) && q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}
bool segmentsIntersect(const pll&p1, const pll&q1, const pll&p2, const pll&q2) {
    return (orientation(p1, q1, p2) != orientation(p1, q1, q2) && orientation(p2, q2, p1) != orientation(p2, q2, q1))
           || onSegment(p1, p2, q1) || onSegment(p1, q2, q1) || onSegment(p2, p1, q2) || onSegment(p2, q1, q2);
}
double pointLineDist(const pll&a, const pll&b, const pll&c) {
    ll px = c.x - b.x, py = c.y - b.y, dAB = px * px + py * py;
    return abs(py*a.x - px*a.y + c.x * b.y - c.y * b.x) / sqrt(dAB);
}

double pointSegmentDistance(const pll&a, const pll&b, const pll&c){
    ll px = c.x - b.x, py = c.y - b.y, dAB = px * px + py * py;
    double u = double((a.x - b.x) * px + (a.y - b.y) * py) / dAB;
    if (u > 1) u = 1;
    if (u < 0) u = 0;
    double dx = b.x + u * px - a.x, dy = b.y + u * py - a.y;
    return sqrt(dx*dx+dy*dy);
}

pair<double,double> pointLineProjection(const pll&a, const pll&b, const pll&c){
    ll px = c.x - b.x, py = c.y - b.y, dAB = px * px + py * py;
    double u = ((a.x - b.x) * px + (a.y - b.y) * py) / dAB;
    double x = b.x + u * px, y = b.y + u * py;
    return {x,y};
}


/*
vector<pii> convexhull(const vector<pii> &v) {
    int N = v.size(); vector<pii> w(N+1); int lo = 0;
    for (int i = 0; i<N; ++i) if (v[i].y < v[lo].y) lo = i;
    pii o = v[lo];
    for (int i = 0; i<N; ++i) w[i+1] = {v[i].x-o.x,v[i].y-o.y};
    swap(w[1],w[lo+1]);
    sort(w.begin()+2,w.end(),polar);
    w[0] = w[N];
    int M=1;
    for (int i=2;i<=N;++i) {
        while(ccw(w[M-1],w[M],w[i]) <= 0) if (M>1) --M; else if (i == N) break; else ++i;
        ++M;
        swap(w[M],w[i]);
    }
    vector<pii> res(M);
    for (int i=0;i<M;++i) res[i] = {w[i+1].x+o.x,w[i+1].y+o.y};
    return res;
}

*/