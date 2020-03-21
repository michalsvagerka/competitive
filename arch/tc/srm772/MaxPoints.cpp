#include "../l/lib.h"
#include "../l/fenwick.h"
class MaxPoints {
public:
    int findMaxPoints(int N, vector <int> XG, vector <int> YG, long long K, int seedX, int seedY) {
        vector<int> A(N), X(N), B(N), Y(N);
        A[0] = seedX;
        for (int i = 1; i < N; ++i) A[i] = (A[i-1]*1103515245LL + 12345) % 2147483648LL;
        for (int i = 0; i < XG.size(); ++i) X[i] = XG[i];
        for (int i = XG.size(); i < N; ++i) X[i] = (A[i] % 2000001) - 1000000;

        B[0] = seedY;
        for (int i = 1; i < N; ++i) B[i] = (B[i-1]*1103515245LL + 12345) % 2147483648LL;
        for (int i = 0; i < YG.size(); ++i) Y[i] = YG[i];
        for (int i = XG.size(); i < N; ++i) Y[i] = (B[i] % 2000001) - 1000000;

        vector<ll> All(N, 0);
        vector<pii> XX(N), YY(N);
        for (int i = 0; i < N; ++i) {
            XX[i] = {X[i], i};
            YY[i] = {Y[i], i};
        }
        sort(XX.begin(),XX.end());
        sort(YY.begin(),YY.end());
        vector<ll> XXX(N), YYY(N);
        for (int i = 0; i < N; ++i) {
            XXX[i] = XX[i].x;
            YYY[i] = YY[i].x;
        }
        Fenwick<ll> FX{XXX, 0LL}, FY{YYY, 0LL};
        for (int i = 0; i < N; ++i) {
            All[XX[i].y] += i * ll(XX[i].x) - (i==0?0:FX.range(0,i-1)) + (i==N-1?0:FX.range(i+1,N-1)) - (N-i-1) * ll(XX[i].x);
            All[YY[i].y] += i * ll(YY[i].x) - (i==0?0:FY.range(0,i-1)) + (i==N-1?0:FY.range(i+1,N-1)) - (N-i-1) * ll(YY[i].x);
        }

//        vector<ll> Brute(N, 0);
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                Brute[i] += abs(X[i]-X[j]) + abs(Y[i]-Y[j]);
//            }
//        }
//        cerr << Brute;

        sort(All.begin(),All.end());
        K *= 2;
        ll tot = accumulate(All.begin(),All.end(),0LL);
        int ans = N;
        while (ans >= 0 && tot > K) {
            ans--;
            if (ans >= 0) tot -= 2*All[ans];
        }
        return ans;
    }
    
    void solve(istream& cin, ostream& cout) {
        cout << findMaxPoints(3,{1, 2, 1000},{1, 2, 1000},2,1,1) << endl;
        cout << findMaxPoints(3,{1, 1, 1},{2, 2, 2},0,1,1) << endl;
        cout << findMaxPoints(3,{1, 1, 1},{2, 2, 2}, -1,1,1) << endl;
        cout << findMaxPoints(4,{},{}, -5397718,1825126330,704277911) << endl;
        cout << findMaxPoints(100000,{},{}, -3829423936963408,1225224201,441244497) << endl;
    }
};
