#include "ClubOfficer.h"
#include "User.h"
using namespace std;

// Constructor
ClubOfficer ClubOfficer(const string& username, const string& password, const string& skill_level)
    : User(username, password, "ClubOfficer"), skill_level_(skill_level), requests(), days_played() {
}

// Check if the club officer can reserve a slot for the given reservation
bool ClubOfficer can_reserve_slot(const Reservation& reservation) const {
    bool officer_hours = within_officer_hours(reservation.get_start_time()) && within_officer_hours(reservation.get_end_time());
    bool within_7_days = within_seven_days(reservation.get_start_time());

    // Officers are members too, so they have the same limits
    bool has_played_today = has_played_on_day(reservation.get_start_time());
    bool has_played_twice_this_week = days_played.size() >= 2;

    return officer_hours && within_7_days && !has_played_today && !has_played_twice_this_week;
}

// Check if the club officer can modify reservations
bool ClubOfficer can_modify_reservation() const {
    // Officers can modify reservations.
    return true;
}

// Add a request to the club officer's list of requests
void ClubOfficer add_request(const string& request) {
    requests.push_back(request);
}

// Remove a request from the club officer's list of requests
void ClubOfficer remove_request(const string& request) {
    auto it = remove_if(requests.begin(), requests.end(),
                             [&request](const string& r) {
                                 return r == request;
                             });
    requests.erase(it, requests.end());
}

// Print the list of requests
string ClubOfficer print_requests() const {
    string result;
    if (requests.empty()) {
        return "\nNo requests\n";
    }
    for (const string& request : requests) {
        result += request + "\n";
    }
    return result;
}

// Check if the club officer has played on the given day
bool ClubOfficer has_played_on_day(const time_point& date) const {
    for (const auto& day : days_played) {
        if (day == date) {
            return true;
        }
    }
    return false;
}

// Add a played day to the club officer's list of days played
void ClubOfficer add_day_played(const time_point& date) {
    days_played.push_back(date);
}

// Remove a played day from the club officer's list of days played
void ClubOfficer remove_day_played(const time_point& date) {
    auto it = remove_if(days_played.begin(), days_played.end(),
                             [&date](const time_point& d) {
                                 return d == date;
                             });
    days_played.erase(it, days_played.end());
}

// Reset the list of days played
void ClubOfficer reset_days_played() {
    days_played.clear();
}

// Get the skill level of the club officer
string& ClubOfficer get_skill_level() {
    return skill_level_;
}
