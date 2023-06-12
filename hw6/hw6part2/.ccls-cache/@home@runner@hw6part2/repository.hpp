#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include <vector>
#include <algorithm>
#include <iostream>

template<typename T>
class Repository {
public:
    Repository() = default;
    Repository(const std::vector<T>& items);
    void add(const T& item);
    void add(const std::vector<T>& items);
    bool contains(const T& item) const;
    int findOrder(const T& item) const;
    void remove(const T& item);
    void remove(const std::vector<T>& items);
    int count() const;
    void printList() const;

private:
    std::vector<T> itemList_;
};

template<typename T>
Repository<T>::Repository(const std::vector<T>& items)
    : itemList_(items) {}

template<typename T>
void Repository<T>::add(const T& item) {
    auto it = std::find(itemList_.begin(), itemList_.end(), item);
    if (it != itemList_.end()) {
        *it = item;
    } else {
        itemList_.push_back(item);
    }
}

template<typename T>
void Repository<T>::add(const std::vector<T>& items) {
    for (const auto& item : items) {
        add(item);
    }
}

template<typename T>
bool Repository<T>::contains(const T& item) const {
    return std::find(itemList_.begin(), itemList_.end(), item) != itemList_.end();
}

template<typename T>
int Repository<T>::findOrder(const T& item) const {
    auto it = std::find(itemList_.begin(), itemList_.end(), item);
    if (it != itemList_.end()) {
        return std::distance(itemList_.begin(), it);
    }
    return -1;
}

template<typename T>
void Repository<T>::remove(const T& item) {
    itemList_.erase(std::remove(itemList_.begin(), itemList_.end(), item), itemList_.end());
}

template<typename T>
void Repository<T>::remove(const std::vector<T>& items) {
    for (const auto& item : items) {
        remove(item);
    }
}

template<typename T>
int Repository<T>::count() const {
    return itemList_.size();
}

template<typename T>
void Repository<T>::printList() const {
    for (const auto& item : itemList_) {
        std::cout << item << std::endl;
    }
}

#endif  // REPOSITORY_HPP

