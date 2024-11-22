#ifndef LIDARDRIVER_INCLUDE_BUFFER_H_
#define LIDARDRIVER_INCLUDE_BUFFER_H_

#include <cstddef>
#include <assert.h>
#include <algorithm>

class Buffer {
private:
    int size_;
    bool is_valid(int i) const;
    double* data_;

public:
    class InvalidRange{};

    explicit Buffer(int sz);
    Buffer(const Buffer& b);
    Buffer(Buffer&& b);
    ~Buffer();

    int size() const;

    double& at(int i);
    double at(int i) const;

    Buffer& operator=(const Buffer& b);
    Buffer& operator=(Buffer&& b);
    double& operator[](int i);
    double operator[](int i) const;
};

#endif // LIDARDRIVER_INCLUDE_BUFFER_H_
