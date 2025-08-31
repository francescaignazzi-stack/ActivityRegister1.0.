//
// Created by fra20 on 22/08/2025.
//

#include "TimeFormat.h"
#include <sstream>
#include <iomanip>
TimeFormat::TimeFormat(int h, int m, int s) : hours(h), minutes(m), seconds(s){}
std::string TimeFormat::toString24() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":";
    oss << std::setw(2) << std::setfill('0') << minutes << ":";
    oss << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}
std::string TimeFormat::toString12() const {
    int h12 = hours % 12;
    if (h12 == 0) {
        h12 = 12;
    }
    std::string ampm = (hours < 12) ? "AM" : "PM";
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << h12 << ":";
    oss << std::setw(2) << std::setfill('0') << minutes << ":";
    oss << std::setw(2) << std::setfill('0') << seconds << " " << ampm;
    return oss.str();
}
bool TimeFormat::isBefore(const TimeFormat& other) const {
    if (hours != other.hours) return hours < other.hours;
    if (minutes != other.minutes) return minutes < other.minutes;
    return seconds < other.seconds;
}
bool TimeFormat::isEqual(const TimeFormat& other) const {
    return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
}




