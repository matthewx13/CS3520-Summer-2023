#include "ClubMember.h"

ClubMember::ClubMember(const std::string& username, const std::string& password, const std::string& skill_level)
    : User(username, password, "ClubMember"), skill_level_(skill_level), days_played(0) {
}

bool ClubMember::can_reserve_slot(const Reservation& reservation) const {
    bool open_hours = within_opening_hours(reservation.get_start_time()) && within_opening_hours(reservation.get_end_time());
    bool within_2_days = within_two_days(reservation.get_start_time());
    // members only get one session a day, and two sessions a week
    time_point start_time = reservation.get_start_time();
    bool has_played_today = has_played_on_day(start_time);
    bool has_played_twice_this_week = days_played.size() >= 2;

    return open_hours && within_2_days && !has_played_today && !has_played_twice_this_week;
}

bool ClubMember::has_played_on_day(const time_point& date) const {
    for (const auto& day : days_played) {
        if (day == date) {
            return true;
        }
    }
    return false;
}

void ClubMember::add_day_played(const time_point& date) {
    days_played.push_back(date);
}

void ClubMember::remove_day_played(const time_point& date) {
    auto it = std::remove_if(days_played.begin(), days_played.end(),
                             [&date](const time_point& d) {
                                 return d == date;
                             });
    days_played.erase(it, days_played.end());
}

void ClubMember::reset_days_played() {
    days_played.clear();
}

std::string& ClubMember::get_skill_level() {
    return skill_level_; 
}
