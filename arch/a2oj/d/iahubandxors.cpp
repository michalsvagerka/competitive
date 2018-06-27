#include "../l/lib.h"

template<typename T> struct Fenwick2 {
    explicit Fenwick2(ui N=0, T t=T()):N(1u<<logceil(N)),F(this->N,this->N,t),t(t){}
    void add(int x, int y, T v){
        while(x<=N){ int z = y; while(z<=N) { F[x][z] ^= v; z += lsb(z+1); }x +=lsb(x+1); }
    }

    T sum(int x, int y) {
        T sum(t);
        while (x <= N) { int z = y;while (z <= N) { sum ^= F[x][z];z -= lsb(z + 1); }x -= lsb(x + 1); }
        return sum;
    }
    T range(int x1, int y1, int x2, int y2) {
        T ans = sum(x2, y2);
        if (x1) ans ^= sum(x1-1, y2);
        if (y1) ans ^= sum(x2, y1-1);
        if (x1 && y1) ans ^= sum(x1-1,y1-1);
        return ans;
    }
    constexpr int lsb(int i)const{return i&-i;}
    ui N;vector2<T> F;T t;
};

class iahubandxors {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        ui W = N/2+3;
        vector<vector<Fenwick2<ll>>> F(2);
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                F[i].emplace_back(W, 0);
            }
        }

        for (int i = 0; i < M; ++i) {
            int t, x1, y1, x2, y2; cin >> t >> x1 >> y1 >> x2 >> y2;
            --x1; --y1; --x2; --y2;
            if (t == 1) {
                --x1; --y1;
                ll ans = F[x2%2][y2%2].sum(x2/2,y2/2);
                if (x1 >= 0) ans ^= F[x1%2][y2%2].sum(x1/2,y2/2);
                if (y1 >= 0) ans ^= F[x2%2][y1%2].sum(x2/2,y1/2);
                if (x1 >= 0 && y1 >= 0) ans ^= F[x1%2][y1%2].sum(x1/2,y1/2);
                cout << ans << '\n';
            } else {
                ll x; cin >> x;
                x2++; y2++;
                F[x1%2][y1%2].add(x1/2,y1/2,x);
                F[x2%2][y1%2].add(x2/2,y1/2,x);
                F[x1%2][y2%2].add(x1/2,y2/2,x);
                F[x2%2][y2%2].add(x2/2,y2/2,x);
            }
        }



    }
};
