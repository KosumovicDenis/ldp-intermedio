#ifndef LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_
#define LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <vector>

class LidarDriver {
    static constexpr int BUFFER_DIM = 10;
    static constexpr uint16_t POV = 180;
    const int RESOLUTION;

    int index, oldest_element_idx;
    std::vector<std::vector<double>> scan;
    bool is_valid(int degree) const;
public:
    void new_scan(const std::vector<double>& buff);
    std::vector<double> get_scan();
    void clear_buffer();
    double get_distace(double degree);

    LidarDriver(int degree = 1);

    class InvalidDegree{};
    class InvalidScan{};
    friend std::ostream& operator<<(std::ostream& os, const LidarDriver& l);
};


#endif // LDI_INTERMEDIO_INCLUDE_LIDARDRIVER_H_
