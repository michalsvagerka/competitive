auto polar = [](pii&a,pii&b) {
    if (a.y==0&&a.x>0) return true;
	if (b.y==0&&b.x>0) return false;
	if (a.y>0&&b.y<0) return true;
	return !(a.y<0&&b.y>0) && ((ll)a.x*b.y-(ll)a.y*b.x)>0;
};
typedef pair<ll,ll> pll;

ll ccw(const pll&a, const pll&b, const pll&c) { return (ll)(b.x-a.x)*(c.y-a.y) - (ll)(b.y-a.y)*(c.x-a.x); }
ll area(const pll&a,const pll&b,const pll&c) { return abs(ccw(a,b,c)); }

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

