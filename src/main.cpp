#include <iostream>
#include <fstream>

#include "LidarDriver.h"

#define LOG(x) std::cout << x << std::endl

int main(int argc, char *argv[])
{
    LOG("Starting LidarDriver");

    // TODO: file input
    if (argc <= 1)
    {
    	LOG("Error! An input filename must be specified: ./ldp-intermedio input.txt");
    	return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
    	LOG("Error reading the file \"" << argv[1] << "\"!");
    }
    else
    {
    	LOG("Parsing file " << argv[1]);
    }

    std::string str;

    while (std::getline(file, str))
    {
        // TODO
    }

    if (file.bad())
    {
    	LOG("Error while reading file");
    }

    // Initialize LidarDriver
    LidarDriver l = LidarDriver(5);
    LOG("1. Initialized LidarDriver object (without any new_scan):");
    LOG(l);
    LOG("================================================================================\n");

    // Perform first new_scan
    std::vector<double> bu1 = {1.2, 2.3, 3.4, 4.5, 5.6};
    l.new_scan(bu1);
    LOG("2. After one new_scan call:");
    LOG(l);
    LOG("================================================================================\n");

    // Perform second new_scan with expanded vector
    for (int i = 1; i < 50; i++)
    {
        bu1.push_back(i);
    }
    l.new_scan(bu1);
    LOG("3. After another new_scan call:");
    LOG(l);
    LOG("================================================================================\n");

    // Perform third new_scan with an even larger vector
    for (int i = 1; i < 250; i++)
    {
        bu1.push_back(i);
    }
    l.new_scan(bu1);
    LOG("4. After three new_scan calls:");
    LOG(l);
    LOG("================================================================================\n");

    // Retrieve and print the oldest scan
    LOG("5. Retrieving the oldest scan:");
    std::vector<double> v = l.get_scan();
    LOG("Oldest scan vector:");
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    LOG("");
    LOG("================================================================================\n");

    // Check the buffer after retrieving the oldest scan
    LOG("6. After one get_scan call (oldest scan removed):");
    LOG(l);
    LOG("================================================================================\n");

    LOG("7. Getting a specific distance for angle = 90.3 (nearest valid degree = 90.5):");
    LOG(l.get_distance(90.3));
    LOG("================================================================================\n");

    LOG("8. Getting a specific distance for invalid angle = 400 (expected InvalidAngle)");
    try
    {
        LOG(l.get_distance(400));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    LOG("================================================================================\n");

    // Clear the buffer and verify
    LOG("9. Clearing the buffer:");
    l.clear_buffer();
    LOG("After clearing the buffer:");
    LOG(l);
    LOG("================================================================================\n");

    // Attempt to get a distance from an empty buffer
    LOG("10. Attempting to get distance with an empty buffer (expected BufferEmptyError):");
    try
    {
        LOG(l.get_distance(23.4));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    LOG("================================================================================\n");

    // Fill the buffer with multiple scans
    LOG("11. Filling the scan buffer:");
    l.new_scan(std::vector<double>{1, 2});
    std::vector<double> bu2 = {1, 2, 3, 4, 5, 6};
    l.new_scan(bu2);
    for (int i = 1; i < 270; i++)
    {
        bu2.push_back(i);
    }
    for (int i = 0; i < 8; i++)
    {
        double tmp = bu2[i]; 
        bu2[i] = (i+7)*1000;
        l.new_scan(bu2);
        bu2[i] = std::move(tmp);
    }
    LOG("================================================================================\n");

    // Overwrite the first two scans
    LOG("12. Overwriting the first scan:");
    l.new_scan(bu2);
    LOG("Buffer after overwriting:");
    LOG(l);
    LOG("================================================================================\n");

    // Remove all scans one by one and print them
    LOG("13. Removing all scans from the buffer:");
    for (size_t i = 0; i < 10; i++) {
        LOG(l);
        l.get_scan();
    }
    LOG("After removing all elements:");
    LOG(l);

    LOG("LidarDriver tests completed.");

    return 0;
}
