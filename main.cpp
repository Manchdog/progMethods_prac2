#include "class.h"
#include "search_class.h"

#include <chrono>
#include <map>

int main() {
    std::ofstream out("Time.csv");
    std::ofstream outCollusion("data/COLLUSION_HASH.csv");
    out << "File Name,LINEAR,BINARY TREE,RB TREE,HASH TABLE,std::multimap\n";
    //Чтобы проверить, что поиск работает корретно при первом прогоне запишем найденные элементы в отдельный файл
    for (int i = 1; i <= 10; i++) {
        std::vector<Employee> employees;
        out << std::to_string(i)+"_data.csv,";
        std::cout << std::to_string(i)+"_data.csv\n";

        //LINEAR
        std::cout << "LINEAR\n";
        employees = readCSV("data/"+std::to_string(i)+"_data.csv");
        auto begin = std::chrono::steady_clock::now();
        std::vector<int> answer = linear_search(employees, "Lane Daniel Katerinaevich");
        auto end = std::chrono::steady_clock::now();
        auto difftime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        out << difftime.count() << ",";
        std::cout << difftime.count() << "\n";
        
        if (i == 1) {
            std::ofstream resultOfWork("data/"+std::to_string(i)+"_data_LINEAR.csv");
            for (auto& i : answer) {
                resultOfWork << i << std::endl;
                resultOfWork << employees[i] << "\n";
            }
        }

        //BINARY TREE
        std::cout << "BINARY TREE\n";
        BinaryTree binaryTree(employees);
        begin = std::chrono::steady_clock::now();
        std::vector<BinaryTreeElemPtr> answerTree = binaryTree.findAll("Lane Daniel Katerinaevich");
        end = std::chrono::steady_clock::now();
        difftime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << difftime.count() << "\n";
        out << difftime.count() << ",";

        if (i == 1) {
            std::ofstream resultOfWork("data/"+std::to_string(i)+"_data_BINARY_TREE.csv");
            for (auto& i : answerTree) {
                resultOfWork << i << std::endl;
                resultOfWork << *i << std::endl;
            }
        }

        //RB TREE
        std::cout << "RB TREE\n";
        RBTree rbTree(employees);
        begin = std::chrono::steady_clock::now();
        std::vector<RBTreeElemPtr> answerRBTree = rbTree.findAll("Lane Daniel Katerinaevich");
        end = std::chrono::steady_clock::now();
        difftime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << difftime.count() << "\n";
        out << difftime.count() << ",";

        if (i == 1) {
            std::ofstream resultOfWork("data/"+std::to_string(i)+"_data_RB_TREE.csv");
            for (auto& i : answerRBTree) {
                resultOfWork << i << std::endl;
                resultOfWork << *i << std::endl;
            }
        }

        //HASH TABLE
        std::cout << "HASH TABLE\n";
        HashTable hashTable(employees);
        begin = std::chrono::steady_clock::now();
        std::pair<int, std::vector<int>> answerHash = hashTable.findAll("Lane Daniel Katerinaevich");
        end = std::chrono::steady_clock::now();
        difftime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << difftime.count() << "\n";
        out << difftime.count() << ",";

        if (i == 1) {
            std::ofstream resultOfWork("data/"+std::to_string(i)+"_data_HASH.csv");
            int hash = answerHash.first;
            for (auto& i : answerHash.second) {
                resultOfWork << "INDEX in hash table : " << hash << " "
                             << i << "\nEmployee : " << hashTable.getElem(hash, i).getItem() << "\n";
            }
        }
        outCollusion << i << "," << hashTable.getCollusionCount() << "\n";
    
        //MULTIMAP
        std::cout << "MULTIMAP\n";
        std::multimap<std::string, Employee> employeeMap;
        for (auto &employee : employees) {
            employeeMap.emplace(employee.getFullName(), employee);
        }
        begin = std::chrono::steady_clock::now();
        auto range = employeeMap.equal_range("Lane Daniel Katerinaevich");
        end = std::chrono::steady_clock::now();
        difftime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << difftime.count() << "\n";
        out << difftime.count() << "\n";

        if (i == 1) {
            std::ofstream resultOfWork("data/"+std::to_string(i)+"_data_MULTIMAP.csv");
            for (auto i = range.first; i != range.second; ++i) {
                resultOfWork << i->second << "\n";
            }
        }
    }
    out.close();
    outCollusion.close();
    return 0;
}