#include "../l/lib.h"

class CPalindromicPaths {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<int> A(N, N, -1);
        A[0][0] = 1;
        A[N-1][N-1] = 0;
        int same;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == -1 && i%2==j%2) {
                    int k, l;
                    if (i == 0) { k = 0; l = j-2; }
                    else if (j == 0) { k = i-2; l = 0; }
                    else { k = i-1; l = j-1; }

                    cout << "? " << k+1 << ' ' << l+1 << ' ' << i+1 << ' ' << j+1 << endl;
                    cin >> same;
                    A[i][j] = A[k][l] ^ same ^ 1;
                }
            }
        }

        A[0][1] = 0;
        cout << "? 1 2 3 2" << endl;
        cin >> same;
        A[2][1] = same ^ 1;
        cout << "? 2 1 3 2" << endl;
        cin >> same;
        A[1][0] = A[2][1] ^ same ^ 1;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == -1 && i%2!=j%2) {
                    int k, l;
                    if (i == 0) { k = 0; l = j-2; }
                    else if (j == 0) { k = i-2; l = 0; }
                    else { k = i-1; l = j-1; }

                    cout << "? " << k+1 << ' ' << l+1 << ' ' << i+1 << ' ' << j+1 << endl;
                    cin >> same;
                    A[i][j] = A[k][l] ^ same ^ 1;
                }
            }
        }

//        cout << "!" << endl;
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                cout << A[i][j];
//            }
//            cout << endl;
//        }


        bool solved = false;
        bool reverse = false;
        for (int i = 0; i < N && !solved; ++i) {
            for (int j = 0; j < N && !solved; ++j) {
                if (i+2 < N && j+1 < N) {
                    if (A[i][j] == A[i+1][j+1] && A[i][j] == A[i+2][j]
                        && A[i][j+1] == A[i+1][j] && A[i][j+1] == A[i+2][j+1]) {
                        cout << "? " << i+1 << ' ' << j+1 << ' ' << i+3 << ' ' << j+2 << endl;
                        cin >> same;
                        reverse = A[i][j] ^ A[i][j+1] ^ same ^ 1;
                        solved = true;
                        break;
                    }
                }

                if (i+1 < N && j+2 < N) {
                    if (A[i][j] == A[i+1][j+1] && A[i][j] == A[i][j+2]
                        && A[i][j+1] == A[i+1][j] && A[i][j+1] == A[i+1][j+2]) {
                        cout << "? " << i+1 << ' ' << j+1 << ' ' << i+2 << ' ' << j+3 << endl;
                        cin >> same;
                        reverse = A[i][j] ^ A[i][j+1] ^ same ^ 1;
                        solved = true;
                        break;
                    }
                }
                
                if (i + 1 < N && j + 2 < N) {
                    if (A[i][j] != A[i+1][j+1] && A[i][j] != A[i][j+2] 
                       && A[i+1][j+2] != A[i+1][j] && A[i+1][j+2] != A[i][j+1]) {
                        cout << "? " << i+1 << ' ' << j+1 << ' ' << i+2 << ' ' << j+3 << endl;
                        cin >> same;
                        reverse = A[i][j] ^ A[i+1][j+2] ^ same ^ 1;
                        solved = true;
                        break;
                    }
                }

                if (i != 0 && j != N-1 && A[i][j] != A[i-1][j+1]) {
                    int a,b,c,d;
                    if (j != 0) {
//                        cout << "here\n";
                        a = i-1; b = j-1;
                        c = i; d = j+1;
                    } else {
//                        cout << "there\n";
                        a = i-1; b = j;
                        c = i; d = j+2;
                    }
                    cout << "? " << a+1 << ' ' << b+1 << ' ' << c+1 << ' ' << d+1 << endl;
                    cin >> same;
                    reverse = A[a][b] ^ A[c][d] ^ same ^ 1;
                    solved = true;
                    break;
                }
            }
        }

        if (reverse) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (i%2!=j%2) A[i][j] ^= 1;
                }
            }
        }
        cout << "!" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << A[i][j];
            }
            cout << endl;
        }
    }
};
