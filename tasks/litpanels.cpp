#include "../l/lib.h"
#include "../l/mod.h"

class litpanels {
public:
    int brute(set<vector2<bool>> &Q, vector2<bool> &F, int x, int y, int sx, int sy, int X, int Y, bool q) {
        if (x == X) {
            x = 0;
            y++;
        }

        if (y == Y) {
            bool x1 = false, xl = false, y1 = false, yl = false;
            for (int i = 0; i < X; ++i) { x1 |= F[i][0]; xl |= F[i][Y-1]; }
            for (int i = 0; i < Y; ++i) { y1 |= F[0][i]; yl |= F[X-1][i]; }
            if  (x1 && xl && y1 && yl) {
                Q.insert(F);
                return 1;
            } else {
                return 0;
            }
        }

        int ans = 0;
        if ((q && ((x < sx && y < sy) || (X-x <= sx && Y-y <= sy)))
                || (!q && ((x < sx && Y-y <= sy) || (X-x <= sx && y < sy)))) {
            F[x][y] = true;
            ans += brute(Q, F, x + 1, y, sx, sy, X, Y, q);
        }
        F[x][y] = false;
        ans += brute(Q, F, x+1, y, sx, sy, X, Y, q);
        return ans;
    }

    int brute(int X, int Y, int sx, int sy) {
        vector2<bool> F(X,Y,false);
        set<vector2<bool>> Q;
        int ans = brute(Q, F, 0, 0, sx, sy, X, Y, true);
        if (X > sx && Y > sy) ans += brute(Q, F, 0, 0, sx, sy, X, Y, false);
        if (ans != Q.size()) {
            cerr << X << ' ' << Y << ' ' << sx << ' ' << sy << ' ' << ans << ' ' << Q.size() << endl;
        }

        return Q.size();
    }

    void solve(istream& cin, ostream& cout) {
        int X, Y, sx, sy;
        FieldMod ans = 0;
        FieldMod t = 2;
        cin >> X >> Y >> sx >> sy;
        for (int tx = 1; tx <= X; ++tx) {
            for (int ty = 1; ty <= Y; ++ty) {
                int cnt = (X+1-tx)*(Y+1-ty);
                int rx = min(2*sx,tx);
                int ry = min(2*sy,ty);
                FieldMod cur = 0;
                if (rx == 1) {
                    if (ry == 1) {
                        cur = 1;
                    } else {
                        cur = t.pow(ry-2);
                    }
                } else {
                    if (ry == 1) {
                        cur = t.pow(rx-2);
                    } else {
                        int jx = min(sx,tx);
                        int jy = min(sy,ty);
                        int full = 0;
                        if (ty >= 2*sy || tx >= 2*sx) {
                            full = 2 * jx * jy;
                        } else if (tx > sx && ty > sy) {
                            full = 2 * sx * sy - (2*sx-tx)*(2*sy-ty);
                        } else {
                            full = tx*ty;
                        }

                        int topLeft = 1;
                        int bottomRight = 1;
                        int fullRect = tx <= sx || ty <= sy;

//                        cerr << tx << ' ' << ty << ' ' << empty << ' ' << (tx > sx) <<  (ty > sy) << ' ' << endl;

                        if (tx <= sx) jy = ry;
                        if (ty <= sy) jx = rx;
                        cur = t.pow(full)
                               - 2 * t.pow(full-jx)
                               - 2 * t.pow(full-jy)
                               + 2 * t.pow(full-jx-jy+1)
                               + 2 * t.pow(full-jx-jy+fullRect)
                               + t.pow(full - 2*jx)
                               + t.pow(full - 2*jy)
                               - 2 * t.pow(full-2*jx - jy + 1 + fullRect)
                               - 2 * t.pow(full - jx -2*jy + fullRect + 1)
                               + t.pow(full -2*jx -2*jy + 2*fullRect + 2);

                        if (tx > sx && ty > sy) cur *= 2;
                    }
                }
                ans += cur * cnt;
                int br = brute(tx,ty,sx,sy);
//                cerr << tx << ' ' << ty << ' ' << cur << '=' << br << ' ' << cnt << endl;
            }
        }
        ans += 1; // all empty
        cout << ans << endl;

    }
};
