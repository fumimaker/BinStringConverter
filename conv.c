#include <stdio.h>
#include <stdlib.h>

long GetFileSize(FILE *fp);
unsigned char data[77826] = {};
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

void conv(void)
{
    for (int i = 0; i < fileSize; i = i + 3)
    {
        unsigned char r = data[i] >> 5;
        unsigned char g = data[i + 1] >> 5;
        unsigned char b = data[i + 2] >> 5;
        printf("%03X\n", (r << 6) | (g << 3) | (b << 0));
    }
}

int main(void){
    FILE *fp = fopen("inuko9bit.raw", "rb");
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
    conv();
    return 0;
}



/*
r=getchar()>>5;
g=getchar()>>5;
b=getchar()>>5;
alpha=getchar();
printf(“%03X¥n”, (r << 6) | (g << 3) | (b));
 */