#ifndef STORAGE_DATA_H
#define STORAGE_DATA_H

#include <fstream>
#include <memory>
#include <vector>
#include "User.h"
#include "Schedule.h"

class DataPersistence {
public:
    static void save_data_to_file(const std::string& users_filename, const std::string& reservations_filename, const std::string& reservation_id_filename, const std::vector<std::shared_ptr<User>>& users, int next_reservation_id, const Schedule& schedule);
    static void load_data_from_file(const std::string& users_filename, const std::string& reservations_filename, const std::string& reservation_id_filename, std::vector<std::shared_ptr<User>>& users, int& next_reservation_id, Schedule& schedule);
};

#endif
