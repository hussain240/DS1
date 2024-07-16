#include "pair.h"

pair::pair(int key, int id) : key(key), id(id) {}

int pair::getId() const {
    return this->id;
}

int pair::getKey() const {
    return this->key;
}

void pair::setKey(int key) {
    this->key = key;
}

bool pair::operator<(const pair& other) const {
    if (this->key < other.key) {
        return true;
    }
    if (this->key == other.key) {
        return this->id < other.id;
    }
    return false;
}

bool pair::operator>(const pair& other) const {
    if (this->key > other.key) {
        return true;
    }
    if (this->key == other.key) {
        return this->id > other.id;
    }
    return false;
}