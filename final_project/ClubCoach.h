#pragma once
#include "User.h"

class ClubCoach : public User {
public:
    ClubCoach(const std::string& username, const std::string& password);

    bool can_reserve_slot(const Reservation& reservation) const override;
    std::string& get_skill_level() override;

private:
    std::string skill_level_;
};
