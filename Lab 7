#include <stdio.h>


struct Node{
    int data;
    Node* pNext;
};

struct Queue{
    Node* pHead;
    Node* pTail;
};

void Init(Queue &L){
    L.pHead = L.pTail = NULL;
}

Node* createNode(int val){
    Node* p = new Node;
    p->data = val;
    p->pNext = NULL;
    return p;
}

void push_back(Queue &L, int val){
    Node* p = createNode(val);
    if(L.pHead == NULL) L.pHead = L.pTail = p;
    else{
        L.pTail->pNext = p;
        L.pTail = p;
    }
}
void push_front(Queue &L, int val){
    Node* p = createNode(val);
    if(L.pHead == NULL) L.pHead = L.pTail = p;
    else{
        p->pNext = L.pHead;
        L.pHead = p;
    }
}
int pop(Queue &L){
    int ans = L.pHead->data;
    Node* p = L.pHead;
    L.pHead = p->pNext;
    delete p;
    return ans;
}
int isEmpty(Queue L){
    if(L.pHead == NULL) return 1;
    return 0;
}
int adj[100][100], vt[100], par[100];
int n, m;

void bfs(int u){
    Queue L;
    Init(L);
    push_back(L, u);
    vt[u] = 1;
    while(!isEmpty(L)){
        int v = pop(L);
        for(int i = 1; i <= n; i++){
            if(!vt[i] && adj[v][i]){
                par[i] = v;
                vt[i] = 1;
                push_back(L, i);
            }
        }
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int x, y; 
        scanf("%d%d", &x, &y);
        adj[x][y] = 1;
        adj[y][x] = 1;
    }
    bfs(1);
    int a, b;
    scanf("%d%d", &a, &b);
    if(!vt[a] || !vt[b]){
        printf("khong co duong di.\n");
    }
    else{
        Queue L; Init(L);
        while(b != a){
            push_front(L, b);
            b = par[b];
        }
        push_front(L, a);
        while(!isEmpty(L)){
            int val = pop(L);
            printf("%d ", val);
        }
    }
}
