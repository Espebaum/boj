#include <iostream>
#include <vector>
using namespace std;
//int sie = 0; //sum identity element : 덧셈 항등원 
//int mie = 1; //multiple identity element : 곱셈 항등원

vector<char> child[128];
char par[128];

void    prt(char now)
{
    cout<<now;
    for (int i = 0;i<child[now].size();i++)
    {
        prt(child[now][i]);
    }
}

void    it(char now)
{
    if(child[now].size() > 0)
    {
        it(child[now][0]);
    }
    if(child[now].size() > 1)
    {
        it(child[now][1]);
    }
}

void    pot(char now)
{
    for (int i = 0;i<child[now].size();i++)
    {
        pot(child[now][i]);
    }
    cout<<now;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;cin>>n;
    int N=n;
    while (n--)
    {
        char x, y, z;cin>>x>>y>>z;
        if (y != '.')
        {
            child[x].push_back(y);
            par[y] = x;
            
        }
        if (z != '.')
        {
            child[x].push_back(z);
            par[z] = y;
        } 
    }
    prt('A');cout<<'\n'; //루트 노드를 인자로 받음
    it('A');cout<<'\n';
    pot('A');cout<<'\n';
    return 0;
}