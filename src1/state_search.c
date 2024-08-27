#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int y;
    int m;
    int d;
    int h;
    int min;
    int sec;
    int status;
    int code;
} DATE;

int s21_strlen(char str[]);
char *s21_strcat(char *str1, char *str2);
int check_file(char *path);
int check_empty(FILE *bin);
void outf(int code);

int main() {
    FILE *bin = NULL;
    char path_input[30];
    char path[63] = "../";
    scanf("%29s", path_input);
    s21_strcat(path, path_input);

    if (check_file(path)) {
        printf("n/a");
        return 0;
    }

    bin = fopen(path, "rb");
    if (!bin || check_empty(bin)) {
        printf("n/a");
        if (bin) fclose(bin);
        return 0;
    }

    int day, month, year;
    if (scanf("%d.%d.%d", &day, &month, &year) != 3) {
        printf("n/a");
        fclose(bin);
        return 0;
    }

    DATE d;
    while (fread(&d, sizeof(d), 1, bin) == 1) {
        if (d.y == year && d.m == month && d.d == day) {
            outf(d.code);
            fclose(bin);
            return 0;
        }
    }

    printf("n/a");
    fclose(bin);
    return 0;
}

void outf(int code) {
    FILE *out = fopen("../src/code.txt", "w");
    if (out) {
        fprintf(out, "%d", code);
        fclose(out);
        printf("%d", code);
    }
}

int check_file(char *path) {
    FILE *bin = fopen(path, "rb");
    if (bin) {
        fclose(bin);
        return 0;
    }
    return 1;
}

int check_empty(FILE *bin) {
    fseek(bin, 0, SEEK_END);
    long size = ftell(bin);
    rewind(bin);
    return size == 0;
}

int s21_strlen(char str[]) {
    int i = 0;
    while (str[i] != '\0') ++i;
    return i;
}

char *s21_strcat(char *str1, char *str2) {
    int n = s21_strlen(str1);
    int i;
    for (i = 0; str2[i] != '\0'; ++i) str1[n + i] = str2[i];
    str1[n + i] = '\0';
    return str1;
}
