#include <iostream>
#include <ctime> // For time access
#include <iomanip> // For formatting

struct Time {
    int h, m, s;
};

/**
 * Set the current time of the machine into a given `Time` struct
 * 
 * @param _time Time struct to populate with the current machine time
 */
void set_current_time(Time& _time) {
    time_t timestamp = time(NULL); // Get current timestamp
    tm current_time = *localtime(&timestamp); // Dereference the actual content of tm struct

    // Extracting the relevant data to the `Time` struct
    _time.h = current_time.tm_hour;
    _time.m = current_time.tm_min;
    _time.s = current_time.tm_sec;
}

/**
 * Validating a time struct to be a valid time at day (24H)
 * 
 * @param time Time struct to validate
 * @returns Boolean value indicating whether the value is valid
 */
bool validate_time(Time& time) {
    return (
        0 <= time.h && time.h < 24 && 
        0 <= time.m && time.m < 60 && 
        0 <= time.s && time.s < 60
    );
}

/**
 * Populating an array within a given length via user interactions.
 * 
 * The array will contain the times the user entered except the invalid ones,
 * which will be replaced with the current time of the machine at runtime.
 * 
 * @param arr_length The length of the output array
 */
Time* scan_arr(int& arr_length) {
    Time* output_arr = new Time[arr_length];

    for (int i = 0; i < arr_length; i++) {
        Time time_to_set;
        std::cout << "Enter hour, min, sec (format - space separated): ";
        std::cin >> time_to_set.h >> time_to_set.m >> time_to_set.s;
        
        if (!validate_time(time_to_set))
            set_current_time(time_to_set);
        
        output_arr[i] = time_to_set;
    }

    return output_arr;
}

/**
 * Prints the given time array within the given length
 * 
 * @param arr Pointer to time array
 * @param length Number of elements in the array
 */
void print_array(Time* arr, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << i+1 << ". ";
        std::cout << std::setw(2) << std::setfill('0') << arr[i].h << ":"; 
        std::cout << std::setw(2) << std::setfill('0') << arr[i].m << ":"; 
        std::cout << std::setw(2) << std::setfill('0') << arr[i].s << std::endl;
    }
}

int main() {
    int length = 5;
    Time* arr = scan_arr(length);
    print_array(arr, length);

    // Deallocate the memory
    // There is no need to set the pointer to null because it's the end of the program
    delete[] arr;
    return 0;
}