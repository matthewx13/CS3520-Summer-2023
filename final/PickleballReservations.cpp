#include "PickleballReservations.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

PickleballReservations::PickleballReservations()
    : users_(), next_reservation_id_(1), schedule_(), current_logged_user(nullptr) {

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

            return dynamic_cast<ClubOfficer*>(user_ptr.get());
        }
    }
    return nullptr;

    
}

void PickleballReservations::add_user(const std::string& username, const std::string& password, const std::string& role, const std::string& skill_level) {
    if (find_user(username) != nullptr) {
        std::cout << "User exists" << std::endl;
        return;
    }
    
    if (role == "member") {
        users_.push_back(std::make_shared<ClubMember>(username, password, skill_level));
    } else if (role == "officer") {
        users_.push_back(std::make_shared<ClubOfficer>(username, password, skill_level));
    } else if (role == "coach") {
        users_.push_back(std::make_shared<ClubCoach>(username, password));
    } else {
        std::cout << "Not valid" << std::endl;
    }
}

ClubOfficer* PickleballReservations::find_officer(const std::string& username) {
    for (const auto& user_ptr : users_) {
        if (user_ptr->get_username() == username && user_ptr->get_role() == "officer") {

            return dynamic_cast<ClubOfficer*>(user_ptr.get());
        }
    }
    return nullptr;
}



void PickleballReservations::decrement_limit_for_user(const User& user, const time_point& time) { 
    if (user.get_role() == "officer") {
        dynamic_cast<ClubOfficer*>(find_user(user.get_username()))->remove_day_played(time);
        dynamic_cast<ClubOfficer*>(find_user(user.get_username()))->remove_day_played(time);
    } else if (user.get_role() == "member") {
        dynamic_cast<ClubMember*>(find_user(user.get_username()))->remove_day_played(time);
        dynamic_cast<ClubMember*>(find_user(user.get_username()))->remove_day_played(time);
    }
}

void PickleballReservations::increment_limit_for_user(const User& user, const time_point& time) {
    if (user.get_role() == "officer") {
        dynamic_cast<ClubOfficer*>(find_user(user.get_username()))->add_day_member_played(time);
        dynamic_cast<ClubOfficer*>(find_user(user.get_username()))->add_day_member_played(time);
    } else if (user.get_role() == "member") {
        dynamic_cast<ClubMember*>(find_user(user.get_username()))->add_day_member_played(time);
        dynamic_cast<ClubMember*>(find_user(user.get_username()))->add_day_member_played(time);
    }
}



void PickleballReservations::show_requests_for_res(const ClubOfficer& officer) const {
    std::cout << officer.print_requests() << std::endl;
}

void PickleballReservations::show_reservations(const User& user) const {
    std::cout << schedule_.print_user_reservations(user) << std::endl;
}

void PickleballReservations::display_schedule() const {
    std::cout << schedule_.display_daily_schedule(std::chrono::system_clock::now()) << std::endl;
}



bool PickleballReservations::delete_reservation(int reservation_id, const User& user) {
    const Reservation* res = schedule_.get_reservation(reservation_id);
    if (res == nullptr) {
        std::cout << "Reservation " << reservation_id << " doesn't exist." << std::endl;
        std::cout << "Try again." << std::endl;
        return false;
    }

    bool cancel = schedule_.delete_res(reservation_id, user);
    
    if (!cancel) {

        std::cout << "Reservation " << reservation_id << " doesn't exist." << std::endl;
        std::cout << "Try again." << std::endl;
        return false;
        
    } else {
        std::cout << "Reservation " << reservation_id << " cancelled!" << std::endl;
        return true;
    }

    decrement_limit_for_user(user, res->get_start_time());
}

bool PickleballReservations::add_given_user_to_given_reservation(int reservation_id, const User& user) {
    const Reservation* res = schedule_.get_reservation(reservation_id);
    if (res == nullptr) {
        std::cout << "Reservation " << reservation_id << " doesn't exist." << std::endl;
        std::cout << "Try again." << std::endl;
        return false;
    }

    bool join = schedule_.add_given_user_to_given_reservation(reservation_id, user);

    if (!join) {
        std::cout << "User " << user.get_username() << " not added " << reservation_id << std::endl;
        std::cout << "Try again." << std::endl;
        return false;

        
    } else {
        std::cout << "User " << user.get_username() << " added " << reservation_id << std::endl;
        return true;
    }

    increment_limit_for_user(user, res->get_start_time());
}

void PickleballReservations::reserve_court(const User& user, int court_id,  const std::string& start_date_str, const std::string& start_time_str) {
    time_point start = turn_given_string_to_time_point(start_date_str, start_time_str);

    time_point end = start + std::chrono::minutes(30);

    if (start < std::chrono::system_clock::now()) {
        std::cout << "Start time too early" << std::endl;
        std::cout << "Try again." << std::endl;
        return;
    }

    Reservation new_reservation(next_reservation_id_, user.get_username(), start, end);

    std::cout << "Details:" << std::endl;
    std::cout << new_reservation.to_string() << std::endl;
    std::cout << "Confirm? (y/n): ";
    std::string confirm;
    std::cin >> confirm;
    if (confirm != "y") {
        std::cout << "Reservation cancelled." << std::endl;
        return;
    }

    if (user.is_slot_open(new_reservation)) {
        schedule_.have_court_add_reservation(court_id, new_reservation);
        next_reservation_id_++;
    } else {
        std::cout << "Reservation " << next_reservation_id_ << " not available." << std::endl;
    }


    increment_limit_for_user(user, start);
}

bool PickleballReservations::delete_from_reservation_given_user(int reservation_id, const User& user) {
    const Reservation* res = schedule_.get_reservation(reservation_id);
    if (res == nullptr) {
        std::cout << "Reservation " << reservation_id << " doesn't exist." << std::endl;
        std::cout << "Try again." << std::endl;
        return false;
    }

    bool removing = schedule_.delete_from_reservation_given_user(reservation_id, user);

    if (removing) {
        std::cout << "User " << user.get_username() << " deleted from reservation " << reservation_id << std::endl;
        return true;
    } else {
        std::cout << "User " << user.get_username() << " not deleted from reservation " << reservation_id << std::endl;
        return false;
    }


    decrement_limit_for_user(user, res->get_start_time());
}

bool PickleballReservations::attempt_to_modify_reservation_request(int reservation_id, const User& requester, ClubOfficer& officer) {
   
    if (requester.get_role() == "ClubOfficer") {
        return false;
    }

   
    if (officer.get_role() != "ClubOfficer") {
        return false;
    }

    bool requesting = schedule_.request_reservation_cancellation(reservation_id, requester, officer);

    if (requesting) {
        std::cout << "Request to change reservation " << reservation_id << " sent " << officer.get_username() << std::endl;
        return true;
    } else {
        std::cout << "Request to change reservation " << reservation_id << " not sent " << officer.get_username() << std::endl;
        return false;
    }
}

void PickleballReservations::login(const std::string& username, const std::string& password) {
 
    std::cout << "Logging in" << std::endl;
  
    User* user = find_user(username);
 
    if (user == nullptr) {
        std::cout << "User doesn't exist" << std::endl;
    } else {
        
        if (user->authenticate(password)) {
            current_logged_user = user;
        }
    }
}


const User* PickleballReservations::get_logged_in_user() const {
    return current_logged_user;
}

void PickleballReservations::signup(const std::string& username, const std::string& password, const std::string& lowered_role, const std::string& skill_level) {
    if (find_user(username) != nullptr) {
        std::cout << "Username taken" << std::endl;
        return;
    }
  
    add_user(username, password, lowered_role, skill_level);
   
    login(username, password);
}

void PickleballReservations::logout() {
    std::cout << "Seeya!" << std::endl;
    current_logged_user = nullptr;
}

int PickleballReservations::get_next_reservation_id() const {
    return next_reservation_id_;
}

bool PickleballReservations::is_logged_in() const {
    return current_logged_user != nullptr;
}


void PickleballReservations::load_from_in_file() {
    DataPersistence::load_from_in_file("pickleball_users.txt", "pickleball_reservations.txt", "pickleball_reservation_id.txt", users_, next_reservation_id_, schedule_);
}

void PickleballReservations::save_to_out_file() const {
    DataPersistence::save_to_out_file("pickleball_users.txt", "pickleball_reservations.txt", "pickleball_reservation_id.txt", users_, next_reservation_id_, schedule_);
}
