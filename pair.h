//
// Created by LENOVO on 7/16/2024.
//

#ifndef DS1_PAIR_H
#define DS1_PAIR_H

class pair {
    int key;
    int id;
public:
    pair(int key, int id);
    pair() = default;
    int getId() const;
    int getKey() const;
    void setKey(int key);
    bool operator<(const pair& other) const;
    bool operator>(const pair& other) const;
};


#endif //DS1_PAIR_H
