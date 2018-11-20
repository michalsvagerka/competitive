#ifndef MAJK_ENVELOPE_H
#define MAJK_ENVELOPE_H

#include "int128.h"

/** Computing lower and upper envelope. Useful for "convex hull trick". */
namespace Envelope {
    template<typename T>
    struct Line {
        T m, b; int id;
        mutable function<const Line<T> *()> succ;

        bool operator<(const Line &rhs) const {
            if (rhs.b != numeric_limits<T>::min()) return m < rhs.m;
            const Line *s = succ();
            if (!s) return 0;
            return b - s->b < (s->m - m) * rhs.m;
        }
    };

    template<typename T>
    struct Upper : public multiset<Envelope::Line<T>> {
        using parent = multiset<Line<T>>;

        bool bad(typename parent::iterator y) {
            auto z = next(y);
            if (y == parent::begin()) {
                return z != parent::end() && y->m == z->m && y->b <= z->b;
            } else {
                auto x = prev(y);
                if (z == parent::end()) {
                    return y->m == x->m && y->b <= x->b;
                } else {
                    return fractionGreaterOrEqual(x->b - y->b, y->m - x->m, y->b - z->b, z->m - y->m);
                }
            }
        }

        void insert_line(T m, T b, int i = 0) {
            auto y = parent::insert({m, b, i});
            y->succ = [=] { return next(y) == parent::end() ? 0 : &*next(y); };
            if (bad(y)) { parent::erase(y); return; }
            while (next(y) != parent::end() && bad(next(y))) parent::erase(next(y));
            while (y != parent::begin() && bad(prev(y))) parent::erase(prev(y));
        }

        T operator[](T x) const {
            auto l = parent::lower_bound({x, numeric_limits<T>::min()});
            return l == parent::end() ? numeric_limits<T>::min() : l->m * x + l->b;
        }

        int best(T x) const {
            auto l = parent::lower_bound({x, numeric_limits<T>::min()});
            return l == parent::end() ? -1 : l->id;
        }
    };

    // Lower envelope. WARNING: the internal representation changes m & b.
    template<typename T>
    struct Lower : public Upper<T> {
        void insert_line(T m, T b, int i = 0) { Upper<T>::insert_line(-m, -b, i); }
        T operator[](T x) const { return -Upper<T>::operator[](x); }
    };
}

/* UpperEnvelope that with O(N) build and amortized O(1) query.
 * The updates need be sorted by (m,b), the queries need to be sorted by x, and
 * updates need to come before queries. */
namespace LinearEnvelope {
    template<typename T> struct Line { T m, b; int id; };

    template <typename T>
    struct Upper : public vector<Line<T>> {
        using parent = vector<Line<T>>;
        using parent::at; using parent::back; using parent::size;

        T t; int i;

        Upper() : t(0), i(0) {}

        void clear() {
            parent::clear();
            i = 0;
            t = 0;
        }

        void insert_line(T m, T b, int i = 0) {
            assert(t == 0);
            if (size() > 0 && back().m == m && back().b >= b) return;
            while (size() > 0 && ((back().b < b) || (back().b == b && back().m < m))) parent::pop_back();
            while (size() >= 2 && fractionGreaterOrEqual(at(size()-2).b - back().b, back().m - at(size()-2).m, back().b - b, m - back().m)) parent::pop_back();
            parent::push_back({m,b,i});
        }

        pair<T,int> advance(T x) {
            assert(x >= 0);
            t += x;
            while (i+1 < size() && at(i).m * t + at(i).b < at(i+1).m * t + at(i+1).b) ++i;
            return {at(i).m * t + at(i).b, at(i).id};
        }
    };};


#endif //MAJK_ENVELOPE_H
