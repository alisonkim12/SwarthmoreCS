/* memory test
 *
 * The purpose of this program is to create an array of the first n = ten
 * integers, print them out, and then reverse them and print them again.
 * However, there are a number of memory errors.
 * Use valgrind to detect and fix the errors.
 *
 * Charlie Kazer, Joshua Brody
 * Spring 2020
 */
#include<iostream>

using namespace std;

int main() {

  // (1) create an array of n=ten integers
  int n = 10;
  int *some_nums = NULL;

  // (2) initialize the list to be the first ten positive ints
  for (int i=0; i<n; i++) {
    some_nums[i] = i;
  }

  // (3) print the numbers
  for(int i=0; i<n; i++) {
    cout << some_nums[i] << endl;
  }

  // (4) reverse the numbers
  int temp;
  for(int i=0; i<n/2; i++) {
    //swap i, 10-i-1  (the -1 is so we swap 0<-->9, 1<-->8, etc)
    temp = some_nums[i];
    some_nums[i] = some_nums[n-1-i];
    some_nums[n-1-i] = temp;
  }

  // (4) print the numbers again
  for(int i=0; i<=n; i++) {
    cout << some_nums[i] << endl;
  }

  // (5) are there any other errors?

  return 0;
}
