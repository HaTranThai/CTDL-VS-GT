#include <stdio.h>
#include <string.h>

struct sach{
    char name[20];
    char tacGia[5][50];
    char nXB[20];
    int namXB;
    int sztg;
};
struct Node{
    sach data;
    Node* pNext;
};
struct List{
    Node* pHead;
    Node* pTail;
};
struct thongKeTG{
    char tenTacGia[50];
    int slSach;
};
struct Node1{
    thongKeTG dataThongKe;
    Node1* pnext;
};
struct danhSachThongKe{
    Node1* ptail;
    Node1* phead;
};
void Init(List &L){ L.pHead = L.pTail = NULL;}
void InitTK(danhSachThongKe &TK){ TK.phead = TK.ptail = NULL;}
Node* createNode(sach data){
    Node* p = new Node();

    p->data = data;
    p->pNext = NULL;

    return p;
}
void push_back(List &L, sach data){
    Node* p = createNode(data);

    if(L.pTail == NULL) L.pHead = L.pTail = p;
    else{
        L.pTail->pNext = p;
        L.pTail = p;
    }
}
sach input(){
    sach data;
    printf("\n---Nhap thong tin sach---\n");
    printf("Nhap ten sach: "); scanf("%[^\n]", &data.name); fflush(stdin);

    printf("Nhap so luong tac gia: "); scanf("%d", &data.sztg); fflush(stdin);

    for(int i = 0; i < data.sztg; i++){
        printf("Nhap ten tac gia %d: ", i + 1);

        scanf("%[^\n]", &data.tacGia[i]); fflush(stdin);

    }

    printf("Nhap ten nha xuat ban: "); scanf("%[^\n]", &data.nXB); fflush(stdin);

    printf("Nhap nam xuat ban: "); scanf("%d", &data.namXB);

    return data;
}
void output(sach data){
    printf("Ten sach: %s\n", data.name);
    printf("--Ten tac gia--\n");
    for(int i = 0; i < data.sztg; i++){
        printf("%d. %s\n", i + 1, data.tacGia[i]);
    }
    printf("Ten nha xuat ban: %s\n", data.nXB);
    printf("Nam xuat ban: %d\n", data.namXB);
    printf("\n--------------\n");
}
void display(List L){
    Node* p = L.pHead;

    while(p != NULL){
        output(p->data);
        p = p->pNext;
    }
}
void ghiFile(List L){   // Câu 1
    FILE* f = fopen("list1.bin", "wb+");

    Node* p = L.pHead;

    while(p != NULL){
        fwrite(&p->data, sizeof(sach), 1, f);
        p = p->pNext;
    }

    fclose(f);
}
int soSachcuaTG(char TG[], List L){     // Câu 2 
    int cnt = 0;
    Node* p = L.pHead;
    
    while(p != NULL){
        for(int i = 0; i < p->data.sztg; i++){
            if(strcmp(p->data.tacGia[i], TG) == 0) cnt++;
        }
        p = p->pNext;
    }

    return cnt;
}
void soSachNXBInYear(char NXB[], int YEAR, List L){    // Câu 3
    Node* p = L.pHead;

    int i = 1;

    printf("--Danh sach--\n");
    
    while(p != NULL){
        if(strcmp(p->data.nXB, NXB) == 0 && p->data.namXB == YEAR){
            printf("%d. %s\n", i, p->data.name); i++;
        }
        p = p->pNext;
    }

    if(i == 1) printf("Khong co du lieu phu hop\n");

}
void xoaSachTGX(char* TG, List &L){ // Câu 4
    Node* p = L.pHead;
    Node* pre = NULL;

    while(p != NULL){
        int yes = 0;
        for(int i = 0; i < p->data.sztg; i++)
            if(strcmp(p->data.tacGia[i], TG) == 0) yes = 1;

        if(yes){
            if(pre == NULL) L.pHead = p->pNext;
            else{
                pre->pNext = p->pNext;
            }

            if(p == L.pTail) L.pTail = pre;

            p = p->pNext;
        }
        else pre = p, p = p->pNext;
    }

    FILE* f = fopen("data.txt", "w+");

    Node* q = L.pHead;

    while(q != NULL){
        fprintf(f, "Ten sach: %s\n", q->data.name);
        fprintf(f, "--Ten tac gia--\n");
        for(int i = 0; i < q->data.sztg; i++){
            fprintf(f, "%d. %s\n", i + 1, q->data.tacGia[i]);
        }
        fprintf(f, "Ten nha xuat ban: %s\n", q->data.nXB);
        fprintf(f, "Nam xuat ban: %d\n", q->data.namXB);
        fprintf(f, "--------------------\n");
        q = q->pNext;
    }

    fclose(f);
}
void thongKeVaGhiKetQua(List L) {    // Câu 5
    FILE* f = fopen("list.bin", "wb+");

    Node* p = L.pHead;
    thongKeTG exit[30];
    int cnt = 0;

    while(p != NULL) {
        for (int i = 0; i < p->data.sztg; i++) {
            int flag = 1;
            for(int j = 0; j < cnt; j++){
                if(strcmp(p->data.tacGia[i], exit[j].tenTacGia) == 0) flag = 0;
            }
            if(!flag) continue;
            
            int count = soSachcuaTG(p->data.tacGia[i], L);
            exit[cnt].slSach = count;
            strcpy(exit[cnt].tenTacGia, p->data.tacGia[i]);
            cnt++;
        }

        p = p->pNext;
    }

    for(int i = 0; i < cnt; i++){
        fwrite(&exit[i], sizeof(thongKeTG), 1, f);
    }

    fclose(f);
}
void docFileThongKe(){      // Câu 6
    FILE* f = fopen("list.bin", "rb+");

    thongKeTG TG;

    while(fread(&TG, sizeof(thongKeTG), 1, f) >= 1){
        printf("Tac gia: %s - So luong sach: %d\n", TG.tenTacGia, TG.slSach);
    }

    fclose(f);
}
void docFileVaoList(List &L1){      // Câu 7
    FILE* f = fopen("list1.bin", "rb+");

    sach Sach;
    
    while(fread(&Sach, sizeof(sach), 1, f) >= 1){
        push_back(L1, Sach);
    }

    display(L1);

    fclose(f);
}
void push(danhSachThongKe &TK, thongKeTG val){
    Node1* p = new Node1;
    p->dataThongKe = val;
    p->pnext = NULL;

    if(TK.ptail == NULL) TK.phead = TK.ptail = p;
    else{
        TK.ptail->pnext = p;
        TK.ptail = p;
    }
}
void docFileThongKVaoList(danhSachThongKe &TK){     // Câu 8
    FILE* f = fopen("list.bin", "rb+");

    thongKeTG TG;

    while(fread(&TG, sizeof(thongKeTG), 1, f) >= 1){
        push(TK, TG);
    }

    fclose(f);
}
void displayDSTK(danhSachThongKe TK){
    Node1* p = TK.phead;

    while(p != NULL){
        printf("Tac gia: %s - So luong sach: %d\n", p->dataThongKe.tenTacGia, p->dataThongKe.slSach);
        p = p->pnext;
    }

}
void Menu(){
    printf("\n---------MENU---------\n");
    printf("1. Tao danh sach chua thong tin quyen sach va ghi vao file\n");
    printf("2. So luong quyen sach cua tac gia\n");
    printf("3. Nhung quyen sach duoc phat hanh vao nam YYYY boi tac gia ABC\n");
    printf("4. Xoa tat ca quyen sach cua tac gia X va ghi ket qua vao file\n");
    printf("5. Thong ke so luong sach cua moi tac gia vaf ghi ket qua thong ke len file\n");
    printf("6. Doc du lieu thong ke tu cau 5. Xuat len man hinh\n");
    printf("7. Doc du lieu tu cau 1 va dua vao danh sach\n");
    printf("8. Doc du lieu duoc thong ke tu cau 5 va dua vao danh sach\n");
    printf("9. Thoat\n");
}
int main(){
    List L; Init(L);
    List L1; Init(L1);
    danhSachThongKe TK; InitTK(TK);

    int EXIT = 0;

    // Câu 5, 6, 8 dùng chung file là list.bin
    // Câu 1 với 7 dùng chung file list1.bin
    // Câu 4 dùng file data.txt

    Menu();
    do{
        int choose;
        printf("\n Nhap lua chon: "); scanf("%d", &choose);
        switch(choose){
            case 1:{
                printf("\n1. Tao danh sach chua thong tin quyen sach va ghi vao file\n");
                int res; 
                printf("Nhap so luong sach: "); scanf("%d", &res); 
                for(int i = 1; i <= res; i++){
                    fflush(stdin);
                    sach a = input();
                    push_back(L, a);
                }
                ghiFile(L);
                break;
            }
            case 2:{
                printf("\n2. So luong quyen sach cua tac gia\n");
                char TG[50];

                printf("Nhap ten tac gia: "); fflush(stdin);
                scanf("%[^\n]", &TG); 

                int res = soSachcuaTG(TG, L);
                printf("So sach cau tac gia %s la: %d\n", TG, res);
                break;
            }
            case 3:{
                printf("\n3. Nhung quyen sach duoc phat hanh vao nam YYYY boi tac gia ABC\n");

                char NXB[20]; 
                int YEAR;
                printf("\nNhap ten NXB: "); fflush(stdin);
                scanf("%[^\n]", &NXB);
                printf("Nhap nam phat hanh: ");
                scanf("%d", &YEAR);

                soSachNXBInYear(NXB, YEAR, L);
                break;
            }
            case 4:{
                printf("\n4. Xoa tat ca quyen sach cua tac gia X va ghi ket qua vao file\n");
                char TG[50];

                printf("Nhap ten tac gia: "); fflush(stdin);
                scanf("%[^\n]", &TG); 
                xoaSachTGX(TG, L);
                break;
            }
            case 5:{
                printf("\n5. Thong ke so luong sach cua moi tac gia vaf ghi ket qua thong ke len file\n");
                thongKeVaGhiKetQua(L);
                break;
            }
            case 6:{
                printf("\n6. Doc du lieu thong ke tu cau 5. Xuat len man hinh\n");

                docFileThongKe();
                break;
            }
            case 7:{
                printf("\n7. Doc du lieu tu cau 1 va dua vao danh sach\n");

                docFileVaoList(L1);
                break;
            }
            case 8:{
                printf("\n8. Doc du lieu duoc thong ke tu cau 5 va dua vao danh sach\n");
                
                docFileThongKVaoList(TK);
                displayDSTK(TK);
                break;
            }
            case 9:{
                printf("\n9. Thoat\n");
                EXIT = 9;
                break;
            }
        }
    }while(EXIT != 9);

}




