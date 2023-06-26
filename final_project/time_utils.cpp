#include "time_utils.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <ctime>

#include <ctime>
#include <sstream>
#include <iomanip>

std::string print_time_and_date(const time_point& time_point) {
    std::time_t time_t = std::chrono::system_clock::to_time_t(time_point);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

time_point string_to_time_point(const std::string& date_str, const std::string& time_str) {
    std::tm tm = {};
    std::istringstream date_stream(date_str + " " + time_str);
    date_stream >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    if (date_stream.fail()) {
        throw std::runtime_error("Failed to parse time string");
    }
    std::time_t time_t = std::mktime(&tm);
    if (time_t == -1) {
        throw std::runtime_error("Failed to convert time string to time_t");
    }
    return std::chrono::system_clock::from_time_t(time_t);
}

std::string get_date_string(const time_point& time_point) {
    std::time_t time_t = std::chrono::system_clock::to_time_t(time_point);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d");
    return ss.str();
}

std::string get_time_string(const time_point& time_point) {
    std::time_t time_t = std::chrono::system_clock::to_time_t(time_point);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%H:%M");
    return ss.str();
}

// The rest of the functions remain the same as in the previous response

time_point string_to_time_point(const std::string& date_str, const std::string& time_str) {
    // Convert date_str and time_str to a time_point
    std::tm tm = {};
    std::istringstream ss(date_str + " " + time_str);
    
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse time string");
    }

    std::time_t tt = std::mktime(&tm);
    if (tt == -1) {
        throw std::runtime_error("Failed to convert time string to time_t");
    }

    auto time_point = std::chrono::system_clock::from_time_t(tt);
    return time_point - std::chrono::hours(1);
}

bool is_future_date(const time_point& time_point) {
    // Check if time_point is in the future
    return time_point > std::chrono::system_clock::now();
}

bool is_date_valid(const std::string& date_str, const std::string& time_str) {
    // Validate date_str and time_str
    std::tm tm = {};
    std::istringstream ss(date_str + " " + time_str);

    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    return !ss.fail();
}

bool two_days_in_advance(const time_point& time_point) {
    // 48 hours in advance
    return time_point - std::chrono::hours(48) > std::chrono::system_clock::now();
}

bool within_two_days(const time_point& time_point) {
    return std::chrono::system_clock::now() + std::chrono::hours(48) >= time_point;
}

bool within_seven_days(const time_point& time_point) {
    return std::chrono::system_clock::now() + std::chrono::hours(168) >= time_point;
}

bool within_opening_hours(const time_point& time_point) {
    // 6am to midnight
    return get_hour_from_time_point(time_point) >= 6 && get_hour_from_time_point(time_point) < 24;
}

bool within_coach_hours(const time_point& time_point) {
    // 9am-Noon everyday. And extra 3-6pm on weekdays and Sundays
    int day = get_day_from_time_point(time_point);
    int hour = get_hour_from_time_point(time_point);
    bool is_weekday_or_sunday = (day >= 1 && day <= 5) || day == 0;
    bool is_morning = hour >= 9 && hour <= 12;
    bool is_afternoon = hour >= 15 && hour <= 18;
    return (is_morning || (is_weekday_or_sunday && is_afternoon));
}

bool within_officer_hours(const time_point& time_point) {
    // 6-9pm
    int hour = get_hour_from_time_point(time_point);
    return hour >= 18 && hour <= 21;
}
