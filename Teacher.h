//
// Created by Maxim Kukuruz on 1/12/23.
//

#ifndef HW3_SCHEDULE_TEACHER_H
#define HW3_SCHEDULE_TEACHER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Teacher {
    string name;
    int quan = 0; //Количество рабочих дней в неделю

    vector<bool> Monday;
    vector<bool> Tuesday;
    vector<bool> Wednesday;
    vector<bool> Thursday;
    vector<bool> Friday;
    vector<bool> Saturday;

    Teacher();
    void clear();

    Teacher(const string&, const vector<bool>&, const vector<bool>&, const vector<bool>&,
            const vector<bool>&, const vector<bool>&, const vector<bool>&);
    virtual ~Teacher();

    Teacher file_read(ifstream &file);
    int num_of_classes(const string &day);
    int num_of_classes(const string &day, const int& start);
    bool empty(const string &day);

    bool operator==(const Teacher &teacher) const;
};


#endif //HW3_SCHEDULE_TEACHER_H
