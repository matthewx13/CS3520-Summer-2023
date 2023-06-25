#include "ClubOfficer.h"
#include "User.h"

ClubOfficer::ClubOfficer(const std::string& username, const std::string& password, const std::string& skill_level)
    : User(username, password, "ClubOfficer"), skill_level_(skill_level), requests(), days_played() {
}

bool ClubOfficer::can_reserve_slot(const Reservation& reservation) const {
    bool officer_hours = within_officer_hours(reservation.get_start_time()) && within_officer_hours(reservation.get_end_time());
    bool within_7_days = within_seven_days(reservation.get_start_time());

    // officers are members too, so they have the same limits
    bool has_played_today = has_played_on_day(reservation.get_start_time());
    bool has_played_twice_this_week = days_played.size() >= 2;

    return officer_hours && within_7_days && !has_played_today && !has_played_twice_this_week;
}


bool ClubOfficer::can_modify_reservation() const {
    // Officers can modify reservations.
    return true;
}

void ClubOfficer::add_request(const std::string& request) {
    requests.push_back(request);
}

void ClubOfficer::remove_request(const std::string& request) {
    auto it = std::remove_if(requests.begin(), requests.end(),
                             [&request](const std::string& r) {
                                 return r == request;
                             });
    requests.erase(it, requests.end());
}

std::string ClubOfficer::print_requests() const {
    std::string result;
    if (requests.empty()) {
        return "\nNo requests\n";
    }
    for (const std::string& request : requests) {
        result += request + "\n";
    }
    return result;
}

bool ClubOfficer::has_played_on_day(const time_point& date) const {
    for (const auto& day : days_played) {
        if (day == date) {
            return true;
        }
    }
    return false;
}

void ClubOfficer::add_day_played(const time_point& date) {
    days_played.push_back(date);
}

void ClubOfficer::remove_day_played(const time_point& date) {
    auto it = std::remove_if(days_played.begin(), days_played.end(),
                             [&date](const time_point& d) {
                                 return d == date;
                             });
    days_played.erase(it, days_played.end());
}

void ClubOfficer::reset_days_played() {
    days_played.clear();
}

std::string& ClubOfficer::get_skill_level() {
    return skill_level_;
}
