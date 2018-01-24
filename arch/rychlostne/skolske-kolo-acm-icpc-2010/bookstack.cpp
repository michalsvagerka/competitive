#include "../l/lib.h"
// #include "../l/mod.h"

class bookstack {
public:

    void solve(istream& cin, ostream& cout) {
        int K; cin >> K;
        stack<int> B;
        deque<int> T;
        bool d = true;
        int c; cin >> c;
        while (c) {
            if (c == -1) {
                if (d) {
                    cout << T.front() << '\n';
                    T.pop_front();
                    if (!B.empty()) {
                        T.push_back(B.top());
                        B.pop();
                    }
                } else {
                    cout << T.back() << '\n';
                    T.pop_back();
                    if (!B.empty()) {
                        T.push_front(B.top());
                        B.pop();
                    }
                }
            } else if (c == -2) {
                d = !d;
            } else {
                if (d) {
                    T.push_front(c);
                    if (T.size() == K+1) {
                        B.push(T.back());
                        T.pop_back();
                    }
                } else {
                    T.push_back(c);
                    if (T.size() == K+1) {
                        B.push(T.front());
                        T.pop_front();
                    }
                }
            }
            
            cin >> c;
        }
    }
};
