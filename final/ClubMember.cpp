#include "ClubMember.h"

ClubMember::ClubMember(const std::string& username, const std::string& password, const std::string& skill_level)
    : User(username, password, "ClubMember"), skill_(skill_level), days_played(0) {
}

bool ClubMember::is_slot_open(const Reservation& reservation) const {
    time_point start_time = reservation.get_start_time();
    bool played_today = !played_on_day(start_time);
    bool played_twice = !days_played.size() >= 2;

    bool within_open_hours = new_time_in_opening_hours(reservation.get_start_time()) && new_time_in_opening_hours(reservation.get_end_time());
    bool within_2_days = new_time_in_two_days(reservation.get_start_time());

    return played_today && played_twice && within_open_hours && within_2_days;
}

bool ClubMember::played_on_day(const time_point& date) const {
    for (const auto& day : days_played) {
        if (day == date) {
            return true;
        }
    }
    return false;
}

void ClubMember::add_day_member_played(const time_point& date) {
    days_played.push_back(date);
}

void ClubMember::remove_day_played(const time_point& date) {
    auto it = std::remove_if(days_played.begin(), days_played.end(),
                             [&date](const time_point& d) {
                                 return d == date;
                             });
    days_played.erase(it, days_played.end());
}

void ClubMember::clear_days_played() {
    days_played.clear();
}

std::string& ClubMember::get_skill_of_member() {
    return skill_; 
}
