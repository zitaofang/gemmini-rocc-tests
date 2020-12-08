// See LICENSE for license details.

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifndef BAREMETAL
#include <sys/mman.h>
#endif
#include "util.h"
#include "include/gemmini_testutils.h"
#include "chol_data.h"

#define CHECK_RESULT 1

#define NO_BIAS 1
#define FULL_BIAS_WIDTH 1

#if FULL_BIAS_WIDTH
typedef acc_t ACC_T;
#else
typedef elem_t ACC_T;
#error variable-bitwidth bias not currently supported
#endif

void print_tile(elem_t* in, int tile_dim, int in_dim) {
  for (size_t r = 0; r < tile_dim; r++) {
    printf("row starts at: %p\n", in +r*in_dim);
    for (size_t c = 0; c < tile_dim; c++) {
      printf("%d.%d ", (int)(*(in +r*in_dim + c)), ((int)((*(in +r*in_dim + c))*100))%100);
    }
    printf("\n");
  }
}

void full_matmul(elem_t A[MAT_DIM][MAT_DIM], elem_t B[MAT_DIM][MAT_DIM], ACC_T D[MAT_DIM][MAT_DIM], full_t C_full[MAT_DIM][MAT_DIM]) {
  for (size_t r = 0; r < MAT_DIM; r++)
    for (size_t c = 0; c < MAT_DIM; c++) {
      C_full[r][c] = D[r][c];
      for (size_t k = 0; k < MAT_DIM; k++)
        C_full[r][c] += A[r][k]*B[k][c];
    }
}

void full_transposed_matmul(int I_block, int J_block, int K_block, int A_stride, int B_stride, int C_stride, elem_t* A, elem_t* B, elem_t* C, bool sub) {

	bool no_B_tiling = false;
	if(I_block > 1 && J_block == 1 && K_block == 1)
		no_B_tiling = true;

	if(no_B_tiling)
		tiled_matmul_auto_notileB(block_dim*I_block, block_dim, block_dim,
				A, B, sub ? C : NULL, C,
				A_stride, B_stride, C_stride, C_stride,
				MVIN_SCALE_IDENTITY, sub ? (-1) : MVIN_SCALE_IDENTITY, MVIN_SCALE_IDENTITY,
				NO_ACTIVATION, ACC_SCALE_IDENTITY, 
				0, false, 
				false, true, 
				WS);	
	else
		tiled_matmul_auto(block_dim*I_block, block_dim*J_block, block_dim*K_block,
				A, B, sub ? C : NULL, C,
				A_stride, B_stride, C_stride, C_stride,
				MVIN_SCALE_IDENTITY, sub ? (-1) : MVIN_SCALE_IDENTITY, MVIN_SCALE_IDENTITY,
				NO_ACTIVATION, ACC_SCALE_IDENTITY, 
				0, false, 
				false, true, 
				WS);	
}

void full_printMatrix(elem_t m[MAT_DIM][MAT_DIM]) {
  for (size_t i = 0; i < MAT_DIM; ++i) {
    for (size_t j = 0; j < MAT_DIM; ++j)
		 printf("%d.%d ", (int)m[i][j], ((int)(m[i][j]*100))%100);
    printf("\n");
  }
}

int full_is_equal(elem_t x[MAT_DIM][MAT_DIM], elem_t y[MAT_DIM][MAT_DIM]) {
  for (size_t i = 0; i < MAT_DIM; ++i)
    for (size_t j = 0; j < MAT_DIM; ++j)
      if (((int)(x[i][j]*50)) != ((int)(y[i][j]*50))){
			printf("i: %d, j: %d, value: %d.%d, %d.%d \n", i, j, (int)x[i][j], ((int)(x[i][j]*1000))%1000 , (int)y[i][j], ((int)(y[i][j]*1000))%1000);
         return 0;
		}
  return 1;
}

void full_matshift(full_t full[MAT_DIM][MAT_DIM], elem_t out[MAT_DIM][MAT_DIM], int shift) {
  for (size_t r = 0; r < MAT_DIM; r++)                             
    for (size_t c = 0; c < MAT_DIM; c++) {
      // Bitshift and round element
      full_t shifted = ROUNDING_RIGHT_SHIFT(full[r][c], shift);

      // Saturate and cast element
#ifndef ELEM_T_IS_FLOAT
      full_t elem = shifted > elem_t_max ? elem_t_max : (shifted < elem_t_min ? elem_t_min : shifted);
      out[r][c] = elem;
#else
      out[r][c] = shifted; // TODO should we also saturate when using floats?
#endif
    }
}

void lower_triangle_inverse(elem_t* A, elem_t M[block_dim][block_dim]){
//	for(int i = 0; i < block_dim; i++)
//		for(int j = 0; j < block_dim; j++)
//			M[i][j] = 0;

	for(int i = 0; i < block_dim; i++){
		M[i][i] = 1/(*(A+i*MAT_DIM+i));
		for(int j = i+1; j < block_dim; j++){
			elem_t sum = 0;
			for(int k = i; k < j; k++)
				sum += (*(A+j*MAT_DIM+k))*M[k][i];///(*(A+j*MAT_DIM+j));
			M[j][i] = M[j][i] - sum/(*(A+j*MAT_DIM+j));
		}
	}
}

//store transposed inverse for vector
void lower_triangle_inverse_transpose(elem_t* A, elem_t M[block_dim][block_dim]){
//	for(int i = 0; i < block_dim; i++)
//		for(int j = 0; j < block_dim; j++)
//			M[i][j] = 0;

	for(int i = 0; i < block_dim; i++){
		M[i][i] = 1/(*(A+i*MAT_DIM+i));
		for(int j = i+1; j < block_dim; j++){
			elem_t sum = 0;
			for(int k = i; k < j; k++)
				sum += (*(A+j*MAT_DIM+k))*M[i][k];///(*(A+j*MAT_DIM+j));
			M[i][j] = M[i][j] - sum/(*(A+j*MAT_DIM+j));
		}
	}
}

void full_right_chol(elem_t* L){
	for(int k = 0; k < block_dim; k++){
		//printf("%d %d \n", (int)(L[k][k]*100), (int)((float)(sqrt(L[k][k]))*100));
		*(L+k*MAT_DIM+k) = (float)(sqrt(*(L+k*MAT_DIM+k)));
		for(int i = 0; i < block_dim; i++){
			if(i > k) *(L+i*MAT_DIM+k) = (float)(*(L+i*MAT_DIM+k) / *(L+k*MAT_DIM+k));
			else if(i < k) *(L+i*MAT_DIM+k) = 0;
		}
		for(int j = k+1; j < block_dim; j++)
			for(int i = j; i < block_dim; i++){
				//if(i==block_dim-1 && j==block_dim-1) printf("Lkk: %d, Lik:%d, Ljk: %d, mult: %d \n", (int)(L[i][j]*100), (int)(L[i][k]*100), (int)(L[j][k]*100), (int)(L[i][k]*L[j][k]*100));
				*(L+i*MAT_DIM+j) -= (*(L+i*MAT_DIM+k))*(*(L+j*MAT_DIM+k));
			}
				//printf("%d \n", (int)(L[k][k]));
	}
}
void full_left_chol(elem_t* L){
	for(int j=0; j < block_dim; j++){
		for(int k=0; k < j; k++){
			*(L+j*MAT_DIM+j) -= (*(L+j*MAT_DIM+k))*(*(L+j*MAT_DIM+k));
			for(int i = j+1; i < block_dim; i++)
				*(L+i*MAT_DIM+j) -= (*(L+i*MAT_DIM+k))*(*(L+j*MAT_DIM+k));
		}
		*(L+j*MAT_DIM+j) = (float)(sqrt(*(L+j*MAT_DIM+j)));
		for(int i = j+1; i < block_dim; i++)
			*(L+i*MAT_DIM+j) = (float)((*(L+i*MAT_DIM+j))/(*(L+j*MAT_DIM+j)));
		for(int i = 0; i < j; i++)
			*(L+i*MAT_DIM+j) = 0;
	}
}

void copy_matrix(int block_size, int A_dim, int B_dim, elem_t* A, elem_t* B){
	for(int i = 0; i < block_size; i++)
		for(int j = 0; j < block_size; j++)
			*(B+i*B_dim+j) = *(A+i*A_dim+j);
}


void block_right_chol(elem_t* L){
	for(int k = 0; k < num_block; k++){
		full_right_chol(L+block_dim*(MAT_DIM*k+k));
		elem_t temp[block_dim][block_dim] = {0};
		lower_triangle_inverse(L+(k*MAT_DIM+k)*block_dim, temp);
		for(int i = k+1; i < num_block; i++){	
			elem_t temp_mult[block_dim][block_dim] = {0};
			full_transposed_matmul(1, 1, 1, MAT_DIM, block_dim, block_dim, L+block_dim*(i*MAT_DIM+k), (elem_t*) temp, (elem_t*) temp_mult, false);	
			copy_matrix(block_dim, block_dim, MAT_DIM, (elem_t*) temp_mult, L+block_dim*(i*MAT_DIM+k));
		}
		for(int j = k+1; j < num_block; j++)
			full_transposed_matmul((num_block-j), 1, 1, MAT_DIM, MAT_DIM, MAT_DIM, L+block_dim*(j*MAT_DIM+k), L+block_dim*(j*MAT_DIM+k), L+block_dim*(j*MAT_DIM+j), true);
//			for(int i = j; i < num_block; i++)
//				full_transposed_matmul(block_dim, 1, 1, 1, MAT_DIM, MAT_DIM, MAT_DIM, L+block_dim*(i*MAT_DIM+k), L+block_dim*(j*MAT_DIM+k), L+block_dim*(i*MAT_DIM+j), true);	
	}
}
static elem_t LR_mt[MAT_DIM][MAT_DIM] row_align(1) = {0};	
//static bool thread_lock = false;

void thread_entry(int cid, int nc){
  for (int i = 0; i < nc; i++) {
    if (i == cid) printf("Thread %d/%d starting\n", cid, nc);
    barrier(nc);
  }

 int block_size = block_dim;
 
#if CHECK_RESULT == 1
 for(int i = 0; i < num_block; i++)
	 for(int j = 0; j < num_block; j++)
		 for(int ii = 0; ii < block_size; ii++){
			 for(int jj = 0; jj < block_size; jj++){
				 if(j > i)
					 LR_mt[i*block_size+ii][j*block_size+jj] = 0;
				 else
					 LR_mt[i*block_size+ii][j*block_size+jj] = in_A[i*block_size+ii][j*block_size+jj];
			 }
		 }
#endif
  gemmini_flush(0);
  for (int i = 0; i < nc; i++) {
    if (i == cid) printf("Starting gemmini tiled_matmul\n");
    barrier(nc);
  }

  elem_t* LR_pt = (elem_t *) LR_mt;

  unsigned long start = read_cycles();
  barrier(nc);
  //set up
	
  for(int k = 0; k < num_block-1; k++){
		if(cid == 0 && (k == 0)){
			full_right_chol(LR_pt+block_dim*(MAT_DIM*k+k));
		}
		barrier(nc);
		elem_t temp[block_dim][block_dim] = {0};
		lower_triangle_inverse(LR_pt+(k*MAT_DIM+k)*block_dim, temp);	
		barrier(nc);

		for(int i = k+1; i < num_block; i++){
			if(i%nc == cid){
				bool skip_B = (i != k+1) && (i != k+2);
				full_transposed_matmul(1, 1, 1, MAT_DIM, block_dim, MAT_DIM, LR_pt+block_dim*(i*MAT_DIM+k), skip_B ? NULL : (elem_t*) temp, LR_pt+block_dim*(i*MAT_DIM+k), false);				
			}
		}
		barrier(nc);
		for (int i = 0; i < nc; i++){
			if(i==cid) printf("k: %d, mid: %d\n", k, k+1+(int)((num_block-k)/7));
			barrier(nc);
		}
		for(int j = k+1; j < num_block; j++){
			int left = num_block - k;
			int id0 = j + (int)(left/7); //to be determined
			if((j <= id0 && cid==0)||(j>id0&&cid!=0))
				full_transposed_matmul((num_block-j), 1, 1, MAT_DIM, MAT_DIM, MAT_DIM, LR_pt+block_dim*(j*MAT_DIM+k), LR_pt+block_dim*(j*MAT_DIM+k), LR_pt+block_dim*(j*MAT_DIM+j), true);
		}
		if(cid == 0 && k < num_block - 1)
			full_right_chol(LR_pt+block_dim*(MAT_DIM+1)*(k+1));
		barrier(nc);
  }

  unsigned long end = read_cycles();
  unsigned long total_cycles = end - start;
  for (int i = 0; i < nc; i++) {
	 if (i == cid) printf("Thread %d Cycles taken: %u\n", cid, total_cycles);
    barrier(nc);
  }

#if CHECK_RESULT == 1
  if(cid == 0){
	  if (!full_is_equal(LR_mt, gold_L)) {
			printf("C:\n");
			full_printMatrix(LR_mt);
			printf("thread 0 Block Right Gold:\n");
			full_printMatrix(gold_L);
			printf("\n");
		}
  }
  barrier(nc);
#endif
  /*
  if(cid != 0){
	  if (!full_is_equal(LR_mt, gold_L)) {
			printf("C:\n");
			full_printMatrix(LR_mt);
			printf("thread 0 Block Right Gold:\n");
			full_printMatrix(gold_L);
			printf("\n");
		}
  }
  */
  exit(0);

}


int main() {
#ifndef BAREMETAL
	if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0) {
      perror("mlockall failed");
      exit(1);
    }
#endif

    gemmini_flush(0);

    static elem_t LR[MAT_DIM][MAT_DIM] row_align(1) = {0};
	 static elem_t LL[MAT_DIM][MAT_DIM] row_align(1) = {0};

    static elem_t LR_block[MAT_DIM][MAT_DIM] row_align(1) = {0};
	 static elem_t LL_block[MAT_DIM][MAT_DIM] row_align(1) = {0};

	 unsigned long cpu_start = 0;
	 unsigned long cpu_end = 0;


#if CHECK_RESULT == 1

	 for(int k = 0; k < MAT_DIM; k++)
		 for(int j = k; j < MAT_DIM; j++){
			 LR[j][k] = in_A[j][k];
			 LR_block[j][k] = in_A[j][k];
		 }

	 for(int k = 0; k < MAT_DIM; k++)
		 for(int j = 0; j < MAT_DIM; j++)
			 LR[j][k] = in_A[j][k];
/*
	 printf("Starting naive right CPU chol\n");
    cpu_start = read_cycles();
    full_right_chol(MAT_DIM, (elem_t *) LR);
    cpu_end = read_cycles();
    printf("Cycles taken: %u\n", cpu_end-cpu_start);

	 for(int j = 0; j < MAT_DIM; j++)
		 for(int jj = j; jj < MAT_DIM; jj++)
			 LL[jj][j] = in_A[jj][j];

	 printf("Starting naive left CPU chol\n");
	 cpu_start = read_cycles();
	 full_left_chol(MAT_DIM, (elem_t *) LL);
	 cpu_end = read_cycles();
	 printf("Cycles taken: %u\n", cpu_end-cpu_start);
*/
	 int block_size = MAT_DIM/num_block;

	 for(int i = 0; i < num_block; i++)
		 for(int j = 0; j < num_block; j++)
			 for(int ii = 0; ii < block_size; ii++){
				 for(int jj = 0; jj < block_size; jj++){
					 if(j > i){
						 LR_block[i*block_size+ii][j*block_size+jj] = 0;
						 LL_block[i*block_size+ii][j*block_size+jj] = 0;
					 }
					 else{
						 LR_block[i*block_size+ii][j*block_size+jj] = in_A[i*block_size+ii][j*block_size+jj];
					    LL_block[i*block_size+ii][j*block_size+jj] = in_A[i*block_size+ii][j*block_size+jj];
					 }
				 }
			 }

#endif

	 printf("Starting block right CPU chol\n");
    cpu_start = read_cycles();
    block_right_chol((elem_t *) LR_block);
    cpu_end = read_cycles();
    printf("Cycles taken: %u\n", cpu_end-cpu_start);



#if CHECK_RESULT == 1
/*
	 if (!full_is_equal(LR, gold_L)) {
      printf("C:\n");
      full_printMatrix(LR);
      printf("Right Gold:\n");
      full_printMatrix(gold_L);
      printf("\n");

      exit(1);
    }
*/
	 if (!full_is_equal(LR_block, gold_L)) {
		printf("C:\n");
		full_printMatrix(LR_block);
		printf("Block Right Gold:\n");
		full_printMatrix(gold_L);
		printf("\n");
		exit(1);

	 }

#endif

  exit(0);
}

