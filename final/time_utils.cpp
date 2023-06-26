#include "time_utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

int get_day_from_given_time(const time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm* tm = std::localtime(&time_t);
    return tm->tm_wday;
}

int get_hour_from_given_time(const time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm* time = std::localtime(&time_t);
    return time->tm_hour;
}

std::string print_given_time_point(const std::chrono::system_clock::time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm time = *std::localtime(&time_t);

    const int max_chars = 100;
    char buffer[max_chars];

    std::strftime(buffer, max_chars, "%Y-%m-%d %H:%M:%S", &time);

    return std::string(buffer);
}

std::string get_given_string_for_date(const std::chrono::system_clock::time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm = *std::localtime(&time_t);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << (tm.tm_year + 1900) << "-"
        << std::setw(2) << (tm.tm_mon + 1) << "-"
        << std::setw(2) << tm.tm_mday;

    return oss.str();
}


std::string get_given_time_point_time_string(const time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm time = *std::localtime(&time_t);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << time.tm_hour << ":"
        << std::setw(2) << time.tm_min;

    return oss.str();
}

time_point turn_given_string_to_time_point(const std::string& date_str, const std::string& time_str) {
    std::tm time_m = {};
    std::istringstream ss(date_str + " " + time_str);
    
    
    int year, month, day, hour, minute;
    char delimiter;

    ss >> year >> delimiter >> month >> delimiter >> day >> hour >> delimiter >> minute;
    
    time_m.tm_year = year - 1900;
    time_m.tm_mon = month - 1;
    time_m.tm_mday = day;
    time_m.tm_hour = hour;
    time_m.tm_min = minute;
    
    std::time_t time_to = std::mktime(&time_m);
    
    return std::chrono::system_clock::from_time_t(time_to) - std::chrono::hours(1);
}


bool is_given_date_valid(const std::string& date_str, const std::string& time_str) {
    std::tm time_m = {};
    std::istringstream ss(date_str + " " + time_str);
    
    
    int year, month, day, hour, minute;
    char delimiter;

    ss >> year >> delimiter >> month >> delimiter >> day >> hour >> delimiter >> minute;

    if (ss.fail()) {
        return false;
    }
    
    time_m.tm_year = year - 1900;
    time_m.tm_mon = month - 1;
    time_m.tm_mday = day;
    time_m.tm_hour = hour;
    time_m.tm_min = minute;
    
    std::time_t time_t = std::mktime(&time_m);

    if (time_t != -1) {
        return true;
    }
    
    return false;
}

bool future_date_valid(const time_point& time_point) {
    
    return time_point > std::chrono::system_clock::now();
}

bool new_time_in_seven_days(const time_point& time_point) {
    return std::chrono::system_clock::now() + std::chrono::hours(168) >= time_point;
}

bool new_time_in_opening_hours(const time_point& time_point) {
    
    return get_hour_from_given_time(time_point) >= 6 && get_hour_from_given_time(time_point) < 24;
}

bool check_two_days(const time_point& time_point) {
    
    return time_point - std::chrono::hours(48) > std::chrono::system_clock::now();
}

bool new_time_in_two_days(const time_point& time_point) {
    return std::chrono::system_clock::now() + std::chrono::hours(48) >= time_point;
}

bool check_if_officer_available(const time_point& time_point) {
  
    int hour = get_hour_from_given_time(time_point);
    return hour >= 18 && hour <= 21;
}

bool check_if_coach_available(const time_point& time_point) {
    
    int day = get_day_from_given_time(time_point);
    int hour = get_hour_from_given_time(time_point);
    bool check_day = (day >= 1 && day <= 5) || day == 0;
    bool is_morning = hour >= 9 && hour <= 12;
    bool is_afternoon = hour >= 15 && hour <= 18;
    return (is_morning || (check_day && is_afternoon));
}