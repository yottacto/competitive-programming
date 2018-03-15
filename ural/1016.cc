// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <iterator>
#include <algorithm>
#include <utility>
#include <vector>
#include <limits>
#include <queue>
#include <map>

// 8 (a..h) * 8 * 24 (6 * 4)
auto constexpr maxn = 8 * 8 * 24;
int from[maxn];
std::vector<std::map<int, int>> g(maxn);
std::vector<int> face(6);
std::string start;
std::string end;

enum axis
{
    px, // near
    nx, // far
    pz, // top
    py, // right
    nz, // bottom
    ny, // left
};

struct cube
{
    int id() const;

    axis x; // +x
    axis y; // +y
    axis z; // +z
};

bool operator==(cube const& lhs, cube const& rhs)
{
    return lhs.x == rhs.x
        && lhs.y == rhs.y
        && lhs.z == rhs.z;
}

std::string dir(axis a)
{
    switch (a) {
        case px: return "+x";
        case nx: return "-x";
        case py: return "+y";
        case ny: return "-y";
        case pz: return "+z";
        case nz: return "-z";
    }
}

std::ostream& operator<<(std::ostream& os, cube const& a)
{
    os << dir(a.x) << " " << dir(a.y) << " " << dir(a.z);
    return os;
}

struct node
{
    node(int x, int y, cube _c)
        : x{x}, y{y}, c{std::move(_c)}
    {
        pos = std::string{char('a' + x)} + std::string{char('0' + y + 1)};
    }

    node(std::string _pos, cube _c)
        : pos{std::move(_pos)}, x{pos[0] - 'a'}, y{pos[1] - '0' - 1}, c{std::move(_c)}
    {
    }

    operator int() const
    {
        // std::cerr << c.id() << " " << x << " " << y << "\n";
        return c.id() * 64 + y * 8 + x;
    }

    std::string pos;
    int x;
    int y;
    cube c;
};

std::ostream& operator<<(std::ostream& os, node const& a)
{
    os << a.pos << " " << a.c;
    return os;
}

std::vector<cube> iter{
    {px, py, pz}, {px, nz, py}, {px, ny, nz}, {px, pz, ny},
    {nx, ny, pz}, {nx, nz, ny}, {nx, py, nz}, {nx, pz, py},
    {py, nx, pz}, {py, nz, nx}, {py, px, nz}, {py, pz, px},
    {ny, px, pz}, {ny, nz, px}, {ny, nx, nz}, {ny, pz, nx},
    {pz, py, nx}, {pz, px, py}, {pz, ny, px}, {pz, nx, ny},
    {nz, py, px}, {nz, nx, py}, {nz, ny, nx}, {nz, px, ny},
};

int cube::id() const
{
    for (auto i = 0u; i < iter.size(); i++)
        if (iter[i] == *this)
            return i;
    std::cerr << "-> " << *this << "\n";
    return -1;
}

int constexpr opt[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

bool inrange(int x, int y)
{
    return (0 <= x && x < 8)
        && (0 <= y && y < 8);
}

axis minus(axis a)
{
    switch (a) {
        case px: return nx;
        case nx: return px;
        case py: return ny;
        case ny: return py;
        case pz: return nz;
        case nz: return pz;
    }
}

cube rotate(cube const& c, int dir)
{
    switch (dir) {
        // left rotate
        case 0: return {c.x, minus(c.z), c.y};
        // right rotata
        case 1: return {c.x, c.z, minus(c.y)};
        // up rotate
        case 2: return {minus(c.z), c.y, c.x};
        // down rotate
        default: return {c.z, c.y, minus(c.x)};
    }
}

int bottom(cube const& c)
{
    return minus(c.z);
}

void add_edge(int u, int v, int cost)
{
    g[u][v] = cost;
}

void init_graph()
{
    for (auto i = 0; i < maxn; i++)
        from[i] = i;
    for (auto i = 0; i < 8; i++)
        for (auto j = 0; j < 8; j++) {
            int tit = 0;
            for (auto const& it : iter) {
                node now{i, j, it};
                for (auto k = 0; k < 4; k++) {
                    auto tx = now.x + opt[k][0];
                    auto ty = now.y + opt[k][1];
                    if (!inrange(tx, ty)) continue;

                    // std::cerr << i << ", " << j << ", "
                    //     << tit << ", " << k << ".\n";

                    auto next = node{tx, ty, rotate(now.c, k)};
                    add_edge(now, next, face[bottom(next.c)]);

                    // std::cerr << now << ", " << next << "\n";
                }
                tit++;
            }
        }
}

std::vector<int> dist(maxn, std::numeric_limits<int>::max());
bool vis[maxn];

std::string parse_pos(int id)
{
    // auto c = id / 64;
    auto y = (id % 64) / 8;
    auto x = (id % 64) % 8;
    return std::string{char('a' + x)} + std::string{char('0' + y + 1)};
}

void spfa(int s)
{
    std::queue<int> q;
    q.push(s);
    dist[s] = face[bottom(iter[0])];
    vis[s] = true;
    while (!q.empty()) {
        auto now = q.front();
        vis[now] = false;
        q.pop();
        for (auto const& e: g[now]) {
            auto to   = e.first;
            auto cost = e.second;
            if (dist[to] > dist[now] + cost) {
                dist[to] = dist[now] + cost;
                from[to] = now;
                if (!vis[to]) {
                    vis[to] = true;
                    q.push(to);
                }
            }
        }
    }
    auto ans = std::numeric_limits<int>::max();
    int last;
    for (auto const& it : iter) {
        int tn{node{end, it}};
        if (ans > dist[tn]) {
            ans = dist[tn];
            last = tn;
        }
    }
    std::cout << ans << " ";

    std::vector<std::string> path;
    for (last = from[last]; last != s; last = from[last])
        path.emplace_back(parse_pos(last));
    path.emplace_back(start);
    std::copy(
        path.rbegin(),
        path.rend(),
        std::ostream_iterator<std::string>{std::cout, " "}
    );
    std::cout << end << "\n";
}

int main()
{
    std::cin >> start >> end;
    for (auto& v : face)
        std::cin >> v;
    init_graph();

    spfa(node{start, iter[0]});
}

