#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int sorted[MAX_SIZE];
int list[MAX_SIZE];
int n;

// 전역 변수로 비교 횟수와 이동 횟수를 저장
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
        comparisons++;  // 비교 수 증가

        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
            moves++;  // 이동 수 증가
        }
        else {
            sorted[k++] = list[j++];
            moves++;  // 이동 수 증가
        }
    }

    if (i > mid) {
        for (l = j; l <= right; l++) {
            sorted[k++] = list[l];
            moves++;  // 이동 수 증가
        }
    }
    else {
        for (l = i; l <= mid; l++) {
            sorted[k++] = list[l];
            moves++;  // 이동 수 증가
        }
    }

    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
        moves++;  // 이동 수 증가
    }
}

void merge_sort(int list[], int left, int right, int iteration) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        merge_sort(list, left, mid, iteration);
        merge_sort(list, mid + 1, right, iteration);

        if (iteration == 19) {
            // 20번째 호출일 때만 출력
            print_array(list, n);
        }

        merge(list, left, mid, right);
    }
}

int main(void) {
    int i;
    n = MAX_SIZE;
    srand(time(NULL));

    // 전체 비교 횟수와 이동 횟수를 초기화
    int totalComparisons = 0;
    int totalMoves = 0;

    // 20회 반복
    for (i = 0; i < 20; i++) {
        // 배열 초기화
        for (int j = 0; j < n; j++) {
            list[j] = rand() % 100;
        }
        if (i == 19) {
            printf("original list: ");
            print_array(list, n);
        }
        // 정렬 수행
        comparisons = 0;
        moves = 0;
        merge_sort(list, 0, n - 1, i);

        // 각 반복에서의 비교 횟수와 이동 횟수를 누적
        totalComparisons += comparisons;
        totalMoves += moves;
    }
    printf("Merge Sort: ");
    print_array(sorted, n);
    // 평균값 계산 및 출력
    int avgComparisons = totalComparisons / 20;
    int avgMoves = totalMoves / 20;

    printf("Average Comparisons: %d\n", avgComparisons);
    printf("Average Moves: %d\n", avgMoves);

    return 0;
}