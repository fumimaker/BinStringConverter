#include <stdio.h>
#include <stdlib.h>
#define array_num 131071
long GetFileSize(FILE *fp);
int main(void)
{
    FILE *fp = fopen("inuko9bit.raw", "rb");
    if (fp == NULL){
        fputs("ファイルオープンに失敗しました。\n", stderr);
        exit(EXIT_FAILURE);
    }

    
    long fileSize = GetFileSize(fp); //77826
    printf("%ld\n", fileSize);
    unsigned char data[77826] = {};

    if (fread(&data, sizeof(data), fileSize, fp) < 1){
        fputs("読み込み中にエラーが発生しました。\n", stderr);
        exit(EXIT_FAILURE);
    }

    

    if (fclose(fp) == EOF){
        fputs("ファイルクローズに失敗しました。\n", stderr);
        exit(EXIT_FAILURE);
    }

    return 0;
}

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