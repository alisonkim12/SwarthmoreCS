/*
 * implement a circular queue using an array.  
 * first element added is the first to be replaced (overwritten)
 * when there is no more space in the array. 
 * circular: wraps around: 0, 1, 2, ..., 9, 0, 1, 2, 
 * (newhall, 2013)
 */
#include <stdio.h>

#define N 10

// let's use global variables for the queue and its state
// you MAY ADD MORE GLOBAL VARIABLES if you need them
static int queue[N];
static int queue_next = 0;  // the next place to insert in the queue
static int queue_size = 0;  // the number of items in the queue

void add_queue(int val);
void print_queue(void);

/*****************************************/
int main() {

  int i, val;

  // some circular queue test code
  // add more to help you test for correctness
  for(i=0; i < N-1; i++) {
    add_queue(i);
  }
  print_queue();

  for(i=0; i < N; i++) {
    printf("Enter a value: ");
    scanf("%d", &val);
    add_queue(val);
    print_queue();
  }
  return 0;
}
/*****************************************/
// add the val to the circular queue
// update its state to reflect that
// a new value has been added 
void add_queue(int val) {


}
/*****************************************/
// print out the values in order that they
// were added to the queue: first to last
// print:  bucket_index_value: bucket_value
//
void print_queue(void){

}
