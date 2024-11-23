#include "../include/LidarDriver.h"

LidarDriver::LidarDriver(double degree): size {0}, first_element_index {0}, RESOLUTION {degree}
{
    if(!is_valid(degree)) throw InvalidDegree();
}

// Checks whether the degree value passed by the user is valid.
// Returns true if 0.1 <= degree <= 1, otherwise returns false.
// This function is used in the constructor.
bool LidarDriver::is_valid(double degree) const
{
    return degree >= 0.1 && degree <= 1;
}

void LidarDriver::new_scan(const std::vector<double>& buff)
{
    // Get the index for the new insertion
    int new_scan_index = (first_element_index + size++) % BUFFER_DIM;

    // Inserts a new element into the scan vector until it reaches the maximum buffer size.
    // If the scan size is less than BUFFER_DIM, a new vector is added.
    if (scan.size() <= BUFFER_DIM) {
        scan.push_back(std::vector<double>((POV/RESOLUTION) + 1));
    }

    // Calculates the minimum size between the buff vector (new scan passed by the user) 
    // and the size of a single scan buffer. 
    int min = buff.size() > scan[0].size() ? scan[0].size() : buff.size();
    // Fills the scan buffer up to min.
    for (int i = 0; i < min; i++) {
        scan[new_scan_index].at(i) = buff.at(i);
    }
    // If the user-provided array is not long enough, the remaining elements are filled with zeros.
    for (int i = min; i < scan[0].size(); i++) {
        scan[new_scan_index].at(i) = 0;
    }
    
    // After adding a new scan to the buffer, if the total number of scans exceeds BUFFER_DIM 
    // (indicating that the oldest entry is overwritten), update first_element_index to point 
    // to the next element and decrement the size by one. The maximum number of scans in the 
    // buffer is BUFFER_DIM.
    if (size == BUFFER_DIM + 1) {
        first_element_index = (first_element_index + 1) % BUFFER_DIM;
        size--;
    }
}

std::vector<double> LidarDriver::get_scan()
{
    // Throws an InvalidScan exception if no scan is available.
    if (size == 0) throw InvalidScan();

    // Retrieves the oldest scan from the buffer. Updates first_element_index to point to the 
    // next oldest scan, decrements the size, and returns the retrieved scan.
    int oldest_element_index = first_element_index;
    first_element_index = (first_element_index + 1) % BUFFER_DIM;
    size--;

    // if (size == 0) first_element_index = 0;

    return scan.at(oldest_element_index);
}

// Clears the buffer by resetting the size to 0
// and clearing all elements in the scan vector.
void LidarDriver::clear_buffer()
{
    size = 0;
    // first_element_index = 0;
    for(int i = 0; i < scan.size(); i++) {
        // Erases all elements from the container. After this call, size() returns zero.
        // Leaves the capacity() of the vector unchanged!
        scan[i].clear();
    }
}

// Retrieves the distance from the latest scan based on the specified degree.
// The degree is converted to an index, and an additional index is added if the degree 
// is large enough (greater than or equal to 0.5 times the RESOLUTION)
double LidarDriver::get_distance(double degree) const {
    // Returns -1 to indicate an invalid distance when no scan data is available.
    if (size == 0) return -1;
    if (degree < 0 || degree > 180) throw InvalidDegree();
    int addictional_index = 0;
    if (std::fmod(degree, RESOLUTION) >=  RESOLUTION / 2) { addictional_index++; }
    return scan[(first_element_index + size - 1) % BUFFER_DIM][static_cast<int>(degree / RESOLUTION) + addictional_index];
}

std::ostream& operator<<(std::ostream& os, const LidarDriver& l) {
    os << "----- Lidar driver output  ~ Size: " << l.size << " -----\n";
    if (l. size == 0) os << "~ Empty buffer ~\n";
    for (int i = 0; i < l.size; i++)
    {
        os << " ~ Buffer n°" << i + 1 << " ~ \n";
        int k = (l.first_element_index + i) % l.BUFFER_DIM;
        os << "k: " << k << '\n';
        for (int j = 0; j < l.scan[k].size(); j++)
        {
            os << l.scan[k][j] << '\t';
        }
        os << '\n';
    }
    os << "-------------------------------";

    return os;
}
