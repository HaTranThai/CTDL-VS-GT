#include <stdio.h>

struct MatHang{
    int maMH;
    char tenMH[12];
};

struct Node{
    MatHang data;
    Node* pNext;
};

struct Queue{
    int soluong;
    Node* pHead;
    Node* pTail;
};

void Init(Queue &Q){
    Q.pHead = Q.pTail = NULL, Q.soluong = 0;
}

int isEmpty(Queue Q){
    if(Q.pHead == NULL) return 1;
    return 0;
}

Node* createNode(MatHang val){
    Node* NNode = new Node;
    
    NNode->data = val;
    NNode->pNext = NULL;
    
    return NNode;
}

void push_MH(Queue &Q, MatHang val){
    Node* NNode = createNode(val);

    if(Q.pHead == NULL) Q.pHead = Q.pTail = NNode;
    else{
        Q.pTail->pNext = NNode;
        Q.pTail = NNode;
    }
}

MatHang pop_MH(Queue &Q){
    MatHang a;
    if(isEmpty(Q)){
        a.maMH = -1;
        printf("Kho rong.\n"); return a;
    }

    MatHang data = Q.pHead->data;

    Node* tmp = Q.pHead;
    Q.pHead = tmp->pNext;

    delete tmp;

    return data;
}

void Nhap_Kho(Queue &Q, int &n){

    printf("\n=== NHAP HANG TRONG KHO===\n");
    printf("Nhap so luong hang trong kho: "); scanf("%d", &n);
    
    MatHang a;

    for(int i = 1; i <= n; i++){
        printf("Nhap ma mat hang: "); scanf("%d", &a.maMH); fflush(stdin);
        printf("Nhap ten mat hang: "); scanf("%[^\n]", a.tenMH);
        printf("-------------------\n");
        push_MH(Q, a);
    }

}

void Xuat_1(MatHang a){
    printf("Ma mat hang: %d\n", a.maMH);
    printf("Ten mat hang: %s\n", a.tenMH);
    printf("-------------------\n");
}

void Xuat_MH_F(Queue Q){
    if(isEmpty(Q)){
        printf("Kho rong.\n"); return;
    }
    Xuat_1(Q.pHead->data);
}
void Xuat_MH_R(Queue Q){
    if(isEmpty(Q)){
        printf("Kho rong.\n"); return;
    }
    Xuat_1(Q.pTail->data);
}
void Display_All(Queue Q){
    if(isEmpty(Q)){
        printf("Kho rong.\n"); return;
    }
    Node* p = Q.pHead;

    while(p){
        Xuat_1(p->data);
        p = p->pNext;
    }
}
void Xuat_All(Queue &Q){
    if(isEmpty(Q)){
        printf("Kho rong.\n"); return;
    }
    Node* p = Q.pHead;
    
    while(!isEmpty(Q)){
        MatHang a = pop_MH(Q);
        Xuat_1(a);
    }
}

void Menu(){
    printf("\n== Moi lua chon chuc nang ==\n");
    printf("1. Nhap kho hang\n");
    printf("2. Xuat mot san pham\n");
    printf("3. Xem san pham chuan bi xuat\n");
    printf("4. Xem san pham moi nhap\n");
    printf("5. Xem cac san pham co trong kho\n");
    printf("6. Xuat tat ca cac mat hang co trong kho\n");
    printf("7. Ket thuc chuong trinh\n");
}

int main(){
    Queue Q; Init(Q);
    int EXIT = 1, choice = 0, n;

    Menu();

    do{
        printf("-------------------\n");
        printf("Nhap lua chon : "); scanf("%d", &choice);

        switch(choice){
            case 1 :{
                Nhap_Kho(Q, n);
                break;
            }
            case 2:{
                MatHang x = pop_MH(Q);
                if(x.maMH != -1){
                    Xuat_1(x);
                }
                break;
            }
            case 3:{
                Xuat_MH_F(Q);
                break;
            }
            case 4:{
                Xuat_MH_R(Q);
                break;
            }
            case 5:{
                Display_All(Q);
                break;
            }
            case 6:{
                Xuat_All(Q);
                break;
            }
            case 7:{
                EXIT = 7;
                break;
            }
        }
    }while(EXIT != 0);

    return 0;
}
