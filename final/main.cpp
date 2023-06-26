#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <limits>
#include "PickleballReservations.h"

void display_menu(const std::string& role) {
    
    if (role == "ClubOfficer") {
        std::cout << "\n1. View today's schedule\n"
                     "2. Reserve court\n"
                     "3. Delete reservation\n"
                     "4. Add user to reservation\n"
                     "5. Remove user from reservation\n"
                     "6. View Reservations\n"
                     "7. View requests\n"
                     "8. Logout\n"
                     "Enter your choice: ";
        return;
    } else if (role == "ClubMember") {
        std::cout << "\n1. View today's schedule\n"
                     "2. Reserve court\n"
                     "3. Delete my reservations\n"
                     "4. Join reservation\n"
                     "5. Remove yourself from reservation\n"
                     "6. Request officer to delete or modify reservation\n"
                     "7. View Reservations\n"
                     "8. Logout\n"
                     "Enter your choice: ";
        return;
    } else if (role == "ClubCoach") {
        std::cout << "\n1. View today's schedule\n"
                     "2. Reserve court\n"
                     "3. Delete my reservations\n"
                     "4. Add user to reservation\n"
                     "5. Request officer to delete or modify reservation\n"
                     "6. View Reservations\n"
                     "7. Logout\n"
                     "Enter your choice: ";
        return;
    }
}

void display_login_menu() {
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Sign up" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

void login(PickleballReservations& system);
void signup(PickleballReservations& system);

void reserve_court(PickleballReservations& system, const User& user);
void delete_reservation(PickleballReservations& system, const User& user);
void join_reservation(PickleballReservations& system, const User& user);
void add_reservation_from_user(PickleballReservations& system);
void delete_from_reservation_current_user(PickleballReservations& system, const User& user);
void delete_from_reservation_given_user(PickleballReservations& system);
void ask_officer_change_reservation(PickleballReservations& system, const User& user);

void officer_menu(PickleballReservations& system);
void member_menu(PickleballReservations& system);
void coach_menu(PickleballReservations& system);

void handle_menu_response(const std::string role, PickleballReservations& system);

void get_user(PickleballReservations& system, User*& user) {
    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;
    user = system.find_user(username);
}

void login(PickleballReservations& system) {
    std::string username;
    std::string password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;
    system.login(username, password);
}

void signup(PickleballReservations& system) {
    std::string username, role, lowered_role, skill_level, password1, password2;
    std::cout << "Enter username: ";
    std::cin >> username;
    do {
        std::cout << "Enter password: ";
        std::cin >> password1;
        std::cout << "Confirm password: ";
        std::cin >> password2;
        if (password1 != password2) {
            std::cout << "Passwords do not match. Please try again." << std::endl;
        }
    } while (password1 != password2);
    
    do {
        std::cout << "Enter role (member, officer, coach): ";
        std::cin >> role;
        lowered_role = role;
        std::transform(lowered_role.begin(), lowered_role.end(), lowered_role.begin(), ::tolower);
        if (lowered_role == "member" || lowered_role == "officer") {
            std::cout << "Enter skill level (A, B, C): ";
            std::cin >> skill_level;
        }
    } while (lowered_role != "member" && lowered_role != "officer" && lowered_role != "coach");
    system.signup(username, password1, lowered_role, skill_level);
}

void reserve_court(PickleballReservations& system, const User& user) {
    int court_id;
    std::string start_time_str, start_date_str;

    do {
        std::cout << "Enter court ID (1-3): ";
        std::cin >> court_id;
    } while (court_id < 1 || court_id > 3);


    std::string role = user.get_role();
    std::cout << "Available times: " << std::endl;
    if (role == "ClubOfficer") {
        std::cout << "18:00 - 21:00" << std::endl;
    } else if (role == "ClubMember") {
        std::cout << "6:00 - 00:00" << std::endl;
    } else if (role == "ClubCoach") {
        std::cout << "Two days in advance: 9:00 - 12:00" << std::endl;
        std::cout << "Weekdays + Sundays: 15:00 - 18:00" << std::endl;
    }
    std::cout << "Up to 7 days from now." << std::endl;
    do {
        std::cout << "Enter start date and time (format: YYYY-MM-DD HH:MM): ";
        std::cin >> start_date_str >> start_time_str;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!is_given_date_valid(start_date_str, start_time_str));


    system.reserve_court(user, court_id, start_date_str, start_time_str);
}

void delete_reservation(PickleballReservations& system, const User& user) {
    int reservation_id;
    std::cout << "Enter reservation ID: ";
    std::cin >> reservation_id;
    system.delete_reservation(reservation_id, user);
}

void join_reservation(PickleballReservations& system, const User& user) {
    int reservation_id;
    std::cout << "Enter reservation ID: ";
    std::cin >> reservation_id;
    system.add_given_user_to_given_reservation(reservation_id, user);
}

void add_reservation_from_user(PickleballReservations& system) {
    // get reservation id and user username to add
    int reservation_id;
    std::string username;

    std::cout << "Enter reservation ID: ";
    std::cin >> reservation_id;
    std::cout << "Enter username to add: ";
    std::cin >> username;
    
 
    User* user = system.find_user(username);
  
    system.add_given_user_to_given_reservation(reservation_id, *user);
}

void delete_from_reservation_current_user(PickleballReservations& system, const User& user) {
    int reservation_id;
    std::cout << "Enter reservation ID: ";
    std::cin >> reservation_id;
    system.delete_from_reservation_given_user(reservation_id, user);
}

void delete_from_reservation_given_user(PickleballReservations& system) {
    
    int reservation_id;
    std::string username;
    std::cout << "Enter reservation ID: ";
    std::cin >> reservation_id;
    std::cout << "Enter username to remove: ";
    std::cin >> username;
    User* user = system.find_user(username);
    system.delete_from_reservation_given_user(reservation_id, *user);
}

void ask_officer_change_reservation(PickleballReservations& system, const User& user) {

    std::string officer_username;
    int reservation_id;
    ClubOfficer* officer;

    std::cout << "Enter officer's username or enter \"any\" to get any officer: ";
    std::cin >> officer_username;
    if (officer_username == "any") {
        officer = system.find_officer();
    } else {
        officer = system.find_officer(officer_username);
    }
   
    std::cout << "Enter reservation ID: ";
    std::cin >> reservation_id;
    system.attempt_to_modify_reservation_request(reservation_id, user, *officer);
}

void officer_menu(PickleballReservations& system) {
    int choice;
    std::cin >> choice;

    const User* user = system.get_logged_in_user();
    const ClubOfficer* officer = dynamic_cast<const ClubOfficer*>(user);

    switch (choice) {
        case 1:
            system.display_schedule();
            break;
        case 2:
            reserve_court(system, *user);
            break;
        case 3:
            delete_reservation(system, *user);
            break;
        case 4:
            add_reservation_from_user(system);
            break;
        case 5:
            delete_from_reservation_given_user(system);
            break;
        case 6:
            system.show_reservations(*user);
            break;
        case 7:
            system.show_requests_for_res(*officer);
            break;
        case 8:
            system.logout();
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
    }
}

void member_menu(PickleballReservations& system) {
    int choice;
    std::cin >> choice;

    const User* user = system.get_logged_in_user();

    switch (choice) {
        case 1:
            system.display_schedule();
            break;
        case 2:
            reserve_court(system, *user);
            break;
        case 3:
            delete_reservation(system, *user);
            break;
        case 4:
            join_reservation(system, *user);
            break;
        case 5:
            delete_from_reservation_current_user(system, *user);
            break;
        case 6:
            ask_officer_change_reservation(system, *user);
            break;
        case 7:
            system.show_reservations(*user);
            break;
        case 8:
            system.logout();
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
    }
}

void coach_menu(PickleballReservations& system) {
    int choice;
    std::cin >> choice;

    const User* user = system.get_logged_in_user();

    switch (choice) {
        case 1:
            system.display_schedule();
            break;
        case 2:
            reserve_court(system, *user);
            break;
        case 3:
            delete_reservation(system, *user);
            break;
        case 4:
            add_reservation_from_user(system);
            break;
        case 5:
            ask_officer_change_reservation(system, *user);
            break;
        case 6:
            system.show_reservations(*user);
            break;
        case 7:
            system.logout();
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
    }   
}

void handle_menu_response(const std::string role, PickleballReservations& system) {
        if (role == "ClubOfficer") {
            officer_menu(system);
        } else if (role == "ClubMember") {
            member_menu(system);
        } else if (role == "ClubCoach") {
            coach_menu(system);
        }
}

int main() {
    PickleballReservations system;
    bool exit = false;

    while (!exit) {
        if (!system.is_logged_in()) {
            display_login_menu();

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    login(system);
                    std::cout << "Welcome, " << system.get_logged_in_user()->get_username() << "!" << std::endl;
                    break;
                }
                case 2: {
                    signup(system);
                    std::cout << "Welcome, " << system.get_logged_in_user()->get_username() << "!" << std::endl;
                    break;
                }
                case 3:
                    exit = true;
                    break;
                default:
                    std::cout << "Invalid option. Please try again." << std::endl;
            }
        } else {
            const std::string role = system.get_logged_in_user()->get_role();

            display_menu(role);

            handle_menu_response(role, system);
        }
    }

    // Save data to file at the end
    system.save_to_out_file();

    return 0;
}