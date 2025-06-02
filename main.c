#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
int find_halfnum_h( int M, int N) {
	int hcount = 0, lcount = 0, halfnum_h; 
	if (N % 2 == 0) { halfnum_h = N / 2; } else { halfnum_h = N / 2 + 1; }
	return halfnum_h - 1 ;
}

int find_halfnum_l(int M, int N) {
	int hcount = 0, lcount = 0, halfnum_l;
	if (M % 2 == 0) { halfnum_l = M / 2; } else { halfnum_l = M / 2 + 1; }
	return halfnum_l - 1;
}

int** pointer_arr_mem_alloc(int** pointer_arr, int N, int M) {
	int hcount = 0;
	while (hcount < N) {
		pointer_arr[hcount] = (int*)malloc(M * sizeof(int));
		hcount++;
	}
	return pointer_arr;
}

int** rand_arr(int** pointer_arr, int M , int N) {
	pointer_arr = pointer_arr_mem_alloc(pointer_arr, N, M);
	int hcount = 0, lcount = 0;
	while (hcount < N) {
		while (lcount < M) {
			pointer_arr[hcount][lcount] = rand();
			lcount++;
		}
		lcount = 0;
		hcount++;
	}
	return pointer_arr;
}

int** find_less(int** pointer_arr, int** less_arr, int* less_arr_length, int M, int N, int A) {
	int hcount = 0, lcount = 0, lesscount=0;
	pointer_arr = rand_arr(pointer_arr, M, N);
	while (hcount < N) {
		while (lcount < M) {
			if (hcount < find_halfnum_h(M, N) && lcount < find_halfnum_l(M, N) && pointer_arr[hcount][lcount] < A) { 
				less_arr[lesscount] = &pointer_arr[hcount][lcount];
				lesscount++;
			}
			if (hcount > find_halfnum_h(M, N) && lcount > find_halfnum_l(M, N) && pointer_arr[hcount][lcount] < A) {
				less_arr[lesscount] = &pointer_arr[hcount][lcount];
				lesscount++;
			}
			lcount++;
		}
		lcount = 0;
		hcount++;
	}
	less_arr_length = &lesscount;
	return less_arr;
}

int less_on_pointer_arr_match(int** less_arr, int element, int *less_arr_length, int N, int M) {
	int lesscount = 0;
	while (lesscount <= *less_arr_length) {
		if (less_arr[lesscount] == &element) { return 1; }
		else { return 0; }
	}
}

void print(int** pointer_arr, int **less_arr, int less_arr_length, int M, int N, int A) {
	int hcount = 0, lcount = 0, linecount = 0, lesscount = 0, halfnum_h = 0, halfnum_l = 0, nflag = 0, matchframeflag=0;
	less_arr = find_less(pointer_arr, less_arr, less_arr_length, M, N, A);
	halfnum_h = find_halfnum_h(M, N);
	halfnum_l = find_halfnum_l(M, N);
	while (hcount < N) {
		if (nflag == 1) { printf(""); }
		else { printf("\n"); }
		nflag = 0;
		if (M % 2 == 0) { printf("     "); }
		else { printf(""); }
		while (linecount < halfnum_l) { printf("          "); linecount++; }
		printf("  |  ");
		printf("\n"); 
		linecount = 0;
		while (lcount < M) {
			if (less_on_pointer_arr_match(less_arr, pointer_arr[hcount][lcount], less_arr_length, N, M)) { matchframeflag = 1; }
			else { matchframeflag = 0; }
			if (N % 2 == 0) {
				if (M % 2 == 0) {
					if (lcount == halfnum_l && hcount == halfnum_h) {
						while (linecount < halfnum_l ) {
							 linecount++;
						}
						linecount = 0;
						if (matchframeflag) { printf("|%5d| |  ", pointer_arr[hcount][lcount]); }
						else { printf("%5d  |  ", pointer_arr[hcount][lcount]); }
					}
					else if (lcount == halfnum_l && hcount != halfnum_h) { 
						if (matchframeflag) { printf("|%5d| |  ", pointer_arr[hcount][lcount]); } 
						else { printf("%5d  |  ", pointer_arr[hcount][lcount]); }
					}
					else if (lcount != halfnum_l && hcount == halfnum_h) { 
						if (lcount == M - 1) {
							if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
							else { printf("%5d     ", pointer_arr[hcount][lcount]); }
							printf("\n");
							printf("-----");
							while (linecount < halfnum_l) {
								printf("----------");
								linecount++;
							}
							printf("--|--");
							while (linecount < halfnum_l * 2 + 1) {
								printf("----------");
								linecount++;
							}
							linecount = 0;
						}
						else { 
							if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
							else { printf("%5d     ", pointer_arr[hcount][lcount]); }
						}
					}
					else { 
						if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
						else { printf("%5d     ", pointer_arr[hcount][lcount]); }
					}
				}
				else {
					if (lcount == halfnum_l && hcount == halfnum_h) {
						while (linecount < halfnum_l) {
							linecount++;
						}
						linecount = 0;
						printf("%5d     ", pointer_arr[hcount][lcount]);
					}
					else if (lcount == halfnum_l && hcount != halfnum_h) {
						if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
						else { printf("%5d     ", pointer_arr[hcount][lcount]); }
					}
					else if (lcount != halfnum_l && hcount == halfnum_h) {
						if (lcount == M - 1) {
							if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
							else { printf("%5d     ", pointer_arr[hcount][lcount]); }
							printf("\n");
							while (linecount < halfnum_l) {
								printf("----------");
								linecount++;
							}
							printf("--|--");
							while (linecount < halfnum_l * 2 ) {
								printf("----------");
								linecount++;
							}
							printf("-----");
							linecount = 0;
							nflag = 1;
						}
						else { 
							if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
							else { printf("%5d     ", pointer_arr[hcount][lcount]); }
						}
					}
					else { 
						if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
						else { printf("%5d     ", pointer_arr[hcount][lcount]); }
					}
				}
			}
			else {
				if (M % 2 == 0) {
					if (lcount == halfnum_l && hcount == halfnum_h) {
						if (matchframeflag) { printf("|%5d|-|--", pointer_arr[hcount][lcount]); }
						else { printf("%5d--|--", pointer_arr[hcount][lcount]); }
					}
					else if (lcount == halfnum_l && hcount != halfnum_h) { 
						if (matchframeflag) { printf("|%5d| |  ", pointer_arr[hcount][lcount]); }
						else { printf("%5d  |  ", pointer_arr[hcount][lcount]); }
					}
					else if (lcount != halfnum_l && hcount == halfnum_h) { 
						if (matchframeflag) { printf("|%5d|----", pointer_arr[hcount][lcount]); }
						else { printf("%5d-----", pointer_arr[hcount][lcount]); }
					}
					else { 
						if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
						else { printf("%5d     ", pointer_arr[hcount][lcount]); }
					}
				}
				else {
					if (lcount != halfnum_l && hcount == halfnum_h || lcount == halfnum_l && hcount == halfnum_h) { 
						if (matchframeflag) { printf("|%5d|----", pointer_arr[hcount][lcount]); }
						else { printf("%5d-----", pointer_arr[hcount][lcount]); }
					}
					else if (lcount == halfnum_l && hcount != halfnum_h) { 
						if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
						else { printf("%5d     ", pointer_arr[hcount][lcount]); }
					}
					else { 
						if (matchframeflag) { printf("|%5d|    ", pointer_arr[hcount][lcount]); }
						else { printf("%5d     ", pointer_arr[hcount][lcount]); }
					}
				}
			}
			lcount++;
		}
		lcount = 0;
		hcount++;
	}
	hcount = 0, lcount = 0, linecount = 0;
	printf("\n");
	while (linecount < 20) { printf("="); linecount++; }
	printf("\n");
	printf("List of elements less than %d: \n", A);
	while (lesscount < less_arr_length) {
		printf("%5d\n", **less_arr[lesscount]);
		lesscount++;
	}
}

void clean_mem_pointer_subarr(int** pointer_arr, int N) {
	int hcount = 0;
	while (hcount < N) { free(pointer_arr[hcount]); hcount++; }
}
int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int** pointer_arr, **less_arr, *less_arr_length, M = 0, N = 0, A=0, line = 0;
	while (1) {
		scanf_s("%d %d %d", &N, &M, &A);
		while (line < 20) { printf("="); line++; }
		line = 0;
		pointer_arr = (int**)malloc(N * sizeof(int*));
		if (pointer_arr == NULL) { perror("Ошибка выделения памяти"); return 1; }
		less_arr = (int*)malloc(((N * M) / 2 + 1) * sizeof(int*));
		print(pointer_arr, *less_arr_length, less_arr, M, N, A);
		clean_mem_pointer_subarr(pointer_arr, N);
		free(pointer_arr);
		free(less_arr);
		while (line < 20) { printf("V"); line++; }
		printf("\n");
	}
	return 0;
}
