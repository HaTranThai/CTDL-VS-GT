#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* pNext;

    Node (int data): data(data), pNext(NULL){} 
};
struct Queue{
private:
    Node* pHead;
    Node* pTail;
public:
    Queue(): pHead(NULL), pTail(NULL){}

    void push(int data){
        Node* p = new Node(data);

        if(pHead == NULL) pHead = pTail = p;
        else{
            pTail->pNext = p;
            pTail = p; 
        }
    }

    void pop(){
        Node* p = pHead;
        pHead = pHead->pNext;

        delete p;
    }
    int top(){
        return pHead->data;
    }
    int empty(){
        if(pHead == NULL) return 1;
        else return 0;
    }
};


int adj[100][100], vt[100];
int n, m;

void bfs(int u){
    Queue q;
    q.push(u);
    vt[u] = 1;
    cout << 1 << ' ';
    while(!q.empty()){
        int u = q.top(); q.pop();
        for(int i = 1; i <= n; i++){
            if(!vt[i] && adj[u][i]){
                cout << i << ' ';
                vt[i] = 1;
                q.push(i);
            }
        }
    }
}


int main(){
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int x, y; cin >> x >> y;
        adj[x][y] = 1;
        adj[y][x] = 1;
    }

    bfs(1);

    return 0;
}
