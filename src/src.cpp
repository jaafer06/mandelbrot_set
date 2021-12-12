#include <CL/cl.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <iostream>
#include <string>
#include "utils/openCL.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "utils/stb_image_write.h"

void mandelBrotSet(utils::openCL::CLInfo& info, unsigned char* data, unsigned int width, unsigned int height);

void savePNG(std::string&& fileName, unsigned char* data, unsigned int width, unsigned int height, unsigned int channels=3) {
    stbi_write_png(fileName.c_str(), width, height, channels, data, width * channels);
}

int main() {
    auto device = utils::openCL::getDefaultDevice();
    auto [program, context] = utils::openCL::readKernelFile("../src/kernels/array_addition.cl", device);
    utils::openCL::CLInfo clInfo{ device, context, program };
    constexpr int width = 500;
    constexpr int height = 500;
    constexpr int channels = 3;
    std::vector<unsigned char> data(width*height*channels);
    //uint8_t data[width * height * channels] = { 100 };
    //for (int i = 0; i < width * height * channels; i+=channels) {
    //    data[i+1] = 255;
    //}
    //stbi_write_png("testpng_4.png", width, height, channels, data, width * channels);
    utils::openCL::CLInfo info{device, context, program};
    mandelBrotSet(info, data.data(), width, height);
    savePNG("mandel_brot_set.png", data.data(), width, height);
    //std::cin.get();
    return 0;
}


void mandelBrotSet(utils::openCL::CLInfo& info, unsigned char* data, unsigned int width, unsigned int height) {
    auto [device, context, program] = info;
    cl::Buffer dataBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, width * height * 3 * sizeof(unsigned char), data);

    cl::Kernel kernel(program, "mandelBrotSet");
    kernel.setArg(0, dataBuffer);
    //kernel.setArg(1, width);
    //kernel.setArg(2, height);

    cl::CommandQueue queue(context, device);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(width, height), cl::NDRange(1, 1));
    queue.enqueueReadBuffer(dataBuffer, CL_TRUE, 0, width * height * 3 * sizeof(unsigned char), data);
}
