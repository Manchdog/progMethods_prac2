#include "class.h"

#include <bits/stdc++.h> //для функции std::count

// SUPPORT FUNCTIONS

bool isCorrectFormat(std::string date) {
    if (std::count(date.begin(), date.end(), '.') > 0 &&
        std::count(date.begin(), date.end(), '/') > 0 ||
        std::count(date.begin(), date.end(), '.') > 0 &&
        std::count(date.begin(), date.end(), '-') > 0 ||
        std::count(date.begin(), date.end(), '-') > 0 &&
        std::count(date.begin(), date.end(), '/') > 0) return false;
    if (std::count(date.begin(), date.end(), '.') != 2 &&
        std::count(date.begin(), date.end(), '/') != 2 &&
        std::count(date.begin(), date.end(), '-') != 2) return false;
    return true;
}

Date fromString(std::string date) {
    if (!isCorrectFormat(date)) {
        std::cerr << "ERROR: Incorrect date format" << std::endl;
        return Date();        
    }
    if (date.find('.') != -1) {
        int day = std::stoi(date.substr(0,date.find(".")));
        int month = std::stoi(date.substr(date.find(".")+1, date.rfind(".")-date.find(".")-1));
        int year = std::stoi(date.substr(date.rfind(".")+1));
        return Date(day, month, year);
    }
    if (date.find('-') != -1) {
        int day = std::stoi(date.substr(0,date.find("-")));
        int month = std::stoi(date.substr(date.find("-")+1, date.rfind("-")-date.find("-")-1));
        int year = std::stoi(date.substr(date.rfind("-")+1));
        return Date(day, month, year);
    }
    int day = std::stoi(date.substr(0,date.find("/")));
    int month = std::stoi(date.substr(date.find("/")+1, date.rfind("/")-date.find("/")-1));
    int year = std::stoi(date.substr(date.rfind("/")+1));
    return Date(day, month, year);
}

bool isCorrectDate(int day, int month, int year) {
    const int leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (year < 1) return false;
    if (month < 1 || month > 12) return false;
    int daysInMonth[] = { 31, 28 + leapYear, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return day > 0 && day <= daysInMonth[month - 1];
}

// CONSTRUCTOR

Date::Date(int day, int month, int year) {
    if (!isCorrectDate(day, month, year)) {
            std::cerr << "ERROR: Inccorect date" << std::endl;
            this->day = 0;
            this->month = 0;
            this->year = 0;
    } else {
        this->day = day;
        this->month = month;
        this->year = year;
    } 
}

// OPERATORS

bool Date::operator==(const Date& date) {
    return (year == date.year) && 
           (month == date.month) && 
           (day == date.day);
}

bool Date::operator>(const Date& date) {
    if (year != date.year)  return year > date.year;
    if (month != date.month) return month > date.month;
    return day > date.day;
}

bool Date::operator<(const Date& date) {
    if (year != date.year) return year < date.year;
    if (month != date.month) return month < date.month;
    return day < date.day;
}

bool Date::operator!=(const Date& date) {
    return !(*this == date);
}

bool Date::operator<=(const Date& date) {
    return !(*this > date);
}

bool Date::operator>=(const Date& date) {
    return !(*this < date);
}

std::ostream& operator<<(std::ostream &os, const Date &date) {
    return os << date.day << "/" << date.month << "/" << date.year;
}