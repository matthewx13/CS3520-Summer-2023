#include "ClubMember.h"
using namespace std;

// Constructor for the ClubMember class.
ClubMember::ClubMember(const string& username, const string& password, const string& skill_level)
    : User(username, password, "ClubMember"), skill_level_(skill_level), days_played(0) {
}

// Checks if the ClubMember can reserve a slot for a given reservation.
bool ClubMember::can_reserve_slot(const Reservation& reservation) const {
    bool open_hours = within_opening_hours(reservation.get_start_time()) && within_opening_hours(reservation.get_end_time());
    bool within_2_days = within_two_days(reservation.get_start_time());
    // Club members are allowed one session a day and two sessions a week
    time_point start_time = reservation.get_start_time();
    bool has_played_today = has_played_on_day(start_time);
    bool has_played_twice_this_week = days_played.size() >= 2;

    return open_hours && within_2_days && !has_played_today && !has_played_twice_this_week;
}

// Checks if the ClubMember has played on a given day.
bool ClubMember::has_played_on_day(const time_point& date) const {
    for (const auto& day : days_played) {
        if (day == date) {
            return true;
        }
    }
    return false;
}

// Adds a day to the list of days the ClubMember has played.
void ClubMember::add_day_played(const time_point& date) {
    days_played.push_back(date);
}

// Removes a day from the list of days the ClubMember has played.
void ClubMember::remove_day_played(const time_point& date) {
    auto it = std::remove_if(days_played.begin(), days_played.end(),
                             [&date](const time_point& d) {
                                 return d == date;
                             });
    days_played.erase(it, days_played.end());
}

// Resets the list of days the ClubMember has played.
void ClubMember::reset_days_played() {
    days_played.clear();
}

// Retrieves the skill level of the ClubMember.
string& ClubMember::get_skill_level() {
    return skill_level_;
}

std::string& ClubMember::get_skill_level() {
    return skill_level_; // qualifiers dropped in binding reference of type "std::__1::string &" to initializer of type "const std::__1::string" so we 
}
