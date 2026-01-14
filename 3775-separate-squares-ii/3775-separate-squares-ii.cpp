#define ll long long
#define N 100005
int x[N];
struct SegTree {
    struct Data {
        int cnt;
        ll tot;
    };

    vector<Data> segtree;
    SegTree(int n) {
        segtree.resize(4*n);
    }
    void update(int idx, int s, int e, int l, int r, int delta) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            segtree[idx].cnt += delta;
        } else {
            int m = (s + e)/2;
            update(2*idx, s, m, l, r, delta);
            update(2*idx + 1, m + 1, e, l, r, delta);
        }
        
        if (segtree[idx].cnt > 0)
            segtree[idx].tot = x[e + 1] - x[s];
        else {
            if (s == e)
                segtree[idx].tot = 0;
            else
                segtree[idx].tot = segtree[2*idx].tot + segtree[2*idx + 1].tot;
        }

    }
    int covered() {
        return segtree[1].tot;
    }
};
struct Event {
    double y;
    int x1, x2, type;
};
class Solution {
public:
    int segments;
    int top;
    unordered_map<int,int> xToIdx;
    double separateSquares(vector<vector<int>>& squares) {
        top = 0;
        int maxY = -1;
        for (auto &sq : squares) {
            x[top++] = sq[0];
            x[top++] = sq[0] + sq[2];
            maxY = max(maxY, sq[1] + sq[2]);
        }
        sort(x, x + top);
        top = unique(x, x + top) - x;
        segments = top - 1;
        for (int i = 0; i < top; i++) xToIdx[x[i]] = i;

        vector<Event> events;
        for (auto &sq : squares) {
            events.push_back(Event{1.00 * sq[1], xToIdx[sq[0]], xToIdx[sq[0] + sq[2]], 1});
            events.push_back(Event{1.00 * (sq[1] + sq[2]), xToIdx[sq[0]], xToIdx[sq[0] + sq[2]], -1});
        }
        sort(events.begin(), events.end(), [](auto &e1, auto &e2) {
            return e1.y < e2.y;
        });
        SegTree tree(segments);

        double tot = 0;

        // calculate tot area
        ll prev_y = -1;
        for (auto &e : events) {
            if (prev_y != -1) {
                tot += (e.y - prev_y) * tree.covered();
            }
            prev_y = e.y;
            tree.update(1, 0, segments - 1, e.x1, e.x2 - 1, e.type);
        }

        // find optimal y
        prev_y = -1;
        double cur_area = 0;
        for (auto &e : events) {
            if (prev_y != -1) {
                double nxt_area = (e.y - prev_y) * tree.covered();
                if ((cur_area + nxt_area) >= tot / 2) {
                    return (tot/2 - cur_area) / tree.covered() + prev_y;
                }
                cur_area += nxt_area;
            }
            prev_y = e.y;
            tree.update(1, 0, segments - 1, e.x1, e.x2 - 1, e.type);
        }

        return -1;
    }
};