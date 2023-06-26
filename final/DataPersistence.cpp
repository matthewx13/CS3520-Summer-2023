#include "DataPersistence.h"
#include "ClubMember.h"
#include "ClubOfficer.h"
#include "ClubCoach.h"
#include "time_utils.h"

void DataPersistence::save_data_to_file(const std::string& users_filename, const std::string& reservations_filename, const std::string& reservation_id_filename, const std::vector<std::shared_ptr<User>>& users, int next_reservation_id, const Schedule& schedule) {
    // Save users
    std::ofstream users_outfile(users_filename);
    users_outfile << users.size() << std::endl;
    for (const auto& user : users) {
        users_outfile << user->get_username() << "|" << user->get_role() << "|" << user->get_skill_level() << "|" << user->get_password() << std::endl;
    }
    users_outfile.close();

    // Save reservation ID
    std::ofstream reservation_id_outfile(reservation_id_filename);
    reservation_id_outfile << next_reservation_id << std::endl;
    reservation_id_outfile.close();

    // Save reservations
    std::ofstream reservations_outfile(reservations_filename);
    const auto& courts = schedule.get_courts();
    reservations_outfile << courts.size() << std::endl;
    for (const auto& court : courts) {
        const auto& reservations = court.get_reservations();
        reservations_outfile << reservations.size() << std::endl;
        for (const auto& reservation : reservations) {
            reservations_outfile << reservation.to_string() << std::endl;
        }
    }
    reservations_outfile.close();

    std::cout << "Data saved." << std::endl;
}

void DataPersistence::load_data_from_file(const std::string& users_filename, const std::string& reservations_filename, const std::string& reservation_id_filename, std::vector<std::shared_ptr<User>>& users, int& next_reservation_id, Schedule& schedule) {
    // Load users
    std::ifstream users_infile(users_filename);
    if (users_infile.peek() != std::ifstream::traits_type::eof()) {
        std::cout << "Loading users..." << std::endl;

        size_t num_users;
        users_infile >> num_users;
        users_infile.ignore(); // Ignore newline character

        users.clear();
        for (size_t i = 0; i < num_users; ++i) {
            std::string line;
            std::getline(users_infile, line);
            std::stringstream ss(line);

            std::string username, role, skill_level, password;
            std::getline(ss, username, '|');
            std::getline(ss, role, '|');
            std::getline(ss, skill_level, '|');
            std::getline(ss, password, '|');

            if (role == "ClubMember") {
                users.push_back(std::make_shared<ClubMember>(username, password, skill_level));
            } else if (role == "ClubOfficer") {
                users.push_back(std::make_shared<ClubOfficer>(username, password, skill_level));
            } else if (role == "ClubCoach") {
                users.push_back(std::make_shared<ClubCoach>(username, password));
            }
        }
    }
    users_infile.close();

    // Load reservation ID
    std::ifstream reservation_id_infile(reservation_id_filename);
    if (reservation_id_infile.peek() != std::ifstream::traits_type::eof()) {
        std::cout << "Loading reservation ID..." << std::endl;
        reservation_id_infile >> next_reservation_id;
    }
    reservation_id_infile.close();

    // Load reservations
    std::ifstream reservations_infile(reservations_filename);
    if (reservations_infile.peek() != std::ifstream::traits_type::eof()) {
        std::cout << "Loading reservations..." << std::endl;

        size_t num_courts;
        reservations_infile >> num_courts;
        reservations_infile.ignore(); // Ignore newline character

        for (size_t i = 0; i < num_courts; ++i) {
            size_t num_reservations;
            reservations_infile >> num_reservations;
            reservations_infile.ignore(); // Ignore newline character

            for (size_t j = 0; j < num_reservations; ++j) {
                std::string line;
                std::getline(reservations_infile, line);

                    if (line.empty()) {
                        continue;
                    }

                std::stringstream ss(line);

                int id;
                std::string user, start_time_str, start_date_str, player;
                std::vector<std::string> players;

                ss >> id;
                ss.ignore(3, '|'); // Ignore " | "
                ss >> user;
                ss.ignore(3, '|'); // Ignore " | "
                ss >> start_date_str;
                ss.ignore(3, '|'); // Ignore " | "
                ss >> start_time_str;
                ss.ignore(3, '|'); // Ignore " | "

                while (std::getline(ss, player, ',')) {
                    players.push_back(player);
                }

                time_point start_time = string_to_time_point(start_date_str, start_time_str);
                time_point end_time = start_time + std::chrono::minutes(30);

                Reservation reservation(id, user, start_time, end_time, players);

                schedule.add_reservation_to_court(i, reservation);
            }
        }
    }
    reservations_infile.close();

    std::cout << "Data loaded." << std::endl;
}

