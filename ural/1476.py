m, n, k = map(int, input().split())

# m = 2
# n = 2
# k = 1

c = [[0] * (m+1) for i in range(m+1)]
c[0][0] = 1
for i in range(1, m+1):
    c[i][0] = 1
    for j in range(1, m+1):
        c[i][j] = c[i-1][j] + c[i-1][j-1]

f = [[0] * (m+1) for i in range(n+1)]

for i in range(m+1):
    f[1][i] = c[m][i]

g = [[0] * (m+1) for i in range(m+1)]
for prev_white in range(m + 1):
    for matched_white in range(min(prev_white+1, k+1)):
        for remain_white in range(m - prev_white + 1):
            g[prev_white][remain_white + prev_white - matched_white] += \
                    c[prev_white][matched_white] * c[m - prev_white][remain_white]

for i in range(1, n):
    for prev_white in range(m + 1):
        for next_white in range(m+1):
            f[i + 1][next_white] += f[i][prev_white] * g[prev_white][next_white]

print(sum(f[n]))

