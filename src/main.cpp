#include <iostream>
#include <fstream>

#include "LidarDriver.h"

#define LOG(x) std::cout << x << std::endl

int main(int argc, char *argv[])
{
    LOG("Starting LidarDriver");

    if (argc > 1) // If input file path is present
    {
        std::vector<double> numbers_from_file;
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
            try
            {
                numbers_from_file.push_back(std::stod(str));
            }
            catch(const std::exception& e)
            {
                std::cerr << "Couldn't convert \"" << str << "\" " << "to double" << '\n';
            }
        }

        if (file.bad())
        {
            LOG("Error while reading file");
        }

        LidarDriver lidar(0.9);
        lidar.new_scan(numbers_from_file);
        LOG("Latest scan parsed from file:");
        LOG(lidar);
    }

    // Initialize LidarDriver

    LidarDriver l;
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
    bu1.clear();
    for (int i = 1; i < 250; i++)
    {
        bu1.push_back(i);
    }
    l.new_scan(bu1);
    LOG("4. After three new_scan calls:");
    LOG(l);
    LOG("================================================================================\n");

    LOG("5. Retrieving the oldest scan:");
    std::vector<double> v = l.get_scan();
    LOG("Oldest scan vector:");
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    LOG("");
    LOG("================================================================================\n");

    LOG("6. Most recent scan is still the same after removal:");
    LOG(l);
    LOG("================================================================================\n");

    LOG("7. Getting a specific distance for angle:");
    LOG("-100°: " << l.get_distance(-100));
    LOG("0°: " << l.get_distance(0));
    LOG("10°: " << l.get_distance(10));
    LOG("10.2°: " << l.get_distance(10.2));
    LOG("10.5°: " << l.get_distance(10.5));
    LOG("10.55°: " << l.get_distance(10.55));
    LOG("10.9°: " << l.get_distance(10.9));
    LOG("90.3°: " << l.get_distance(90.3));
    LOG("300°: " << l.get_distance(300));
    LOG("================================================================================\n");

    // Clear the buffer and verify
    LOG("8. Clearing the buffer:");
    l.clear_buffer();
    LOG("After clearing the buffer:");
    LOG(l);
    LOG("================================================================================\n");


    LOG("9. Getting a specific distance for when buffer is empty (Expected BufferEmptyError):");
    try
    {
        LOG(l.get_distance(42));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    LOG("================================================================================\n");

    LOG("10. Filling the scan buffer:");
    l.new_scan({1, 2});
    LOG("Added {1, 2}");
    LOG(l);
    std::vector<double> bu2 = {1, 2, 3, 4, 5, 6};
    l.new_scan(bu2);
    LOG("Added {1, 2, 3, 4, 5, 6}");
    LOG(l);
    for (int i = 1; i < 270; i++)
    {
        bu2.push_back(i);
    }
    for (int i = 0; i < 8; i++)
    {
        double tmp = bu2[i];
        bu2[i] = (i + 7) * 1000;
        l.new_scan(bu2);
        LOG(i << " Added bu2 vector");
        bu2[i] = tmp;
        LOG(l);
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
    for (size_t i = 0; i < 10; i++)
    {
        LOG(l);
        l.get_scan();
    }
    LOG("After removing all elements:");
    LOG(l);
    LOG("================================================================================\n");

    // Remove all scans one by one and print them
    LOG("14. Should throw InvalidResolution exception:");
    try
    {
        LidarDriver l1 = LidarDriver(1000);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    LOG("================================================================================\n");

    LOG("LidarDriver tests completed.");

    return 0;
}
