#include "../l/lib.h"
#include "../l/segtree.h"
#include "../l/runtimemod.h"

template <typename ValueType, typename TagType>
struct LSegTree {
    LSegTree(const vector<ValueType> & data, const ValueType& nullValue, const TagType& nullTag)
            : n(1<<logceil(data.size())), nullValue(nullValue), nullTag(nullTag), T(2*n, {nullValue, nullTag}) {
        for (int i = 0; i < data.size(); ++i) T[n+i].x = data[i];
        for (ui i = n-1; i > 0; i--) T[i].x = combineValues(T[i<<1].x,T[i<<1|1].x);
    }

    LSegTree(ui size, const ValueType& nullValue, const TagType& nullTag)
            : n(1<<logceil(size)), nullValue(nullValue), nullTag(nullTag), T(2*n, {nullValue, nullTag}) {
        for (ui i = n-1; i > 0; i--) T[i].x = combineValues(T[i<<1].x,T[i<<1|1].x);
    }

    inline void put(ui x, const TagType &n) { put(x, x, n); }
    inline void put(ui from, ui to, TagType v) { putInner(from, to, v, 1, n); }

    inline ValueType operator[](pair<ui,ui> x) { return get(x.x, x.y); }
    inline ValueType operator[](ui x) { return get(x, x); }
    inline ValueType get(ui x) { return get(x, x); }
    inline ValueType get(ui from, ui to) { return getInner(from, to, 1, n); }

    void directSet(ui x, const ValueType&v) {
        put(x, nullTag); // propagate all tags down
        x += n;
        T[x].x = v;
        while (x != 1) {
            T[x/2].x = combineValues(T[x].x, T[x^1].x);
            x/=2;
        }
    }

    void putInner(ui from, ui to, TagType v, ui i, ui s) {
        vector<int> Q;
        ui r = i;
        while (true) {
            if (from == 0 && to == s - 1) {
                applyTag(T[i].x, v, s);
                combineTag(T[i].y, v);
                break;
            }
            pushTagDown(i, s);
            s >>= 1;
            i <<= 1;
            if (from & s) {
                from ^= s;
                to ^= s;
                i ^= 1;
            } else if (to & s) {
                putInner(0, to ^ s, v, i | 1, s);
                to = s - 1;
            }
        }

        while (i != r) {
            T[i >> 1].x = combineValues(T[i].x, T[i^1].x);
            i >>= 1;
        }
    }


    ValueType getInner(ui from, ui to, ui i, ui s) {
        while (true) {
            if (from == 0 && to == s-1) return T[i].x;
            pushTagDown(i, s);
            s >>= 1; i <<= 1;
            if (to & s) {
                to ^= s;
                if (from & s) {
                    from ^= s; i |= 1;
                } else {
                    return combineValues(
                            getInner(from, s-1, i, s),
                            getInner(0, to, i|1, s)
                    );
                }
            }
        }
    }

    void pushTagDown(ui i, ui s) {
        applyTag(T[i<<1].x, T[i].y, s>>1);
        applyTag(T[i<<1|1].x, T[i].y, s>>1);
        combineTag(T[i << 1].y, T[i].y);
        combineTag(T[i << 1 | 1].y, T[i].y);
        T[i].y = nullTag;
    }

    ui n;
    ValueType nullValue;
    TagType nullTag;
    vector<pair<ValueType, TagType>> T;

    void combineTag(TagType&a, TagType b) {
        a *= b;
    }

    void applyTag(ValueType& a, TagType t, ui) {
        a *= t;
    }

    ValueType combineValues(ValueType a, ValueType b) {
        return a + b;
    }
};

using MulTree = LSegTree<RField, RField>;

class ESashaAndAVeryEasyTest {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        cin >> MOD;
        int PHI = MOD;
        vector<int> F;
        int mm = MOD;
        for (int i = 2; i*i <= mm; ++i) {
            if (mm%i==0) {
                while (mm%i==0) mm/=i;
                PHI /= i;
                PHI *= i-1;
                F.push_back(i);
            }
        }
        if (mm!=1) {
            F.push_back(mm);
            PHI /= mm;
            PHI *= mm-1;
        }

        int FF = F.size();
        vector<int> A(N), B(N);
        cin >> A;
        vector2<int> Z(FF, N, 0);
        for (int i = 0; i < N; ++i) {
            int a = A[i];
            for (int j = 0; j < FF; ++j) {
                while (a%F[j]==0) {
                    Z[j][i]++;
                    a /= F[j];
                }
            }
            B[i] = a;
        }

        vector<AddMaxTree<int>> TS(FF);
        for (int i = 0; i < FF; ++i) TS[i].setup(Z[i], 0);

        vector<RField> AF(N), BF(N);
        for (int i = 0; i < N; ++i) AF[i] = RField(int(A[i]));
        for (int i = 0; i < N; ++i) BF[i] = RField(int(B[i]));
        MulTree TA{AF, 0, 1}, TB{BF, 0, 1};

        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int t; cin >> t;
            if (t == 1) {
                int l, r, x; cin >> l >> r >> x;
                --l; --r;
                TA.put(l, r, RField(x));
                for (int i = 0; i < FF; ++i) {
                    int c = 0;
                    while (x % F[i] == 0) {
                        x /= F[i];
                        ++c;
                    }
                    if (c) TS[i].put(l, r, c);
                }
                TB.put(l, r, RField(x));
            } else if (t == 2) {
                int p, x; cin >> p >> x;
                --p;
                for (int i = 0; i < FF; ++i) {
                    int c = 0;
                    while (x % F[i] == 0) {
                        x /= F[i];
                        ++c;
                    }
                    if (c) TS[i].put(p, -c);
                }

                RField oldCoprime = TB.get(p);
                RField inv = RField(x).pow(PHI-1);
                RField curCoprime = oldCoprime * inv;
                RField curReal = curCoprime;
                for (int i = 0; i < FF; ++i) {
                    int s = TS[i].get(p);
                    if (s) curReal *= RField{F[i]}.pow(s);
                }
                TA.directSet(p, curReal);
                TB.directSet(p, curCoprime);
            } else {
                int l, r; cin >> l >> r;
                --l; --r;
                cout << TA.get(l, r) << '\n';
            }
        }
    }
};
