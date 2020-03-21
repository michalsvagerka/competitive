#include "../l/lib.h"
#include "../l/random.h"

class DNewYearAndConference {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> A(N), B(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i] >> B[i];
        }

        for (int t = 0; t < 2; ++t) {
            map<int, vector<pii>> Events;
            for (int i = 0; i < N; ++i) {
                Events[A[i].x].push_back({1, B[i].x});
                Events[A[i].x].push_back({2, B[i].y});
                Events[A[i].y+1].push_back({3, B[i].x});
                Events[A[i].y+1].push_back({4, B[i].y});
            }

            multiset<int> Start, End;
            for (auto a: Events) {
                for (pii ev: a.y) {
                    if (ev.x == 1) {
                        Start.insert(ev.y);
                    } else if (ev.x == 2) {
                        End.insert(ev.y);
                    } else if (ev.x == 3) {
                        Start.erase(Start.find(ev.y));
                    } else {
                        End.erase(End.find(ev.y));
                    }
                }
                if (!Start.empty() && !End.empty() && *Start.rbegin() > *End.begin()) {
                    cout << "NO\n";
                    return;
                }
            }

            swap(A, B);
        }

        cout << "YES\n";
    }
};
