/**
 * This kernel function sums two arrays of integers and returns its result
 * through a third array.
 **/

 __kernel void mandelBrotSet(__global unsigned char* data){
   size_t width = get_global_size(0);
   size_t height = get_global_size(1);
   size_t x = get_global_id(0);
   size_t y = get_global_id(1);
   size_t index = 3*(y*width+x);
   data[index] = 255;
   data[index+1] = 0;
   data[index+2] = 0;
    // c[index] = get_group_id(0);
 }