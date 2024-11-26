#include "LidarDriver.h"

LidarDriver::LidarDriver(const double resolution) : kResolution{resolution}, size_{0}, oldest_scan_idx_{0}
{
    if (resolution < 0.1 || resolution > 1){
        throw InvalidResolution();
    }
}

void LidarDriver::new_scan(const std::vector<double> &scan_to_store)
{
    int new_scan_index = (oldest_scan_idx_ + size_++) % kBufferDim;

    if (scans_.size() <= kBufferDim)
    {
        scans_.push_back(std::vector<double>((kFov / kResolution) + 1));
    }

    // Calculates the minimum size between the scan_to_store vector (new scan passed
    // by the user) and the size of a single scan buffer.
    int min = scan_to_store.size() > scans_[0].size() ? scans_[0].size() : scan_to_store.size();

    for (int i = 0; i < min; i++)
    {
        scans_[new_scan_index].at(i) = scan_to_store.at(i);
    }

    // If the user-provided array is not long enough, the remaining elements are filled with zeros.
    for (size_t i = min; i < scans_[0].size(); i++)
    {
        scans_[new_scan_index].at(i) = 0;
    }

    // After adding a new scan to the buffer, if the total number of scans exceeds
    // BUFFER_DIM (indicating that the oldest entry is overwritten), update
    // oldest_scan_idx_ to point to the next element and decrement the size by one.
    // The maximum number of scans in the buffer is BUFFER_DIM.
    if (size_ == kBufferDim + 1)
    {
        oldest_scan_idx_ = (oldest_scan_idx_ + 1) % kBufferDim;
        size_ = kBufferDim;
    }
}

std::vector<double> LidarDriver::get_scan()
{
    if (size_ == 0)
        throw BufferEmptyError();

    size_t oldest_scan_idx_prev = oldest_scan_idx_;
    // Updates oldest_scan_idx to point to the next oldest scan
    oldest_scan_idx_ = (oldest_scan_idx_ + 1) % kBufferDim;
    size_--;

    return scans_.at(oldest_scan_idx_prev);
}

void LidarDriver::clear_buffer()
{
    size_ = 0;
}

double LidarDriver::get_distance(const double angle) const
{
    // Retrieves the distance from the latest scan based on the specified angle.
    // The angle is converted to an index, and an additional index is added if the
    // angle is large enough (greater than or equal to 0.5 times the RESOLUTION)
    if (size_ == 0){
        throw BufferEmptyError();
    }

    if (angle <= 0)
    {
        return scans_.at((oldest_scan_idx_ + size_ - 1) % kBufferDim).at(0);
    }
    
    size_t angle_idx = std::round(angle/kResolution);

    if (angle_idx >= scans_.at(0).size())
    {
        angle_idx = scans_.at(0).size() - 1;
    }
    return scans_.at((oldest_scan_idx_ + size_ - 1) % kBufferDim).at(angle_idx);
}

std::ostream &operator<<(std::ostream &os, const LidarDriver &l)
{
    if (l.size_ == 0)
    {
        os << "{ }";
    }
    else
    {
        os << "{ ";
        for (size_t i = 0; i < l.scans_.at((l.oldest_scan_idx_ + l.size_ - 1) % l.kBufferDim).size(); i++)
        {
            os << l.scans_.at((l.oldest_scan_idx_ + l.size_ - 1) % l.kBufferDim).at(i) << ", ";
        }
        os << "\b\b }";
    }
    return os;
}
