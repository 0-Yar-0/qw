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

long int date_to_int(DATE d);
long int sum(DATE d);
int check_file(char *path);
int check_empty(FILE *bin);
int parse_date_range(int *start, int *end);
void remove_records(char *path, int start, int end);
char *s21_strcat(char *str1, char *str2);
void print_bin(FILE *bin, char *path);
void bs(FILE *bin, char *path);
int count_el(FILE *bin);
void file_to_array(FILE *bin, DATE *arr, int n);
void array_to_file(FILE *bin, DATE *arr, int n);

int main() {
    char path_input[30];
    char path[63] = "../";
    int start, end;

    scanf("%29s", path_input);
    s21_strcat(path, path_input);

    if (check_file(path) || !parse_date_range(&start, &end)) {
        printf("n/a");
        return 0;
    }

    remove_records(path, start, end);
    FILE *bin = NULL;
    bin = fopen(path, "r+b");
    if (!bin) {
        printf("n/a");
        return 0;
    }
    if (check_empty(bin)) {
        printf("n/a");
        fclose(bin);
        return 0;
    }
    bs(bin, path);
    print_bin(bin, path);
    fclose(bin);
    return 0;
}

long int date_to_int(DATE d) {
    return d.y * 10000000000 + d.m * 100000000 + d.d * 1000000 + d.h * 10000 + d.min * 100 + d.sec;
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

int parse_date_range(int *start, int *end) {
    int day1, month1, year1, day2, month2, year2;

    if (scanf("%d.%d.%d %d.%d.%d", &day1, &month1, &year1, &day2, &month2, &year2) != 6) {
        return 0;
    }

    DATE start_date = {year1, month1, day1, 0, 0, 0, 0, 0};
    DATE end_date = {year2, month2, day2, 0, 0, 0, 0, 0};

    *start = date_to_int(start_date);
    *end = date_to_int(end_date);

    return 1;
}

void remove_records(char *path, int start, int end) {
    FILE *bin = fopen(path, "rb");
    if (!bin || check_empty(bin)) {
        printf("n/a");
        if (bin) fclose(bin);
        return;
    }

    FILE *temp = fopen("temp.bin", "wb");
    if (!temp) {
        printf("n/a");
        fclose(bin);
        return;
    }

    DATE d;
    while (fread(&d, sizeof(d), 1, bin) == 1) {
        long int date_int = date_to_int(d);
        if (date_int < start || date_int > end) {
            fwrite(&d, sizeof(d), 1, temp);
        }
    }

    fclose(bin);
    fclose(temp);

    if (remove(path) != 0 || rename("temp.bin", path) != 0) {
        printf("n/a");
    }
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

void print_bin(FILE *bin, char *path) {
    DATE d;
    rewind(bin);
    while (fread(&d, sizeof(d), 1, bin) == 1) {
        printf("%d %d %d %d %d %d %d %d\n", d.y, d.m, d.d, d.h, d.min, d.sec, d.status, d.code);
    }
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

void file_to_array(FILE *bin, DATE *arr, int n) {
    rewind(bin);
    fread(arr, sizeof(DATE), n, bin);
}

void array_to_file(FILE *bin, DATE *arr, int n) {
    rewind(bin);
    fwrite(arr, sizeof(DATE), n, bin);
}

long int sum(DATE d) {
    return d.y * 10000000000 + d.m * 100000000 + d.d * 1000000 +
           d.h * 10000 + d.min * 100 + d.sec;
}