/*
Biến maxN - Kích thước mảng.
Mảng d[] - Mảng lưu lại khoảng cách từ đỉnh nguồn đến mọi đỉnh.
Mảng par[] - Mảng lưu lại vết đường đi.
Mảng visit[] - Mảng đánh dấu các đỉnh đã thăm.
Vector g[] - Danh sách cạnh kề của mỗi đỉnh.
Hàng đợi q - Chứa các đỉnh sẽ được duyệt theo thứ tự ưu tiên chiều rộng.
*/

int n; // Số lượng đỉnh của đồ thị
int d[maxN], par[maxN];
bool visit[maxN];
vector<int> g[maxN];

void bfs(int s) { // Với s là đỉnh xuất phát (đỉnh nguồn)
    fill_n(d, n + 1, 0);
    fill_n(par, n + 1, -1);
    fill_n(visit, n + 1, false);

    queue<int> q;
    q.push(s);
    visit[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : g[u]) {
            if (!visit[v]) {
                d[v] = d[u] + 1;
                par[v] = u;
                visit[v] = true;
                q.push(v);
            }
        }
    }
}

// Cài đặt truy vết đường đi từ đỉnh nguồn s đến đỉnh u

if (!visit[u])
    cout << "No path!";
else {
    vector<int> path;
    for (int v = u; v != -1; v = par[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (auto v : path)
        cout << v << ' ';
}
