#include "../include/Buffer.h"

Buffer::Buffer(int sz): size_{sz}, data_{new double[sz]} {}

Buffer::Buffer(const Buffer& b): size_{b.size_}, data_{new double(b.size_)} {
    std::copy(b.data_, b.data_ + size_, data_);
}

Buffer::Buffer(Buffer&& b): size_{b.size_}, data_{b.data_} {
    b.size_ = 0;
    b.data_ = nullptr;
}

Buffer::~Buffer() {
    delete[] data_;
}

int Buffer::size() const { return size_; }

double& Buffer::at(int i) {
    if (!is_valid(i)) throw InvalidRange();
    return data_[i];
}

double Buffer::at(int i) const {
    if (!is_valid(i)) throw InvalidRange();
    return data_[i];
}

double& Buffer::operator[](int i) {
    return data_[i];
}

double Buffer::operator[](int i) const {
    return data_[i];
}

Buffer& Buffer::operator=(const Buffer& b) {
    double* temp_p = new double[b.size_];
    std::copy(b.data_, b.data_ + b.size_, temp_p);
    delete[] data_;
    data_ = temp_p;
    size_ = b.size_;
    return *this;
}

Buffer& Buffer::operator=(Buffer&& b) {
    delete[] data_;
    size_ = b.size_;
    data_ = b.data_;
    b.data_ = nullptr;
    b.size_ = 0;
    return *this;
}

bool Buffer::is_valid(int i) const { 
    return  i < size_ && i >= 0;
};
