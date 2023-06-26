#include "time_utils.h"
#include "Schedule.h"

Schedule::Schedule() {
}

void Schedule::have_court_add_reservation(int court_id, const Reservation& reservation) {
    if (court_id < 1 || court_id > 3) {
        return;
    }

    Court& court = courts_[court_id - 1];
    if (!court.reservation_is_free(reservation)) {

        std::cout << "No reservations available" << std::endl;

       
    } else {
         court.reserve_reservation(reservation);
        std::cout << "Reservation " << reservation.get_id() << " reserved to court " << court_id << std::endl;
    }
}


bool Schedule::add_given_user_to_given_reservation(int reservation_id, const User& user) {
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

bool Schedule::reserve_reservation(int court_id, const Reservation& reservation, const User& user) {
    if (court_id < 1 || court_id > 3) {
        return false;
    }

    if (user.is_slot_open(reservation)) {
        Court& court = courts_[court_id - 1];
        if (court.reservation_is_free(reservation)) {
            court.reserve_reservation(reservation);
            return true;
        }
    }
    return false;
}


bool Schedule::delete_res(int reservation_id, const User& user) {
    for (Court& court : courts_) {
        std::vector<Reservation>& reservations = court.get_reservations();
        for (Reservation& r : reservations) {
            if (r.get_id() == reservation_id) {
                if (user.get_role() != "ClubOfficer" && r.get_user() != user.get_username()) {
                    return false;
                }
                court.delete_res(reservation_id);
                return true;
            }
        }
    }
    return false;
}

bool Schedule::delete_from_reservation_given_user(int reservation_id, const User& user) {
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

bool Schedule::request_reservation_cancellation(int reservation_id, const User& requester, ClubOfficer& officer) {
    // add requests to officers list of requests
    std::string requester_username = requester.get_username();
    std::string request = "Request to cancel reservation " + std::to_string(reservation_id) + " from " + requester_username;
    officer.append_request(request);

    return false;
}

std::string Schedule::display_daily_schedule(const std::chrono::system_clock::time_point& date) const {
    std::string schedule;
    // print today's date and time
    schedule += "\nSchedule for " + get_given_string_for_date(date) + "\n";
    schedule += "Opening hours: 6:00 - 12:00\n";
    schedule += "Coaching hours: 9:00 - 12:00 (+15:00 - 18:00 on weekdays and Sundays)\n";
    schedule += "Now: " + get_given_time_point_time_string(date) + "\n\n";
    // print each court's schedule
    for (int i = 0; i < 3; ++i) {
        schedule += "Court " + std::to_string(i + 1) + ":\n";
        const auto& reservations = courts_[i].get_reservations();
        for (const Reservation& r : reservations) {
            if (get_day_from_given_time(r.get_start_time()) == get_day_from_given_time(date)) {
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
            if (r.user_in_given_reservation(user.get_username()) &&  future_date_valid(r.get_start_time())) {
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