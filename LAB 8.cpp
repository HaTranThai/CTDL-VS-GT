#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct item{
	char masv[20];
	char name[20];
	double diem;
};
struct Node{
	item data;
	Node* pLeft;
	Node* pRight;
};
void Init(Node* &T){
	T = NULL;
}
Node* createNode(item val){
	Node* p = new Node;
	p->data = val;
	p->pLeft = p->pRight = NULL;
	
	return p;
}
int addNode(Node* &T, Node* p){
	if(T == NULL) {
		T = p;
        return 1;
	}
	else{
		if(strlen(T->data.masv) == strlen(p->data.masv)){
			if(strcmp(T->data.masv, p->data.masv) > 0) return addNode(T->pLeft, p);
			else if(strcmp(T->data.masv, p->data.masv) < 0) return addNode(T->pRight, p);
			else return 0;
		}
		else if(strlen(T->data.masv) > strlen(p->data.masv)) return addNode(T->pLeft, p);
		else return addNode(T->pRight, p);
	}
}
void outputOne(item a){
	printf("Ma so sinh vien: %s\n", a.masv);
	printf("Ho ten sinh vien: %s\n", a.name);
	printf("Diem cua sinh vien: %.2lf\n", a.diem);
}
void InputOne(item &a){
    fflush(stdin);
    printf("Nhap mssv: "); scanf("%[^\n]", a.masv); 
    fflush(stdin);
    printf("Nhap ho ten: "); scanf("%[^\n]", a.name);
    printf("Nhap diem: "); scanf("%lf", &a.diem);
}
void input(Node* &T, int &n){
	printf("Nhap so luong sinh vien: "); scanf("%d", &n);
	item a;
	for(int  i = 1; i <= n; i++){
		printf("---------------------\n"); 
		InputOne(a);
		Node* p = createNode(a);
		int yes = addNode(T, p);
        if(!yes){
            printf("Trung !!\n"); i--;
        }
		printf("---------------------\n");
	}
}
void LNR(Node* T){
	if(T == NULL) return;
	
	LNR(T->pLeft);
	outputOne(T->data);
	LNR(T->pRight);
}

int Count_leaf(Node* T){
	if(T == NULL) return 0;
	if(T->pLeft == NULL && T->pRight == NULL) return 1;
	return Count_leaf(T->pLeft) + Count_leaf(T->pRight);
}
int max(int a, int b){return (a > b ? a : b);}
int High_tree(Node* T){
	if(T == NULL) return 0;
	if(T->pLeft == NULL && T->pRight == NULL) return 1;
	return max(High_tree(T->pLeft), High_tree(T->pRight)) + 1;
}
Node* search(Node* T, char* X){
	if(strlen(T->data.masv) == strlen(X)){
        if(strcmp(T->data.masv, X) > 0) return search(T->pLeft, X);
        else if(strcmp(T->data.masv, X) < 0) return search(T->pRight, X);
        else {
            return T;
        }
    }
    else if(strlen(T->data.masv) > strlen(X)) return search(T->pLeft, X);
    else return search(T->pRight, X);
}
Node* leftMostValue(Node* current){
    while(current->pLeft != NULL){
        current = current->pLeft;
    }
    return current;
}
Node* deleteNode(Node* T, char* X){
    if(T == NULL) return T;

    if(strlen(T->data.masv) == strlen(X)){
        if(strcmp(T->data.masv, X) == 0){
            if(T->pLeft == NULL){
                Node* tmp = T->pRight;
                return tmp;	
            }	
            if(T->pRight == NULL){
                Node* tmp = T->pLeft;
                return tmp;
            }

            T->data = leftMostValue(T->pRight)->data;
            T->pRight = deleteNode(T->pRight, X);

            return T;
        }
        else if(strcmp(T->data.masv, X) > 0){
            T->pLeft = deleteNode(T->pLeft, X);
        }
        else{
            T->pRight = deleteNode(T->pRight, X);
        }
    }
    else if(strlen(T->data.masv) > strlen(X)) return deleteNode(T->pLeft, X);
    else return deleteNode(T->pRight, X);

	return T;
}
void write_FileHelper(Node* T, FILE* outFile) {
    if (T == NULL) return;

    fprintf(outFile, "%s %s %.2lf\n", T->data.masv, T->data.name, T->data.diem);
    write_FileHelper(T->pLeft, outFile);
    write_FileHelper(T->pRight, outFile);
}
void write_File(Node* T) {
    FILE* outFile = fopen("out1.txt", "w");

    write_FileHelper(T, outFile);

    fclose(outFile);
}
void read_FileHelper(Node* T, FILE* inFile) {
    item a;
    while (fscanf(inFile, "%s %s %lf", a.masv, a.name, &a.diem) == 3) {
        Node* p = createNode(a);
        addNode(T, p);
    }
}
void read_File(Node* T) {
    FILE* inFile = fopen("out1.txt", "r");

    read_FileHelper(T, inFile);

    fclose(inFile);
}
void Menu(){
    printf("\n==MENU==\n");
    printf("1. Nhap du lieu cho cay va kiem tra trung.\n");
    printf("2. Duyet va xua du lieu theo thu tu LNR.\n");
    printf("3. Dem so la cua cay.\n");
    printf("4. Tinh chieu cao cua cay.\n");
    printf("5. Chen 1 Node vao cay.\n");
    printf("6. Tim kiem 1 Node bang MSSV.\n");
    printf("7. Xoa 1 Node.\n");
    printf("8. Ghi du lieu vao file.\n");
    printf("9. Doc du lieu tu file.\n");
}

int main(){
    int EXIT = 0, choose;
    Node* T; Init(T);
    Node* T1; Init(T1);
    int n;

    Menu();
    do{
        printf("-- Nhap lua chon: "); scanf("%d", &choose);
        switch (choose){
            case 1:{
                input(T, n);
                break;
            }
            case 2:{
                LNR(T); 
                break;
            }
            case 3:{
                int cnt = Count_leaf(T);
                printf("So la tren cay: %d\n", cnt);
                break;
            }
            case 4:{
                int cnt = High_tree(T);
                printf("Chieu cao cua cay: %d\n", cnt);
                break;
            }
            case 5:{
                item a;
                printf("Nhap du lieu cua Node can them\n");
                InputOne(a);
                Node* p = createNode(a);
                int cnt = addNode(T, p);
                if(!cnt){
                    printf("Them khong thanh cong do trung\n");
                }
                else printf("Them thanh cong\n");
                break;
            }
            case 6:{
                char X[20];
                printf("\nNhap mssv can tim kiem: "); fflush(stdin);
                scanf("%[^\n]", X);
                Node* res = search(T, X);
                
                outputOne(res->data);
                break;
            }
            case 7:{
                char X[20];
                printf("\nNhap mssv can xoa: "); fflush(stdin);
                scanf("%[^\n]", X);

                Node* res = deleteNode(T, X);
                LNR(T);
                break;
            }
            case 8:{
                write_File(T);
                break;
            }
            case 9:{
                read_File(T);
                break;
            }
            case 10:{
                EXIT = 10;
                break;
            }
        }
    }while(EXIT == 0);

    return 0;
}
