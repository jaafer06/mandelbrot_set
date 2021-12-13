/**
 * This kernel function sums two arrays of integers and returns its result
 * through a third array.
 **/

 __kernel void mandelBrotSet(__global unsigned char* data){
   size_t width = get_global_size(0);
   size_t height = get_global_size(1);
   size_t i = get_global_id(0);
   size_t j = get_global_id(1);
   size_t index = 3*(j*width+i);
   // data[index] = 255;
   // data[index+1] = 0;
   // data[index+2] = 0;

   unsigned char iteration = 0;
   float absValue = 0;
   float x0 = i*0.0004 - 2;
   float y0 = j*0.0004 - 1;
   float x = 0;
   float y = 0;
   float MAX_VALUE = 4;
   while ((absValue < 4) && (iteration < 255)) {
      float tmp = x * x  - y * y  + x0;
      y = 2 * x * y + y0;
      x = tmp;
      absValue = x * x + y * y; 
      ++iteration;
   }
   data[index] = iteration;
   data[index+1] = iteration;
   data[index+2] = iteration;

}