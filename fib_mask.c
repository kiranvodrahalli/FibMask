/*-------------------------------------------------------------------*/
/* fib_mask.c                                                        */
/* Author: Kiran Vodrahalli                                          */
/* Description: fib_mask generates MEMO_SIZE Fibonacci numbers,      */
/*              and prints only the position of a certain digit.     */
/*              This digit is selected by the user. Also, it         */
/*              prints the number of times the digit occurs in       */
/*              each Fibonacci number, and gives the maximum         */
/*              number of times it occurred in any Fibonacci number. */
/*-------------------------------------------------------------------*/

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>

enum{ARRAY_SIZE_BIGINT = 50, MEMO_SIZE = 480, PRINT_SIZE = MEMO_SIZE};

struct BigInt{
  char first[ARRAY_SIZE_BIGINT];
  char last[ARRAY_SIZE_BIGINT];
};

struct BigInt addBigInt(struct BigInt a, struct BigInt b){

  int i = 0;
  int current_sum = 0;
  char carry = 0;
  struct BigInt new;

  for(;i<ARRAY_SIZE_BIGINT;i++){
    current_sum = (int)(carry + a.first[i] + b.first[i]);
    new.first[i] = current_sum%10;
    carry = current_sum/10; 
  }
  i = 0;
  for(;i<ARRAY_SIZE_BIGINT;i++){
    current_sum = (int)(carry + a.last[i] + b.last[i]);
    new.last[i] = current_sum%10;
    carry = current_sum/10;
  }
  assert(carry != 1);
  return new;
}

int main(int argc, char * argv[]){

  struct BigInt i1;
  struct BigInt i2;
  int i = 1;
  int j = ARRAY_SIZE_BIGINT -1;  
  char *val;
  int linecount = 0;
  int max_linecount = 0;
  char input;
  int mask = 0;
  assert(argc > 1);
  input = *argv[1];
  mask = (int)input - 48; /*FIX TO MAKE MORE GENERAL*/
  // printf("Mask which integer? ");
  //scanf("%d", &mask);
  i1.first[0] = 1;
  for(;i<ARRAY_SIZE_BIGINT;i++){
    i1.first[i]=0;
  }
  for(i =0;i<ARRAY_SIZE_BIGINT;i++){
    i1.last[i] = 0;
  }
  i2 = i1;
  struct BigInt * array = (struct BigInt *)calloc(MEMO_SIZE, sizeof(struct BigInt)); 
  array[0] = i1;
  array[1] = i2;
  array[2] = addBigInt(array[0], array[1]);
  i = 2;
  for(;i<MEMO_SIZE-1;i++){
    array[i+1] = addBigInt(array[i], array[i-1]);
  }
  for(i =0;i<PRINT_SIZE;i++){
    if(i<10){
      printf("Fib_%d =   ", i);
    }
    else if(i<100 && i>=10){ printf("Fib_%d =  ", i); }
    else{printf("Fib_%d = ", i);}
    val = array[i].last;
    for(;j>=0;j--){
      if(input == 'a'){
	printf("%d", *(val+j));
      }
      else if(*(val+j) == mask){
	printf("%d", *(val+j));
	linecount++;
      }
      else{printf("%c", '_');}
    }
    j = ARRAY_SIZE_BIGINT -1;
    val = array[i].first;
    for(;j>=0;j--){
      if(input == 'a'){
	printf("%d", *(val +j));
      }
      else if(*(val+j) == mask){
	printf("%d", *(val+j));
	linecount++;
      }
      else{printf("%c", '_');}
    }
    printf("                   %d\n", linecount);
    if(max_linecount < linecount){max_linecount = linecount;}
    linecount = 0;
    j = ARRAY_SIZE_BIGINT -1;
  } 
  printf("Max number of %ds: %d\n", mask, max_linecount);
  free(array);
  return 0;
}
