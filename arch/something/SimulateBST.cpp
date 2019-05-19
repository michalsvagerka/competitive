#include "../l/lib.h"
#include "../l/mod.h"

namespace tc {
    template <typename T> void read(istream& cin, T& v) { cin >> v; }
    template <typename T> void read(istream& cin, string& s) {
        char c; cin >> c >> c;
        while (c != '"') { s += c; cin >> c; }
    }
    template <typename T> void read(istream& cin, vector<T>& v) {
        char c; cin >> c;
        while (c != '}') { T t; cin >> t; v.push_back(t); cin >> c; }
    }
    template<int S, bool Enable, typename ... Args>
    struct FillerImpl { static void fill(tuple<Args...>&, istream&) {}};
    template<int S, typename...Args> struct Filler : public FillerImpl<S, S < sizeof...(Args), Args...> {};
    template<int S, typename ... Args> struct FillerImpl<S, true, Args...> {
        static void fill(tuple<Args...> &T, istream &cin) {
            read(cin, std::get<S>(T));
            Filler<S + 1, Args...>::fill(T, cin);
        }
    };

    template<int ...> struct seq {};
    template<int N, int ...S> struct gens : gens<N - 1, N - 1, S...> {};
    template<int ...S> struct gens<0, S...> { typedef seq<S...> type; };

    template<int ...S, typename Clz, typename Ret, typename ...Args>
    Ret call(seq<S...>, Clz *obj, Ret (Clz::*fn)(Args... args), tuple<Args...> &t) { return (obj->*fn)(std::get<S>(t) ...); }

    template <typename Ret, typename Clz, typename ... Args>
    void test(istream &cin, Clz *obj, Ret (Clz::*fn)(Args... args), ostream& cout) {
        tuple<Args...> T;
        Filler<0, Args...>::fill(T, cin);
        cout << call(typename gens<sizeof...(Args)>::type(), obj, fn, T) << '\n';
    }
}



class SimulateBST {
public:
    int checksum(int n, vector <int> Sprefix, int a, int m) {
        vector<int> S = Sprefix;
        int p = Sprefix.size();
        map<int, int> D;
        map<int, int> L, R;
        for (int i = 0; i < n; ++i) {
            if (i >= p) S.push_back((ll(a) * S[i-p] + D[S[i-1]] + 1 ) % m);
            if (D.empty()) {
                L[S[i]] = -1;
                R[S[i]] = -1;
                D[S[i]] = 0;
            } else {
                int y = -1;
                auto lo = D.lower_bound(S[i]);
                if (lo != D.end() && lo->x == S[i]) continue;

                if (lo == D.end()) {
                    y = prev(lo)->x;
                } else if (L[lo->x] == -1) {
                    y = lo->x;
                } else {
                    y = prev(lo)->x;
                }
                if (y < S[i]) {
                    R[y] = S[i];
                } else {
                    L[y] = S[i];
                }
                D[S[i]] = D[y]+1;
                L[S[i]] = -1;
                R[S[i]] = -1;
            }
        }

        FieldMod ans = 0;
        FieldMod mul = 1;
        for (int i = 0; i < n; ++i) {
            ans += mul * D[S[i]];
            mul *= 100000;
        }

        return (ui)ans;
    }

    void solve(istream& cin, ostream& cout) {
        tc::test(cin, this, &SimulateBST::checksum, cout);
    }
};
