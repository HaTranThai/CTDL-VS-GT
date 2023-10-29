#include <stdio.h>
#include <cstdlib>

struct Node{
    int data;
    Node* pNext;
};
struct List{
    Node* pHead;
    Node* pTail;
};
Node* createNode(int data){
    Node* p = new Node;

    p->data = data;
    p->pNext = NULL;

    return p;

}
void Init(List &L){
    L.pHead = L.pTail = NULL;
}
int isEmpty(List L){
    if(L.pHead == NULL) return 1;
    return 0;
}
void push_back(List &L, int data){
    Node* p = createNode(data);
        
    if(isEmpty(L)) L.pHead = L.pTail = p;
    else{
        L.pTail->pNext = p;
        L.pTail = p;
    } 
}
void push_front(List &L, int data){
    Node* p = createNode(data);

    if(p == NULL){
        printf("Khong du bo nho\n");
        return;
    }    

    if(isEmpty(L)) L.pHead = L.pTail = p;
    else{
        p->pNext = L.pHead;
        L.pHead = p;
    } 
}
void createList(List &L, List &L1, int n){
    printf("---Nhap vao gia tri cua Node---\n");
    for(int i = 0, x; i < n; i++){
        scanf("%d", &x);
        push_back(L, x);
        push_back(L1, x);
    }
}
Node* search_keyK(List L, int val){
    Node* p = L.pHead;
    while(p != NULL) {
        if(p->pNext->data == val) return p;
        p = p->pNext;
    }
    return NULL;
}
void delete_keyK(List &L, int val){
    Node* q = L.pHead;

    if(q != NULL && q->data == val){
        L.pHead = q->pNext;
        q->pNext = NULL;
        free(q);
        return;
    }

    q = search_keyK(L, val);

    if(q == NULL || q->pNext == NULL) return;

    Node* p = q->pNext;
    q->pNext = p->pNext;

    if(L.pTail == q) L.pTail = q;

    delete p;
}
void display(List L){
    Node* p = L.pHead;

    while(p != NULL){
        printf("%d ", p->data);
        p = p->pNext;
    }

    printf("\n");

}
void xoaDau(List &L){
    if(L.pHead == NULL) return;

    Node* p = L.pHead;
    L.pHead = p->pNext;

    if(L.pHead == NULL) L.pTail = NULL;

    delete p;
}
void reqA(List &L, List &A, int val, int &szA, int &szL){
    Node* p = L.pHead;
    Node* pre;

    while(p != NULL){
        if(p->data >= val){
            push_back(A, p->data);
            szA++;
            if(pre == NULL) L.pHead = p->pNext;
            else{
                pre->pNext = p->pNext;
            }
            if(p ==L.pTail) L.pTail = pre;
            Node* q = p;
            p = p->pNext;
            free(q);
        }
        else{
            pre = p;
            p = p->pNext;
        }
    }

    szL -= szA;

} 
void reqB(List L, List &B, List &C, int val, int &szB, int &szC, int &szL1){
    Node* p = L.pHead;
    while(p != NULL){
        if(p->data >= val) push_back(B, p->data), szB++;
        else push_back(C, p->data), szC++;
        p = p->pNext;
    }
}
void ghiFileA(char* filename, List A, List L, int szA, int szL){
    FILE* f = fopen(filename, "wb+");

    Node* p = L.pHead;
    Node* q = A.pHead;

    fwrite(&szL, sizeof(int), 1, f);
    fwrite(&szA, sizeof(int), 1, f);
    
    while(p != NULL){
        fwrite(&(p->data), sizeof(int), 1, f);
        p = p->pNext;
    }

    while(q != NULL){
        fwrite(&(q->data), sizeof(int), 1, f);
        q = q->pNext;
    }

    fclose(f);

}
void ghiFileB(char* filename, List B, List C, List L1,int szB, int szC, int szL1){
    FILE* f = fopen(filename, "wb+");

    Node* p = L1.pHead;
    Node* q = B.pHead;
    Node* w = C.pHead;

    fwrite(&szL1, sizeof(int), 1, f);
    fwrite(&szB, sizeof(int), 1, f);
    fwrite(&szC, sizeof(int), 1, f);

    while(p != NULL){
        fwrite(&(p->data), sizeof(int), 1, f);
        p = p->pNext;
    }

    while(q != NULL){
        fwrite(&(q->data), sizeof(int), 1, f);
        q = q->pNext;
    }

    while(w != NULL){
        fwrite(&(w->data), sizeof(int), 1, f);
        w = w->pNext;
    }

    fclose(f);

}
void docFileA(char* filename){
    FILE* f = fopen(filename, "rb");
    
    int val;
    int arr[3];

    fread(&arr[0], sizeof(int), 1, f);
    fread(&arr[1], sizeof(int), 1, f);
    int it = 0,cnt = 0;

    while(fread(&val, sizeof(int), 1 , f) == 1){
        printf("%d ",val);
        cnt++;
        if(cnt == arr[it]){
            printf("\n");
            cnt = 0, it++;
        }
    }
    
    printf("\n");


    fclose(f);
}
void docFileB(char* filename){
    FILE* f = fopen(filename, "rb");

    int val;
    int arr[3];

    fread(&arr[0], sizeof(int), 1, f);
    fread(&arr[1], sizeof(int), 1, f);
    fread(&arr[2], sizeof(int), 1, f);
    
    int it = 0,cnt = 0;

    while(fread(&val, sizeof(int), 1 , f) == 1){
        printf("%d ",val);
        cnt++;
        if(cnt == arr[it]){
            printf("\n");
            cnt = 0, it++;
        }
    }

    printf("\n");
    
    fclose(f);
}
void MENU(){
    printf("1. Tao danh sach.\n");
    printf("2. In danh sach.\n");
    printf("3. Tao danh sach theo yeu cau a.\n");
    printf("4. Tao danh sach theo yeu cau b.\n");
    printf("5. Ghi danh sach cua yeu cau a vao file.\n");
    printf("6. Ghi danh sach cua yeu cau b vao file.\n");
    printf("7. Doc file a.\n");
    printf("8. Doc file b.\n");
    printf("9. Thoat.\n");
}
int main(){
    List L, L1, A, B, C;
    Init(L); Init(A); Init(B); Init(C); Init(L1);
    char filename[] = "list.bin"; 

    int type, EXIT = 0, szL, szL1, szA, szB, szC;

    MENU();
    do{
        printf("Nhap lua chon : ");
        scanf("%d", &type);

        switch(type){
            case 1:{
                printf("--Tao list--\n");
                int n; printf("Nhap so luong phan tu: "); scanf("%d", &n);
                createList(L, L1, n);
                szL = szL1 = n;
                break;
            }
            case 2:{
                printf("--List--\n");
                display(L);
                break;
            }
            case 3:{
                printf("--Yeu cau A--\n");
                int x; 
                printf("Nhap vao gia tri x: "); scanf("%d", &x);

                reqA(L, A, x, szA, szL);

                printf("--List--\n");
                display(L);
                printf("--List >= x--\n");
                display(A);
                break;
            }
            case 4:{
                printf("--Yeu cau B--\n");
                int x; 
                printf("Nhap vao gia tri x: "); scanf("%d", &x);

                reqB(L1, B, C, x, szB, szC, szL1);

                printf("--List--\n");
                display(L1);
                printf("--List >= x--\n");
                display(B);
                printf("--List < x--\n");
                display(C);
                break;
            }
            case 5:{
                ghiFileA(filename, A, L, szA, szL);
                break;
            }
            case 6:{
                ghiFileB(filename, B, C, L1, szB, szC, szL1);
                break;
            }
            case 7:{
                docFileA(filename);
                break;
            }
            case 8:{
                docFileB(filename);
                break;
            }
            default:{
                EXIT = 11;
                break;
            }
        }
    }while(EXIT != 11);
    return 0;
}
