#include <stdio.h>
#include <string.h>
#include <cstdlib>

struct WORD{
    char NAME[256];
    char Meaning[512];
};
void Nhap(WORD &word){
    printf("hay nhap vao mot tu:"); fflush(stdin);
    scanf("%[^\n]\n%[^\n]", word.NAME, word.Meaning);
}
void Xuat(WORD word){
    printf("%s: %s\n", word.NAME, word.Meaning);
}
void Swap(WORD &a,  WORD &b){
	struct WORD c = a;
	a = b;
	b = c;
}
void sapXep(WORD arr[], int n){
    int min_idx;
 
    for (int i = 0; i < n - 1; i++){
        min_idx = i;
        for (int j = i + 1; j < n; j++){
        	if (strcmp(arr[j].NAME, arr[min_idx].NAME) < 0)
            	min_idx = j;
 
        	if(min_idx != i)
            	Swap(arr[min_idx], arr[i]);
		}
          
    }
}
int timKiem(WORD arr[], int n, char str[]){
	int l = 0, r = n - 1;
	
	while(l <= r){
		int mid = (l + r) / 2;
		if(strcmp(arr[mid].NAME, str) == 0) return mid;
		if(strcmp(arr[mid].NAME, str) > 0){
			r = mid - 1;
		}else l = mid + 1;
	}
	return -1;
}
void ghiTu(char *filename, WORD word){

    FILE *f = fopen(filename, "ab+");

    fwrite(&word, sizeof(WORD), 1, f);

    fclose(f);
}
void ghiMang(char *filename, WORD word[], int sz){
    FILE *f = fopen(filename, "ab+");

    fwrite(word, sizeof(struct WORD), sz, f);

    fclose(f);

}
void docTep(char *filename){
    FILE *f = fopen(filename, "rb");

    struct WORD word;

    while (fread(&word, sizeof(struct WORD), 1, f) == 1) {
        printf("\nName: %s\n", word.NAME);
        printf("Meaning: %s\n", word.Meaning);
    }

    fclose(f);
}
void docMotTu(char *filename, WORD word){
    FILE *f = fopen(filename, "rb");

    WORD tmp;
    int yes = 0;
    while(fread(&tmp, sizeof(WORD), 1, f) == 1){
        if(strcmp(word.NAME, tmp.NAME) == 0 && strcmp(word.Meaning, tmp.Meaning) == 0){
            printf("\nName: %s\n", word.NAME);
            printf("Meaning: %s\n", word.Meaning);
            yes = 1;
        }
    }

    if(!yes) printf("Khong co trong tu dien\n");

    fclose(f);

}
void doiNghiaTu(char *filename, char name[], char newMean[]){
    FILE *f = fopen(filename, "rb");

    char temp_filename[] = "temp_dictionary.bin";
    FILE *tf = fopen(temp_filename, "wb");

    WORD word;

    while(fread(&word, sizeof(WORD), 1, f) == 1){
        if (strcmp(word.NAME, name) == 0) {
            strcpy(word.Meaning, newMean);
        }
        ghiTu(temp_filename, word);
    }

    fclose(f);
    fclose(tf);

    remove(filename);
    rename(temp_filename, filename);

}
void xoaTu(char *filename, char name[]){
    FILE *f = fopen(filename, "rb");
dwdqw
    char temp_filename[] = "temp_dictionary.bin";
    FILE *tf = fopen(temp_filename, "wb");

    WORD word;

    while(fread(&word, sizeof(WORD), 1, f) == 1){
        if (strcmp(word.NAME, name) == 0) {
            continue;
        }
        ghiTu(temp_filename, word);
    }

    fclose(f);
    fclose(tf);

    remove(filename);
    rename(temp_filename, filename);

}
void MENU(){
    printf("1. Nhap thong tin cua tu.\n");
    printf("2. Xuat thong tin cua tu.\n");
    printf("3. Sap xep tu theo NAME tang dan.\n");
    printf("4. Tim kiem tu theo NAME.\n");
    printf("5. Ghi 1 tu vao tep.\n");
    printf("6. Ghi 1 mang tu vao tep.\n");
    printf("7. Doc tep.\n");
    printf("8. Doc mot tu trong tep.\n");
    printf("9. Cap nhat nghia cua tu.\n");
    printf("10. Xoa 1 tu theo NAME.\n");
    printf("11. Thoat.\n");
}

void docTepText(char *filename){
    FILE *f = fopen(filename, "rb");
    FILE *t = fopen("out.txt", "a+");

    struct WORD word;

    while (fread(&word, sizeof(struct WORD), 1, f) == 1) {
        fprintf(t, "\nName: %s\n", word.NAME);
        fprintf(t, "Meaning: %s\n", word.Meaning);
        fprintf(t, "-----------------------");
    }

    fclose(f);
    fclose(t);
}


int main(){
    WORD words[100];
    int indx = 0, choose, exit = 0;
    char filename[] = "diction.bin";

    
    MENU();
    do{
        printf("\n");
        printf("Nhap lua chon :");
        scanf("%d", &choose);
        switch (choose){
            case 1:{
                printf("Nhap Name va nghia cua Name: \n");
                Nhap(words[indx++]);
                break;
            }
            case 2:{
                int ans;
                do{
                    printf("Nhap vao vi tri can in : ");
                    scanf("%d", &ans);
                }while(ans < 0 || ans > indx);

                Xuat(words[ans]);
                break;
            }
            case 3:{
                sapXep(words, indx);
                break;
            }
            case 4:{
                char str[256];
                printf("Nhap vao Name can tim: ");
                fflush(stdin);
                gets(str);
                int res = timKiem(words, indx, str);

                if(res == -1) printf("Not Found !!\n");
                else printf("Vi tri cua %s hien tai la %d\n", str, res);
                break;
            }
            case 5:{
                WORD word;
                printf("Nhap Name va nghia cua Name can ghi vao tep: \n");
                Nhap(word);
                ghiTu(filename, word);
                break;
            }
            case 6:{
                ghiMang(filename, words, indx);
                break;
            }
            case 7:{
                docTep(filename);
                break;
            }
            case 8:{
                WORD word;

                printf("Nhap tu can doc trong file: \n");
                Nhap(word);

                docMotTu(filename, word);
                break;
            }
            case 9:{
                char name[256], newMean[512];
                printf("Nhap NAME va nghia moi: ");
                fflush(stdin);
                scanf("%[^\n]\n%[^\n]", name, newMean);

                doiNghiaTu(filename, name, newMean);\
                break;
            }
            case 10:{
                char del[256];

                printf("Nhap NAME can xoa: ");
                fflush(stdin);
                gets(del); 

                xoaTu(filename, del);
                break;
            }
            case 11:{
                exit = 1;
                break;
            }

        }
    }while(!exit);
    

    // docTepText(filename);


    return 0;
}
