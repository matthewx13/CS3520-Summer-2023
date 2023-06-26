#include "time_utils.h"
#include "Reservation.h"

Reservation::Reservation(int id, const std::string& user, const time_point& start_time, const time_point& end_time, const std::vector<std::string>& players)
    : id_(id), user_(user), start_time_(start_time), end_time_(end_time), players_(players) {
}

int Reservation::get_id() const {
    return id_;
}

const std::string& Reservation::get_user() const {
    return user_;
}

const time_point& Reservation::get_start_time() const {
    return start_time_;
}

const time_point& Reservation::get_end_time() const {
    return end_time_;
}

std::string Reservation::to_string() const {
    std::stringstream ss;
    ss << id_ << " | " << user_ << " | " << get_given_string_for_date(start_time_) << " | " << get_given_time_point_time_string(start_time_) << " | ";
    if (!players_.empty()) {
        for (const std::string& player : players_) {
            ss << player << ",";
        }
    }

    ss << std::endl;
    return ss.str();
}

void Reservation::add_user(const std::string& player) {
    players_.push_back(player);
}

void Reservation::remove_user(const std::string& player) {
    players_.erase(std::remove(players_.begin(), players_.end(), player), players_.end());
}

void Reservation::user_who_requested_modification(const std::string& requester) {
    user_ = requester;
}

bool Reservation::user_in_given_reservation(const std::string& user) const {
    return user_ == user || std::find(players_.begin(), players_.end(), user) != players_.end();
}