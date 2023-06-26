#include "ClubOfficer.h"
#include "User.h"

ClubOfficer::ClubOfficer(const std::string& username, const std::string& password, const std::string& skill_level)
    : User(username, password, "ClubOfficer"), skill_(skill_level), requests(), days_played() {
}

bool ClubOfficer::is_slot_open(const Reservation& reservation) const {
    bool in_officer_hours = within_officer_hours(reservation.get_start_time()) && within_officer_hours(reservation.get_end_time());
    bool within_7_days = within_seven_days(reservation.get_start_time());
    bool played_today = !played_on_day(reservation.get_start_time());
    bool played_twice = days_played.size() >= 2;

    return in_officer_hours && within_7_days && played_today && !played_twice;
}


bool ClubOfficer::able_to_edit_res() const {
    return true;
}

void ClubOfficer::append_request(const std::string& request) {
    requests.push_back(request);
}

void ClubOfficer::delete_request(const std::string& request) {
    auto it = std::remove_if(requests.begin(), requests.end(),
                             [&request](const std::string& r) {
                                 return r == request;
                             });
    requests.erase(it, requests.end());
}

std::string ClubOfficer::print_requests() const {
    std::string result;
    if (requests.empty()) {
        return "\nNo requests yet\n";
    }
    for (const std::string& request : requests) {
        result += request + "\n";
    }
    return result;
}

bool ClubOfficer::played_on_day(const time_point& date) const {
    for (const auto& day : days_played) {
        if (day == date) {
            return true;
        }
    }
    return false;
}

void ClubOfficer::add_day_member_played(const time_point& date) {
    days_played.push_back(date);
}

void ClubOfficer::remove_day_played(const time_point& date) {
    auto it = std::remove_if(days_played.begin(), days_played.end(),
                             [&date](const time_point& d) {
                                 return d == date;
                             });
    days_played.erase(it, days_played.end());
}

void ClubOfficer::clear_days_played() {
    days_played.clear();
}

std::string& ClubOfficer::get_skill_of_member() {
    return skill_;
}