#include "time_utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

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

string print_time_and_date(const time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm = *std::localtime(&time_t);

    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
    return string(buffer);
}

string get_date_string(const time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm = *std::localtime(&time_t);

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
    return string(buffer);
}

string get_time_string(const time_point& time_point) {
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm = *std::localtime(&time_t);

    char buffer[6];
    std::strftime(buffer, sizeof(buffer), "%H:%M", &tm);
    return string(buffer);
}

time_point string_to_time_point(const string& date_str, const string& time_str) {
    std::tm tm = {};

    std::istringstream date_stream(date_str);
    date_stream >> std::get_time(&tm, "%Y-%m-%d");
    if (date_stream.fail()) {
        throw std::runtime_error("Failed to parse date string");
    }

    std::istringstream time_stream(time_str);
    time_stream >> std::get_time(&tm, "%H:%M");
    if (time_stream.fail()) {
        throw std::runtime_error("Failed to parse time string");
    }

    auto time_t = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(time_t);
}


bool is_future_date(const time_point& time_point) {
    return time_point > std::chrono::system_clock::now();
}

bool is_date_valid(const string& date_str, const string& time_str) {
    try {
        string_to_time_point(date_str, time_str);
        return true;
    } catch (...) {
        return false;
    }
}

bool two_days_in_advance(const time_point& time_point) {
    auto now = std::chrono::system_clock::now();
    auto duration = time_point - now;
    return (duration >= std::chrono::hours(48));
}

bool within_two_days(const time_point& time_point) {
    auto now = std::chrono::system_clock::now();
    auto duration = time_point - now;
    return (duration >= std::chrono::hours(0) && duration <= std::chrono::hours(48));
}

bool within_seven_days(const time_point& time_point) {
    auto now = std::chrono::system_clock::now();
    auto duration = time_point - now;
    return (duration >= std::chrono::hours(0) && duration <= std::chrono::hours(168));
}

bool within_opening_hours(const time_point& time_point) {
    int hour = get_hour_from_time_point(time_point);
    return (hour >= 9 && hour < 18);
}

bool within_coach_hours(const time_point& time_point) {
    int hour = get_hour_from_time_point(time_point);
    return (hour >= 9 && hour < 17);
}

bool within_officer_hours(const time_point& time_point) {
    int hour = get_hour_from_time_point(time_point);
    return (hour >= 10 && hour < 17);
}
