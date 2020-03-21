#include "../l/lib.h"

class CBeautifulRectangle {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        map<int,int> C;
        for (int a: A) C[a]++;
        vector<int> W;
        for (pii c: C) W.push_back(c.y);
        sort(W.begin(),W.end());

        int M = W.size();
        vector<int> Pref(M+1, 0);
        for (int i = 0; i < M; ++i) Pref[i+1] = Pref[i] + W[i];
        int best = 1;
        int rows = 1;
        int j = 0;
        for (int i = 1; i <= M; ++i) {
            while (j < M && W[j] < i) ++j;
            int cols = Pref[j]/i + (M-j);
            if (cols >= i && cols*i > best) { best = cols*i; rows = i; }
        }

        int cols = best/rows;
        vector2<int> Ans(rows, cols, -1);
        int i = 0;
        for (pii c: C) {
            if (c.y >= rows) {
                if (i == cols) continue;
                for (int j = 0; j < rows; ++j) {
                    Ans[j][(j+i)%cols] = c.x;
                }
                ++i;
            }
        }

//        for (int i = 0; i < rows; ++i) {
//            for (int j = 0; j < cols; ++j) {
//                cout << (i+j)%rows << ' ' << (i+(i+j)%rows)%cols << endl;
//            }
//        }
        
        i *= rows;
        for (pii c: C) {
            if (c.y >= rows) continue;
            for (int j = 0; j < c.y; ++j) {
                if (i < best) {
                    int pass = i/rows;
                    int k = i%rows;
                    Ans[i%rows][(i/rows+i%rows)%cols] = c.x;
//                    cout << (i+j)%rows << ' ' 
//                    Ans[(k+pass) % rows][(pass/* + (k+pass)%rows*/)%cols/*(i / rows + (i+pass) % rows) % cols*/] = c.x;
                    ++i;
                }
            }
        }
        cout << best << '\n' << rows << ' ' << cols << '\n';
        for (auto&ans: Ans) cout << ans;
    }
};
