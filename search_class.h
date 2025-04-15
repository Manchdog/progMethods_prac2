/**
 * \file search_class.h
 * \brief Файл с классами для реализации алгоритмов поиска.
 * \details В данном файле описаны следующие классы:
 *  - класс, реализующий хэш-таблицу
 *  - класс для бинарного дерева
 *  - класс для RB дерева
 */

#include "class.h"
#include <memory>

#ifndef CLASSES_SEARCH
#define CLASSES_SEARCH

//------------------БИНАРНОЕ ДЕРЕВО------------------
class BinaryTreeElem;

using BinaryTreeElemPtr = std::shared_ptr<BinaryTreeElem>;

/** \brief Класс, реализующий элемент бинарного дерева
 */
class BinaryTreeElem {
    friend class BinaryTree;

    friend std::ostream& operator<<(std::ostream &os, const BinaryTreeElem &elem);

    Employee item;
    BinaryTreeElemPtr left;
    BinaryTreeElemPtr right;

public:
    BinaryTreeElem(Employee &item) : 
                   item(item),
                   left(nullptr),
                   right(nullptr) {};

    /// @brief Фукнция возвращает левый лист данного корня
    BinaryTreeElem getLeft() { return *(this->left); }
    /// @brief Функция возвращает праввый лист данного корня
    BinaryTreeElem getRight() { return *(this->right); }
};

/** \brief Класс, реализующий бинарное дерево
 */
class BinaryTree {
    BinaryTreeElemPtr root = nullptr;

    void insertElemRecursion(BinaryTreeElemPtr &currElem, BinaryTreeElemPtr &newElem);

public:
    BinaryTree() : root(nullptr) {};
    BinaryTree(std::vector<Employee> &employees);

    /// @brief Функция добавляет новый элемент в бинарное дерево
    /// @param newElem - элемент, который нужно добавить
    void insertElem(BinaryTreeElemPtr &newElem);

    /// @brief Функция находит лист, содержащий такой ключ
    /// @param currElem - корень, с которого нужно начать обход
    /// @param FIO - ключ
    /// @return указатель на лист. Если элемент с таким ключом не найден - nullptr
    BinaryTreeElemPtr find(BinaryTreeElemPtr &currElem, const std::string &FIO);

    /// @brief Функция находит все листы с указанным ключом
    /// @param FIO - ключ
    /// @return список указателей на найденные листы. Если таких элементов нет - пустой список
    std::vector<BinaryTreeElemPtr> findAll(const std::string &FIO);

    /// @brief Возвращает указатель на корень дерева
    BinaryTreeElem* getRootPointer() { return this->root.get(); }
};

//------------------RB ДЕРЕВО------------------
class RBTreeElem;

using RBTreeElemPtr = std::shared_ptr<RBTreeElem>;

enum Colour {RED, BLACK};

class RBTreeElem {
    friend class RBTree;

    friend std::ostream& operator<<(std::ostream &os, const RBTreeElem &elem);

    Employee item;
    Colour colour;
    RBTreeElemPtr parent;
    RBTreeElemPtr left;
    RBTreeElemPtr right;
public:
    RBTreeElem(Employee &item) :
               item(item), 
               colour(RED),
               parent(nullptr),
               left(nullptr), 
               right(nullptr) {};

    /// @brief Фукнция возвращает левый лист данного корня
    RBTreeElem getLeft() { return *(this->left); }
    /// @brief Функция возвращает праввый лист данного корня
    RBTreeElem getRight() { return *(this->right); }
};

class RBTree {
    RBTreeElemPtr root;

    void rotateLeft(RBTreeElemPtr curr);
    void rotateRight(RBTreeElemPtr curr);
    void fixLogic(RBTreeElemPtr &curr);

    void insertElemRecursion(RBTreeElemPtr &currElem, RBTreeElemPtr &newElem);

public:
    RBTree() : root(nullptr) {};
    RBTree(std::vector<Employee> &employees);
    /// @brief Функция добавляет новый элемент в RB дерево
    /// @param newElem - элемент, который нужно добавить
    void insertElem(RBTreeElemPtr &newElem);

    /// @brief Функция находит лист, содержащий такой ключ
    /// @param currElem - корень, с которого нужно начать обход
    /// @param FIO - ключ
    /// @return указатель на лист. Если элемент с таким ключом не найден - nullptr
    RBTreeElemPtr find(RBTreeElemPtr &curr, const std::string &FIO);
    /// @brief Функция находит все листы с указанным ключом
    /// @param FIO - ключ
    /// @return список указателей на найденные листы. Если таких элементов нет - пустой список
    std::vector<RBTreeElemPtr> findAll(const std::string &FIO);

    /// @brief Возвращает указатель на корень дерева
    RBTreeElem* getRootPointer() { return this->root.get(); }

};
//------------------ХЭШ-ТАБЛИЦА------------------
/** \brief Класс, реализующий элемент, хранящийся в хэш-таблице
 *  \details 
 *  Класс содержит следующие поля:
 *  -key - ключ, по условию ФИО сотрудника
 *  -item - объект класс Employee
 */
class HashTableElem {
    friend class HashTable;

    friend std::ostream& operator<<(std::ostream &os, const HashTableElem &elem); 

    std::string key;
    Employee item;

public:
    HashTableElem(): key("") {};
    HashTableElem(std::string &key, Employee &employee) :
                  key(key), item(employee) {};
                
    /// @brief Функия возвращает ключ данного элемента
    std::string getKey() { return this->key; }
    /// @brief Функция возвращает объект класса Employee
    Employee getItem() { return this->item; }
};

/** \brief Класс, реализующий хэш-таблицу
 *  \details 
 *  Класс содержит следующие поля: 
 *  -collusionCount - количество коллизий
 *  -size - размер таблицы
 *  -elems - список списка элементов HashTableElem с одним значением хэш-функции
 */
class HashTable {
    friend std::ostream& operator<<(std::ostream &os, const HashTable &table);

    int collusionCount;
    int size;
    std::vector<std::vector<HashTableElem>> elems;

    unsigned int hashFunction(const std::string &FIO);

public:
    HashTable() : collusionCount(0), size(0) {};
    HashTable(std::vector<Employee> &employees);

    /// @brief Функия находит всех сотрудников с указанным ФИО
    /// @return пара (hash, {ind1, ind2, ...}) - где hash позволяет обратиться к элементу хэш-таблицы с таким хэшем, а вектор индексов - к 
    /// конкретным элементам, ключ которых совпал с переданным
    std::pair<int, std::vector<int>> findAll(const std::string &FIO);

    /// @brief Фукнция возвращает число коллизий 
    int getCollusionCount() { return this->collusionCount; }

    /// @brief Функция позволяет обратиться к элементы хэш-таблицы с хэшем i и j индексом
    /// @return объект класса HashTableElem с указанными индексами, если такой элемент существует
    HashTableElem getElem(const int &i, const int &j) { return (i < this->size && 
                                                                !this->elems[i].empty() && 
                                                                j < elems[i].size()) ? this->elems[i][j] : HashTableElem(); }
};

#endif