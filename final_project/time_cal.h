#ifndef TIME_CAL_H
#define TIME_CAL_H

#pragma once
#include <chrono>
#include <string>

using time_point = std::chrono::system_clock::time_point;

int get_hour_from_time_point(const time_point& time_point);
int get_day_from_time_point(const time_point& time_point);
std::string print_time_and_date(const time_point& time_point);
std::string get_date_string(const time_point& time_point);
std::string get_time_string(const time_point& time_point);
time_point string_to_time_point(const std::string& date_str, const std::string& time_str);
bool is_future_date(const time_point& time_point);
bool is_date_valid(const std::string& date_str, const std::string& time_str);
bool two_days_in_advance(const time_point& time_point);
bool within_two_days(const time_point& time_point);
bool within_seven_days(const time_point& time_point);
bool within_opening_hours(const time_point& time_point);
bool within_coach_hours(const time_point& time_point);
bool within_officer_hours(const time_point& time_point);

#endif
