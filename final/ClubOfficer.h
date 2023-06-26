#pragma once
#include "ClubMember.h"
#include <array>

class ClubOfficer : public User {
public:
    ClubOfficer(const std::string& username, const std::string& password, const std::string& skill_level);

    bool is_slot_open(const Reservation& reservation) const override;
    bool able_to_edit_res() const override;
    void append_request(const std::string& request);
    void delete_request(const std::string& request);
    std::string print_requests() const;
    bool played_on_day(const time_point& date) const;
    void add_day_member_played(const time_point& date);
    void remove_day_played(const time_point& date);
    void clear_days_played();
    std::string& get_skill_of_member() override;

private:
    std::string skill_;
    std::vector<std::string> requests;
    std::vector<time_point> days_played;
};
