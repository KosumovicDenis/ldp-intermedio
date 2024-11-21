#ifndef LIDARDRIVER_INCLUDE_LIDARDRIVER_H_
#define LIDARDRIVER_INCLUDE_LIDARDRIVER_H_

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <vector>
#include "Buffer.h"

class LidarDriver {
    static constexpr int BUFFER_DIM = 10;
    static constexpr uint16_t POV = 180;

    uint8_t index;
    uint8_t start_index;
    std::vector<Buffer> scan;

    void new_scan(const std::vector<double>& buff);
    std::vector<double> get_scan();
    void clear_buffer();
    double get_distace(double degree);

public:
    LidarDriver(int degree = 1);
};

std::ostream operator<<(std::ostream& os, const LidarDriver& l);

#endif // LIDARDRIVER_INCLUDE_LIDARDRIVER_H_
