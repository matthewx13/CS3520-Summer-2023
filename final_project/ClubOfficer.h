#pragma once
#include "ClubMember.h"
#include <array>
using namespace std;
class ClubOfficer : public User {
public:
    ClubOfficer(const string& username, const string& password, const string& skill_level);

    bool can_reserve_slot(const Reservation& reservation) const override;
    bool can_modify_reservation() const override;
    void add_request(const string& request);
    void remove_request(const string& request);
    string print_requests() const;
    bool has_played_on_day(const time_point& date) const;
    void add_day_played(const time_point& date);
    void remove_day_played(const time_point& date);
    void reset_days_played();
    string& get_skill_level() override;

private:
    string skill_level_;
    vector<std::string> requests;
    vector<time_point> days_played;
};
