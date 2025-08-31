#include <iostream>
#include <ncurses/ncurses.h>
#include "TimeFormat.h"
#include "Activity.h"
#include "Register.h"
#include <string>
#include <cctype>
#include <regex>
#include <stdexcept>

bool isValidDate (const std::string& date) {
    std::regex pattern (R"(^\d{4}-\d{2}-\d{2}$)"); // YYYY-MM-DD
    return std::regex_match (date, pattern);
}
void validateTime(int h, int m, int s) {
    if (h<0 || h>23 || m<0 || m>59 || s<0 || s>59) {
        throw std::out_of_range("Invalid time");
    }
}

 int main() {
    initscr();
    cbreak();
    echo();
    keypad(stdscr, true);
    Register reg;
    char cont = 'y';
     //inserimento attività
    while (tolower(cont) == 'y') {
        try {
            clear();
        char desc[100];
        char date[11];
        int hStart, mStart, sStart;
        int hEnd, mEnd, sEnd;
        mvprintw(0, 0, "Enter activity description:");
        getnstr(desc, 99);
        if (strlen(desc) == 0) {
            throw std::invalid_argument("The description cannot be empty");
        }
        // lettura e validazione data
        mvprintw(1, 0, "Enter activity date (YYYY-MM-DD): ");
        getnstr(date, 10);
        if (!isValidDate (date)) {
            throw std::invalid_argument("Invalid Date");
        }
        // lettura e validazione orario inizio
        mvprintw(2,0, "Enter start time (HH MM SS): ");
        scanw("%d %d %d", &hStart, &mStart, &sStart);
        validateTime(hStart, mStart, sStart);
        TimeFormat start(hStart, mStart, sStart);
        // lettura e validazione orario fine
        mvprintw(3, 0, "Enter end time (HH MM SS): ");
        scanw("%d %d %d", &hEnd, &mEnd, &sEnd);
        validateTime(hEnd, mEnd, sEnd);
        TimeFormat end(hEnd, mEnd, sEnd);
        if (!(start.isBefore(end))) {
            throw std::invalid_argument("The end time must be after the start time");
        }
        auto activitiesOnDate = reg.getActivitiesByDateObjects(date);
        for (const auto& a : activitiesOnDate) {
            TimeFormat existingStart = a.GetStartTime();
            TimeFormat existingEnd = a.GetEndTime();
            if (!(end.isBefore(existingStart) || start.isBefore(existingEnd) == false)) {
                throw std::invalid_argument("Activity superimposed on another existing one");
            }
        }
        // aggiungi attività
        reg.addActivity(Activity(desc, start, end, date));
        mvprintw(5, 0, "Add another activity? (y/n): ");
        cont = getch();
        }
        catch (const std::exception& e) {
            clear();
            mvprintw(0, 0, "Error: %s", e.what());
            mvprintw(1, 0, "Press a button to re-enter the data");
            getch();
        }

    }
    // visualizzazione attività per data
     bool exitProgram = false;
     char filterDate[11];
     while (!exitProgram) {
         try {
             clear();
             mvprintw(0, 0, "Enter date to display activities (YYYY-MM-DD): ");
             getnstr(filterDate, 10);
             if (!isValidDate (filterDate)) {
                 throw std::invalid_argument("Invalid date");
             }
               mvprintw(1, 0, "Use 24h format? (y/n): ");
             int ch = getch();
             bool use24Hour = (ch == 'y' || ch == 'Y');
             clear();
             mvprintw(0, 0, "Activities for %s:\n", filterDate);
             auto activities = reg.getActivitiesByDate(filterDate, use24Hour);
             int row = 1 ;
             if (activities.empty()) {
                 mvprintw(row++, 0, "No activities found");
             } else {
                 for (const auto& s: activities) {
                     mvprintw(row++, 0, "%s", s.c_str());
                 }
             }
             mvprintw(row + 1, 0, "View another date? (y/n): ");
             int key = getch();
             if (tolower(key) != 'y') {
                 exitProgram = true;
             }
         }
         catch (const std::exception& e) {
             clear();
             mvprintw(0, 0, "Error: %s", e.what());
             mvprintw(1, 0, "Press a button to re-enter the data");
             getch();
         }
     }
     clear();
     mvprintw(0, 0, "Press any key to exit");
     refresh();
     getch();
     endwin();
     return 0;
}