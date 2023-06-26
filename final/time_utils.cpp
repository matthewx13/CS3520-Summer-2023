#include "time_utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

int get_hour_from_time_point(const time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm* tm = std::localtime(&time_t);
    return tm->tm_hour;
}

int get_day_from_time_point(const time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm* tm = std::localtime(&time_t);
    return tm->tm_wday;
}

std::string print_time_and_date(const std::chrono::system_clock::time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm = *std::localtime(&time_t);

    const int max_chars = 100;
    char buffer[max_chars];

    std::strftime(buffer, max_chars, "%Y-%m-%d %H:%M:%S", &tm);

    return std::string(buffer);
}

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

std::string get_date_string(const std::chrono::system_clock::time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm = *std::localtime(&time_t);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << (tm.tm_year + 1900) << "-"
        << std::setw(2) << (tm.tm_mon + 1) << "-"
        << std::setw(2) << tm.tm_mday;

    return oss.str();
}


std::string get_time_string(const time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm = *std::localtime(&time_t);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << tm.tm_hour << ":"
        << std::setw(2) << tm.tm_min;

    return oss.str();
}

time_point string_to_time_point(const std::string& date_str, const std::string& time_str) {
    std::tm tm = {};
    std::istringstream ss(date_str + " " + time_str);
    
    // Extract individual components from date_str and time_str
    int year, month, day, hour, minute;
    char delimiter;

    ss >> year >> delimiter >> month >> delimiter >> day >> hour >> delimiter >> minute;
    
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    
    std::time_t tt = std::mktime(&tm);
    
    return std::chrono::system_clock::from_time_t(tt) - std::chrono::hours(1);
}


bool is_future_date(const time_point& time_point) {
    // check if time_point is in the future
    return time_point > std::chrono::system_clock::now();
}

bool is_date_valid(const std::string& date_str, const std::string& time_str) {
    std::tm tm = {};
    std::istringstream ss(date_str + " " + time_str);
    
    // Extract individual components from date_str and time_str
    int year, month, day, hour, minute;
    char delimiter;

    ss >> year >> delimiter >> month >> delimiter >> day >> hour >> delimiter >> minute;

    if (ss.fail()) {
        return false;
    }
    
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    
    std::time_t tt = std::mktime(&tm);
    if (tt == -1) {
        return false;
    }
    
    return true;
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