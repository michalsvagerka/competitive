#include "../l/lib.h"
// #include "../l/mod.h"

class complroute {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;

        cout << fixed << setprecision(3);
        while (S != "END") {
            if (S == ".") {
                cout << "You can go to (0.000,0.000), the distance is 0.000 steps.\n";
            } else {
                double x = 0, y = 0;
                stringstream ss(S);
                char c = ' ';
                while (c != '.') {
                    int d; ss >> d;
                    int dx=0, dy=0;
                    ss >> c;
                    while (c != ',' && c != '.') {
                        if (c == 'N') dy++;
                        else if (c == 'S') dy--;
                        else if (c == 'E') dx++;
                        else if (c == 'W') dx--;
                        ss >> c;
                    }
                    double step = sqrt(abs(dx)+abs(dy));
                    x += dx*d/step;
                    y += dy*d/step;
                }

                double dist = sqrt(x*x+y*y);
                if (abs(x) < 1e-7) x = 0;
                if (abs(y) < 1e-7) y = 0;
                if (abs(dist) < 1e-7) dist = 0;

                cout << "You can go to (" << x << ',' << y << "), the distance is " << dist << " steps.\n";
            }

            cin >> S;
        }
    }
};
