#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#pragma once
#include <chrono>
#include <string>

using time_point = std::chrono::system_clock::time_point;

int get_hour_from_given_time(const time_point& time_point);
int get_day_from_given_time(const time_point& time_point);
std::string print_given_time_point(const time_point& time_point);
std::string get_given_string_for_date(const time_point& time_point);
std::string get_given_time_point_time_string(const time_point& time_point);
time_point turn_given_string_to_time_point(const std::string& date_str, const std::string& time_str);
bool future_date_valid(const time_point& time_point);
bool is_given_date_valid(const std::string& date_str, const std::string& time_str);
bool check_two_days(const time_point& time_point);
bool new_time_in_two_days(const time_point& time_point);
bool new_time_in_seven_days(const time_point& time_point);
bool new_time_in_opening_hours(const time_point& time_point);
bool check_if_coach_available(const time_point& time_point);
bool check_if_officer_available(const time_point& time_point);

#endif