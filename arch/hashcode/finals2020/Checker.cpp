#include "../l/lib.h"

class Checker {
public:
    int W,H,R,M,T,L;
    vector<pii> Points;
    vector<pair<int, vector<pii>>> Tasks;

    void readInput(istream &cin) {
        cin >> W >> H >> R >> M >> T >> L;
        Points.resize(M); cin >> Points;
        Tasks.resize(T);
        for (int t = 0; t < T; ++t) {
            cin >> Tasks[t].x;
            int s; cin >> s;
            Tasks[t].y.resize(s);
            cin >> Tasks[t].y;
        }
    }

    int readOutput(istream &cin) {
#define checkPoint(p) if (p.x < 0 || p.x >= W || p.y < 0 || p.x >= H) { cerr << "Invalid point " << p << '\n'; return 1; }
        int A; cin >> A;
        if (A > R) { cerr << "too many arms used " << A << " > " << R << '\n'; return 1; }
        vector<pii> MountPoints(A);
        vector<string> Program(A);
        vector<vector<pii>> Target(A);
        vector<int> Assign(T, -1);
        ll score = 0;

        for (int arm = 0; arm < A; ++arm) {
            cin >> MountPoints[arm];
            checkPoint(MountPoints[arm]);

            int Z, K; cin >> Z >> K;
            if (Z < 1 || Z > T) { cerr << "Invalid number of tasks " << Z << " must be in [1," << T << "]\n"; return 1; }
            if (K < 1 || K > L) { cerr << "Invalid number of steps " << K << " must be in [1," << L << "]\n"; return 1; }
            vector<int> TaskIds(Z);
            cin >> TaskIds;
            for (int i = 0; i < Z; ++i) {
                if (TaskIds[i] < 0 || TaskIds[i] >= T) {
                    cerr << "Invalid task id " << TaskIds[i] << " on arm " << arm << " task " << i << "\n"; return 1;
                }
                if (Assign[TaskIds[i]] != -1) {
                    cerr << "Task " << TaskIds[i] << " programmed for arms " << Assign[TaskIds[i]] << " and " << arm << '\n'; return 1;
                }
                Assign[TaskIds[i]] = arm;
                score += Tasks[TaskIds[i]].x;
                for (pii j: Tasks[TaskIds[i]].y) Target[arm].push_back(j);
            }
            for (int i = 0; i < K; ++i) {
                char c; cin >> c;
                if (c != 'R' && c != 'D' && c != 'U' && c != 'L' && c != 'W') {
                    cerr << "Invalid instruction " << i << " for arm " << arm << ": " << c << "\n"; return 1;
                }
                Program[arm] += c;
            }
        }


        vector<vector<pii>> Arms(A);
        vector2<int> Occupier(W, H, -1);
        for (pii mnt: Points) {
            Occupier[mnt.x][mnt.y] = -2;
        }

        for (int i = 0; i < A; ++i) {
            if (Occupier[MountPoints[i].x][MountPoints[i].y] != -2) {
                cout << "Arms " << i << " and " << Occupier[MountPoints[i].x][MountPoints[i].y] << " share mount point " << MountPoints[i] << '\n';
                return 1;
            }
            Occupier[MountPoints[i].x][MountPoints[i].y] = i;
            Arms[i].push_back(MountPoints[i]);
        }

        vector<int> Progress(A, 0);

        for (int t = 0; t < L; ++t) {

            vector<bool> MoveBack(A, false);
            vector<bool> MoveForward(A, false);
            vector<pii> MoveTo(A);
            // move back
            for (int i = 0; i < A; ++i) {
                if (Program[i].size() <= t || Program[i][t] == 'W') continue;
                pii pt = Arms[i].back();
                switch (Program[i][t]) {
                    case 'R':
                        pt.x++; break;
                    case 'L':
                        pt.x--; break;
                    case 'D':
                        pt.y--; break;
                    case 'U':
                        pt.y++; break;
                }
                MoveTo[i] = pt;
                if (Arms[i].size() >= 2 && Arms[i][Arms[i].size()-2] == pt) {
                    MoveBack[i] = true;
                } else {
                    MoveForward[i] = true;
                }
            }

            for (int i = 0; i < A; ++i) {
                if (MoveBack[i]) {
                    Occupier[Arms[i].back().x][Arms[i].back().y] = -1;
                    Arms[i].pop_back();
                }
            }

            for (int i = 0; i < A; ++i) {
                if (MoveForward[i]) {
                    pii pt = MoveTo[i];
                    if (Occupier[pt.x][pt.y] != -1) {
                        cerr << "At time " << t << " arm " << i << " crashes into " << Occupier[pt.x][pt.y] << " at "
                             << pt << '\n';
                        return 1;
                    }
                    while (Progress[i] < Target[i].size() && Target[i][Progress[i]] == pt) {
                        Progress[i]++;
                    }
                    Occupier[pt.x][pt.y] = i;
                    Arms[i].push_back(pt);
                }
            }
        }
        for (int i = 0; i < A; ++i) {
            if (Progress[i] < Target[i].size()) {
                cerr << "Arm " << i << " had " << Target[i].size() << " target points, but hit only " << Progress[i] << '\n';
                return 1;
            }
        }

        cerr << "All OK\n";
        cerr << "Score: " << score << '\n';
        return 0;
    }

    void solve(istream& cin, ostream& cout) {
        readInput(cin);
        readOutput(cin);
    }
};
