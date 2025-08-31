//
// Created by fra20 on 22/08/2025.
//

#include "Register.h"

#include <cstring>

#include "Activity.h"
#include <iostream>
void Register::addActivity(const Activity &a) {
    activities.push_back(a);
}

std::vector<std::string> Register::getActivitiesByDate(const std::string &filterDate, bool use24Hour) const {
    std::vector<std::string> result;
    for (const auto &a : activities) {
        if (a.GetDate() == filterDate) {
            result.push_back(a.ToString(use24Hour));
        }
    }
    return result;
}
std::vector<Activity> Register::getActivitiesByDateObjects(const std::string &date) const {
    std::vector<Activity> result;
    for (const auto &a : activities) {
        if (a.GetDate() == date) {
            result.push_back(a);
        }
    }
    return result;
}