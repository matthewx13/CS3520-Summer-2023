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

    virtual bool can_reserve_slot(const Reservation& reservation) const = 0;
    virtual bool can_modify_reservation() const;

    bool authenticate(const std::string& password) const;
    const std::string& get_username() const;
    const std::string& get_password() const;
    const std::string& get_role() const;
    virtual std::string& get_skill_level() = 0;

protected:
    std::string username_;
    std::string password_;
    std::string role_;
};
