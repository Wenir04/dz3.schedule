//
// Created by Maxim Kukuruz on 1/12/23.
//

#include "Teacher.h"

void Teacher::clear() {
    name.clear();
    quan = 0;

    Monday.assign(Monday.size(), false);
    Tuesday.assign(Tuesday.size(), false);
    Wednesday.assign(Wednesday.size(), false);
    Thursday.assign(Thursday.size(), false);
    Friday.assign(Friday.size(), false);
    Saturday.assign(Saturday.size(), false);
}

Teacher::Teacher() {
    Monday.resize(6, false);
    Tuesday.resize(6, false);
    Wednesday.resize(6, false);
    Thursday.resize(6, false);
    Friday.resize(6, false);
    Saturday.resize(6, false);
}


Teacher::Teacher(const string &tmp_name, const vector<bool> &tmp_Monday, const vector<bool> &tmp_Tuesday,
                 const vector<bool> &tmp_Wednesday, const vector<bool> &tmp_Thursday,
                 const vector<bool> &tmp_Friday, const vector<bool> &tmp_Saturday) {
    name = tmp_name;
    Monday = tmp_Monday;
    Tuesday = tmp_Tuesday;
    Wednesday = tmp_Wednesday;
    Thursday = tmp_Thursday;
    Friday = tmp_Friday;
    Saturday = tmp_Saturday;

    if(!empty("Monday"))
        ++quan;
    if(!empty("Tuesday"))
        ++quan;
    if(!empty("Wednesday"))
        ++quan;
    if(!empty("Thursday"))
        ++quan;
    if(!empty("Friday"))
        ++quan;
    if(!empty("Saturday"))
        ++quan;
}

Teacher Teacher::file_read(ifstream &file) {
    clear();
    if(!file.is_open()){
        cerr << "";
        exit(1);
    }
    string tmp_day, tmp_par;

    file >> name;
    do {
        file >> tmp_day >> tmp_par;
        for(int i = 0; i < tmp_par.size(); ++i) {
            if(tmp_par[i] == '+') {
                if(tmp_day == "Mon" || tmp_day == "mon")
                    Monday[i] = true;
                else if(tmp_day == "Tue" || tmp_day == "tue")
                    Tuesday[i] = true;
                else if(tmp_day == "Wed" || tmp_day == "wed")
                    Wednesday[i] = true;
                else if(tmp_day == "Thu" || tmp_day == "thu")
                    Thursday[i] = true;
                else if(tmp_day == "Fri" || tmp_day == "fri")
                    Friday[i] = true;
                else if(tmp_day == "Sat" || tmp_day == "sat")
                    Saturday[i] = true;
            }
        }

    } while(tmp_day != "Sat");

    //Определяем количество рабочих дней в неделю
    if(!empty("Monday"))
        ++quan;
    if(!empty("Tuesday"))
        ++quan;
    if(!empty("Wednesday"))
        ++quan;
    if(!empty("Thursday"))
        ++quan;
    if(!empty("Friday"))
        ++quan;
    if(!empty("Saturday"))
        ++quan;

    return {name, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
}

//Проверка может ли препод вести пары в заданный день
//true — не может; false — может
bool Teacher::empty(const string &day) {
    bool st = true;
    if(day == "Monday"){
        for(auto && item : Monday) {
            if(item) {
                st = false;
                break;
            }
        }
        return st;
    }
    else if(day == "Tuesday"){
        for(auto && item : Tuesday) {
            if(item) {
                st = false;
                break;
            }
        }
        return st;
    }
    else if(day == "Wednesday"){
        for(auto && item : Wednesday) {
            if(item) {
                st = false;
                break;
            }
        }
        return st;
    }
    else if(day == "Thursday"){
        for(auto && item : Thursday) {
            if(item) {
                st = false;
                break;
            }
        }
        return st;
    }
    else if(day == "Friday"){
        for(auto && item : Friday) {
            if(item) {
                st = false;
                break;
            }
        }
        return st;
    }
    else if(day == "Saturday"){
        for(auto && item : Saturday) {
            if(item) {
                st = false;
                break;
            }
        }
        return st;
    }
    else {
        cerr << "Задан неккоректный день для .empty() !\n";
        exit(1);
    }
}

int Teacher::num_of_classes(const string &day) {
    int num = 0;
    if(day == "Monday"){
        for(bool && item : Monday) {
            if(item)
                ++num;
        }
    }
    else if(day == "Tuesday"){
        for(auto && item : Tuesday) {
            if(item)
                ++num;
        }
    }
    else if(day == "Wednesday"){
        for(auto && item : Wednesday) {
            if(item)
                ++num;
        }
    }
    else if(day == "Thursday"){
        for(auto && item : Thursday) {
            if(item)
                ++num;
        }
    }
    else if(day == "Friday"){
        for(auto && item : Friday) {
            if(item)
                ++num;
        }
    }
    else if(day == "Saturday"){
        for(auto && item : Saturday) {
            if(item)
                ++num;
        }
    }
    else {
        cerr << "Задан неккоректный день для .empty() !\n";
        exit(1);
    }

    return num;
}

int Teacher::num_of_classes(const string &day, const int &start) {
    if(start < 0 || start > 5) {
        cerr << "Неверно задан start в num_of_classes(day, start)\n";
        exit(1);
    }
    int num = 0;
    if(day == "Monday"){
        for(int i = start; i < Monday.size(); ++i) {
            if(Monday[i])
                ++num;
        }
    }
    else if(day == "Tuesday"){
        for(int i = start; i < Tuesday.size(); ++i) {
            if(Tuesday[i])
                ++num;
        }
    }
    else if(day == "Wednesday"){
        for(int i = start; i < Wednesday.size(); ++i) {
            if(Wednesday[i])
                ++num;
        }
    }
    else if(day == "Thursday"){
        for(int i = start; i < Thursday.size(); ++i) {
            if(Thursday[i])
                ++num;
        }
    }
    else if(day == "Friday"){
        for(int i = start; i < Friday.size(); ++i) {
            if(Friday[i])
                ++num;
        }
    }
    else if(day == "Saturday"){
        for(int i = start; i < Saturday.size(); ++i) {
            if(Saturday[i])
                ++num;
        }
    }
    else {
        cerr << "Задан неккоректный день для .empty() !\n";
        exit(1);
    }

    return num;
}


bool Teacher::operator==(const Teacher &teacher) const {
    if(name == teacher.name && quan == teacher.quan && Monday == teacher.Monday &&
               Tuesday == teacher.Tuesday && Wednesday == teacher.Wednesday &&
               Thursday == teacher.Thursday && Friday == teacher.Friday && Saturday == teacher.Saturday) {
        return true;
    }
    return false;
}


Teacher::~Teacher() = default;
