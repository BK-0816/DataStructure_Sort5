#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int sorted[MAX_SIZE];
int list[MAX_SIZE];
int n;

// ���� ������ �� Ƚ���� �̵� Ƚ���� ����
int comparisons = 0;
int moves = 0;

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge(int list[], int left, int mid, int right) {
    int i, j, k, l;
    i = left;
    j = mid + 1;
    k = left;

    while (i <= mid && j <= right) {
        comparisons++;  // �� �� ����

        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
            moves++;  // �̵� �� ����
        }
        else {
            sorted[k++] = list[j++];
            moves++;  // �̵� �� ����
        }
    }

    if (i > mid) {
        for (l = j; l <= right; l++) {
            sorted[k++] = list[l];
            moves++;  // �̵� �� ����
        }
    }
    else {
        for (l = i; l <= mid; l++) {
            sorted[k++] = list[l];
            moves++;  // �̵� �� ����
        }
    }

    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
        moves++;  // �̵� �� ����
    }
}

void merge_sort(int list[], int left, int right, int iteration) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        merge_sort(list, left, mid, iteration);
        merge_sort(list, mid + 1, right, iteration);

        if (iteration == 19) {
            // 20��° ȣ���� ���� ���
            print_array(list, n);
        }

        merge(list, left, mid, right);
    }
}

int main(void) {
    int i;
    n = MAX_SIZE;
    srand(time(NULL));

    // ��ü �� Ƚ���� �̵� Ƚ���� �ʱ�ȭ
    int totalComparisons = 0;
    int totalMoves = 0;

    // 20ȸ �ݺ�
    for (i = 0; i < 20; i++) {
        // �迭 �ʱ�ȭ
        for (int j = 0; j < n; j++) {
            list[j] = rand() % 100;
        }
        if (i == 19) {
            printf("original list: ");
            print_array(list, n);
        }
        // ���� ����
        comparisons = 0;
        moves = 0;
        merge_sort(list, 0, n - 1, i);

        // �� �ݺ������� �� Ƚ���� �̵� Ƚ���� ����
        totalComparisons += comparisons;
        totalMoves += moves;
    }
    printf("Merge Sort: ");
    print_array(sorted, n);
    // ��հ� ��� �� ���
    int avgComparisons = totalComparisons / 20;
    int avgMoves = totalMoves / 20;

    printf("Average Comparisons: %d\n", avgComparisons);
    printf("Average Moves: %d\n", avgMoves);

    return 0;
}