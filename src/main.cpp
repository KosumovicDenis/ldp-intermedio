#include <iostream>
#include "../include/LidarDriver.h"
#define LOG(x) std::cout << x << std::endl;

int main(void) {
    LOG("KDK")
    LidarDriver l = LidarDriver(0.5);

    std::vector<double> bu1 = {1.2, 2.3, 3.4, 4.5, 5.6};

    l.new_scan(bu1);
    LOG(l);

    for(int i = 1; i < 70; i++) {    
        bu1.push_back((4.2 * i) + 2.2 / i);
    }
    l.new_scan(bu1);
    LOG(l);

    for(int i = 1; i < 150; i++) {    
        bu1.push_back((9.65 * i) + 11.3/ i);
    }
    l.new_scan(bu1);
    l.new_scan(bu1);
    l.new_scan(bu1);
    l.new_scan(bu1);
    l.new_scan(bu1);
    l.new_scan(bu1);
    l.new_scan(bu1);
    for(int i = 1; i < 150; i++) {    
        bu1.push_back((2 * i) + 0.1/ i);
    }
    l.new_scan(bu1);

    LOG(l);
    std::vector<double> v = l.get_scan();
    LOG("Vettore");
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << "\t";
    }
    LOG("");
    
    LOG(l);
    LOG(l.get_distance(180));
    l.clear_buffer();
    LOG(l);
    
    return 0;
}
