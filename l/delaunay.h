#ifndef MAJK_DELAUNAY_H
#define MAJK_DELAUNAY_H

#include "geo.h"

/// WARNING: there is an infinite loop on set (1,1), (1,2), (1,3), (4,0)
template <typename T> class Delaunay {
private:
    class QuadEdge {
        friend class Delaunay;
        friend class Factory;
    public:
        QuadEdge() : onext(nullptr), rot(nullptr), orig{0LL,0LL}, mark(false) {}

        inline QuadEdge* sym() const  {return rot->rot; }
        inline Point<T> dest() const { return sym()->orig; }
        inline QuadEdge* rotSym() const { return rot->sym(); }
        inline QuadEdge* oprev() const { return rot->onext->rot; }
        inline QuadEdge* lnext() const { return rotSym()->onext->rot; }
        inline QuadEdge* rprev() const { return sym()->onext; }

        void splice(QuadEdge *b) {
            QuadEdge *alpha = onext->rot, *beta = b->onext->rot;
            QuadEdge *t2 = onext, *t3 = beta->onext, *t4 = alpha->onext;
            onext = b->onext;
            b->onext = t2;
            alpha->onext = t3;
            beta->onext = t4;
        }
        void deleteEdge() {
            splice(oprev());
            sym()->splice(sym()->oprev());
        }

    private:
        QuadEdge *onext, *rot;
        Point<T> orig;
        bool mark;
    };
    class Factory {
    public:
        Factory() : p(0) {};
        QuadEdge* makeEdge(Point<T> orig, Point<T> dest) {
            QuadEdge *q0 = &Q[p], *q1 = &Q[p+1], *q2 = &Q[p+2], *q3 = &Q[p+3];
            p += 4;

            q0->orig = orig; q2->orig = dest;
            q0->onext = q0; q2->onext = q2;
            q1->onext = q3; q3->onext = q1;

            q0->rot = q1; q1->rot = q2;
            q2->rot = q3; q3->rot = q0;
            return q0;
        }
        QuadEdge* connect(QuadEdge *a, QuadEdge *b) {
            QuadEdge* q = makeEdge(a->dest(), b->orig);
            q->splice(a->lnext());
            q->sym()->splice(b);
            return q;
        }
        int p;
        vector<QuadEdge> Q;
    };

public:
    vector<Point<T>> triangulate(vector<Point<T>> &points) {
        sort(points.begin(), points.end());
        factory.Q.resize(40*points.size());
        factory.p = 0;

        QuadEdge* quadEdge = delaunay(points.begin(), points.end()).x;
        vector<Point<T>> faces;
        queue<QuadEdge*> queue;
        queue.push(quadEdge);

        // Mark all outer edges as visited
        while (leftOf(quadEdge->onext->dest(), quadEdge))
            quadEdge = quadEdge->onext;

        QuadEdge* curr = quadEdge;
        do {
            queue.push(curr->sym());
            curr->mark = true;
            curr = curr->lnext();
        } while (curr != quadEdge);

        while (!queue.empty()) {
            QuadEdge *edge = queue.front();
            queue.pop();
            if (!edge->mark) {
                // Stores the edges for a visited triangle. Also pushes sym (neighbour) edges on stack to visit later.
                curr = edge;
                do {
                    faces.push_back(curr->orig);
                    if (!curr->sym()->mark)
                        queue.push(curr->sym());

                    curr->mark = true;
                    curr = curr->lnext();
                } while (curr != edge);
            }
        }

        return faces;
    }

    pair<QuadEdge*, QuadEdge*> delaunay(typename vector<Point<T>>::const_iterator begin, typename vector<Point<T>>::const_iterator end) {
        QuadEdge* a, *b, *c, *t;

        auto dist = std::distance(begin, end);

        cerr << "Dela " << dist << endl;
        if (dist == 2) {
            a = factory.makeEdge(*begin, *next(begin));
            return { a, a->sym() };
        } else if (dist == 3) {
            auto s0 = *begin;
            auto s1 = *next(begin);
            auto s2 = *next(next(begin));
            a = factory.makeEdge(s0, s1);
            b = factory.makeEdge(s1, s2);
            a->sym()->splice(b);

            if (ccw(s0,s1,s2)) {
                c = factory.connect(b,a);
                return { a, b->sym() };
            } else if (ccw(s0,s2,s1)) {
                c = factory.connect(b, a);
                return { c->sym(), c };
            } else { // All three points are colinear
                return { a, b->sym() };
            }
        } else { // |S| >= 4
            auto left = delaunay(begin, begin + dist / 2);
            auto right = delaunay(begin + dist / 2, end);
            QuadEdge *ldo = left.x, *ldi = left.y, *rdi = right.x, *rdo = right.y;

            cerr << "Locota begin\n";
            // Compute the lower common tangent of L and R
            do {

                cerr << "Locota\n";
                if(leftOf(rdi->orig, ldi))
                    ldi = ldi->lnext();
                else if(rightOf(ldi->orig, rdi))
                    rdi = rdi->rprev();
                else
                    break;
            } while(true);

            cerr << "Locota end\n";

            QuadEdge* basel = factory.connect(rdi->sym(), ldi);
            if(ldi->orig == ldo->orig)
                ldo = basel->sym();
            if(rdi->orig == rdo->orig)
                rdo = basel;

            // This is the merge loop.
            do {
                // Locate the first L point (lcand.Dest) to be encountered by the rising bubble,
                // and delete L edges out of base1.Dest that fail the circle test.
                QuadEdge *lcand = basel->sym()->onext;
                if (valid(lcand, basel)) {
                    while (inCircle(basel->dest(), basel->orig, lcand->dest(), lcand->onext->dest())) {
                        t = lcand->onext;
                        lcand->deleteEdge();
                        lcand = t;
                    }
                }

                //Symmetrically, locate the first R point to be hit, and delete R edges
                QuadEdge* rcand = basel->oprev();
                if(valid(rcand, basel)) {
                    while(inCircle(basel->dest(), basel->orig, rcand->dest(), rcand->oprev()->dest())) {
                        t = rcand->oprev();
                        rcand->deleteEdge();
                        rcand = t;
                    }
                }

                // If both lcand and rcand are invalid, then basel is the upper common tangent
                if(!valid(lcand, basel) && !valid(rcand, basel)) break;

                // The next cross edge is to be connected to either lcand.Dest or rcand.Dest
                // If both are valid, then choose the appropriate one using the InCircle test
                if(!valid(lcand, basel) || (valid(rcand, basel) && inCircle(lcand->dest(), lcand->orig, rcand->orig, rcand->dest())))
                    // Add cross edge basel from rcand.Dest to basel.Dest
                    basel = factory.connect(rcand, basel->sym());
                else
                    // Add cross edge base1 from basel.Org to lcand. Dest
                    basel = factory.connect(basel->sym(), lcand->sym());
            } while (true);

            return { ldo, rdo };
        }
    }

private:
    inline bool rightOf(const Point<T> &x, const QuadEdge*e) const { return ccw(x, e->dest(), e->orig); }
    inline bool leftOf(const Point<T> &x, const QuadEdge*e) const { return ccw(x, e->orig, e->dest()); }
    inline bool valid(const QuadEdge *e, const QuadEdge*basel) const { return rightOf(e->dest(), basel); }
    bool inCircle(const Point<T> &a, const Point<T> &b, const Point<T> &c, const Point<T> &d) const {
        if((a.x == d.x && a.y == d.y) || (b.x == d.x && b.y == d.y) || (c.x == d.x && c.y == d.y)) return false;
        double sa = (ll)a.x * a.x + (ll)a.y * a.y, sb = (ll)b.x * b.x + (ll)b.y * b.y, sc = (ll)c.x * c.x + (ll)c.y * c.y, sd = (ll)d.x * d.x + (ll)d.y * d.y;
        double d1 = sc - sd, d2 = c.y - d.y, d3 = c.y * sd - sc * d.y, d4 = c.x - d.x, d5 = c.x * sd - sc * d.x, d6 = (ll)c.x * d.y - (ll)c.y * d.x;
        return a.x * (b.y * d1 - sb * d2 + d3) - a.y * (b.x * d1 - sb * d4 + d5)
               + sa * (b.x * d2 - b.y * d4 + d6) - b.x * d3 + b.y * d5 - sb * d6 > 1; // We have an issue here with number accuracy
    }

    Factory factory;
};


#endif //MAJK_DELAUNAY_H
