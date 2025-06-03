#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
int find_halfnum_h(int N) {
	int halfnum_h; 
	if (N % 2 == 0) { halfnum_h = N / 2; } else { halfnum_h = N / 2 + 1; }
	return halfnum_h - 1;
}

int find_halfnum_l(int M) {
	int halfnum_l;
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

int** less_arr_mem_alloc(int** less_arr, int N, int M) {
	int hcount = 0;
	while (hcount < N) {
		less_arr[hcount] = (int*)malloc(sizeof(int*));
		hcount++;
	}
	return less_arr;
}

int** rand_arr(int** pointer_arr, int N , int M) {
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

int** find_less(int** pointer_arr, int** less_arr, int* less_arr_length, int N, int M, int A) {
	int hcount = 0, lcount = 0, lesscount=0, halfnum_h, halfnum_l;
	halfnum_h = find_halfnum_h(N);
	halfnum_l = find_halfnum_l(M);
	pointer_arr = rand_arr(pointer_arr, N, M);
	less_arr = less_arr_mem_alloc(less_arr, N, M);
	while (hcount < N) {
		while (lcount < M) {
			if (N % 2 == 0 && M % 2 == 0) {
				if (((hcount <= halfnum_h) && (lcount <= halfnum_l) || (hcount > halfnum_h) && (lcount > halfnum_l)) && pointer_arr[hcount][lcount] < A) {
					less_arr[lesscount] = &pointer_arr[hcount][lcount];
					lesscount++;
				}
			}
			else if (N % 2 != 0 && M % 2 == 0) {
				if (((hcount <= halfnum_h) && (lcount <= halfnum_l) || (hcount >= halfnum_h) && (lcount >= halfnum_l)) && pointer_arr[hcount][lcount] < A) {
					less_arr[lesscount] = &pointer_arr[hcount][lcount];
					lesscount++;
				}
			}
			else if (N % 2 == 0 && M % 2 != 0) {
				if (((hcount <= halfnum_h) && (lcount <= halfnum_l) || (hcount > halfnum_h) && (lcount >= halfnum_l)) && pointer_arr[hcount][lcount] < A) {
					less_arr[lesscount] = &pointer_arr[hcount][lcount];
					lesscount++;
				}
			}
			else if (N % 2 != 0 && M % 2 != 0) {
				if (((hcount <= halfnum_h) && (lcount <= halfnum_l) || (hcount >= halfnum_h) && (lcount >= halfnum_l)) && pointer_arr[hcount][lcount] < A) {
					less_arr[lesscount] = &pointer_arr[hcount][lcount];
					lesscount++;
				}
			}
			lcount++;
		}
		lcount = 0;
		hcount++;
	}
	*less_arr_length = lesscount;
	return less_arr;
}

void print(int** pointer_arr, int **less_arr, int* less_arr_length, int N, int M, int A) {
	int hcount = 0, lcount = 0, linecount = 0, lesscount = 0, halfnum_h = 0, halfnum_l = 0, nflag = 0, matchframeflag=0;
	less_arr = find_less(pointer_arr, less_arr, less_arr_length, N, M, A);
	halfnum_h = find_halfnum_h(N);
	halfnum_l = find_halfnum_l(M);
	while (hcount < N) {
		printf("\n");
		if (M % 2 == 0 && nflag == 0) { printf("       "); }
		if (M % 2 != 0 && nflag == 0) { printf(" "); }
		if (nflag == 0) { while (linecount < halfnum_l) { printf("            "); linecount++; } }
		if (nflag == 0) { printf("  |  "); printf("\n");}
		nflag = 0;
		linecount = 0;
		while (lcount < M) {
			if (less_arr[lesscount] == &pointer_arr[hcount][lcount]) { matchframeflag = 1; lesscount++; }
			if (N % 2 == 0) {
				if (M % 2 == 0) {
					if (lcount == halfnum_l && hcount == halfnum_h) {
						if (matchframeflag) { printf("|%5d|  |  ", pointer_arr[hcount][lcount]); }
						else { printf(" %5d   |  ", pointer_arr[hcount][lcount]); }
					}
					else if (lcount == halfnum_l && hcount != halfnum_h) { 
						if (matchframeflag) { printf("|%5d|  |  ", pointer_arr[hcount][lcount]); } 
						else { printf(" %5d   |  ", pointer_arr[hcount][lcount]); }
					}
					else if (lcount != halfnum_l && hcount == halfnum_h) { 
						if (lcount == M - 1) {
							if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
							else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
							printf("\n");
							printf("-------");
							while (linecount < halfnum_l) {
								printf("------------");
								linecount++;
							}
							printf("--|--");
							while (linecount < halfnum_l * 2 + 1) {
								printf("------------");
								linecount++;
							}
							linecount = 0;
							nflag = 1;
						}
						else { 
							if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
							else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
						}
					}
					else { 
						if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
						else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
					}
				}
				else {
					if (lcount == halfnum_l && hcount == halfnum_h) {
						while (linecount < halfnum_l) {
							linecount++;
						}
						linecount = 0;
						printf(" %5d      ", pointer_arr[hcount][lcount]);
					}
					else if (lcount == halfnum_l && hcount != halfnum_h) {
						if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
						else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
					}
					else if (lcount != halfnum_l && hcount == halfnum_h) {
						if (lcount == M - 1) {
							if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
							else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
							printf("\n");
							printf("-");
							while (linecount < halfnum_l) {
								printf("------------");
								linecount++;
							}
							printf("--|--");
							while (linecount < halfnum_l * 2 ) {
								printf("------------");
								linecount++;
							}
							printf("------");
							linecount = 0;
							nflag = 1;
						}
						else { 
							if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
							else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
						}
					}
					else { 
						if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
						else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
					}
				}
			}
			else {
				if (M % 2 == 0) {
					if (lcount == halfnum_l && hcount == halfnum_h) {
						if (matchframeflag) { printf("|%5d|--|--", pointer_arr[hcount][lcount]); }
						else { printf(" %5d --|--", pointer_arr[hcount][lcount]); }
					}
					else if (lcount == halfnum_l && hcount != halfnum_h) { 
						if (matchframeflag) { printf("|%5d|  |  ", pointer_arr[hcount][lcount]); }
						else { printf("%5d    |  ", pointer_arr[hcount][lcount]); }
					}
					else if (lcount != halfnum_l && hcount == halfnum_h) { 
						if (matchframeflag) { printf("|%5d|-----", pointer_arr[hcount][lcount]); }
						else { printf(" %5d -----", pointer_arr[hcount][lcount]); }
					}
					else { 
						if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
						else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
					}
				}
				else {
					if (lcount != halfnum_l && hcount == halfnum_h || lcount == halfnum_l && hcount == halfnum_h) { 
						if (matchframeflag) { printf("|%5d|-----", pointer_arr[hcount][lcount]); }
						else { printf(" %5d -----", pointer_arr[hcount][lcount]); }
					}
					else if (lcount == halfnum_l && hcount != halfnum_h) { 
						if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
						else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
					}
					else { 
						if (matchframeflag) { printf("|%5d|     ", pointer_arr[hcount][lcount]); }
						else { printf(" %5d      ", pointer_arr[hcount][lcount]); }
					}
				}
			}
			matchframeflag = 0;
			lcount++;
		}
		lcount = 0;
		hcount++;
	}
	hcount = 0, lcount = 0, lesscount = 0, linecount = 0;
	printf("\n\n");
	while (linecount < M * 12) { printf("="); linecount++; }
	printf("\n");
	printf("List of elements less than %d: \n\n", A);
	while (lesscount < *less_arr_length) {
		if (lcount < M) {
			printf("%5d      ", less_arr[lesscount][0]);
			lcount++;
		}
		else {printf("\n\n"); lcount = 0;}
		lesscount++;
	}
	printf("\n\n");
}

void clean_mem_pointer_subarr(int** pointer_arr, int N) {
	int hcount = 0;
	while (hcount < N) { free(pointer_arr[hcount]); hcount++; }
}

void clean_mem_less_subarr(int* less_arr, int* less_arr_length) {
	int hcount = 0;
	while (hcount < *less_arr_length) { free(less_arr[hcount]); hcount++; }
	
}

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int** pointer_arr = NULL, **less_arr = NULL, *less_arr_length = NULL, M = 0, N = 0, A=0, line = 0;
	while (1) {
		printf("Enter N_M_number: ");
		scanf_s("%d %d %d", &N, &M, &A);
		printf("\n");
		while (line < M * 12) { printf("="); line++; }
		line = 0;
		printf("\nArray:");
		printf("\n");
		pointer_arr = (int**)malloc(N * sizeof(int*));
		if (pointer_arr == NULL) { perror("Ошибка выделения памяти"); return 1; }
		less_arr = (int**)malloc(N * M * sizeof(int*));
		if (less_arr == NULL) { perror("Ошибка выделения памяти"); return 1; }
		less_arr_length = (int*)malloc(sizeof(int*));
		if (less_arr_length == NULL) { perror("Ошибка выделения памяти"); return 1; }
		print(pointer_arr, less_arr, less_arr_length, N, M, A);
		free(less_arr);
		free(less_arr_length);
		clean_mem_pointer_subarr(pointer_arr, N);
		free(pointer_arr);
		while (line < M * 12) { printf("V"); line++; }
		line = 0;
		printf("\n\n");
	}
	return 0;
}
