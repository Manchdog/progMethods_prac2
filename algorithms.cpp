#include "class.h"
#include "search_class.h"

//------------------ЛИНЕЙНЫЙ ПОИСК------------------

std::vector<int> linear_search(std::vector<Employee> &employees, const std::string &FIO) {
    std::vector<int> occur;
    for (int i = 0; i < employees.size(); i++) {
        if (employees[i].getFullName() == FIO) {
            occur.push_back(i);
        }
    }
    return occur;
}

//------------------БИНАРНОЕ ДЕРЕВО------------------
//Вывод в указанный канал
std::ostream& operator<<(std::ostream &os, const BinaryTreeElem &elem) {
    os << elem.item;
    os << "\n" << "Left: " << elem.left << ", right: " << elem.right << "\n";
    return os;
}

//Вставка элемента
void BinaryTree::insertElemRecursion(BinaryTreeElemPtr &currElem, BinaryTreeElemPtr &newElem) {
    if (newElem->item.getFullName() < currElem->item.getFullName()) {
        if (currElem->left == NULL) {
            currElem->left = newElem;
        } else {
            this->insertElemRecursion(currElem->left, newElem);
        }
    } else {
        if (currElem->right == NULL) {
            currElem->right = newElem;
        } else {
            this->insertElemRecursion(currElem->right, newElem);
        }
    }
}

void BinaryTree::insertElem(BinaryTreeElemPtr &newElem) {
    if (this->root == NULL) {
        this->root = newElem;
        return;
    }
    this->insertElemRecursion(this->root, newElem);
}

BinaryTree::BinaryTree(std::vector<Employee> &employees) {
    for (auto& employee : employees) {
        BinaryTreeElemPtr newElem = std::make_shared<BinaryTreeElem>(employee);
        this->insertElem(newElem);
    }
}

//Поиск
BinaryTreeElemPtr BinaryTree::find(BinaryTreeElemPtr &currElem, const std::string &FIO) {
    if (currElem == nullptr || currElem->item.getFullName() == FIO) return currElem;
    if (FIO < currElem->item.getFullName()) return find(currElem->left, FIO);
    return find(currElem->right, FIO);
}

std::vector<BinaryTreeElemPtr> BinaryTree::findAll(const std::string &FIO) {
    std::vector<BinaryTreeElemPtr> ans;
    BinaryTreeElemPtr curr = nullptr;
    BinaryTreeElemPtr tmp = this->root;
    do {
        curr = find(tmp, FIO);
        if (curr == nullptr) break;
        ans.push_back(curr);
        tmp = curr->right;
    } while(tmp != nullptr);
    return ans;
}

//------------------RB ДЕРЕВО------------------
std::ostream& operator<<(std::ostream &os, const RBTreeElem &elem) {
    os << elem.item;
    os << "\n" << "Left: " << elem.left << ", right: " 
       << elem.right << ", parent: " << elem.parent;
    if (elem.colour == RED) {
        os << ", colour: RED\n";
    } else {
        os << ", colour: BLACK\n";
    }
    return os;
}

//Починка
void RBTree::rotateLeft(RBTreeElemPtr curr) {
    RBTreeElemPtr tmp = curr->right;
    curr->right = tmp->left;
    if (tmp->left != nullptr) {
        tmp->left->parent = curr;
    }
    tmp->parent = curr->parent;
    if (curr->parent == nullptr) { //curr == root
        this->root = tmp;
    } else if (curr == curr->parent->left) { //curr - left child
        curr->parent->left = tmp;
    } else { //curr - right child
        curr->parent->right = tmp;
    }
    tmp->left = curr;
    curr->parent = tmp;
}

void RBTree::rotateRight(RBTreeElemPtr curr) {
    RBTreeElemPtr tmp = curr->left;
    curr->left = tmp->right;
    if (tmp->right != nullptr) {
        tmp->right->parent = curr;
    }
    tmp->parent = curr->parent;
    if (curr->parent == nullptr) {
        this->root = tmp;
    } else if (curr == curr->parent->left) {
        curr->parent->left = tmp;
    } else {
        curr->parent->right = tmp;
    }
    tmp->right = curr;
    curr->parent = tmp;
}

void RBTree::fixLogic(RBTreeElemPtr &curr) {
    while (curr != this->root && curr->parent->parent != nullptr && curr->parent->colour == RED) {
        if (curr->parent == curr->parent->parent->left) { //parent - left child
            RBTreeElemPtr uncle = curr->parent->parent->right;
            if (uncle != nullptr && uncle->colour == RED) { //curr->parent and uncle - red
                curr->parent->colour = BLACK;
                uncle->colour = BLACK;
                curr->parent->parent->colour = RED;
                curr = curr->parent->parent;
            } else { //curr->parent - red, uncle - black or no uncle
                if (curr == curr->parent->right) {
                    curr = curr->parent;
                    rotateLeft(curr);
                }
                curr->parent->colour = BLACK;
                curr->parent->parent->colour = RED;
                rotateRight(curr->parent->parent);
            } 
        } else { //father - right child
            RBTreeElemPtr uncle = curr->parent->parent->left;
            if (uncle != nullptr && uncle->colour == RED) {
                curr->parent->colour = BLACK;
                uncle->colour = BLACK;
                curr->parent->parent->colour = RED;
                curr = curr->parent->parent;
            } else {
                if (curr == curr->parent->left) {
                    curr = curr->parent;
                    rotateRight(curr);
                }
                curr->parent->colour = BLACK;
                curr->parent->parent->colour = RED;
                rotateLeft(curr->parent->parent);
            }
        }
    }
    root->colour = BLACK;
}

//Вставка элемента
void RBTree::insertElemRecursion(RBTreeElemPtr &currElem, RBTreeElemPtr &newElem) {
    if (newElem->item.getFullName() < currElem->item.getFullName()) {
        if (currElem->left == NULL) {
            currElem->left = newElem;
            newElem->parent = currElem;
        } else {
            this->insertElemRecursion(currElem->left, newElem);
        }
    } else {
        if (currElem->right == NULL) {
            currElem->right = newElem;
            newElem->parent = currElem;
        } else {
            this->insertElemRecursion(currElem->right, newElem);
        }
    }
}

void RBTree::insertElem(RBTreeElemPtr &newElem) {
    if (this->root == NULL) {
        this->root = newElem;
        return;
    }
    this->insertElemRecursion(this->root, newElem);
    this->fixLogic(newElem);
}

//Конструктор
RBTree::RBTree(std::vector<Employee> &employees) {
    for (auto& employee : employees) {
        RBTreeElemPtr newElem = std::make_shared<RBTreeElem>(employee);
        this->insertElem(newElem);
    }
}

//Поиск
RBTreeElemPtr RBTree::find(RBTreeElemPtr &currElem, const std::string &FIO) {
    if (currElem == nullptr || currElem->item.getFullName() == FIO) return currElem;
    if (FIO < currElem->item.getFullName()) return find(currElem->left, FIO);
    return find(currElem->right, FIO);
}

std::vector<RBTreeElemPtr> RBTree::findAll(const std::string &FIO) {
    std::vector<RBTreeElemPtr> ans;
    RBTreeElemPtr curr = nullptr;
    RBTreeElemPtr tmp = this->root;
    do {
        curr = find(tmp, FIO);
        if (curr == nullptr) break;
        ans.push_back(curr);
        tmp = curr->right;
    } while(tmp != nullptr);
    return ans;
}

//------------------ХЭШ-ТАБЛИЦА------------------
std::ostream& operator<<(std::ostream &os, const HashTableElem &elem) {
    os << "employee : ";
    os << elem.item;
    return os;
}

//Вывод в указанный канал
std::ostream& operator<<(std::ostream &os, const HashTable &table) {
    for (int i = 0; i < table.size; i++) {
        if (!table.elems[i].empty()) {
            os << "HASH : " << i << "\n";
            for (auto j = table.elems[i].begin(); j != table.elems[i].end(); j++) {
                os << *j << "\n";
            }
        } 
    }
    return os;
}

//Простая хэш-функция
unsigned int HashTable::hashFunction(const std::string &FIO) {
    unsigned int hash = 0;
    for (char ch : FIO) {
        hash += ch;
    }
    return hash % this->size;
}

//Поиск элемента
std::pair<int, std::vector<int>> HashTable::findAll(const std::string &FIO) {
    int hash = hashFunction(FIO);
    if (this->elems[hash].empty()) {
        return {-1, {}};
    }
    std::vector<int> indexes;
    for (int i = 0; i < elems[hash].size(); i++) {
        if (elems[hash][i].item.getFullName() == FIO) {
            indexes.push_back(i);
        }
    }
    return {hash, indexes};
}

HashTable::HashTable(std::vector<Employee> &employees) {
    collusionCount = 0;
    this->size = employees.size();
    this->elems.resize(this->size);
    for (auto& employee : employees) {
        std::string FIO = employee.getFullName();
        int hash = hashFunction(FIO);
        if (!this->elems[hash].empty()) {
            this->collusionCount++;
        }
        this->elems[hash].emplace_back(FIO, employee);
    }
}