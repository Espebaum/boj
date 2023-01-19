#include <iostream>
#include <vector>
using namespace std;
int sie = 0; //sum identity element : 덧셈 항등원 

long long op(long long a, long long b)
{
    return a + b;
    //결합 법칙이 성립하는 어떠한 연산이라도 op로 감싸면 성립한다.
    //밑 코드에서 항등원을 바꿔줘야 한다(항등원을 쓰는 경우).
}

void init(vector<long long> &a, vector<long long> &tree, int node, int start, int end) 
{
    if (start == end) // 리프 노드이다.
    {
        tree[node] = a[start]; //a는 배열, tree는 트리, node 번호
                               //node에 저장된 합의 범위가 start - end
    } 
    else            // 리프 노드가 아니다
    {
        init(a, tree, node*2, start, (start+end)/2);
        init(a, tree, node*2+1, (start+end)/2+1, end);
        tree[node] = op(tree[node*2], tree[node*2+1]); //op 연산 수행하여 합 세그먼트 트리 연산
    }
}

long long query(vector<long long> &tree, int node, int start, int end, int left, int right) 
{
    if (left > end || right < start) //left, right가 start, end와 전혀 겹치지 않음
    {
        return (sie); // 덧셈 항등원 반환
    }
    if (left <= start && end <= right) //left, right가 start, end를 완전히 포함하고 있음
    {
        return tree[node]; // 그 노드를 반환
    }
    // start, end가 left, right를 포함하는 경우 & 걸쳐 있는 경우
    long long lsum = query(tree, node*2, start, (start+end)/2, left, right);
    long long rsum = query(tree, node*2+1, (start+end)/2+1, end, left, right);
    return op(lsum, rsum);
}

void update(vector<long long> &tree, int node, int start, int end, int index, long long diff) 
{   // 수를 변경하는 코드
    if (index < start || index > end) // 바꾸고 싶은 인덱스가 포함되어있지 않으면
        return; //그냥 연산을 끝냄
    tree[node] = op(tree[node], diff); //포함되어 있다면 변량만큼 연산해줌
    if (start != end) // 리프 노드가 아니라면, 재귀를 함
    {
        update(tree,node*2, start, (start+end)/2, index, diff);
        update(tree,node*2+1, (start+end)/2+1, end, index, diff);
    }
}
void update(vector<long long> &tree, int n, int index, long long val) 
{   // (함수 이름이 같고 매개변수가 달라도 된다)
    long long diff = val - query(tree, 1, 0, n-1, index, index); // 변량 연산
    update(tree, 1, 0, n-1, index, diff);
}

void update2(vector<long long> &tree, int node, int start, int end, int index, long long val) 
{   //아래에서 위로 올라가면서 구간합을 업데이트해줌
    if (index < start || index > end) // 변량 인덱스가 전혀 포함되어 있지 않다면
    {
        return; //연산을 끝냄
    }
    if (start == end) //리프 노드라면
    {
        tree[node] = val; // 그 값을 바꾸고 싶은 값으로 변경한다
        return;
    }
    update2(tree, node*2, start, (start+end)/2, index, val); //먼저 재귀로 자식을 전부 바꾸고
    update2(tree,node*2+1, (start+end)/2+1, end, index, val); // 
    tree[node] = op(tree[node*2], tree[node*2+1]); // 최종적으로 제일 높은 트리의 합을 바꾼다
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    vector<long long>a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<long long>tree(36); //36칸 짜리 배열을 0으로 초기화함
    init(a, tree, 1, 0, (int) a.size()); //세그먼트 트리 만들기

    return 0;
}