#pragma once
#include <array>
#include "User.h"
using namespace std;

// The ClubMember class represents a member in a club.
class ClubMember : public User {
public:
    // Constructor for the ClubMember class.
    ClubMember(const std::string& username, const string& password, const string& skill_level);

    // Checks if the member can reserve a slot for a given reservation.
    bool can_reserve_slot(const Reservation& reservation) const override;

    // Checks if the member has played on a given day.
    bool has_played_on_day(const time_point& date) const;

    // Adds a day to the list of days the member has played.
    void add_day_played(const time_point& date);

    // Removes a day from the list of days the member has played.
    void remove_day_played(const time_point& date);

    // Resets the list of days the member has played.
    void reset_days_played();

    // Retrieves the skill level of the member.
    string& get_skill_level() override;

private:
    string skill_level_;             // The skill level of the member.
    vector<time_point> days_played;  // The list of days the member has played.
};
