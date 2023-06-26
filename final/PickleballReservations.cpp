#include "PickleballReservations.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

PickleballReservations::PickleballReservations()
    : users_(), next_reservation_id_(1), schedule_(), current_logged_user(nullptr) {
    // Load data from file (if any)
    load_from_in_file();
}

User* PickleballReservations::find_user(const std::string& username) {
    for (const auto& user_ptr : users_) {
        if (user_ptr->get_username() == username) {
            return user_ptr.get();
        }
    }
    return nullptr;
}

ClubOfficer* PickleballReservations::find_officer() {
    for (const auto& user_ptr : users_) {
        if (user_ptr->get_role() == "officer") {
            // return a non-const pointer to the officer
            return dynamic_cast<ClubOfficer*>(user_ptr.get());
        }
    }
    return nullptr;
}

ClubOfficer* PickleballReservations::find_officer(const std::string& username) {
    for (const auto& user_ptr : users_) {
        if (user_ptr->get_username() == username && user_ptr->get_role() == "officer") {
            // return a non-const pointer to the officer
            return dynamic_cast<ClubOfficer*>(user_ptr.get());
        }
    }
    return nullptr;
}

void PickleballReservations::add_user(const std::string& username, const std::string& password, const std::string& lowered_role, const std::string& skill_level) {
    if (find_user(username) != nullptr) {
        std::cout << "User already exists" << std::endl;
        return;
    }
    
    if (lowered_role == "member") {
        users_.push_back(std::make_shared<ClubMember>(username, password, skill_level));
    } else if (lowered_role == "officer") {
        users_.push_back(std::make_shared<ClubOfficer>(username, password, skill_level));
    } else if (lowered_role == "coach") {
        users_.push_back(std::make_shared<ClubCoach>(username, password));
    } else {
        std::cout << "Invalid role" << std::endl;
    }
}

void PickleballReservations::increment_limit_for_user(const User& user, const time_point& time) {
    if (user.get_role() == "member") {
        dynamic_cast<ClubMember*>(find_user(user.get_username()))->add_day_member_played(time);
        dynamic_cast<ClubMember*>(find_user(user.get_username()))->add_day_member_played(time);
    } else if (user.get_role() == "officer") {
        dynamic_cast<ClubOfficer*>(find_user(user.get_username()))->add_day_member_played(time);
        dynamic_cast<ClubOfficer*>(find_user(user.get_username()))->add_day_member_played(time);
    }
}

void PickleballReservations::decrement_limit_for_user(const User& user, const time_point& time) { 
    if (user.get_role() == "member") {
        dynamic_cast<ClubMember*>(find_user(user.get_username()))->remove_day_played(time);
        dynamic_cast<ClubMember*>(find_user(user.get_username()))->remove_day_played(time);
    } else if (user.get_role() == "officer") {
        dynamic_cast<ClubOfficer*>(find_user(user.get_username()))->remove_day_played(time);
        dynamic_cast<ClubOfficer*>(find_user(user.get_username()))->remove_day_played(time);
    }
}

void PickleballReservations::display_schedule() const {
    std::cout << schedule_.display_daily_schedule(std::chrono::system_clock::now()) << std::endl;
}

void PickleballReservations::show_requests_for_res(const ClubOfficer& officer) const {
    std::cout << officer.print_requests() << std::endl;
}

void PickleballReservations::show_reservations(const User& user) const {
    std::cout << schedule_.print_user_reservations(user) << std::endl;
}

void PickleballReservations::reserve_court(const User& user, int court_id,  const std::string& start_date_str, const std::string& start_time_str) {
    // convert start_time
    time_point start_time = string_to_time_point(start_date_str, start_time_str);
    // set end_time to 30 minutes after start_time
    time_point end_time = start_time + std::chrono::minutes(30);

    // if start_time is before now, return false
    if (start_time < std::chrono::system_clock::now()) {
        std::cout << "Start time is before now." << std::endl;
        std::cout << "Please try again." << std::endl;
        return;
    }

    // create a new reservation
    Reservation new_reservation(next_reservation_id_, user.get_username(), start_time, end_time);

    // print reservation details and confirm with user
    std::cout << "Reservation details:" << std::endl;
    std::cout << new_reservation.to_string() << std::endl;
    std::cout << "Confirm? (y/n): ";
    std::string confirm;
    std::cin >> confirm;
    if (confirm != "y") {
        std::cout << "Reservation cancelled." << std::endl;
        return;
    }

    if (user.is_slot_open(new_reservation)) {
        // add reservation to schedule
        schedule_.add_reservation_to_court(court_id, new_reservation);
        next_reservation_id_++;
    } else {
        std::cout << "Reservation " << next_reservation_id_ << " not available for your privileges." << std::endl;
    }

    // if user is member or officer, increment their daily/weekly limits
    increment_limit_for_user(user, start_time);
}

bool PickleballReservations::delete_reservation(int reservation_id, const User& user) {
    // get reservation
    const Reservation* r = schedule_.get_reservation(reservation_id);
    if (r == nullptr) {
        std::cout << "Reservation " << reservation_id << " not found." << std::endl;
        std::cout << "Please try again." << std::endl;
        return false;
    }

    bool cancellation = schedule_.delete_res(reservation_id, user);
    
    if (cancellation) {
        std::cout << "Reservation " << reservation_id << " cancelled!" << std::endl;
        return true;
    } else {
        std::cout << "Reservation " << reservation_id << " not found." << std::endl;
        std::cout << "Please try again." << std::endl;
        return false;
    }

    // if user is member or officer, decrement their daily/weekly limits
    decrement_limit_for_user(user, r->get_start_time());
}

bool PickleballReservations::add_user_to_reservation(int reservation_id, const User& user) {
    // get reservation
    const Reservation* r = schedule_.get_reservation(reservation_id);
    if (r == nullptr) {
        std::cout << "Reservation " << reservation_id << " not found." << std::endl;
        std::cout << "Please try again." << std::endl;
        return false;
    }

    bool joining = schedule_.add_user_to_reservation(reservation_id, user);

    if (joining) {
        std::cout << "User " << user.get_username() << " added to reservation " << reservation_id << std::endl;
        return true;
    } else {
        std::cout << "User " << user.get_username() << " not added to reservation " << reservation_id << std::endl;
        std::cout << "Please try again." << std::endl;
        return false;
    }

    // if user is member or officer, increment their daily/weekly limits
    increment_limit_for_user(user, r->get_start_time());
}

bool PickleballReservations::delete_from_reservation_given_user(int reservation_id, const User& user) {
    // get reservation
    const Reservation* r = schedule_.get_reservation(reservation_id);
    if (r == nullptr) {
        std::cout << "Reservation " << reservation_id << " not found." << std::endl;
        std::cout << "Please try again." << std::endl;
        return false;
    }

    bool removing = schedule_.delete_from_reservation_given_user(reservation_id, user);

    if (removing) {
        std::cout << "User " << user.get_username() << " removed from reservation " << reservation_id << std::endl;
        return true;
    } else {
        std::cout << "User " << user.get_username() << " not removed from reservation " << reservation_id << std::endl;
        return false;
    }

    // if user is member or officer, decrement their daily/weekly limits
    decrement_limit_for_user(user, r->get_start_time());
}

bool PickleballReservations::request_reservation_modification(int reservation_id, const User& requester, ClubOfficer& officer) {
    // if requester get_role() is a ClubOfficer, return false
    if (requester.get_role() == "ClubOfficer") {
        return false;
    }

    // if officer get_role() is not a ClubOfficer, return false
    if (officer.get_role() != "ClubOfficer") {
        return false;
    }

    bool requesting = schedule_.request_reservation_cancellation(reservation_id, requester, officer);

    if (requesting) {
        std::cout << "Request to modify reservation " << reservation_id << " sent to officer " << officer.get_username() << std::endl;
        return true;
    } else {
        std::cout << "Request to modify reservation " << reservation_id << " not sent to officer " << officer.get_username() << std::endl;
        return false;
    }
}

void PickleballReservations::save_to_out_file() const {
    DataPersistence::save_to_out_file("pickleball_users.txt", "pickleball_reservations.txt", "pickleball_reservation_id.txt", users_, next_reservation_id_, schedule_);
}

void PickleballReservations::load_from_in_file() {
    DataPersistence::load_from_in_file("pickleball_users.txt", "pickleball_reservations.txt", "pickleball_reservation_id.txt", users_, next_reservation_id_, schedule_);
}

void PickleballReservations::login(const std::string& username, const std::string& password) {
    // print logging in
    std::cout << "Logging in..." << std::endl;
    // find the user
    User* user = find_user(username);
    // If user is not found, return
    if (user == nullptr) {
        std::cout << "User not found" << std::endl;
    } else {
        // make sure password is correct
        if (user->authenticate(password)) {
            current_logged_user = user;
        }
    }
}

// signup(username, password, lowered role, skill_level)
void PickleballReservations::signup(const std::string& username, const std::string& password, const std::string& lowered_role, const std::string& skill_level) {
    // check if username is already taken
    if (find_user(username) != nullptr) {
        std::cout << "Username already taken" << std::endl;
        return;
    }
    // add the user
    add_user(username, password, lowered_role, skill_level);
    // login the user
    login(username, password);
}

void PickleballReservations::logout() {
    std::cout << "Goodbye!" << std::endl;
    current_logged_user = nullptr;
}

bool PickleballReservations::is_logged_in() const {
    return current_logged_user != nullptr;
}

const User* PickleballReservations::get_logged_in_user() const {
    return current_logged_user;
}

int PickleballReservations::get_next_reservation_id() const {
    return next_reservation_id_;
}