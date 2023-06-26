#pragma once
#include "User.h"

class ClubCoach : public User {
public:
    ClubCoach(const std::string& username, const std::string& password);

    bool is_slot_open(const Reservation& reservation) const override;
    std::string& get_skill_of_member() override;

private:
    std::string skill_;
};