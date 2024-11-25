#include <iostream>
#include "../include/LidarDriver.h"

#define LOG(x) std::cout << x << std::endl;

int main(void) {
    // Group Toni Kosumovic, Davide Rorato, Denis Kosumovic
    LOG("Starting LidarDriver tests - Group: KDK");

    // Initialize LidarDriver
    LidarDriver l = LidarDriver(0.5);
    LOG("\n1. Initialized LidarDriver object (without any new_scan):");
    LOG(l);

    // Perform first new_scan
    std::vector<double> bu1 = {1.2, 2.3, 3.4, 4.5, 5.6};
    l.new_scan(bu1);
    LOG("\n2. After one new_scan call:");
    LOG(l);

    // Perform second new_scan with expanded vector
    for (int i = 1; i < 50; i++) {    
        bu1.push_back((4.2 * i) + 2.2 / i);
    }
    l.new_scan(bu1);
    LOG("\n3. After another new_scan call:");
    LOG(l);

    // Perform third new_scan with an even larger vector
    for (int i = 1; i < 250; i++) {    
        bu1.push_back((9.65 * i) + 11.3 / i);
    }
    l.new_scan(bu1);
    LOG("\n4. After three new_scan calls:");
    LOG(l);

    // Retrieve and print the oldest scan
    LOG("\n5. Retrieving the oldest scan:");
    std::vector<double> v = l.get_scan();
    LOG("Oldest scan vector:");
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << "\t";
    }
    LOG("");

    // Check the buffer after retrieving the oldest scan
    LOG("\n6. After one get_scan call (oldest scan removed):");
    LOG(l);

    // Retrieve a specific distance based on degree
    LOG("\n7. Getting a specific distance for degree = 90.3 (nearest valid degree = 90.5):");
    LOG(l.get_distance(90.3));

    // Clear the buffer and verify
    LOG("\n8. Clearing the buffer:");
    l.clear_buffer();
    LOG("After clearing the buffer:");
    LOG(l);

    // Attempt to get a distance from an empty buffer
    LOG("\n9. Attempting to get distance with an empty buffer (expected -1):");
    LOG(l.get_distance(23.4));
    LOG("Note: -1 indicates invalid distance as the buffer is empty.");

    // Fill the buffer with multiple scans
    LOG("\n10. Filling the scan buffer:");
    l.new_scan(std::vector<double>{1, 2});
    std::vector<double> bu2 = {1, 2, 3, 4, 5, 6};
    l.new_scan(bu2);
    for (int i = 1; i < 270; i++) {    
        bu2.push_back((2 * i));
    }
    for (int i = 0; i < 8; i++) {
        l.new_scan(bu2);
    }
    LOG("Buffer after filling:");
    LOG(l);

    // Overwrite the first two scans
    LOG("\n11. Overwriting the first two scans:");
    l.new_scan(bu2);
    l.new_scan(bu2);
    LOG("Buffer after overwriting:");
    LOG(l);

    // Remove all scans one by one and print them
    LOG("\n12. Removing all scans from the buffer:");
    for (int i = 0; i < 10; i++) {
        v = l.get_scan();
        std::cout << "Vector " << i + 1 << ":\n";
        for (int j = 0; j < v.size(); j++) {
            std::cout << v[j] << "\t";
        }
        LOG("");
    }
    LOG("After removing all elements:");
    LOG(l);

    LOG("\nLidarDriver tests completed.");

    return 0;
}
