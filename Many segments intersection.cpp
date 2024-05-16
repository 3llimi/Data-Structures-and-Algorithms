//Ahmed Baha Eddine Alimi
#include <bits/stdc++.h>
 
 
 
using namespace std;
 
 
//Struct representing a point
struct Point {
    int index;
    long long x;
    long long y;
    long long position;
 
    Point(long long a, long long b, long long p, long long i) {
        x = a;
        y = b;
        position = p;
        index = i;
    }
 
    Point() {}
 
    bool operator >(Point a) {
        if (x == a.x) {
            return y > a.y;
        }
        return x > a.x;
    }
 
    bool operator <(Point a) {
        if (x == a.x) {
            return y < a.y;
        }
        return x < a.x;
    }
 
    bool operator >=(Point a) {
        if (x > a.x || x == a.x) {
            return true;
        }
        return false;
    }
 
    bool operator <=(Point a) {
        if (x < a.x || x == a.x) {
            return true;
        }
        return false;
    }
 
    bool operator ==(Point a) {
        if (x == a.x && y == a.y) return true;
        return false;
    }
};
 
ostream& operator << (ostream& output, Point& a) {
    output << a.x << " " << a.y;
    return output;
}
 
//Struct representing a segment
struct Segment {
    Point start;
    Point end;
 
    Segment(Point s, Point e) {
        start = s;
        end = e;
    }
 
    void print() {
        cout << start.x << " " << start.y << " " << end.x << " " << end.y << endl;
    }
};
 
// Function to check if two segments intersect
bool doIntersect(Segment s1, Segment s2) {
    long long xa = s1.start.x;
    long long xb = s1.end.x;
    long long xc = s2.start.x;
    long long xd = s2.end.x;
    long long ya = s1.start.y;
    long long yb = s1.end.y;
    long long yc = s2.start.y;
    long long yd = s2.end.y;
    long long denom = (xa - xb) * (yc - yd) - (ya - yb) * (xc - xd);
    if (denom == 0) return false;
 
    double xp = (double(xa * yb - ya * xb) * double(xc - xd) - double(xa - xb) * double(xc * yd - yc * xd));
    xp /= double(xa - xb) * (yc - yd) - double(ya - yb) * (xc - xd);
    double yp = (double(xa * yb - ya * xb) * double(yc - yd) - double(ya - yb) * double(xc * yd - yc * xd));
    yp /= double(xa - xb) * (yc - yd) - double(ya - yb) * (xc - xd);
 
    double cross = (yp - ya) * (xb - xa) - (xp - xa) * (yb - ya);
    if (fabs(cross) > 1e-8) return false;
    double dot = (xp - xa) * (xb - xa) + (yp - ya) * (yb - ya);
    if (dot < 0) return false;
    double temp = double(xb - xa) * double(xb - xa) + double(yb - ya) * double(yb - ya);
    if (dot > temp) return false;
 
    cross = (yp - yc) * (xd - xc) - (xp - xc) * (yd - yc);
    if (fabs(cross) > 1e-8) return false;
    dot = (xp - xc) * (xd - xc) + (yp - yc) * (yd - yc);
    if (dot < 0) return false;
    temp = double(xd - xc) * double(xd - xc) + double(yd - yc) * double(yd - yc);
    if (dot > temp) return false;
 
    return true;
}
 
//Struct representing a node in Red-Black Tree
struct Node {
    Point val;
    Node* left;
    Node* right;
    Node* parent;
    int color; // 0 for black, 1 for red
 
    Node() : val(), left(nullptr), right(nullptr), parent(nullptr), color(0) {}
    explicit Node(Point v) : val(v), left(nullptr), right(nullptr), parent(nullptr), color(0) {}
};
 
//Class representing Red-Black Tree
class RBTree {
    Node* TNULL; // null node
 
 
 
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
 
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
 
    void rbInsertFixup(Node* k) {
        while (k != root && k->parent->color == 1) {
            if (k->parent == k->parent->parent->left) {
                Node* y = k->parent->parent->right;
                if (y->color == 1) {
                    k->parent->color = 0;
                    y->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            else {
                Node* y = k->parent->parent->left;
                if (y->color == 1) {
                    k->parent->color = 0;
                    y->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = 0;
    }
 
    void rbTransplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
 
    Node* minimum(Node* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }
 
    void rbDeleteFixup(Node* x) {
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == 1) {
                    w->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == 0 && w->right->color == 0) {
                    w->color = 1;
                    x = x->parent;
                }
                else {
                    if (w->right->color == 0) {
                        w->left->color = 0;
                        w->color = 1;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                Node* w = x->parent->left;
                if (w->color == 1) {
                    w->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == 0 && w->left->color == 0) {
                    w->color = 1;
                    x = x->parent;
                }
                else {
                    if (w->left->color == 0) {
                        w->right->color = 0;
                        w->color = 1;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }
 
    void deleteNodeHelper(Node* node, long long key) {
        Node* z = TNULL;
        Node* x, * y;
        while (node != TNULL) {
            if (node->val.x == key) {
                z = node;
            }
            if (node->val.x <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }
        if (z == TNULL) {
            return;
        }
        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            rbDeleteFixup(x);
        }
    }
 
public:
    RBTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
 
 
    void insert(Point key) {
        Node* node = new Node(key);
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;
        Node* y = nullptr;
        Node* x = this->root;
        while (x != TNULL) {
            y = x;
            if (node->val.x < x->val.x) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->val.x < y->val.x) {
            y->left = node;
        }
        else {
            y->right = node;
        }
        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }
        if (node->parent->parent == nullptr) {
            return;
        }
        rbInsertFixup(node);
    }
 
    void del(Point data) {
        deleteNodeHelper(this->root, data.x);
    }
 
    Node* next(Node* x, Point key) {
        Node* succ = nullptr;
        while (x != TNULL) {
            if (x->val.x <= key.x) {
                x = x->right;
            }
            else {
                succ = x;
                x = x->left;
            }
        }
        return succ;
    }
 
    Node* prev(Node* x, Point key) {
        Node* pred = nullptr;
        while (x != TNULL) {
            if (x->val.x >= key.x) {
                x = x->left;
            }
            else {
                pred = x;
                x = x->right;
            }
        }
        return pred;
    }
    Node* root;
};
 
template<class T>
int partition(vector<T>& arr, int low, int high, bool(*compare)(T ta, T tb)) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compare(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
 
template<class T>
void quickSort(vector<T>& arr, int low, int high, bool(*compare)(T ta, T tb)) {
    if (low < high) {
        int pi = partition(arr, low, high, compare);
        quickSort(arr, low, pi - 1, compare);
        quickSort(arr, pi + 1, high, compare);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    RBTree rbtree;
    vector<Point> points;
    vector<Segment> segments;
    vector<Segment> originalSegments;
 
    int n;
    cin >> n;
 
    for (int i = 0; i < n; i++) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
 
        Point p1(x1, y1, 0, segments.size());
        Point p2(x2, y2, 1, segments.size());
 
        Segment seg(p1, p2);
        originalSegments.push_back(seg);
 
        if (y2 < y1) {
            p1.position = 1;
            p2.position = 0;
            seg.start = p2;
            seg.end = p1;
        }
        segments.push_back(seg);
 
        points.push_back(p1);
        points.push_back(p2);
    }
 
    quickSort<Point>(points, 0, points.size() - 1, [](Point p1, Point p2) {
        return p1.y <= p2.y;
    });
 
    for (int i = 0; i < int(points.size()); i++) {
        Point currentPoint = points[i];
 
        if (currentPoint.position == 0) {
            rbtree.insert(currentPoint);
 
            Node* nextPt = rbtree.next(rbtree.root, currentPoint);
 
            if (nextPt != nullptr) {
                Point nextPoint = nextPt->val;
 
                Segment s1 = segments[currentPoint.index];
                Segment s2 = segments[nextPoint.index];
 
                if (doIntersect(s1, s2)) {
                    cout << "INTERSECTION" << endl;
                    originalSegments[currentPoint.index].print();
                    originalSegments[nextPoint.index].print();
                    return 0;
                }
            }
 
            Node* prevPt = rbtree.prev(rbtree.root, currentPoint);
 
            if (prevPt != nullptr) {
                Point prevPoint = prevPt->val;
 
                Segment s1 = segments[currentPoint.index];
                Segment s2 = segments[prevPoint.index];
 
                if (doIntersect(s1, s2)) {
                    cout << "INTERSECTION" << endl;
                    originalSegments[currentPoint.index].print();
                    originalSegments[prevPoint.index].print();
                    return 0;
                }
            }
        }
        else {
            Point start = segments[currentPoint.index].start;
 
            Node* nextPt = rbtree.next(rbtree.root, start);
            Node* prevPt = rbtree.prev(rbtree.root, start);
 
            if (nextPt != nullptr && prevPt != nullptr) {
                Point nextPoint = nextPt->val;
                Point prevPoint = prevPt->val;
 
                Segment s1 = segments[nextPoint.index];
                Segment s2 = segments[prevPoint.index];
 
                if (doIntersect(s1, s2)) {
                    cout << "INTERSECTION" << endl;
                    originalSegments[nextPoint.index].print();
                    originalSegments[prevPoint.index].print();
                    return 0;
                }
            }
            rbtree.del(start);
        }
    }
 
    cout << "NO INTERSECTIONS" << endl;
    return 0;
}