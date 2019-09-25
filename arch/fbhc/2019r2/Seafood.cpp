#include "../l/lib.h"
#include "../l/consttree.h"

class Seafood {
public:
    vector<int> G;
    void remove(int i, int l, int r, int L, int R) {
        if (G[i] == 0) return;

        if (L <= l && R >= r) G[i] = 0;
        else if (L >= r || R <= l) return;
        else {
            remove(2*i, l, (l+r)/2, L, R);
            remove(2*i+1, (l+r)/2, r, L, R);
            G[i] = G[2*i] + G[2*i+1];
        }
    };

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            int N; cin >> N;
            int P1, P2, H1, H2;
            ll Ap, Bp, Cp, Dp, Ah, Bh, Ch, Dh;
            cin >> P1 >> P2 >> Ap >> Bp >> Cp >> Dp >> H1 >> H2 >> Ah >> Bh >> Ch >> Dh;
            string O; cin >> O;
            vector<ll> P{P1, P2};
            vector<ll> H{H1, H2};
            for (int i = 2; i < N; ++i) P.push_back(1 + (Ap * P[i-2] + Bp * P[i-1] + Cp) % Dp);
            for (int i = 2; i < N; ++i) H.push_back(1 + (Ah * H[i-2] + Bh * H[i-1] + Ch) % Dh);

            vector<pair<pii, int>> E;
            for (int i = 0; i < N; ++i) E.push_back({{P[i], O[i]=='C'}, H[i]});
            sort(E.begin(),E.end());

            int hardestRock = 0, hardestClam = 0, rightRock = 0;
            vector<pii> Clams, Rocks, RockRight;
            for (int i = N-1; i >= 0; --i) {
                if (E[i].x.y == 1) {
                    // clam
                    hardestClam = max(hardestClam, E[i].y);
                    if (hardestRock <= E[i].y) {
                        Clams.push_back({E[i].x.x, E[i].y});
                    }
                } else {
                    // rock
                    if (hardestClam > 0) {
                        hardestRock = max(hardestRock, E[i].y);
                        Rocks.push_back({E[i].x.x, E[i].y});
                    } else {
                        rightRock = max(rightRock, E[i].y);
                        RockRight.push_back({E[i].y, E[i].x.x}); // they are reversed
                    }
                }
            }

            if (hardestClam >= max(hardestRock, rightRock)) {
                cout << "Case #" << t << ": -1\n";
            } else {
                sort(Rocks.begin(),Rocks.end()); // by x coordinate
                sort(Clams.begin(),Clams.end()); // by x coordinate

                sort(RockRight.begin(),RockRight.end()); // by hardness
                reverse(RockRight.begin(),RockRight.end());

                int R = Rocks.size(), C = Clams.size();

                vector<int> RockHard;
                for (pii rock: Rocks) RockHard.push_back(rock.y);
                ConstTree<int, MaxQOp<int>> CT(RockHard);
                int minOnTheRight = 0;
                vector<pair<int, pii>> Back;
                for (pii clam: Clams) {
                    int j = R == 0 ? -1 : bsh(0, R-1, [&](int i) { return Rocks[i].x <= clam.x; });
                    int i = j == -1 ? -1 : bsh(0, j, [&](int k) { return CT.get(k,j) > clam.y; });
                    if (i != -1) {
                        Back.push_back({clam.y, {Rocks[i].x, clam.x}});
                    } else {
                        minOnTheRight = max(minOnTheRight, clam.y);
                    }
                }
                sort(Back.begin(),Back.end());
                reverse(Back.begin(),Back.end()); // by hardness descending
//
                ll ans = 1e18;
                if (minOnTheRight == 0) {
//                    cout << "Can solve without right edge  " << endl;
                    vector<pii> Go;
                    for (auto clam: Back) Go.push_back(clam.y);
                    sort(Go.begin(),Go.end());
                    ll cur = 0;
                    int l = 0, r = 0;
                    for (auto clam: Go) {
                        if (clam.x <= r) {
                            r = max(r, clam.y);
                        } else {
                            cur += r-l;
                            l = clam.x;
                            r = clam.y;
                        }
                    }
                    cur *= 2;
                    cur += r-l;
                    cur += Go.back().y;
//                    cout << "Is " << cur << endl;
                    ans = min(ans, cur);
                }

                set<int> Coords{0, 1};
                for (auto clam : Back) {Coords.insert(clam.y.x);Coords.insert(clam.y.y);}
                int idx = 0;
                vector<int> CoordsV(Coords.begin(),Coords.end());
                map<int,int> Conv;
                for (int coord: CoordsV) Conv[coord] = idx++;
                vector<int> Lens;
                for (int i = 0; i < CoordsV.size()-1; ++i) Lens.push_back(CoordsV[i+1] - CoordsV[i]);
//                cout << Lens;

                int NN = 1<<logceil(Lens.size()+3);
                G.assign(2*NN + 6, 0);
                for (int i = 0; i < Lens.size(); ++i) G[NN+i] = Lens[i];
                for (int i = NN-1; i > 0; --i) G[i] = G[2*i] + G[2*i+1];

                auto activate = [&](pii range) {
                    int a = Conv[range.x];
                    int b = Conv[range.y];
                    // delete [a,b)
                    remove(1, 0, NN, a, b);
                };

                int j = 0;
                for (int i = 0; i < RockRight.size(); ++i) {
//                    cout << "Putting rock " << RockRight[i] << endl;
                    if (RockRight[i].x <= minOnTheRight) break; // cannot use this at all
                    // activate all clam intervals
                    while (j < Back.size() && Back[j].x >= RockRight[i].x) {
//                        cout << "Clam " << Back[j] << " is too hard, needs to go back" << endl;
                        activate(Back[j].y);
                        j++;
                    }

//                    cerr << "Union of all unused intervals " << G[1] << endl;
//                    cerr << "Right rock"
                    ll cur = 2L*(CoordsV.back() - G[1]) + ll(RockRight[i].y);

                    ans = min(ans, cur);
                }

                cout << "Case #" << t << ": " << ans << "\n";
            }
        }

    }
};
