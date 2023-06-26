#pragma once
#include <array>
#include <string>
#include "Court.h"
#include "Reservation.h"
#include "User.h"
#include "ClubOfficer.h"
#include "time_utils.h"

class Schedule {
public:
    Schedule();


    void add_reservation_to_court(int court_id, const Reservation& reservation);
    bool reserve_reservation(int court_id, const Reservation& reservation,  const User& user);
    bool add_user_to_reservation(int reservation_id, const User& user);
    bool delete_from_reservation_given_user(int reservation_id, const User& user);
    bool delete_res(int reservation_id, const User& user);
    bool request_reservation_cancellation(int reservation_id, const User& requester, ClubOfficer& officer);
    std::string display_daily_schedule(const std::chrono::system_clock::time_point& date) const;
    std::string print_user_reservations(const User& user) const;
    const std::array<Court, 3>& get_courts() const;
    const Reservation* get_reservation(int reservation_id) const;

private:
    std::array<Court, 3> courts_;
};
