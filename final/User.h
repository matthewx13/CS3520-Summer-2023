#pragma once
#include <string>
#include "time_utils.h"
#include "Reservation.h"

enum class Role {
    ClubMember,
    ClubOfficer,
    ClubCoach
};

class User {
public:
    User(const std::string& username, const std::string& password, const std::string& role);
    virtual ~User() = default;

    virtual bool is_slot_open(const Reservation& reservation) const = 0;
    virtual bool able_to_edit_res() const;

    bool authenticate(const std::string& password) const;
    const std::string& get_username() const;
    const std::string& get_password() const;
    const std::string& get_role() const;
    virtual std::string& get_skill_of_member() = 0;

protected:
    std::string username_;
    std::string password_;
    std::string role_;
};
