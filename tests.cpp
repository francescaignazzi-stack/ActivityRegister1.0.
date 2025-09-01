//
// Created by fra20 on 01/09/2025.
//
#define CATCH_CONFIG_MAIN
#include "libs/catch2/catch_amalgamated.hpp"
#include "Activity.h"
#include "Register.h"
#include "TimeFormat.h"
#include <string>

// test della classe TimeFormat
TEST_CASE("TimeFormat comparisons and string output", "[TimeFormat]") {
    TimeFormat t1(10, 30, 0);
    TimeFormat t2(12, 0, 0);
    TimeFormat t3(10, 30, 0);

    REQUIRE(t1.isBefore(t2) == true);
    REQUIRE(t2.isBefore(t1) == false);
    REQUIRE(t1.isEqual(t3) == true);
    REQUIRE(t1.isEqual(t2) == false);

    REQUIRE(t1.toString24() == "10:30:00");
    REQUIRE(t2.toString12() == "12:00:00 PM");
}

// Test della classe Activity
TEST_CASE("Activity creation and string representation", "[Activity]") {
    TimeFormat start(9, 0, 0);
    TimeFormat end(10, 0, 0);
    std::string date = "2025-09-01";
    Activity act("Running", start, end, date);

    REQUIRE(act.GetDescription() == "Running");
    REQUIRE(act.GetStartTime().isEqual(start));
    REQUIRE(act.GetEndTime().isEqual(end));
    REQUIRE(act.GetDate() == date);
    REQUIRE(act.ToString(true) == "09:00:00-10:00:00:Running");
    REQUIRE(act.ToString(false) == "09:00:00 AM-10:00:00 AM:Running");
}

// Test della classe Register
TEST_CASE("Register adds and retrieves activities", "[Register]") {
    Register reg;
    TimeFormat start1(8, 0, 0);
    TimeFormat end1(9, 0, 0);
    TimeFormat start2(10, 0, 0);
    TimeFormat end2(11, 0, 0);
    std::string date = "2025-09-01";

    Activity act1("Breakfast", start1, end1, date);
    Activity act2("Meeting", start2, end2, date);

    reg.addActivity(act1);
    reg.addActivity(act2);

    // Verifica oggetti
    auto activitiesObj = reg.getActivitiesByDateObjects(date);
    REQUIRE(activitiesObj.size() == 2);
    REQUIRE(activitiesObj[0].GetDescription() == "Breakfast");
    REQUIRE(activitiesObj[1].GetDescription() == "Meeting");

    // Verifica stringhe formato 24h
    auto activitiesStr24 = reg.getActivitiesByDate(date, true);
    REQUIRE(activitiesStr24.size() == 2);
    REQUIRE(activitiesStr24[0] == "08:00:00-09:00:00:Breakfast");
    REQUIRE(activitiesStr24[1] == "10:00:00-11:00:00:Meeting");

    // Verifica stringhe formato 12h
    auto activitiesStr12 = reg.getActivitiesByDate(date, false);
    REQUIRE(activitiesStr12.size() == 2);
    REQUIRE(activitiesStr12[0] == "08:00:00 AM-09:00:00 AM:Breakfast");
    REQUIRE(activitiesStr12[1] == "10:00:00 AM-11:00:00 AM:Meeting");
}
