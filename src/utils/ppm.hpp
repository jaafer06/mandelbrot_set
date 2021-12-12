#pragma once
#include <string>
#include <fstream>

namespace utils {
	namespace ppm {
		void saveImage(std::string&& file, unsigned int width, unsigned int height) {
			std::fstream fileStream(file, std::ios::out);
			if (!fileStream.is_open()) {
				std::cout << "can t open file " << file << std::endl;
				throw "can t open file " + file ;
			}
			fileStream << "P3\n" << width << ' ' << height << "\n255\n";

			for (int j = height - 1; j >= 0; --j) {
				for (int i = 0; i < width; ++i) {

					int ir = 255;
					int ig = 0;
					int ib = 0;

					fileStream << ir << ' ' << ig << ' ' << ib << '\n';
				}
			}
			fileStream.close();
		}
	}
}