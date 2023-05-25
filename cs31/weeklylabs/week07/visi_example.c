/*
 * An example sequential animatation a 2D grid computation using
 * the C pthreads interface of the ParaVis library.
 * (this example uses some wrapper functions around the ParaVis
 * visi library interface in:  /usr/local/include/qtvis/pthreadGridVisi.h
 *
 * To run:
 *   ./a.out 100 100 80    # run with rows cols dimensions for num_iteratons
 *
 * The program is structured like the following to use ParaVis
 * Need to define:
 * (0) a struct containing all program specific data
 *     including a color3 * for the visi buffer to color
 *
 * The main control flow for using visi library:
 * (1) initialize all application-specific data
 * (2) call init_pthread_animation and get visi_handle
 * (3) call get_animation_buffer to get the animation buffer
 * (4) call connect_animation passing it: 
 *     (1) initialized appl_data struct 
 *     (2) a function that performs the main application computation
 *         (prototype must be: void <func_name>(struct appl_data *data)):
 *         loop: 
 *               do next computation step
 *               update color3 buf 
 *               call draw_ready
 * (5) call run_animation to start animation
 * (6) exit and clean-up
 *
 * (newhall, 2019)
 */
#include <pthreadGridVisi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define SLEEPYTIME   30000

/* application-specific struct definition */
struct appl_data {
   int *grid;  
   int iters;  
   int curr_iter;
   int rows;
   int cols;
   /* fields for using the visi library: */
   visi_handle handle;
   color3 *image_buff;
};

static char visi_name[] = "Visualize!";

void update_grid(struct appl_data *data);
int init_state(struct appl_data *data, int r, int c, int iters);

// main application function prototype must match this:
void do_something(struct appl_data *data);

/*** 
 * Do not modify this function: wrapper function for seqential 
 * animation using visi library functions ***/
int connect_animation(void (*applfunc)(struct appl_data *data), 
    struct appl_data* data);

/**********************************************************/
int main(int argc, char *argv[]) {

  int cols, rows, iters;
  struct appl_data data;

  /* (1) initalize application-specific state */
  //     (a) parse command line arguments
  if ((argc < 3) || (argc > 4)) {
    printf("usage: ./visi_example [rows] [cols] [num_iters]\n");
    exit(1);
  }
  rows = atoi(argv[1]);
  cols = atoi(argv[2]);
  iters = atoi(argv[3]); 

  //    (b) create and initialize program data
  if(init_state(&data, rows, cols, iters) != 0) {
    printf("ERROR init world\n");
    exit(1);
  }
  printf("rows (height) = %d, cols (width) = %d iters %d\n",
      rows, cols, iters);

  // (2) call init_pthread_animation and get visi_handle
  data.handle = init_pthread_animation(1, rows, cols, visi_name);
  if(data.handle == NULL) {
    printf("ERROR init_pthread_animation\n");
    exit(1);
  }

  // (3) get the animation buffer
  data.image_buff = get_animation_buffer(data.handle);
  if(data.image_buff == NULL) {
       printf("ERROR get_animation_buffer returned NULL\n");
       exit(1);
  }

  // (4) connect animation to main application loop function:
  //     your main application loop function's prototype must match:
  //         void <func_name>(struct appl_data *data);
  connect_animation(do_something, &data);

  // (5) start animation
  run_animation(data.handle, iters);

  // (6) clean-up before exit
  free(data.grid);
}
/**********************************************************/
/* the application main loop function:
 *  updates program state and notifies visi library when
 *  it is ready for it to draw what it has updated
 *     args: pointer to a struct appl_data 
 */
void do_something(struct appl_data *data) {

  int iters, i, j, index, c, r;

  /*  application specific state initalization:  */
  iters = data->iters;
  c = data->cols;
  r = data->rows;
  // init the grid
  for(i=0; i < r; i++) {
    for(j=0; j < c; j++) {
      index = i*c + j;
      data->grid[index] = j;
    }
  }

  if(iters == 0 ) {
    while(1) { /* run forever */
       update_grid(data);
       draw_ready(data->handle);
       usleep(SLEEPYTIME);   // otherwise animation too fast
    }
  } else {
    for(i=0; i < iters; i++ ) {  /* run some number of iters */
       update_grid(data);
       draw_ready(data->handle);
       usleep(SLEEPYTIME);
    }
  }
}
/**********************************************************/
/*
 * initialize application state
 *  data: appl_data struct to initialize
 *  r: number of rows
 *  c: number of cols
 *  i: number of iters
 *  returns: 0 on success 1 on error
 */
int init_state(struct appl_data *data, int r, int c, int iters) {

  data->iters = iters;
  data->curr_iter = 0;
  data->rows = r;
  data->cols = c;
  data->grid = (int *)malloc(sizeof(int)*r*c);
  if(!data->grid) {
    printf("ERROR malloc\n");
    return 1;
  }
  return 0;
}
/**********************************************************/
/*
 * performs one step of the application
 *   data:  the application data
 */
void update_grid(struct appl_data *data) {

  int i, j, r, c, index, buff_i, iter;
  color3 *buff;

  iter = data->curr_iter;   // just for readability
  buff = data->image_buff;
  r = data->rows;
  c = data->cols;

  for(i=0; i < r; i++) {
    for(j=0; j < c; j++) {
      index = i*c + j;
      // translate row index to y-coordinate value
      buff_i = (r - (i+1))*c + j;
      // update animation buffer
      buff[buff_i].r = (data->grid[index]) % 256;
      buff[buff_i].g = (data->grid[index] + j) % 256;
      buff[buff_i].b = 200;
      // change grid for next round
      data->grid[index] = (data->grid[index] + 10) % 256;
    }
  }
  data->curr_iter = iter + 1;
}

/******************************************************/
/* START: DO NOT MODIFY THIS CODE */
/* sequential wrapper functions around visi library functions */

void (*mainloop)(struct appl_data *data);

void* seq_do_something(void * args){
  mainloop((struct appl_data *)args);
  return 0;
}

int connect_animation(void (*applfunc)(struct appl_data *data),
    struct appl_data* data) 
{
  pthread_t pid;

  mainloop = applfunc; 
  if( pthread_create(&pid, NULL, seq_do_something, (void *)data) ) {
    printf("pthread_created failed\n");
    return 1;
  }
  return 0;
}

/* END: DO NOT MODIFY THIS CODE */
/******************************************************/
