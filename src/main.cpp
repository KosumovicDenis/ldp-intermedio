#include <iostream>
#include "../include/LidarDriver.h"
#define LOG(x) std::cout << x << std::endl;

int main(void) {
    LOG("KDK")
    LidarDriver l = LidarDriver(1);

    std::vector<double> bu1 = {1.2, 2.3, 3.4, 4.5, 5.6};

    l.new_scan(bu1);
    bu1.push_back(44.2);
    bu1.push_back(42.2);
    bu1.push_back(43.2);
    bu1.push_back(7.2);
    bu1.push_back(9.2);
    l.new_scan(bu1);

    LOG(l);
    std::vector<double> v = l.get_scan();
    LOG("Vettore");
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << "\t";
    }
    LOG("");
    
    LOG(l);
    v = l.get_scan();
    LOG("Vettore");
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << "\t";
    }
    LOG("");
    
    LOG(l);
    
    return 0;
}
