//
// Created by fra20 on 22/08/2025.
//

#ifndef ACTIVITYREGISTER1_0_REGISTER_H
#define ACTIVITYREGISTER1_0_REGISTER_H
# include <vector>
#include "Activity.h"

class Register {
private:
    std::vector<Activity> activities;
public:
    Register() = default;
    void addActivity(const Activity &a);
    std::vector<std::string> getActivitiesByDate (const std::string &filterDate, bool use24Hour = true) const;
    std::vector<Activity> getActivitiesByDateObjects(const std::string &date) const;

};


#endif //ACTIVITYREGISTER1_0_REGISTER_H