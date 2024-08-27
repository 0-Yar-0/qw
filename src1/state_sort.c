#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int y, m, d, h, min, sec, status, code;
} DATE;

long int sum(DATE d);
void print_bin(FILE *bin, char *path);
void bs(FILE *bin, char *path);
int count_el(FILE *bin);
int check_file(char *path);
int check_empty(FILE *bin);
int add_el(FILE *bin);
void file_to_array(FILE *bin, DATE *arr, int n);
void array_to_file(FILE *bin, DATE *arr, int n);
int s21_strlen(char str[]);
char *s21_strcat(char *str1, char *str2);

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

    bin = fopen(path, "r+b");
    if (!bin) {
        printf("n/a");
        return 0;
    }

    int op;
    if (scanf("%d", &op) != 1 || op < 0 || op > 2) {
        printf("n/a");
        fclose(bin);
        return 0;
    }

    if (check_empty(bin)) {
        printf("n/a");
        fclose(bin);
        return 0;
    }

    switch (op) {
        case 0:
            print_bin(bin, path);
            break;
        case 1:
            bs(bin, path);
            print_bin(bin, path);
            break;
        case 2:
            if (add_el(bin)) {
                printf("n/a");
            } else {
                bs(bin, path);
                print_bin(bin, path);
            }
            break;
    }

    fclose(bin);
    return 0;
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

void print_bin(FILE *bin, char *path) {
    DATE d;
    rewind(bin);
    while (fread(&d, sizeof(d), 1, bin) == 1) {
        printf("%d %d %d %d %d %d %d %d\n", d.y, d.m, d.d, d.h, d.min, d.sec, d.status, d.code);
    }
}

long int sum(DATE d) {
    return d.y * 10000000000 + d.m * 100000000 + d.d * 1000000 +
           d.h * 10000 + d.min * 100 + d.sec;
}

void bs(FILE *bin, char *path) {
    int n = count_el(bin);
    DATE *arr = malloc(n * sizeof(DATE));
    if (!arr) {
        printf("n/a");
        return;
    }

    file_to_array(bin, arr, n);

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (sum(arr[j]) > sum(arr[j + 1])) {
                DATE temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    array_to_file(bin, arr, n);
    free(arr);
}

int count_el(FILE *bin) {
    rewind(bin);
    int n = 0;
    DATE d;
    while (fread(&d, sizeof(d), 1, bin) == 1) {
        ++n;
    }
    rewind(bin);
    return n;
}

int add_el(FILE *bin) {
    DATE d;
    if (scanf("%d %d %d %d %d %d %d %d", &d.y, &d.m, &d.d, &d.h, &d.min, &d.sec, &d.status, &d.code) != 8) {
        return 1;
    }
    fseek(bin, 0, SEEK_END);
    fwrite(&d, sizeof(d), 1, bin);
    return 0;
}

void file_to_array(FILE *bin, DATE *arr, int n) {
    rewind(bin);
    fread(arr, sizeof(DATE), n, bin);
}

void array_to_file(FILE *bin, DATE *arr, int n) {
    rewind(bin);
    fwrite(arr, sizeof(DATE), n, bin);
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