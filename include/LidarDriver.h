#ifndef LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_
#define LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_

#include <vector>
#include <ostream>
#include <cmath>

class LidarDriver
{
    static constexpr int kBufferDim = 10;
    static constexpr int kFov = 180;
    const double kResolution;

    size_t size_, oldest_scan_idx_;
    std::vector<std::vector<double>> scans_;

public:
    /// Instances the class LidarDriver
    /// \throws InvalidResolution If the resolution is out of the range [0.1, 1]
    /// \param resolution The angular resolution of the sensor in degrees
    explicit LidarDriver(const double resolution = 1);

    /// Accepts a std::vector<double> containing a scan and stores it in the buffer
    /// (overwriting the oldest scan if the buffer is full).
    /// This function also checks the size of the buffer: if the readings are less
    /// than expected, it completes missing data to 0, if they are more they get
    /// discarded.
    /// \param scan_to_store Dati da memorizzare nel buffer interno
    void new_scan(const std::vector<double> &scan_to_store);

    /// Retrieves the oldest scan and removes it from the internal buffer
    /// \throws BufferEmptyError If the buffer is empty
    /// \returns The oldest scan
    std::vector<double> get_scan();

    /// Deletes all stored scans
    void clear_buffer();

    /// Accepts an angle in degrees and returns the reading that corresponds to
    /// that angle in the most recent reading from the sensor.
    /// This reading doesn't get deleted from the buffer.
    /// If the reading doesn't get deleted from the buffer and the requested angle
    /// isn't available it returns the reading of the closest angle.
    /// \throws BufferEmptyError If the buffer is empty
    /// \param angle The angle in degrees
    double get_distance(const double angle) const;

    /// Prints the most recent scan saved, it doesn't get removed from the buffer
    friend std::ostream &operator<<(std::ostream &os, const LidarDriver &l);

    class BufferEmptyError {};

    class InvalidResolution {};
};

#endif // LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_
