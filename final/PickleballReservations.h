// PickleballReservations.h
#pragma once
#include <vector>
#include "User.h"
#include "ClubMember.h"
#include "ClubOfficer.h"
#include "ClubCoach.h"
#include "Schedule.h"
#include "time_utils.h"
#include "DataPersistence.h"
#include <memory>

class PickleballReservations {
public:
    PickleballReservations();

    User* find_user(const std::string& username);
    ClubOfficer* find_officer();
    ClubOfficer* find_officer(const std::string& username);
    void add_user(const std::string& username, const std::string& password, const std::string& lowered_role, const std::string& skill_level);
    void display_schedule() const;
    void show_requests_for_res(const ClubOfficer& officer) const;
    void show_reservations(const User& user) const;
    void reserve_court(const User& user, int court_id, const std::string& start_date_str, const std::string& start_time_str);
    bool delete_reservation(int reservation_id, const User& user);
    bool add_given_user_to_given_reservation(int reservation_id, const User& user);
    bool delete_from_reservation_given_user(int reservation_id, const User& user);
    bool attempt_to_modify_reservation_request(int reservation_id, const User& requester, ClubOfficer& officer);
    void save_to_out_file() const;
    void load_from_in_file();
    void login(const std::string& username, const std::string& password);
    void signup(const std::string& username, const std::string& password, const std::string& lowered_role, const std::string& skill_level);
    void logout();
    bool is_logged_in() const;
    const User* get_logged_in_user() const;
    int get_next_reservation_id() const;

private:
    std::vector<std::shared_ptr<User>> users_;
    int next_reservation_id_;
    Schedule schedule_;
    User* current_logged_user;

    void increment_limit_for_user(const User& user, const time_point& time);
    void decrement_limit_for_user(const User& user, const time_point& time);
};
