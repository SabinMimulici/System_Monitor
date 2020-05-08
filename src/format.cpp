#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    long hours, min, sec, min_sec;
    
    hours = seconds / 3600;
    min_sec = seconds % 3600;
    min = min_sec / 60;
    sec = min_sec % 60;

    return std::to_string(hours) +':'+ std::to_string(min) +':'+ std::to_string(sec);

}