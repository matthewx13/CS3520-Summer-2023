// ReservationSystem.h
#pragma once
#include <vector>
#include "User.h"
#include "ClubMember.h"
#include "ClubOfficer.h"
#include "ClubCoach.h"
#include "Schedule.h"
#include "time_utils.h"
#include "StorageData.h"
#include <memory>

class PickleballReservationSystem {
public:
    PickleballReservationSystem();

    User* find_user(const std::string& username);
    ClubOfficer* find_officer();
    ClubOfficer* find_officer(const std::string& username);
    void add_user(const std::string& username, const std::string& password, const std::string& lowered_role, const std::string& skill_level);
    void display_schedule() const;
    void view_requests(const ClubOfficer& officer) const;
    void view_reservations(const User& user) const;
    void reserve_court(const User& user, int court_id, const std::string& start_date_str, const std::string& start_time_str);
    bool delete_reservation(int reservation_id, const User& user);
    bool add_user_to_reservation(int reservation_id, const User& user);
    bool remove_user_from_reservation(int reservation_id, const User& user);
    bool request_reservation_modification(int reservation_id, const User& requester, ClubOfficer& officer);
    void save_data_to_file() const;
    void load_data_from_file();
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
    User* logged_in_user_;

    void increment_user_limits(const User& user, const time_point& time);
    void decrement_user_limits(const User& user, const time_point& time);
};
