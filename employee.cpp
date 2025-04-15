#include <filesystem>

#include "class.h"

// CONSTRUCTOR

Employee::Employee(std::string fullNameInput, std::string departmentNameInput, 
                   std::string jobTitleInput, Date workEntryInput) {
    if (workEntryInput.getDay() > 0 && workEntryInput.getMonth() > 0 && 
        workEntryInput.getYear() > 0) {
        std::transform(departmentNameInput.begin(), 
                       departmentNameInput.end(), 
                       departmentNameInput.begin(),
                       [](unsigned char c) {return std::tolower(c);});
        std::transform(jobTitleInput.begin(), 
                       jobTitleInput.end(), 
                       jobTitleInput.begin(),
                       [](unsigned char c) {return std::tolower(c);});
        bool capitalNext = true;
        for (char& s : fullNameInput) {
            if (s == ' ') {
                capitalNext = true;
            } else {
                if (capitalNext) {
                    s = std::toupper(s);
                } else {
                    s = std::tolower(s);
                }
                capitalNext = false;
            }  
        }
        this->fullName = fullNameInput;
        this->departmentName = departmentNameInput;
        this->jobTitle = jobTitleInput;
        this->workEntry = workEntryInput;
    }
}

// OPERATORS

bool Employee::operator==(const Employee& employee) {
    return (departmentName == employee.departmentName) && 
           (fullName == employee.fullName) && 
           (workEntry == employee.workEntry) && 
           (jobTitle == employee.jobTitle);
}

bool Employee::operator>(const Employee& employee) {
    if (departmentName != employee.departmentName) {
        return departmentName > employee.departmentName;
    }
    if (fullName != employee.fullName) {
        return fullName > employee.fullName;
    }
    if (workEntry != employee.workEntry) {
        return workEntry > employee.workEntry;
    }
    return jobTitle > employee.jobTitle;
}

bool Employee::operator<(const Employee& employee) {
    if (departmentName != employee.departmentName) {
        return departmentName < employee.departmentName;
    }
    if (fullName != employee.fullName) {
        return fullName < employee.fullName;
    }
    if (workEntry != employee.workEntry) {
        return workEntry < employee.workEntry;
    }
    return jobTitle < employee.jobTitle;
}

bool Employee::operator!=(const Employee& employee) {
    return !(*this == employee);
}

bool Employee::operator<=(const Employee& employee) {
    return !(*this > employee);
}

bool Employee::operator>=(const Employee& employee) {
    return !(*this < employee);
}

std::ostream& operator<<(std::ostream &os, const Employee &employee) {
    if (employee.fullName == "") return os << "";

    return os << employee.fullName << "," 
              << employee.departmentName << "," 
              << employee.jobTitle << "," 
              << employee.workEntry;
}

// Чтение из файла (должен быть заголовок)
std::vector<Employee> readCSV(const std::string& filename) {
    std::vector<Employee> employees;
    if (!std::filesystem::exists(filename)) {
        std::cerr << "File doesn't exist" << std::endl;
        return employees;
    }

    std::ifstream file(filename);
    if (!file.is_open())  {
        std::cerr << "ERROR: File cannot be opened" << std::endl;
        return employees;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string fullName, departmentName, jobTitle, workEntry;
        Date dateWorkEntry;

        std::getline(ss, fullName, ',');
        std::getline(ss, departmentName, ',');
        std::getline(ss, jobTitle, ',');
        std::getline(ss, workEntry, ',');
        dateWorkEntry = fromString(workEntry);

        if (dateWorkEntry.getDay() > 0 && 
            dateWorkEntry.getMonth() > 0 && 
            dateWorkEntry.getYear() > 0) {
            employees.emplace_back(fullName, departmentName, jobTitle, dateWorkEntry);
        }
    }

    return employees;
}

// Запись в файл
void writeCSV(const std::string &filename, std::vector<Employee> employees) {
    std::ofstream file(filename);
    if (!file.is_open())  {
        std::cerr << "ERROR: File cannot be opened" << std::endl;
        return;
    }
    file << "Full Name,Department,Job Title,Hiring day\n";
    for (int i = 0; i < employees.size(); i++) {
        file << employees[i] << "\n";
    }
    file.close();
}