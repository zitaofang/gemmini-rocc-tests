// See LICENSE for license details.

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "include/systolic.h"
#include "util.h"

#define N (2)

void operands(int c, int * a, int * b, int * d) {
  *d = c % N;
  *b = (c / N) % N;
  *a = c / (N*N);
}

int main() {
  static elem_t ZERO[DIM][DIM];

  for (int it = 0; it < 8; it++) {
    static elem_t A[N][DIM][DIM];
    static elem_t B[N][DIM][DIM];
    static elem_t D[N][DIM][DIM];

    static elem_t A_tp[N][DIM][DIM];

    // We will try out every combination of A, B, D possible
    static elem_t C[N*N*N][DIM][DIM];
    static elem_t gold[N*N*N][DIM][DIM];

    // ...taking into account the preloads or accumulates
    static int preload[N*N*N] = {1};
    for (int i = 1; i < N*N*N; ++i)
        preload[i] = rand() % 2;

    // ...and for the actual preloads, do we just preload zeros?
    static int preload_zeros[N*N*N];
    for (int i = 0; i < N*N*N; ++i)
        preload_zeros[i] = rand() % 2;

    // ...and finally, which results won't produce any output
    static int no_output[N*N*N];
    for (int i = 0; i < N*N*N-1; ++i)
        no_output[i] = !preload[i+1];
    no_output[N*N*N-1] = 0;

    // Print the sequence out
    printf("Preloads: ");
    for (int i = 0; i < N*N*N; ++i)
      printf("%d, ", preload[i]);
    printf("\n");
    printf("Zeros: ");
    for (int i = 0; i < N*N*N; ++i)
      printf("%d, ", preload_zeros[i]);
    printf("\n");
    printf("No outputs: ");
    for (int i = 0; i < N*N*N; ++i)
      printf("%d, ", no_output[i]);
    printf("\n");

    for (size_t n = 0; n < N; ++n) {
      for (size_t i = 0; i < DIM; ++i) {
        for (size_t j = 0; j < DIM; ++j) {
          A[n][i][j] = rand() % 6;
          B[n][i][j] = rand() % 6;
          D[n][i][j] = rand() % 6;
        }
      }
    }

    for (size_t n = 0; n < N; ++n)
      transpose(A[n], A_tp[n]);

    for (size_t g = 0; g < N*N*N; ++g) {
      int a, b, d; 
      operands(g, &a, &b, &d);

      if (!preload[g])
        matmul(A[a], B[b], gold[g-1], gold[g]);
      else if (preload_zeros[g])
        matmul(A[a], B[b], ZERO, gold[g]);
      else
        matmul(A[a], B[b], D[d], gold[g]);
    }

    int A_addr = 0;
    int B_addr = N*DIM;
    int D_addr = 2*N*DIM;
    int C_addr = 3*N*DIM;

    // printf("Moving in\n");
    for (size_t n = 0; n < N; ++n)
      for (size_t i = 0; i < DIM; ++i)
        matmul_mvin(A_tp[n][i], A_addr + n*DIM + i, 0, 0, 0, 0);
    
    for (size_t n = 0; n < N; ++n)
      for (size_t i = 0; i < DIM; ++i)
        matmul_mvin(B[n][i], B_addr + n*DIM + i, 0, 0, 0, 0);

    for (size_t n = 0; n < N; ++n)
      for (size_t i = 0; i < DIM; ++i)
        if (n == N-1 && i == DIM-1) {
          matmul_mvin(D[n][i], D_addr + n*DIM + i, 0, 0, 1, 0);
        } else {
          matmul_mvin(D[n][i], D_addr + n*DIM + i, 0, 0, 0, 0);
        }

    // printf("Setting mode\n");
    matmul_setmode(OUTPUT_STATIONARY, 1, 0);

    // printf("Matmulling\n");
    for (size_t c = 0; c < N*N*N; ++c) {
      int a, b, d;
      operands(c, &a, &b, &d);
      
      uint64_t out_addr = C_addr + c*DIM;
      if (no_output[c])
        out_addr = GARBAGE_ADDR;

      if (!preload[c]) {
        if (c == N*N*N-1) {
          matmul_preload_zeros(out_addr, 0, 0, 1, 0);
        } else {
          matmul_preload_zeros(out_addr, 0, 0, 0, 0);
        }
        matmul_compute_accumulated(A_addr + a*DIM, B_addr + b*DIM);
      } else if (preload_zeros[c]) {
        if (c == N*N*N-1) {
          matmul_preload_zeros(out_addr, 0, 0, 1, 0);
        } else {
          matmul_preload_zeros(out_addr, 0, 0, 0, 0);
        }
        matmul_compute_preloaded(A_addr + a*DIM, B_addr + b*DIM);
      } else {
        if (c == N*N*N-1) {
          matmul_preload(D_addr + d*DIM, out_addr, 0, 0, 1, 0);
        } else {
          matmul_preload(D_addr + d*DIM, out_addr, 0, 0, 0, 0);
        }
        matmul_compute_preloaded(A_addr + a*DIM, B_addr + b*DIM);
      }
    }

    // printf("Moving out\n");
    for (size_t c = 0; c < N*N*N; ++c)
      for (size_t i = 0; i < DIM; ++i)
        if (!no_output[c])
          if (c == 0 && i == 0) {
            matmul_mvout(C[c][i], C_addr + c*DIM + i, 0, 0, 0, 1);
          } else {
            matmul_mvout(C[c][i], C_addr + c*DIM + i, 0, 0, 0, 0);
          }

    printf("Moved out\n");
    for (int n = 0; n < N*N*N; ++n) {
      if (!no_output[n]) {
        printf("C:\n");
        printMatrix(C[n]);
        printf("Gold:\n");
        printMatrix(gold[n]);
        printf("\n");
      }
    }

    for (int n = 0; n < N*N*N; ++n)
      if (!no_output[n] && !is_equal(C[n], gold[n]))
          exit(1);
  }

  exit(0);
}

