#include "User.h"

User::User(const std::string& username, const std::string& password, const std::string& role)
    : username_(username), password_(password), role_(role) {
}

const std::string& User::get_username() const {
    return username_;
}

const std::string& User::get_password() const {
    return password_;
}

const std::string& User::get_role() const {
    return role_;
}

bool User::able_to_edit_res() const {
    return false;
}

bool::User::authenticate(const std::string& password) const {
    return password == password_;
}