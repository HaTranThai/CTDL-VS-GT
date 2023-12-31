#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct sinhVien{
    int mssv;
    char hoTen[50];
    char gt[10];
    char diaChi[50];
    float dTB;
};
void nhapTT1(sinhVien &sv){
    printf("\nNhap mssv: "); 
    scanf("%d", &sv.mssv);
    fflush(stdin);
    printf("\nNhap ho va ten: "); 
    scanf("%[^\n]", sv.hoTen);
    fflush(stdin);
    printf("\nNhap gioi tinh: "); 
    scanf("%[^\n]", sv.gt);
    fflush(stdin);
    printf("\nNhap dia chi: "); 
    scanf("%[^\n]", sv.diaChi);
    fflush(stdin);
    printf("\nNhap diem trung binh: "); 
    scanf("%f", &sv.dTB);
}
void inPut(sinhVien sv[], int n){
    for(int i = 0; i < n; i++){
        printf("\n---Nhap thong tin sinh vien %d---", i + 1);
        nhapTT1(sv[i]);
    }
}
void xuatTT1(sinhVien sv){
    printf("|%20d|%20s|%20s|%40s|%20.2f|\n", sv.mssv, sv.hoTen, sv.gt, sv.diaChi, sv.dTB);
}
void outPut(sinhVien sv[], int n){
    printf("|%20s|%20s|%20s|%40s|%20s|\n", "MSSV", "Ho va Ten", "Gioi tinh", "Dia chi", "Diem trung binh");
    for(int i = 0; i < n; i++){
        xuatTT1(sv[i]);
    }
}
void thongTinsvX(sinhVien sv[], int n, int mssvx){
    for(int i = 0; i < n; i++){
        if(sv[i].mssv == mssvx){
            printf("|%20s|%20s|%20s|%40s|%20s|\n", "MSSV", "Ho va Ten", "Gioi tinh", "Dia chi", "Diem trung binh");
            xuatTT1(sv[i]);
            return;
        }
    }
}
void Swap(sinhVien &a, sinhVien &b){
    sinhVien tmp = a;
    a = b;
    b= tmp;
}
void sapXepDTB(sinhVien sv[], int n){
    int i, j, min_idx;
 
    for (i = 0; i < n - 1; i++) {
 
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (sv[j].dTB < sv[min_idx].dTB)
                min_idx = j;
        }
        if (min_idx != i)
            Swap(sv[min_idx], sv[i]);
    }
}
void sapXepHoTen(sinhVien sv[], int n){
    int i, j, min_idx;
 
    for (i = 0; i < n - 1; i++) {
  
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (sv[j].hoTen > sv[min_idx].hoTen)
                min_idx = j;
        }
        if (min_idx != i)
            Swap(sv[min_idx], sv[i]);
    }
}
void ghiDSSV(char *filename, sinhVien sv[], int n){
    FILE* f = fopen(filename, "ab");

    fwrite(sv, sizeof(sinhVien), n, f);

    fclose(f);
}
void docDSSV(char *filename){
    FILE* f = fopen(filename, "rb");

    printf("|%20s|%20s|%20s|%40s|%20s|\n", "MSSV", "Ho va Ten", "Gioi tinh", "Dia chi", "Diem trung binh");
    sinhVien sv;
    while(fread(&sv, sizeof(sinhVien), 1, f) == 1){
        xuatTT1(sv);
    }

    fclose(f);
}
void suaTTsvX(char *filename, int mssvX, sinhVien svX){
    FILE* f = fopen(filename, "r + b");

    sinhVien sv;

    while(fread(&sv, sizeof(sinhVien), 1, f) == 1){
        if(sv.mssv == mssvX){
            fseek(f, -sizeof(sinhVien), SEEK_CUR);
            fwrite(&svX, sizeof(sinhVien), 1, f);
            fclose(f);
            return;
        }
    }
    
}
void xoasvX(char *filename, int mssvX, int &n){
    FILE* f = fopen(filename, "rb+");

    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    sinhVien *data = (sinhVien *)malloc(file_size);

    fread(data, 1, file_size, f);

    int k = 0;    

    for(int i = 0; i < n; i++){
        if(data[i].mssv == mssvX) k = 1;
        if(k){
            data[i] = data[i + 1];
        }
    }

    if(k) n--;

    int fd = fileno(f);
    ftruncate(fd, sizeof(sinhVien) * n);
    
    rewind(f);

    fwrite(data, sizeof(sinhVien), n, f);

    fclose(f);
    free(data);
    
}
void dTBMax(char *filename){
    FILE* f = fopen(filename, "rb");

    float amax = 0;

    sinhVien sv;

    while(fread(&sv, sizeof(sinhVien), 1, f) == 1) if(sv.dTB > amax) amax = sv.dTB;

    fseek(f, 0, SEEK_SET);

    while(fread(&sv, sizeof(sinhVien), 1, f) == 1){
        if(sv.dTB == amax){
            xuatTT1(sv);
        }
    }

    fclose(f);
}
void MENU(){
    printf("1. Nhap cac sinh vien vao danh sach\n");
    printf("2. In danh sach sinh vien\n");
    printf("3. Xuat thong tin sinh vien co ma X\n");
    printf("4. Sap xep danh sach sinh vien theo thu tu tang dan cua diem trung binh\n");
    printf("5. Sap xep danh sach sinh vien theo thu tu tang dan cua Ho va Ten\n");
    printf("6. Ghi danh sach sinh vien vao file\n");
    printf("7. Doc danh sach sinh vien tu file\n");
    printf("8. Sua danh sach sinh vien co ma X\n");
    printf("9. Xoa sinh vien co ma X\n");
    printf("10. Xuat cac sinh vien co diem trung binh cao nhat\n");
    printf("11. Thoat\n");
}
int main(){
    sinhVien sv[57];
    int n; 
    char filename[] = "sv.bin";
    MENU();

    int EXIT = 0;

    do{
        int type;
        printf("-----------------\n");
        printf("Nhap vao lua chon : "); scanf("%d", &type);

        switch(type){
            case 1:{
                printf("Nhap vao so luong sinh vien: "); scanf("%d", &n);
                inPut(sv, n);
                break;
            }
            case 2:{
                outPut(sv, n);
                break;
            }
            case 3:{
                int mssvX; printf("Nhap vao mssv X: "); scanf("%d", &mssvX);
                thongTinsvX(sv, n, mssvX);
                break;
            }
            case 4:{
                sapXepDTB(sv, n);
                break;
            }
            case 5:{
                sapXepHoTen(sv, n);
                break;
            }
            case 6:{
                ghiDSSV(filename, sv, n);
                break;
            }
            case 7:{
                docDSSV(filename);
                break;
            }
            case 8:{
                int mssvX; printf("Nhap vao mssv X: "); scanf("%d", &mssvX);

                sinhVien svX;
                printf("Nhap vao thong tin can sua: ");
                nhapTT1(svX);

                suaTTsvX(filename, mssvX, svX);
                break;
            }
            case 9:{
                int mssvX; printf("Nhap vao mssv X: "); scanf("%d", &mssvX);
                xoasvX(filename, mssvX, n);
                break;
            }
            case 10:{
                dTBMax(filename);
                break;
            }
            case 11:{
                EXIT = 11;
                break;
            }
        }
    }while(EXIT != 11);




}
