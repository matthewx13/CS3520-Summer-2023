#include "time_utils.h"
#include "Schedule.h"

Schedule::Schedule() {
}

void Schedule::add_reservation_to_court(int court_id, const Reservation& reservation) {
    if (court_id < 1 || court_id > 3) {
        return;
    }

    Court& court = courts_[court_id - 1];
    if (court.is_slot_available(reservation)) {
        court.reserve_slot(reservation);
        std::cout << "Reservation " << reservation.get_id() << " added to court " << court_id << std::endl;
    } else {
        std::cout << "Reservation not available." << std::endl;
    }
}

bool Schedule::reserve_slot(int court_id, const Reservation& reservation, const User& user) {
    if (court_id < 1 || court_id > 3) {
        return false;
    }

    if (user.can_reserve_slot(reservation)) {
        Court& court = courts_[court_id - 1];
        if (court.is_slot_available(reservation)) {
            court.reserve_slot(reservation);
            return true;
        }
    }
    return false;
}

bool Schedule::add_user_to_reservation(int reservation_id, const User& user) {
    for (Court& court : courts_) {
        std::vector<Reservation>& reservations = court.get_reservations();
        for (Reservation& r : reservations) {
            if (r.get_id() == reservation_id) {
                r.add_user(user.get_username());
                return true;
            }
        }
    }
    return false;
}

bool Schedule::remove_user_from_reservation(int reservation_id, const User& user) {
    // loop through courts and reservations to find reservation
    for (Court& court : courts_) {
        std::vector<Reservation>& reservations = court.get_reservations();
        for (Reservation& r : reservations) {
            if (r.get_id() == reservation_id) {
                r.remove_user(user.get_username());
                return true;
            }
        }
    }
    return false;
}

bool Schedule::cancel_reservation(int reservation_id, const User& user) {
    // loop through courts and reservations to find reservation
    for (Court& court : courts_) {
        std::vector<Reservation>& reservations = court.get_reservations();
        for (Reservation& r : reservations) {
            if (r.get_id() == reservation_id) {
                // only ClubOfficers can cancel other users' reservations
                if (user.get_role() != "ClubOfficer" && r.get_user() != user.get_username()) {
                    return false;
                }
                court.cancel_reservation(reservation_id);
                return true;
            }
        }
    }
    return false;
}

bool Schedule::request_reservation_cancellation(int reservation_id, const User& requester, ClubOfficer& officer) {
    // add requests to officers list of requests
    std::string requester_username = requester.get_username();
    std::string request = "Request to cancel reservation " + std::to_string(reservation_id) + " from " + requester_username;
    officer.add_request(request);

    return false;
}

std::string Schedule::display_daily_schedule(const std::chrono::system_clock::time_point& date) const {
    std::string schedule;
    // print today's date and time
    schedule += "\nSchedule for " + get_date_string(date) + "\n";
    schedule += "Opening hours: 6:00 - 12:00\n";
    schedule += "Coaching hours: 9:00 - 12:00 (+15:00 - 18:00 on weekdays and Sundays)\n";
    schedule += "Now: " + get_time_string(date) + "\n\n";
    // print each court's schedule
    for (int i = 0; i < 3; ++i) {
        schedule += "Court " + std::to_string(i + 1) + ":\n";
        const auto& reservations = courts_[i].get_reservations();
        for (const Reservation& r : reservations) {
            if (get_day_from_time_point(r.get_start_time()) == get_day_from_time_point(date)) {
                schedule += r.to_string() + "\n";
            }
        }
        schedule += "\n";
    }
    return schedule;
}

std::string Schedule::print_user_reservations(const User& user) const {
    std::string reservations;
    reservations += "\nReservations for " + user.get_username() + ":\n";
    // loop through courts and reservations to find reservation
    for (const Court& court : courts_) {
        const std::vector<Reservation>& court_reservations = court.get_reservations();
        for (const Reservation& r : court_reservations) {
            // if user is in reservation and its in the future print it
            if (r.is_user_in_reservation(user.get_username()) &&  is_future_date(r.get_start_time())) {
                reservations += r.to_string() + "\n";
            }
        }
    }
    return reservations;
}

const std::array<Court, 3>& Schedule::get_courts() const {
    return courts_;
}

const Reservation* Schedule::get_reservation(int reservation_id) const {
    for (const Court& court : courts_) {
        const std::vector<Reservation>& reservations = court.get_reservations();
        for (const Reservation& r : reservations) {
            if (r.get_id() == reservation_id) {
                return &r;
            }
        }
    }
    return nullptr;
}
