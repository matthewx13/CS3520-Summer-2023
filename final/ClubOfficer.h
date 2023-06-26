#pragma once
#include "ClubMember.h"
#include <array>

class ClubOfficer : public User {
public:
    ClubOfficer(const std::string& username, const std::string& password, const std::string& skill_level);

    bool can_reserve_slot(const Reservation& reservation) const override;
    bool can_modify_reservation() const override;
    void add_request(const std::string& request);
    void remove_request(const std::string& request);
    std::string print_requests() const;
    bool has_played_on_day(const time_point& date) const;
    void add_day_played(const time_point& date);
    void remove_day_played(const time_point& date);
    void reset_days_played();
    std::string& get_skill_level() override;

private:
    std::string skill_level_;
    std::vector<std::string> requests;
    std::vector<time_point> days_played;
};
