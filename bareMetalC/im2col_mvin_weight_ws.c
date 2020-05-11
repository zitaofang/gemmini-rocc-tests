// See LICENSE for license details.

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BAREMETAL
#include <sys/mman.h>
#endif
#include "include/gemmini.h"

#define input_width 5
#define weight_width 3 //make output width 4x4
#define channel 5 //im2col 27x16
#define im2col_en 1
#define channel_turn (int)(16/(weight_width*weight_width))
#define input_leftover 16-channel_turn*weight_width*weight_width
#define im2col_turn (int)(weight_width*weight_width*channel/16) + 1
#define N 3
#define weight_stride 1

int main() {
#ifndef BAREMETAL
    if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0) {
      perror("mlockall failed");
      exit(1);
    }
#endif

  printf("input width: %d, weight width: %d, channel: %d, channel per unit: %d, leftover input: %d, how many turns: %d \n", input_width, weight_width, channel, channel_turn, input_leftover, im2col_turn);

  printf("Flush Gemmini TLB of stale virtual addresses\n");
  gemmini_flush(0);

  printf("Initialize our input and output matrices in main memory\n");
  elem_t In[N][DIM][DIM];
  elem_t Out[DIM][DIM];

  elem_t Identity[N][DIM][DIM];
  for(size_t n = 0; n < N; n++)
  for (size_t i = 0; i < DIM; i++)
    for (size_t j = 0; j < DIM; j++){
      Identity[n][i][j] = i == j;
      In[n][i][j] = n+ i*DIM + j;
    }

//  printf("Calculate the scratchpad addresses of all our matrices\n");
//  printf("  Note: The scratchpad is \"row-addressed\", where each address contains one matrix row\n");
  size_t In_sp_addr = 0;
//  uint32_t Out_sp_addr = 3*BANK_ROWS;//(1<<31);
  uint32_t Out_sp_addr = 1<<31;
  size_t Identity_sp_addr = BANK_ROWS;

//  printf("Move \"In\" matrix from main memory into Gemmini's scratchpad\n");
	for(size_t n= 0; n < N; n++){
	  gemmini_mvin(In[n], n*DIM + In_sp_addr);
	  gemmini_mvin(Identity[n], n*DIM + Identity_sp_addr);
	}

//  printf("Move \"Identity\" matrix from main memory into Gemmini's scratchpad\n");
  printf("Multiply \"In\" matrix with \"Identity\" matrix with a bias of 0\n");
 
  gemmini_config_ex(WEIGHT_STATIONARY, 0, 0, 0, 0, 
		input_width, weight_width, channel, im2col_en, weight_stride);
 
//	for(size_t n=0; n<No; n++){
	  gemmini_preload(Identity_sp_addr, Out_sp_addr);
  	  gemmini_compute_preloaded(In_sp_addr, GARBAGE_ADDR);
//	}
  printf("Move \"Out\" matrix from Gemmini's scratchpad into main memory\n");

//	for(size_t n=0; n<No; n++){
	  gemmini_mvout(Out, Out_sp_addr);
//	}

//  printf("Fence till Gemmini completes all memory operations\n");
  gemmini_fence();

  printf("Check whether \"In\" and \"Out\" matrices are identical\n");
//  if (!is_equal(In, Out)) {
//    printf("Input and output matrices are different!\n");
//    printf("\"In\" matrix:\n");
//    printMatrix(In);
    printf("\"Out\" matrix:\n");
//  for(size_t n=0; n<No; n++){
    printMatrix(Out);
    printf("\n");
//  }
    exit(1);
//  }

//  printf("Input and output matrices are identical, as expected\n");
//  exit(0);
}

