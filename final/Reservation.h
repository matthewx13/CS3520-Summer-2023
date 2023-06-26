#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "time_utils.h"

class Reservation {
public:
    Reservation(int id, const std::string& user, const time_point& start_time, const time_point& end_time, const std::vector<std::string>& players = {});

    int get_id() const;
    const std::string& get_user() const;
    const time_point& get_start_time() const;
    const time_point& get_end_time() const;
    std::string to_string() const;
    void add_user(const std::string& player);
    void remove_user(const std::string& player);
    void user_who_requested_modification(const std::string& requester);
    bool user_in_given_reservation(const std::string& user) const;

private:
    int id_;
    std::string user_;
    time_point start_time_;
    time_point end_time_;
    std::vector<std::string> players_;
};

#endif
