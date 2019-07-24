#include <stdio.h>
#include <stdlib.h>
#define array_size 230402
#define array_size_tmp array_size/3

long GetFileSize(FILE *fp);
unsigned char data[array_size] = {};
long fileSize;

long GetFileSize(FILE *fp)
{
    // 現在のファイルポジションを保存
    long fpos_save = ftell(fp);

    // ファイルの末尾まで移動して、その位置を調べる
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    // ファイルポジションを元に戻す
    fseek(fp, fpos_save, SEEK_SET);

    return size;
}

unsigned int conv(int i){
    unsigned char r = data[i*3] >> 5;
    unsigned char g = data[i*3 + 1] >> 5;
    unsigned char b = data[i*3 + 2] >> 5;
    unsigned int color9 = (r << 6) | (g << 3) | (b << 0);
    //printf("%03X\n", color9);

    return color9;
}

int main(void){
    FILE *fp = fopen("inuko24.bin", "rb");
    if (fp == NULL){
        fputs("ファイルオープンに失敗しました。\n", stderr);
        exit(EXIT_FAILURE);
    }

    
    fileSize = GetFileSize(fp); //77826
    printf("%ld\n", fileSize);
    

    if (fread(&data, sizeof(data), fileSize, fp) < 1){
        fputs("読み込み中にエラーが発生しました。\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (fclose(fp) == EOF){
        fputs("ファイルクローズに失敗しました。\n", stderr);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < array_size_tmp; i++){
        int col = conv(i);//intで帰ってくる
        FILE *outputfile;
        outputfile = fopen("output.txt", "a");
        if (outputfile == NULL){
            printf("書き込み異常発生");
            exit(1);
        }
        fprintf(outputfile, "%03X\n", col);
        fclose(outputfile);
        printf("%03X\n", col);
    }
    return 0;
}



/*
r=getchar()>>5;
g=getchar()>>5;
b=getchar()>>5;
alpha=getchar();
printf(“%03X¥n”, (r << 6) | (g << 3) | (b));
 */