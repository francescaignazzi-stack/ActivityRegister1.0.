//
// Created by fra20 on 22/08/2025.
//

#include "Activity.h"
#include <sstream>

Activity::Activity(const std::string &desc, TimeFormat &start, TimeFormat &end, const std::string &d) : description(desc), StartTime(start), EndTime(end), date(d) {}
std::string Activity::GetDescription() const { return description; }
TimeFormat Activity::GetStartTime() const { return StartTime; }
TimeFormat Activity::GetEndTime() const { return EndTime; }
std::string Activity::GetDate() const { return date;}
std::string Activity::ToString(bool use24Hour) const {
    std::ostringstream oss;
    if (use24Hour) {
        oss << StartTime.toString24() << "-" << EndTime.toString24();
    } else {
        oss << StartTime.toString12() << "-" << EndTime.toString12();
    }
    oss << ":" << description;
    return oss.str();
}

