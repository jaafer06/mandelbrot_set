#pragma once
#include <CL/cl.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

namespace utils {
	namespace openCL {
        struct CLInfo {
            cl::Device device;
            cl::Context contex;
            cl::Program program;
        };
        cl::Device getDefaultDevice() {
            std::vector<cl::Platform> platforms;
            cl::Platform::get(&platforms);
            if (platforms.empty()) {
                std::cerr << "No platforms found!" << std::endl;
                exit(1);
            }
            auto platform = platforms.front();
            std::vector<cl::Device> devices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

            if (devices.empty()) {
                std::cerr << "No devices found!" << std::endl;
                exit(1);
            }

            size_t valueSize;
            cl::Device device = devices.front();
            
            clGetDeviceInfo(device(), CL_DEVICE_NAME, 0, NULL, &valueSize);
            char* value = new char[valueSize];
            clGetDeviceInfo(device(), CL_DEVICE_NAME, valueSize, value, NULL);
            std::cout << "selected device: " << value << std::endl;
            delete[] value;
            return device;
        }

        std::pair<cl::Program,cl::Context> readKernelFile(std::string&& file, cl::Device& device) {
            std::string src;
            std::ifstream fileStream(file, std::ios::in);
            if (fileStream.is_open()) {
                std::stringstream sstr;
                sstr << fileStream.rdbuf();
                src = sstr.str();
                fileStream.close();
            } else {
                throw ("could not open file " + file);
            }

            cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));
            cl::Context context = cl::Context(device);
            auto program = cl::Program(context, sources);

            auto err = program.build();
            if (err != CL_BUILD_SUCCESS) {
                std::cerr << "Error!\nBuild Status: " << program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(device)
                    << "\nBuild Log:\t " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
                throw "kernel compiler error";
            }
            return {program, context};
        }
	}
}
