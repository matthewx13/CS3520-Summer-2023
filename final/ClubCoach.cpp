#include "ClubCoach.h"

ClubCoach::ClubCoach(const std::string& username, const std::string& password)
    : User(username, password, "ClubCoach"), skill_("Pro") {
}

bool ClubCoach::is_slot_open(const Reservation& reservation) const {
    bool is_two_days = check_two_days(reservation.get_start_time());
    bool is_coach_hours = check_if_coach_available(reservation.get_start_time()) && check_if_coach_available(reservation.get_end_time());
    bool within_7_days = new_time_in_seven_days(reservation.get_start_time());

    return is_two_days && is_coach_hours && within_7_days;
}

std::string& ClubCoach::get_skill_of_member() {
    return skill_;
}
