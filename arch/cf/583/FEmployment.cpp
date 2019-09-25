#include "../l/lib.h"
#include "../l/segtree.h"

class FEmployment {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> M >> N;
        vector<pii> A(N), B(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i].x;
            A[i].x--;
            A[i].y = i;
        }
        for (int i = 0; i < N; ++i) {
            cin >> B[i].x;
            B[i].x--;
            B[i].y = i;
        }
        sort(A.begin(),A.end());
        sort(B.begin(),B.end());

//        vector<ll> BR(N,0);
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                int x = 0;
//                int a = A[i].x, b = B[j].x;
//                int l = (M+a-b)%M, r = (M+b-a)%M;
//                int sh = (N+j-i)%N;
//                BR[sh] += min(l,r);
//            }
//        }
//        cout << BR;

        AddSumTree<ll> T;
        T.setup(2*N, 0);
        vector<int> C1(N, N), C2(N, N), C3(N, N);
        int left = 0, mid = 0, right = 0;
        for (int i = 0; i < N; ++i) {
            int a = A[i].x;
            int sh = N-i;
            while (left != N && B[left].x < a - M/2) { C1[left] = i; left++; }
            while (mid != N && B[mid].x < a) { C2[mid] = i; mid++; }
            while (right != N && B[right].x < a + (M+1)/2) { C3[right] = i; right++; }

            if (left != 0) T.put(sh+0, sh+left-1, M - a); // +b
            if (left != mid) T.put(sh+left, sh+mid-1, a); // -b
            if (mid != right) T.put(sh+mid, sh+right-1, - a); // +b
            if (right != N) T.put(sh+right, sh+N-1, M + a); // -b;

        }

        for (int i = 0; i < N; ++i) {
            int b = B[i].x;
            int sh = i + 1;
            if (C3[i] != 0) T.put(sh+(N-1)-(C3[i]-1), sh+(N-1)-0, -b);
            if (C3[i] != C2[i]) T.put(sh+(N-1)-(C2[i]-1), sh+(N-1)-C3[i], b);
            if (C1[i] != C2[i]) T.put(sh+(N-1)-(C1[i]-1), sh+(N-1)-C2[i], -b);
            if (C1[i] != N) T.put(sh+(N-1)-(N-1), sh+(N-1)-C1[i], b);

        }

        vector<ll> SH(N, 0);
        for (int i = 0; i < N; ++i) {
            SH[i] = T.get(i) + T.get(N+i);
        }

        int best = 0;
        for (int i = 0; i < N; ++i) {
            if (SH[i] < SH[best]) best = i;
        }

        vector<int> ID(N, -1);
        for (int i = 0; i < N; ++i) {
            int j = (i + best)%N;
//            cout << i << ' ' << j << endl;
            ID[A[i].y] = B[j].y + 1;
        }

        cout << SH[best] << endl;
        cout << ID;
    }
};
