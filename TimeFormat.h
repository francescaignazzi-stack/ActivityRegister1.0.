//
// Created by fra20 on 22/08/2025.
//

#ifndef ACTIVITYREGISTER1_0_TIMEFORMAT_H
#define ACTIVITYREGISTER1_0_TIMEFORMAT_H
#include <string>

class TimeFormat {
private:
    int hours, minutes, seconds;
    public:
    TimeFormat(int h=0, int m=0, int s=0);
    std::string toString24() const;
    std::string toString12() const;
    bool isBefore(const TimeFormat& other) const;
    bool isEqual(const TimeFormat &other) const;
};


#endif //ACTIVITYREGISTER1_0_TIMEFORMAT_H