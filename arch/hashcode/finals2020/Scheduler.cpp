#include "../l/lib.h"
#include "../l/random.h"

const bool PREBOOK = false;
const int MAX_WAIT = 20;
//const bool BACKHOME = true;
//const int LIMIT_ARMS = 90;

class Scheduler {
public:
    int W,H,R,M,T,L;
    vector<pii> Points;
    vector<pair<int, vector<pii>>> Tasks;

    ll globalTime = 0;
    vector<vector<ll>> BFS;
    vector<vector<pii>> Back;

    vector<pii> bfs(int armId, const vector2<int>&Occupier, pii from) {
        if (Occupier[from.x][from.y] != -1) return {};

        globalTime++;

        vector<pii> Q{from};
        Back[from.x][from.y] = {-1,-1};
        BFS[from.x][from.y] = globalTime;
        for (int q = 0; q < Q.size(); ++q) {
            pii pt = Q[q];
            vector<pii> Next;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (abs(dx)+abs(dy) == 1) {
                        pii newPt = {pt.x+dx, pt.y+dy};
                        if (newPt.x >= 0 && newPt.x < W && newPt.y >= 0 && newPt.y < H && BFS[newPt.x][newPt.y] < globalTime) {
                            if (Occupier[newPt.x][newPt.y] == armId) {
                                vector<pii> path{newPt};
                                pii target = pt;
                                while (target.x != -1) {
                                    path.push_back(target);
                                    target = Back[target.x][target.y];
                                }
                                reverse(path.begin(),path.end());
                                return path;
                            } else if (Occupier[newPt.x][newPt.y] == -1) {
                                Next.push_back(newPt);
                            }
                        }
                    };
                }
            }

//            shuffle(Next.begin(),Next.end(),rng);
            for (pii newPt: Next) {
                BFS[newPt.x][newPt.y] = globalTime;
                Back[newPt.x][newPt.y] = pt;
                Q.push_back(newPt);
            }
        }

        return {};
    };

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

        BFS = vector2<ll>(W, H, -1);
        Back = vector2<pii>(W, H, pii{-1,-1});
    }

    int run(istream &cin, ostream&cout) {
        int A; cin >> A;
//        A = min(A, LIMIT_ARMS);
        if (A > R) { cerr << "too many arms used " << A << " > " << R << '\n'; return 1; }
        vector<pii> MountPoints(A);
        vector<string> Program(A);
        vector<vector<pii>> Target(A);
        vector<vector<int>> Finishes(A);
        vector<vector<int>> TaskIdsPerArm(A);
        vector<int> Assign(T, -1);

        for (int arm = 0; arm < A; ++arm) {
            cin >> MountPoints[arm];
            int Z; cin >> Z;
//            vector<int> TaskIds(Z);
//            cin >> TaskIds;
//            TaskIdsPerArm[arm] = TaskIds;
            for (int i = 0; i < Z; ++i) {
                int s; cin >> s;
                bool fail = false;
                if (s < 0 || s >= T) {
                    fail = true;
//                    cerr << "Invalid task id " << TaskIds[i] << " on arm " << arm << " task " << i << "\n"; return 1;
                }
                if (Assign[s] != -1) {
                    fail = true;
//                    cerr << "Task " << TaskIds[i] << " programmed for arms " << Assign[TaskIds[i]] << " and " << arm << '\n'; return 1;
                }
                if (!fail) {
                    Assign[s] = arm;
                    TaskIdsPerArm[arm].push_back(s);
                    for (pii j: Tasks[s].y) {
                        Finishes[arm].push_back(0);
                        Target[arm].push_back(j);
                    }
                    Finishes[arm].back() = 1;
                }
            }
        }

        cerr << "Targets: " << Target;

        vector<vector<pii>> Arms(A);
        vector2<int> Occupier(W, H, -1);
        for (pii mnt: Points) {
            Occupier[mnt.x][mnt.y] = -2;
        }

        for (int i = 0; i < A; ++i) {
            Occupier[MountPoints[i].x][MountPoints[i].y] = i;
            Arms[i].push_back(MountPoints[i]);
        }

        vector<int> Progress(A, 0);

        vector<pii> Retract(A, {-1,-1});
        vector<vector<pii>> Paths(A);
        vector<int> Finished(A, 0);
        vector<int> LastFail(A, -1);
        vector<int> LastFailSize(A, 1);
        vector<bool> BackHome(A, false);

        for (int t = 0; t < L; ++t) {
            cerr << "TIME ========= " << t << " =========" << endl;
            vector<bool> MoveBack(A, false);
            vector<bool> MoveForward(A, false);

            for (int i = 0; i < A; ++i) {
                if (Retract[i].x != -1) {
                    if (Arms[i].back() == Retract[i]) {
                        // successful retract
                        cerr << "Arm " << i << " successfully retracted to " << Retract[i] << '\n';
                        Retract[i] = {-1,-1};
                    }
                }

                if (Retract[i].x == -1 && Paths[i].empty() && Progress[i] < Target[i].size()) {
                    if (t < LastFail[i] + LastFailSize[i]) {
                        continue;
                    }

                    // we have nothing to do, try to formulate a plan
                    vector<pii> Path = bfs(i, Occupier, Target[i][Progress[i]]);
                    if (Path.empty()) {
                        // this is unreachable (the BFS was probably quite expensive)
                        cerr << "Failed to plan " << i << " to " << Target[i][Progress[i]] << '\n';
                        LastFail[i] = t;
                        LastFailSize[i] = min(MAX_WAIT,LastFailSize[i]*2);
                    } else {
                        // successful plan
                        cerr << "Planned " << i << " " << Arms[i].back() << " -> " << Path.back() << " -> " << Target[i][Progress[i]] << '\n';
                        LastFail[i] = -1;
                        LastFailSize[i] = 1;
//                        cerr << "Path (reversed): " << Path;

                        // the last element is the starting position
                        // it might be the current position of the arm, or we might need to retract first
                        Retract[i] = Path.back();
                        if (Retract[i] == Arms[i].back()) {
                            // already there, yay!
                            Retract[i] = {-1,-1};
                        }

                        Path.pop_back();

                        // book the path
                        if (PREBOOK) {
                            for (pii path: Path) {
                                Occupier[path.x][path.y] = i;
                            }
                        }

                        Paths[i] = Path;
                    }
                }
            }

            for (int i = 0; i < A; ++i) {
                if (Retract[i].x != -1) {
                    // nothing to do, go backward
                    MoveBack[i] = true;
                } else if (!Paths[i].empty()) {
                    // there is a plan, go forward
                    MoveForward[i] = true;
                } else {
                    // nothing to do, just retract
                    MoveBack[i] = true;
                }
            }


            auto putCommand = [&](pii from, pii to, int armId) {
                if (to.x == from.x + 1) {
                    Program[armId].push_back('R');
                } else if (to.x == from.x - 1) {
                    Program[armId].push_back('L');
                } else if (to.y == from.y + 1) {
                    Program[armId].push_back('U');
                } else if (to.y == from.y - 1) {
                    Program[armId].push_back('D');
                }
            };

            for (int i = 0; i < A; ++i) {
                if (MoveForward[i]) {
                    pii to = Paths[i].back();
                    if (!PREBOOK && Occupier[to.x][to.y] != -1) {
                        cerr << "Arm " << i << " blocked by " << Occupier[to.x][to.y] << " at " << to << endl;
                        // bad - this is occuppied. Destroy current plan, retract and try again next time
//                        MoveBack[i] = true;
                        Paths[i].clear();
                    } else {
                        // perform move
                        pii from = Arms[i].back();
                        putCommand(from, to, i);
                        Occupier[to.x][to.y] = i;
                        Paths[i].pop_back();
                        Arms[i].push_back(to);
//                        cerr << "Arm " << i << " forwards " << to << '\n';

                        continue;
                    }
                }

                if (MoveBack[i]) {
                    if (Arms[i].size() == 1) {
                        // I'm afraid I can't do that
                        Program[i].push_back('W');
//                    cerr << "Arm " << i << " waits " << endl;
                    } else {

                        // perform retract
                        pii from = Arms[i].back();
                        Arms[i].pop_back();
                        pii to = Arms[i].back();
                        putCommand(from, to, i);
                        Occupier[from.x][from.y] = -1;

//                    cerr << "Arm " << i << " retracts " << to << '\n';
                    }
                } else {
                    Program[i].push_back('W');
                }
            }


            for (int i = 0; i < A; ++i) {
                // collect points
                pii pt = Arms[i].back();
                while (Progress[i] < Target[i].size() && Target[i][Progress[i]] == pt) {
                    cerr << "Arm " << i << " reached point (finishedTasks=" << Finishes[i][Progress[i]] << ")\n";
                    Finished[i] += Finishes[i][Progress[i]];
                    Progress[i]++;
//                    if (BACKHOME && Finishes[i][Progress[i]]) {
//                        Retract[i] = Arms[i][max((int)Arms[i].size()-5,0)];
//                    }
                }
            }
        }

        int realA = 0;
        for (int i = 0; i < A; ++i) {
            if (Finished[i] > 0) ++realA;
        }
        cout << realA << endl;

        ll score = 0;

        cerr << "Branch scores: ";
        vector<ll> MyScores(A);
        vector<int> Missing(A);
        int correct = 0;
        for (int i = 0; i < A; ++i) {
            if (Finished[i] == 0) continue;
            cout << MountPoints[i] << ' ' << Finished[i] << ' ' << Program[i].size() << '\n';
            ll myScore = 0;
            correct += Finished[i];
            for (int j = 0; j < Finished[i]; ++j) {
                myScore += Tasks[TaskIdsPerArm[i][j]].x;
                cout << TaskIdsPerArm[i][j] << " \n"[j+1==Finished[i]];
            }
            score += myScore;
            for (int j = 0; j < Program[i].size(); ++j) {
                cout << Program[i][j] << " \n"[j+1==Program[i].size()];
            }
            MyScores[i] = myScore;
            Missing[i] = TaskIdsPerArm[i].size() - Finished[i];
        }
        cerr << "Scores: " << MyScores;
        cerr << "Finished: " << Finished;
        cerr << "Missing: " << Missing;

        cerr << "Score: " << correct << "/" << score << '\n';
        return 0;
    }

    void solve(istream& cin, ostream& cout) {
        readInput(cin);
        run(cin, cout);
    }
};
