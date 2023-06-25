#include "ClubCoach.h"
using namespace std;

// Constructor for the ClubCoach class.
ClubCoach::ClubCoach(const string& username, const string& password)
    : User(username, password, "ClubCoach"), skill_level_("Pro") {
}

// Checks if the ClubCoach can reserve a slot for a given reservation.
bool ClubCoach::can_reserve_slot(const Reservation& reservation) const {
    bool two_days = two_days_in_advance(reservation.get_start_time());
    bool coach_hours = within_coach_hours(reservation.get_start_time()) && within_coach_hours(reservation.get_end_time());
    bool within_7_days = within_seven_days(reservation.get_start_time());

    return two_days && coach_hours && within_7_days;
}

// Retrieves the skill level of the ClubCoach.
string& ClubCoach::get_skill_level() {
    return skill_level_;
}
