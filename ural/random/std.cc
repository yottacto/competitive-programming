// ml:run = cp $bin std
// ml:opt = 0
// ml:ccf += -g
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=15000+50;

struct Node
{
    int x,y;
};

int n;
int c[maxn];
Node a[maxn];
int b[maxn],ans[maxn];

int cmp(Node a,Node b)
{
    if(a.x==b.x) return a.y<b.y;
    else return a.x<b.x;
}

inline int lowbit(int x)
{
    return x&(-x);
}

int sum(int x)
{
    int tot=0;
    while(x>0)
    {
        tot+=c[x];
        x-=lowbit(x);
    }
    return tot;
}

void add(int x,int num)
{
    while(x<=n)
    {
        c[x]+=num;
        x+=lowbit(x);
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        b[i]=a[i].y;
    }

    sort(b,b+n);
    int cnt=unique(b,b+n)-b;

    sort(a,a+n,cmp);

    for(int i=0; i<n; i++)
    {
        int x=lower_bound(b,b+n,a[i].y)-b+1;
        ans[sum(x)]++;
        add(x,1);
    }

    for(int i=0; i<n; i++)
    {
        printf("%d\n",ans[i]);
    }

    return 0;
}

