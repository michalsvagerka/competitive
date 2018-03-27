#include "../../../l/lib.h"
// #include "../l/mod.h"


class TaskD {
public:
    struct State {
        int guysShot;
        int loadingTimeDone;
        int backLoaded, backLane;
    };

    vector3<State> DP;

    void put(int x, int isLoaded, int lane, State state) {
        auto &d = DP[x][isLoaded][lane];
        if (state.guysShot > d.guysShot || (state.guysShot == d.guysShot && state.loadingTimeDone > d.loadingTimeDone)) {
            d = state;
        }
        
    }



    void solve(istream& cin, ostream& cout) {
        int N, M1, M2, T; cin >> N >> M1 >> M2 >> T;

        vector<vector<int>> OBST(2);
        OBST[0].resize(M1);
        OBST[1].resize(M2);
        cin >> OBST;

        vector<int> X{0};
        vector<vector<bool>> C{{false,false}};
        int i = 0, j = 0;
        while (i < M1 || j < M2) {
            if (i < M1 && j < M2 && OBST[0][i] == OBST[1][j]) {
                X.push_back(OBST[0][i]);
                C.emplace_back(vector<bool>{true,true});
                ++i; ++j;
            } else if (i < M1 && (j == M2 || OBST[0][i] < OBST[1][j])) {
                X.push_back(OBST[0][i]);
                C.emplace_back(vector<bool>{true,false});
                ++i;
            } else {
                X.push_back(OBST[1][j]);
                C.emplace_back(vector<bool>{false,true});
                ++j;
            }
        }
        X.push_back(N+1);
        C.emplace_back(vector<bool>{false,false});

        int Z = X.size();
        DP = vector3<State>(Z, 2, 2, {-1,-1,-1,-1});
        DP[0][0][0] = {0,0,-1,-1};
        for (int x = 1; x < X.size(); ++x) {
            for (int wasLoaded = 0; wasLoaded <= 1; ++wasLoaded) {
                for (int wasLane = 0; wasLane <= 1; ++wasLane) {
                    bool meHasObst = C[x][wasLane];
                    bool otherHasObst = C[x][!wasLane];
                    bool hadObst = C[x-1][wasLane];
                    bool otherHadObst = C[x-1][!wasLane];

                    auto &d = DP[x-1][wasLoaded][wasLane];
                    if (d.guysShot == -1) continue;
                    {
                        int time = d.loadingTimeDone + (X[x] - X[x - 1]);
                        int g = d.guysShot + time / T - meHasObst;
                        if (g > 0 && time >= T) put(x, 1, wasLane, {g - 1, T, wasLoaded, wasLane});
                        if (g >= 0 && time%T + g >= meHasObst) put(x, 0, wasLane, {g, time % T, wasLoaded, wasLane});
                    }

                    if (X[x] - X[x - 1] == 1 && (otherHasObst || meHasObst) && otherHadObst) {
                        // cannot switch now from bottom to top:
                        // ....#....
                        // .....#...
                        continue;
                    }

                    {
                        int time = d.loadingTimeDone + (X[x] - X[x - 1]);
                        if (otherHadObst && d.loadingTimeDone == T) --time; // cannot shoot right away
                        int g = time / T - otherHasObst;
                        if (g > 0 && time >= T) put(x, 1, 1 - wasLane, {g - 1, T, wasLoaded, wasLane});
                        if (g >= 0 && time%T + g >= otherHasObst) put(x, 0, 1 - wasLane, {g, time % T, wasLoaded, wasLane});
                    }
                }
            }
        }

        for (int loaded = 0; loaded <= 1; ++loaded) {
            for (int lane = 0; lane <= 1; ++lane) {
                if (DP[Z-1][loaded][lane].guysShot != -1) {
                    cout << "Yes\n";
                    vector<int> SW;
                    vector<vector<int>> S(2);
                    for (int x = Z-1; x >= 1; --x) {
                        bool laneSwitch = lane != DP[x][loaded][lane].backLane;
                        bool canShootImmediately = true;
                        if (laneSwitch) {
                            bool meHadObst = C[x-1][lane];
                            canShootImmediately = !meHadObst;
                            SW.push_back(X[x-1]+meHadObst);
                        }

                        int r = DP[x][loaded][lane].backLane;
                        int s = DP[x][loaded][lane].backLoaded;
                        auto &d = DP[x-1][s][r];
                        int time = d.loadingTimeDone;
                        if (!canShootImmediately && time == T) --time;
                        for (int pos = X[x-1] - time + T; pos <= X[x] - DP[x][loaded][lane].loadingTimeDone; pos += T) {
                            if (OBST[lane].empty() || OBST[lane].back() <= X[x-1] - time + T) break;
                            S[lane].push_back(pos);
                            OBST[lane].pop_back();
                        }
                        loaded = s;
                        lane = r;
                    }

                    vector<pii> SH;
                    for (int s:S[0]) SH.push_back({s,1});
                    for (int s:S[1]) SH.push_back({s,2});
                    sort(SH.begin(),SH.end());

                    reverse(SW.begin(),SW.end());
                    cout << SW.size() << endl;
                    cout << SW;
                    cout << SH.size() << endl;
                    for (pii sh: SH) cout << sh << '\n';

                    return;
                }
            }
        }

        cout << "No\n";
    }
};
