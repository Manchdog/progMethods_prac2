/**
 * \file class.h
 * \brief Файл с основным классом, дополнительным и объявлением функции, реализующий алгоритм линейного поиска.
 * \details В данном файле описаны следующие классы:
 *  - основной класс для работы с данными о сотрудниках предприятия
 *  - дополнительный класс для работы с датами
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#ifndef CLASSES
#define CLASSES

/**
 * \brief Класс, созданный для работы с датами
 * 
 * \details В данном классе переопределены операции сравнения и вывода. 
 * В том числе реализованы функции для получения значения полей класса.
 * Поля класса следующие:
 * - day - день даты
 * - month - номер месяца
 * - year - номер года
 * 
 * При создании объекта класса, проверяется корректность введенной даты, 
 * и в случае ее некорректности все поля класса принимают значение 0
 */
class Date {
    friend std::ostream& operator<<(std::ostream &os, const Date &date);

    int day, month, year;

public:
    Date() : day(0), month(0), year(0) {}
    Date(int day, int month, int year);

    ///Возвращает значение поля "day"
    int getDay() { return day; }
    ///Возвращает значение поля "month"
    int getMonth() { return month; }
    ///Возвращает значение поля "year"
    int getYear() { return year; }

    bool operator==(const Date& date);
    bool operator>(const Date& date);
    bool operator<(const Date& date);
    bool operator!=(const Date& date);
    bool operator<=(const Date& date);
    bool operator>=(const Date& date);
};
/**
 * \brief Класс для работы с данными сотрудников предприятий
 * 
 * В данном классе переопределены операции сравнения и вывода.
 * 
 * Поля класса соответствуют заданию, то есть:
 * - fullName - ФИО сотрудника
 * - departmentName - наименование отдела
 * - jobTitle - должность сотрудника
 * - workEntry - день приема на работу
 * 
 * При создании объекта класса происходит следующее:
 * - Если введенная дата некорректна (0/0/0), поля класса остаются пустыми 
 * и такой объект не будет выводиться на экран или в файл через оператор "<<"
 * - Введенное имя, независимо от изначального формата, записывается в виде "John Jonah Jameson"
 * - Введенное наименование отдела записывается в виде "the daily bugle"
 * - Введенная должность - "head editor-in-chief"
 */
class Employee {
    friend std::ostream& operator<<(std::ostream &os, const Employee &employee);

    std::string fullName;
    std::string departmentName;
    std::string jobTitle;
    Date workEntry;

public:
    Employee(): fullName(""), departmentName(""),
                jobTitle("") {};
    Employee(std::string fullName, std::string departmentName, 
             std::string jobTitle, Date workEntry);
    
    /// @brief Возвращает ФИО сотрудника
    std::string getFullName() { return this->fullName; }

    bool operator==(const Employee& employee);
    bool operator>(const Employee& employee);
    bool operator<(const Employee& employee);
    bool operator!=(const Employee& employee);
    bool operator<=(const Employee& employee);
    bool operator>=(const Employee& employee);
};

// WRITE_TO_CSV AND READ_FROM_CSV FUNCTIONS

/// @brief Функция считывает данные из csv файла и создает вектор из объектов класса Employee
/// @param filename - путь к файлу, из которого нужно считать данные
/// @return вектор объектов класса Employee
std::vector<Employee> readCSV(const std::string& filename);

/// @brief Функция записывает объекты класса Employee в файл
/// @param filename - путь к выходному файлу
/// @param employees - массив объектов, которые нужно записать в указанный файл
void writeCSV(const std::string &filename, std::vector<Employee> employees);

// SUPPORT FUNCTIONS

/// @brief Проверяет корректна ли введенная дата (с учетом високосного года)
/// @return true, если дата корректна, в ином случае - false
bool isCorrectDate(int day, int month, int year);

/// @brief Проверяет, соответствует ли строка таким форматам: "D*-M*-Y*", "D*/M*/Y*", "D*.M*.Y*"
/// @param date - строка, которая должна являться датой 
/// @return true, если соответствует, иначе - false
bool isCorrectFormat(std::string date);

/// @brief Переводит std::string в Date
/// @param date - дата в виде строки
/// @return если формат даты некорректный, то возвращает Date(), то есть дату 0/0/0
Date fromString(std::string date);

// SEARCHING ALGORITHMS

/// @brief Реализация алгоритма линейного поиска всех вхождений по переданному ключу
/// @param employees - массив объектов класса Employee
/// @param FIO - значение, по которому искать нужно
/// @return список индексов всех подходящих объектов
std::vector<int> linear_search(std::vector<Employee> &employees, const std::string &FIO);

#endif
