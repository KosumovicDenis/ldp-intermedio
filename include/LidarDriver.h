#ifndef LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_
#define LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <vector>
#include <iostream>

class LidarDriver {
    static constexpr int BUFFER_DIM = 10;
    static constexpr uint16_t POV = 180;
    const double RESOLUTION;

    int size, first_element_index;
    std::vector<std::vector<double>> scan;
    bool is_valid(double degree) const;
public:
    explicit LidarDriver(double degree = 1);

    void new_scan(const std::vector<double>& buff);
    std::vector<double> get_scan();
    void clear_buffer();
    double get_distance(double degree) const;

    class InvalidDegree{};
    class InvalidScan{};
    friend std::ostream& operator<<(std::ostream& os, const LidarDriver& l);
};


#endif // LDI_INTERMEDIO_INCLUDE_LIDARDRIVER_H_
