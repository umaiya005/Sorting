#include <stdio.h>
#include <stdlib.h>

long mergeCount = 0, quickCount = 0;

void Merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        mergeCount++;
        if (L[i] <= R[j]) a[k++] = L[i++];
        else              a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];

    free(L);
    free(R);
}

void MergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        MergeSort(a, l, m);
        MergeSort(a, m + 1, r);
        Merge(a, l, m, r);
    }
}

int Partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        quickCount++;
        if (a[j] <= pivot) {
            i++;
            int t = a[i]; a[i] = a[j]; a[j] = t;
        }
    }

    int t = a[i + 1]; a[i + 1] = a[high]; a[high] = t;
    return i + 1;
}

void QuickSort(int a[], int low, int high) {
    if (low < high) {
        int p = Partition(a, low, high);
        QuickSort(a, low, p - 1);
        QuickSort(a, p + 1, high);
    }
}

void PrintArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("File not found!\n");
        return 1;
    }

    int n, m;
    if (fscanf(file, "%d %d", &n, &m) != 2 || n < 0 || m < 0) {
        printf("Invalid input!\n");
        fclose(file);
        return 1;
    }

    int *arr1 = malloc((n > 0 ? n : 1) * sizeof(int));
    int *arr2 = malloc((n > 0 ? n : 1) * sizeof(int));
    int *batch = malloc((m > 0 ? m : 1) * sizeof(int));
    int *result = malloc((n + m > 0 ? n + m : 1) * sizeof(int));

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &arr1[i]) != 1) {
            printf("Invalid input!\n");
            fclose(file);
            return 1;
        }
        arr2[i] = arr1[i];
    }

    for (int i = 0; i < m; i++) {
        if (fscanf(file, "%d", &batch[i]) != 1) {
            printf("Invalid input!\n");
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    if (n > 0) {
        MergeSort(arr1, 0, n - 1);
        QuickSort(arr2, 0, n - 1);
    }

    printf("Merge Sort: ");
    PrintArray(arr1, n);
    printf("Quick Sort: ");
    PrintArray(arr2, n);
    printf("Merge Comparisons: %ld\n", mergeCount);
    printf("Quick Comparisons: %ld\n", quickCount);

    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (arr1[i] <= batch[j]) result[k++] = arr1[i++];
        else                     result[k++] = batch[j++];
    }
    while (i < n) result[k++] = arr1[i++];
    while (j < m) result[k++] = batch[j++];

    printf("Updated Array: ");
    PrintArray(result, n + m);

    free(arr1);
    free(arr2);
    free(batch);
    free(result);
    return 0;
}

