#pragma once
#include "User.h"
using namespace std;

// The ClubCoach class represents a coach in a club.
class ClubCoach : public User {
public:
    // Constructor for the ClubCoach class.
    ClubCoach(const string& username, const string& password);

    // Checks if the coach can reserve a slot for a given reservation.
    bool can_reserve_slot(const Reservation& reservation) const override;

    // Retrieves the skill level of the coach.
    string& get_skill_level() override;

private:
    string skill_level_; // The skill level of the coach.
};
