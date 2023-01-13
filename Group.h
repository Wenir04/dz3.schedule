//
// Created by Maxim Kukuruz on 1/12/23.
//

#ifndef HW3_SCHEDULE_GROUP_H
#define HW3_SCHEDULE_GROUP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include "Teacher.h"
using namespace std;

struct Group {
    string name = "CS201";

    vector<Teacher> teachers;

    vector<pair<Teacher, bool>> Monday;   //Monday[0] — первая пара, Monday[1] — вторая пара и тд
    vector<pair<Teacher, bool>> Tuesday;
    vector<pair<Teacher, bool>> Wednesday;
    vector<pair<Teacher, bool>> Thursday;
    vector<pair<Teacher, bool>> Friday;
    vector<pair<Teacher, bool>> Saturday;

    vector<Teacher> tmp_teachers;   //Для составления расписания
    vector<vector<pair<Teacher, bool>>> Schedule; //Расписание

    vector<Teacher> file_teachers_read(const string &file_name);
    Group();
    explicit Group(const string &file_name);
    vector<vector<pair<Teacher, bool>>> create_schedule();
    void print_schedule();
    void print_schedule(const string& file_name);

    virtual ~Group();
};


#endif //HW3_SCHEDULE_GROUP_H
