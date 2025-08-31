//
// Created by fra20 on 22/08/2025.
//

#ifndef ACTIVITYREGISTER1_0_ACTIVITY_H
#define ACTIVITYREGISTER1_0_ACTIVITY_H
#include <string>
# include "TimeFormat.h"

class Activity {
private:
    std::string description;
    TimeFormat StartTime;
    TimeFormat EndTime;
    std::string date;
public:
    Activity(const std::string &desc, TimeFormat &start, TimeFormat &end, const std::string &d);

    [[nodiscard]] std::string GetDescription() const;
    [[nodiscard]] TimeFormat GetStartTime() const;
    [[nodiscard]] TimeFormat GetEndTime() const;
    [[nodiscard]] std::string GetDate() const;
    [[nodiscard]] std::string ToString(bool usa24Hour = true) const;

};


#endif //ACTIVITYREGISTER1_0_ACTIVITY_H