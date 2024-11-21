#ifndef LIDARDRIVER_INCLUDE_BUFFER_H_
#define LIDARDRIVER_INCLUDE_BUFFER_H_

class Buffer {
    int size;
    double* values;

    class InvadilRange{};

public:
    Buffer(int sz);
    Buffer(const Buffer& b);
    Buffer(Buffer&& b);
    ~Buffer();

    double& at(int i);
    double at(int i) const;

    Buffer& operator=(const Buffer& b);
    Buffer& operator=(Buffer&& b);
    double& operator[](int i);
    double operator[](int i) const;
};

#endif // LIDARDRIVER_INCLUDE_BUFFER_H_
