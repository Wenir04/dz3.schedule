//
// Created by Maxim Kukuruz on 1/12/23.
//

#include "Group.h"

vector<Teacher> Group::file_teachers_read(const string &file_name) {
    ifstream file(file_name);
    if(!file.is_open()) {
        cerr << "Не удалось открыть файл: "<< file_name << '\n';
        exit(1);
    }

    Teacher tmp_teacher;
    while(!file.eof()) {
        tmp_teacher.file_read(file);
        teachers.push_back(tmp_teacher);
    }

    file.close();
    tmp_teachers = teachers;
    return teachers;
}


Group::Group() {
    teachers.resize(15, Teacher());
    Monday.resize(6, make_pair(Teacher(), false));
    Tuesday.resize(6, make_pair(Teacher(), false));
    Wednesday.resize(6, make_pair(Teacher(), false));
    Thursday.resize(6, make_pair(Teacher(), false));
    Friday.resize(6, make_pair(Teacher(), false));
    Saturday.resize(6, make_pair(Teacher(), false));

    Schedule.resize(6, vector<pair<Teacher, bool>> (4,  make_pair(Teacher(), false)));
}

Group::Group(const string &file_name) {
    Monday.resize(6, make_pair(Teacher(), false));
    Tuesday.resize(6, make_pair(Teacher(), false));
    Wednesday.resize(6, make_pair(Teacher(), false));
    Thursday.resize(6, make_pair(Teacher(), false));
    Friday.resize(6, make_pair(Teacher(), false));
    Saturday.resize(6, make_pair(Teacher(), false));

    Schedule.resize(6, vector<pair<Teacher, bool>> (4,  make_pair(Teacher(), false)));

    file_teachers_read(file_name);
}

vector<vector<pair<Teacher, bool>>> Group::create_schedule() {
    bool window = false;
    int quantity_cls = 0;   //Количество пар в один день (<4)

    vector<Teacher> techs;      //Преподаватели, ведущие пары в данный день
    vector<Teacher> tmp_techs;  ////Преподаватели, ведущие определённую пару в данный день


    int current_cls = 0; //Номер текущей пары (<6)
    bool st = false; //Проверка на то, что препод может вести только одну пару

    Teacher tmp_teach;

    //Выделяем преподователей, могущих вести в понедельник
    for(auto & teacher : tmp_teachers) {
        if(!teacher.empty("Monday")) {
            techs.push_back(teacher);
        }
    }
    //Составляем расписание на понедельник
    vector<Teacher> specific_techs;
    int k = 0;
    while(quantity_cls < 4 && current_cls < 6) {
        st = false;
        tmp_techs.clear();
        //Выделяем преподавателей, могущих вести первую пару
        for(Teacher &teacher: techs) {
            if(teacher.Monday[current_cls /*первая пара*/]) {
                tmp_techs.push_back(teacher);
            }
        }
        specific_techs.clear();
        for(const Teacher &teacher: tmp_techs) {
            if(teacher.quan == 1)           //Те, кто ведут 1 день в неделю
                specific_techs.push_back(teacher);
        }


        if(tmp_techs.empty()){  //Если никто не может вести в этот день
            if(quantity_cls != 0 && !window) {
                window = true;
                ++k;
                ++current_cls;
            } else if(k == 1){
                //Если намечается второе окно, то break
                break;
            }
            if (!window) {
                ++current_cls;
            }
        }
        else if(!specific_techs.empty()) {
            for(int i = 0; i < specific_techs.size(); ++i) {
                if(specific_techs[i].num_of_classes("Monday", current_cls) == 1){
                    //Поставили препода, который может вести только эту пару
                    Monday[current_cls] = make_pair(specific_techs[i], true);
                    tmp_teach = specific_techs[i];
                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                    st = true;
                    break;
                }
            }
            if(st){
                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
            } else {
                /*
                if(current_cls == 0 || (current_cls == 1 && !Monday[current_cls - 1].second)
                    || (current_cls >= 2 && !Monday[current_cls - 2].second && Monday[current_cls - 1].second)) {
                    ++current_cls;
                }
                */

                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Monday", current_cls) == 2){
                        //Поставили препода, который может вести только эту пару
                        Monday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Monday", current_cls) == 3){
                            //Поставили препода, который может вести только эту пару
                            Monday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    }
                    else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            //Поставили препода, который может вести только эту пару
                            Monday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                }

            }

            ++quantity_cls;
            ++current_cls;
        }
        else {
            //Смотрим тех, кто может вести только 2 дня в неделю

            specific_techs.clear();
            for(const Teacher &teacher: tmp_techs) {
                if(teacher.quan == 2)           //Те, кто ведут 2 дня в неделю
                    specific_techs.push_back(teacher);
            }
            if(!specific_techs.empty()) {
                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Monday", current_cls) == 1){
                        //Поставили препода, который может вести только эту пару
                        Monday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Monday", current_cls) == 2){
                            //Поставили препода, который может вести только эту пару
                            Monday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Monday", current_cls) == 3){
                                //Поставили препода, который может вести только эту пару
                                Monday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        }
                        else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                //Поставили препода, который может вести только эту пару
                                Monday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                    }

                }

                ++quantity_cls;
                ++current_cls;
            } else {
                //Смотрим тех, кто может вести только 3 дня в неделю

                specific_techs.clear();
                for(const Teacher &teacher: tmp_techs) {
                    if(teacher.quan == 3)           //Те, кто ведут 3 дняВ в неделю
                        specific_techs.push_back(teacher);
                }
                if(!specific_techs.empty()) {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Monday", current_cls) == 1){
                            //Поставили препода, который может вести только эту пару
                            Monday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Monday", current_cls) == 2){
                                //Поставили препода, который может вести только эту пару
                                Monday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Monday", current_cls) == 3){
                                    //Поставили препода, который может вести только эту пару
                                    Monday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            }
                            else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    //Поставили препода, который может вести только эту пару
                                    Monday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                        }

                    }

                    ++quantity_cls;
                    ++current_cls;
                } else {
                    specific_techs = tmp_techs;
                    if(!specific_techs.empty()) {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Monday", current_cls) == 1){
                                //Поставили препода, который может вести только эту пару
                                Monday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Monday", current_cls) == 2){
                                    //Поставили препода, который может вести только эту пару
                                    Monday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            } else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    if(specific_techs[i].num_of_classes("Monday", current_cls) == 3){
                                        //Поставили препода, который может вести только эту пару
                                        Monday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                }
                                if(st){
                                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                }
                                else {
                                    for(int i = 0; i < specific_techs.size(); ++i) {
                                        //Поставили препода, который может вести только эту пару
                                        Monday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                    if(st){
                                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                    }
                                }
                            }
                        }

                        ++quantity_cls;
                        ++current_cls;
                    }
                }
            }
        }
    }


    //Выделяем преподователей, могущих вести во вторник
    for(auto & teacher : tmp_teachers) {
        if(!teacher.empty("Tuesday")) {
            techs.push_back(teacher);
        }
    }
    //Составляем расписание на вторник
    specific_techs.clear();
    tmp_teach.clear();
    quantity_cls = current_cls = k = 0;
    window = false;
    while(quantity_cls < 4 && current_cls < 6) {
        st = false;
        tmp_techs.clear();
        //Выделяем преподавателей, могущих вести первую пару
        for(Teacher &teacher: techs) {
            if(teacher.Tuesday[current_cls /*первая пара*/]) {
                tmp_techs.push_back(teacher);
            }
        }
        specific_techs.clear();
        for(const Teacher &teacher: tmp_techs) {
            if(teacher.quan == 1)           //Те, кто ведут 1 день в неделю
                specific_techs.push_back(teacher);
        }


        if(tmp_techs.empty()){  //Если никто не может вести в этот день
            if(quantity_cls != 0 && !window) {
                window = true;
                ++k;
                ++current_cls;
            } else if(k == 1){
                //Если намечается второе окно, то break
                break;
            }
            else if (!window) {
                ++current_cls;
            }
        }
        else if(!specific_techs.empty()) {
            for(int i = 0; i < specific_techs.size(); ++i) {
                if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 1){
                    //Поставили препода, который может вести только эту пару
                    Tuesday[current_cls] = make_pair(specific_techs[i], true);
                    tmp_teach = specific_techs[i];
                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                    st = true;
                    break;
                }
            }
            if(st){
                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
            } else {
                /*
                if(current_cls == 0 || (current_cls == 1 && !Tuesday[current_cls - 1].second)
                    || (current_cls >= 2 && !Tuesday[current_cls - 2].second && Tuesday[current_cls - 1].second)) {
                    ++current_cls;
                }
                */

                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 2){
                        //Поставили препода, который может вести только эту пару
                        Tuesday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 3){
                            //Поставили препода, который может вести только эту пару
                            Tuesday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    }
                    else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            //Поставили препода, который может вести только эту пару
                            Tuesday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                }

            }

            ++quantity_cls;
            ++current_cls;
        }
        else {
            //Смотрим тех, кто может вести только 2 дня в неделю

//            specific_techs.clear();
            for(const Teacher &teacher: tmp_techs) {
                if(teacher.quan == 2)           //Те, кто ведут 2 дня в неделю
                    specific_techs.push_back(teacher);
            }
            if(!specific_techs.empty()) {
                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 1){
                        //Поставили препода, который может вести только эту пару
                        Tuesday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 2){
                            //Поставили препода, который может вести только эту пару
                            Tuesday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 3){
                                //Поставили препода, который может вести только эту пару
                                Tuesday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        }
                        else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                //Поставили препода, который может вести только эту пару
                                Tuesday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                    }

                }

                ++quantity_cls;
                ++current_cls;
            } else {
                //Смотрим тех, кто может вести только 3 дня в неделю

//                specific_techs.clear();
                for(const Teacher &teacher: tmp_techs) {
                    if(teacher.quan == 3)           //Те, кто ведут 3 дняВ в неделю
                        specific_techs.push_back(teacher);
                }
                if(!specific_techs.empty()) {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 1){
                            //Поставили препода, который может вести только эту пару
                            Tuesday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 2){
                                //Поставили препода, который может вести только эту пару
                                Tuesday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 3){
                                    //Поставили препода, который может вести только эту пару
                                    Tuesday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            }
                            else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    //Поставили препода, который может вести только эту пару
                                    Tuesday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                        }

                    }

                    ++quantity_cls;
                    ++current_cls;
                } else {
                    specific_techs = tmp_techs;
                    if(!specific_techs.empty()) {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 1){
                                //Поставили препода, который может вести только эту пару
                                Tuesday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 2){
                                    //Поставили препода, который может вести только эту пару
                                    Tuesday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            } else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    if(specific_techs[i].num_of_classes("Tuesday", current_cls) == 3){
                                        //Поставили препода, который может вести только эту пару
                                        Tuesday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                }
                                if(st){
                                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                }
                                else {
                                    for(int i = 0; i < specific_techs.size(); ++i) {
                                        //Поставили препода, который может вести только эту пару
                                        Tuesday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                    if(st){
                                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                    }
                                }
                            }

                        }

                        ++quantity_cls;
                        ++current_cls;
                    }
                }
            }
        }
    }

    //Выделяем преподователей, могущих вести в среду
    for(auto & teacher : tmp_teachers) {
        if(!teacher.empty("Wednesday")) {
            techs.push_back(teacher);
        }
    }
    //Составляем расписание на среду
    specific_techs.clear();
    tmp_teach.clear();
    quantity_cls = current_cls = k = 0;
    window = false;
    while(quantity_cls < 4 && current_cls < 6) {
        st = false;
        tmp_techs.clear();
        //Выделяем преподавателей, могущих вести первую пару
        for(Teacher &teacher: techs) {
            if(teacher.Wednesday[current_cls /*первая пара*/]) {
                tmp_techs.push_back(teacher);
            }
        }
        specific_techs.clear();
        for(const Teacher &teacher: tmp_techs) {
            if(teacher.quan == 1)           //Те, кто ведут 1 день в неделю
                specific_techs.push_back(teacher);
        }


        if(tmp_techs.empty()){  //Если никто не может вести в этот день
            if(quantity_cls != 0 && !window) {
                window = true;
                ++k;
                ++current_cls;
            } else if(k == 1){
                //Если намечается второе окно, то break
                break;
            }
            else if (!window) {
                ++current_cls;
            }
        }
        else if(!specific_techs.empty()) {
            for(int i = 0; i < specific_techs.size(); ++i) {
                if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 1){
                    //Поставили препода, который может вести только эту пару
                    Wednesday[current_cls] = make_pair(specific_techs[i], true);
                    tmp_teach = specific_techs[i];
                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                    st = true;
                    break;
                }
            }
            if(st){
                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
            } else {
                /*
                if(current_cls == 0 || (current_cls == 1 && !Wednesday[current_cls - 1].second)
                    || (current_cls >= 2 && !Wednesday[current_cls - 2].second && Wednesday[current_cls - 1].second)) {
                    ++current_cls;
                }
                */

                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 2){
                        //Поставили препода, который может вести только эту пару
                        Wednesday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 3){
                            //Поставили препода, который может вести только эту пару
                            Wednesday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    }
                    else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            //Поставили препода, который может вести только эту пару
                            Wednesday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                }

            }

            ++quantity_cls;
            ++current_cls;
        }
        else {
            //Смотрим тех, кто может вести только 2 дня в неделю

            specific_techs.clear();
            for(const Teacher &teacher: tmp_techs) {
                if(teacher.quan == 2)           //Те, кто ведут 2 дня в неделю
                    specific_techs.push_back(teacher);
            }
            if(!specific_techs.empty()) {
                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 1){
                        //Поставили препода, который может вести только эту пару
                        Wednesday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 2){
                            //Поставили препода, который может вести только эту пару
                            Wednesday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 3){
                                //Поставили препода, который может вести только эту пару
                                Wednesday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        }
                        else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                //Поставили препода, который может вести только эту пару
                                Wednesday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                    }

                }

                ++quantity_cls;
                ++current_cls;
            } else {
                //Смотрим тех, кто может вести только 3 дня в неделю

                specific_techs.clear();
                for(const Teacher &teacher: tmp_techs) {
                    if(teacher.quan == 3)           //Те, кто ведут 3 дняВ в неделю
                        specific_techs.push_back(teacher);
                }
                if(!specific_techs.empty()) {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 1){
                            //Поставили препода, который может вести только эту пару
                            Wednesday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 2){
                                //Поставили препода, который может вести только эту пару
                                Wednesday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 3){
                                    //Поставили препода, который может вести только эту пару
                                    Wednesday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            }
                            else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    //Поставили препода, который может вести только эту пару
                                    Wednesday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                        }

                    }

                    ++quantity_cls;
                    ++current_cls;
                } else {
                    specific_techs = tmp_techs;
                    if(!specific_techs.empty()) {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 1){
                                //Поставили препода, который может вести только эту пару
                                Wednesday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 2){
                                    //Поставили препода, который может вести только эту пару
                                    Wednesday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            } else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    if(specific_techs[i].num_of_classes("Wednesday", current_cls) == 3){
                                        //Поставили препода, который может вести только эту пару
                                        Wednesday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                }
                                if(st){
                                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                }
                                else {
                                    for(int i = 0; i < specific_techs.size(); ++i) {
                                        //Поставили препода, который может вести только эту пару
                                        Wednesday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                    if(st){
                                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                    }
                                }
                            }

                        }

                        ++quantity_cls;
                        ++current_cls;
                    }
                }
            }
        }
    }

    //Выделяем преподователей, могущих вести в четверг
    for(auto & teacher : tmp_teachers) {
        if(!teacher.empty("Thursday")) {
            techs.push_back(teacher);
        }
    }
    //Составляем расписание на четверг
    specific_techs.clear();
    tmp_teach.clear();
    quantity_cls = current_cls = k = 0;
    window = false;
    while(quantity_cls < 4 && current_cls < 6) {
        st = false;
        tmp_techs.clear();
        //Выделяем преподавателей, могущих вести первую пару
        for(Teacher &teacher: techs) {
            if(teacher.Thursday[current_cls /*первая пара*/]) {
                tmp_techs.push_back(teacher);
            }
        }
        specific_techs.clear();
        for(const Teacher &teacher: tmp_techs) {
            if(teacher.quan == 1)           //Те, кто ведут 1 день в неделю
                specific_techs.push_back(teacher);
        }


        if(tmp_techs.empty()){  //Если никто не может вести в этот день
            if(quantity_cls != 0 && !window) {
                window = true;
                ++k;
                ++current_cls;
            } else if(k == 1){
                //Если намечается второе окно, то break
                break;
            }
            else if (!window) {
                ++current_cls;
            }
        }
        else if(!specific_techs.empty()) {
            for(int i = 0; i < specific_techs.size(); ++i) {
                if(specific_techs[i].num_of_classes("Thursday", current_cls) == 1){
                    //Поставили препода, который может вести только эту пару
                    Thursday[current_cls] = make_pair(specific_techs[i], true);
                    tmp_teach = specific_techs[i];
                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                    st = true;
                    break;
                }
            }
            if(st){
                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
            } else {
                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Thursday", current_cls) == 2){
                        //Поставили препода, который может вести только эту пару
                        Thursday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Thursday", current_cls) == 3){
                            //Поставили препода, который может вести только эту пару
                            Thursday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    }
                    else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            //Поставили препода, который может вести только эту пару
                            Thursday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                }

            }

            ++quantity_cls;
            ++current_cls;
        }
        else {
            //Смотрим тех, кто может вести только 2 дня в неделю

            specific_techs.clear();
            for(const Teacher &teacher: tmp_techs) {
                if(teacher.quan == 2)           //Те, кто ведут 2 дня в неделю
                    specific_techs.push_back(teacher);
            }
            if(!specific_techs.empty()) {
                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Thursday", current_cls) == 1){
                        //Поставили препода, который может вести только эту пару
                        Thursday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Thursday", current_cls) == 2){
                            //Поставили препода, который может вести только эту пару
                            Thursday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Thursday", current_cls) == 3){
                                //Поставили препода, который может вести только эту пару
                                Thursday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        }
                        else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                //Поставили препода, который может вести только эту пару
                                Thursday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                    }

                }

                ++quantity_cls;
                ++current_cls;
            } else {
                //Смотрим тех, кто может вести только 3 дня в неделю

                specific_techs.clear();
                for(const Teacher &teacher: tmp_techs) {
                    if(teacher.quan == 3)           //Те, кто ведут 3 дня в неделю
                        specific_techs.push_back(teacher);
                }
                if(!specific_techs.empty()) {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Thursday", current_cls) == 1){
                            //Поставили препода, который может вести только эту пару
                            Thursday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Thursday", current_cls) == 2){
                                //Поставили препода, который может вести только эту пару
                                Thursday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Thursday", current_cls) == 3){
                                    //Поставили препода, который может вести только эту пару
                                    Thursday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            }
                            else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    //Поставили препода, который может вести только эту пару
                                    Thursday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                        }

                    }

                    ++quantity_cls;
                    ++current_cls;
                } else {
                    specific_techs = tmp_techs;
                    if(!specific_techs.empty()) {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Thursday", current_cls) == 1){
                                //Поставили препода, который может вести только эту пару
                                Thursday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Thursday", current_cls) == 2){
                                    //Поставили препода, который может вести только эту пару
                                    Thursday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            } else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    if(specific_techs[i].num_of_classes("Thursday", current_cls) == 3){
                                        //Поставили препода, который может вести только эту пару
                                        Thursday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                }
                                if(st){
                                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                }
                                else {
                                    for(int i = 0; i < specific_techs.size(); ++i) {
                                        //Поставили препода, который может вести только эту пару
                                        Thursday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                    if(st){
                                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                    }
                                }
                            }

                        }

                        ++quantity_cls;
                        ++current_cls;
                    }
                }
            }
        }
    }

    //Выделяем преподователей, могущих вести в пятницу
    for(auto & teacher : tmp_teachers) {
        if(!teacher.empty("Friday")) {
            techs.push_back(teacher);
        }
    }
    //Составляем расписание на пятницу
    specific_techs.clear();
    tmp_teach.clear();
    quantity_cls = current_cls = k = 0;
    window = false;
    while(quantity_cls < 4 && current_cls < 6) {
        st = false;
        tmp_techs.clear();
        //Выделяем преподавателей, могущих вести первую пару
        for(Teacher &teacher: techs) {
            if(teacher.Friday[current_cls /*первая пара*/]) {
                tmp_techs.push_back(teacher);
            }
        }
        specific_techs.clear();
        for(const Teacher &teacher: tmp_techs) {
            if(teacher.quan == 1)           //Те, кто ведут 1 день в неделю
                specific_techs.push_back(teacher);
        }


        if(tmp_techs.empty()){  //Если никто не может вести в этот день
            if(quantity_cls != 0 && !window) {
                window = true;
                ++k;
                ++current_cls;
            } else if(k == 1){
                //Если намечается второе окно, то break
                break;
            }
            else if (!window) {
                ++current_cls;
            }
        }
        else if(!specific_techs.empty()) {
            for(int i = 0; i < specific_techs.size(); ++i) {
                if(specific_techs[i].num_of_classes("Friday", current_cls) == 1){
                    //Поставили препода, который может вести только эту пару
                    Friday[current_cls] = make_pair(specific_techs[i], true);
                    tmp_teach = specific_techs[i];
                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                    st = true;
                    break;
                }
            }
            if(st){
                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
            } else {
                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Friday", current_cls) == 2){
                        //Поставили препода, который может вести только эту пару
                        Friday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Friday", current_cls) == 3){
                            //Поставили препода, который может вести только эту пару
                            Friday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    }
                    else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            //Поставили препода, который может вести только эту пару
                            Friday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                }

            }

            ++quantity_cls;
            ++current_cls;
        }
        else {
            //Смотрим тех, кто может вести только 2 дня в неделю

            specific_techs.clear();
            for(const Teacher &teacher: tmp_techs) {
                if(teacher.quan == 2)           //Те, кто ведут 2 дня в неделю
                    specific_techs.push_back(teacher);
            }
            if(!specific_techs.empty()) {
                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Friday", current_cls) == 1){
                        //Поставили препода, который может вести только эту пару
                        Friday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Friday", current_cls) == 2){
                            //Поставили препода, который может вести только эту пару
                            Friday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Friday", current_cls) == 3){
                                //Поставили препода, который может вести только эту пару
                                Friday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        }
                        else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                //Поставили препода, который может вести только эту пару
                                Friday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                    }

                }

                ++quantity_cls;
                ++current_cls;
            } else {
                //Смотрим тех, кто может вести только 3 дня в неделю

                specific_techs.clear();
                for(const Teacher &teacher: tmp_techs) {
                    if(teacher.quan == 3)           //Те, кто ведут 3 дня в неделю
                        specific_techs.push_back(teacher);
                }
                if(!specific_techs.empty()) {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Friday", current_cls) == 1){
                            //Поставили препода, который может вести только эту пару
                            Friday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Friday", current_cls) == 2){
                                //Поставили препода, который может вести только эту пару
                                Friday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Friday", current_cls) == 3){
                                    //Поставили препода, который может вести только эту пару
                                    Friday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            }
                            else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    //Поставили препода, который может вести только эту пару
                                    Friday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                        }

                    }

                    ++quantity_cls;
                    ++current_cls;
                } else {
                    specific_techs = tmp_techs;
                    if(!specific_techs.empty()) {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Friday", current_cls) == 1){
                                //Поставили препода, который может вести только эту пару
                                Friday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Friday", current_cls) == 2){
                                    //Поставили препода, который может вести только эту пару
                                    Friday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            } else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    if(specific_techs[i].num_of_classes("Friday", current_cls) == 3){
                                        //Поставили препода, который может вести только эту пару
                                        Friday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                }
                                if(st){
                                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                }
                                else {
                                    for(int i = 0; i < specific_techs.size(); ++i) {
                                        //Поставили препода, который может вести только эту пару
                                        Friday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                    if(st){
                                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                    }
                                }
                            }

                        }

                        ++quantity_cls;
                        ++current_cls;
                    }
                }
            }
        }
    }

    //Выделяем преподователей, могущих вести в субботу
    for(auto & teacher : tmp_teachers) {
        if(!teacher.empty("Saturday")) {
            techs.push_back(teacher);
        }
    }
    //Составляем расписание на субботу
    specific_techs.clear();
    tmp_teach.clear();
    quantity_cls = current_cls = k = 0;
    window = false;
    while(quantity_cls < 4 && current_cls < 6) {
        st = false;
        tmp_techs.clear();
        //Выделяем преподавателей, могущих вести первую пару
        for(Teacher &teacher: techs) {
            if(teacher.Saturday[current_cls /*первая пара*/]) {
                tmp_techs.push_back(teacher);
            }
        }
        specific_techs.clear();
        for(const Teacher &teacher: tmp_techs) {
            if(teacher.quan == 1)           //Те, кто ведут 1 день в неделю
                specific_techs.push_back(teacher);
        }


        if(tmp_techs.empty()){  //Если никто не может вести в этот день
            if(quantity_cls != 0 && !window) {
                window = true;
                ++k;
                ++current_cls;
            } else if(k == 1){
                //Если намечается второе окно, то break
                break;
            }
            else if (!window) {
                ++current_cls;
            }
        }
        else if(!specific_techs.empty()) {
            for(int i = 0; i < specific_techs.size(); ++i) {
                if(specific_techs[i].num_of_classes("Saturday", current_cls) == 1){
                    //Поставили препода, который может вести только эту пару
                    Saturday[current_cls] = make_pair(specific_techs[i], true);
                    tmp_teach = specific_techs[i];
                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                    st = true;
                    break;
                }
            }
            if(st){
                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
            } else {
                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Saturday", current_cls) == 2){
                        //Поставили препода, который может вести только эту пару
                        Saturday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Saturday", current_cls) == 3){
                            //Поставили препода, который может вести только эту пару
                            Saturday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    }
                    else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            //Поставили препода, который может вести только эту пару
                            Saturday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                }

            }

            ++quantity_cls;
            ++current_cls;
        }
        else {
            //Смотрим тех, кто может вести только 2 дня в неделю

            specific_techs.clear();
            for(const Teacher &teacher: tmp_techs) {
                if(teacher.quan == 2)           //Те, кто ведут 2 дня в неделю
                    specific_techs.push_back(teacher);
            }
            if(!specific_techs.empty()) {
                for(int i = 0; i < specific_techs.size(); ++i) {
                    if(specific_techs[i].num_of_classes("Saturday", current_cls) == 1){
                        //Поставили препода, который может вести только эту пару
                        Saturday[current_cls] = make_pair(specific_techs[i], true);
                        tmp_teach = specific_techs[i];
                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                        st = true;
                        break;
                    }
                }
                if(st){
                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                } else {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Saturday", current_cls) == 2){
                            //Поставили препода, который может вести только эту пару
                            Saturday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Saturday", current_cls) == 3){
                                //Поставили препода, который может вести только эту пару
                                Saturday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        }
                        else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                //Поставили препода, который может вести только эту пару
                                Saturday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                    }

                }

                ++quantity_cls;
                ++current_cls;
            } else {
                //Смотрим тех, кто может вести только 3 дня в неделю

                specific_techs.clear();
                for(const Teacher &teacher: tmp_techs) {
                    if(teacher.quan == 3)           //Те, кто ведут 3 дня в неделю
                        specific_techs.push_back(teacher);
                }
                if(!specific_techs.empty()) {
                    for(int i = 0; i < specific_techs.size(); ++i) {
                        if(specific_techs[i].num_of_classes("Saturday", current_cls) == 1){
                            //Поставили препода, который может вести только эту пару
                            Saturday[current_cls] = make_pair(specific_techs[i], true);
                            tmp_teach = specific_techs[i];
                            techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                            st = true;
                            break;
                        }
                    }
                    if(st){
                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                    } else {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Saturday", current_cls) == 2){
                                //Поставили препода, который может вести только эту пару
                                Saturday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Saturday", current_cls) == 3){
                                    //Поставили препода, который может вести только эту пару
                                    Saturday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            }
                            else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    //Поставили препода, который может вести только эту пару
                                    Saturday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                        }

                    }

                    ++quantity_cls;
                    ++current_cls;
                } else {
                    specific_techs = tmp_techs;
                    if(!specific_techs.empty()) {
                        for(int i = 0; i < specific_techs.size(); ++i) {
                            if(specific_techs[i].num_of_classes("Saturday", current_cls) == 1){
                                //Поставили препода, который может вести только эту пару
                                Saturday[current_cls] = make_pair(specific_techs[i], true);
                                tmp_teach = specific_techs[i];
                                techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                st = true;
                                break;
                            }
                        }
                        if(st){
                            tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                        } else {
                            for(int i = 0; i < specific_techs.size(); ++i) {
                                if(specific_techs[i].num_of_classes("Saturday", current_cls) == 2){
                                    //Поставили препода, который может вести только эту пару
                                    Saturday[current_cls] = make_pair(specific_techs[i], true);
                                    tmp_teach = specific_techs[i];
                                    techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                    st = true;
                                    break;
                                }
                            }
                            if(st){
                                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                            } else {
                                for(int i = 0; i < specific_techs.size(); ++i) {
                                    if(specific_techs[i].num_of_classes("Saturday", current_cls) == 3){
                                        //Поставили препода, который может вести только эту пару
                                        Saturday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));//ogo
                                        st = true;
                                        break;
                                    }
                                }
                                if(st){
                                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                }
                                else {
                                    for(int i = 0; i < specific_techs.size(); ++i) {
                                        //Поставили препода, который может вести только эту пару
                                        Saturday[current_cls] = make_pair(specific_techs[i], true);
                                        tmp_teach = specific_techs[i];
                                        techs.erase(find(techs.begin(), techs.end(), tmp_teach));
                                        st = true;
                                        break;
                                    }
                                    if(st){
                                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
                                    }
                                }
                            }

                        }

                        ++quantity_cls;
                        ++current_cls;
                    }
                }
            }
        }
    }

    if(!tmp_teachers.empty()) {
        cerr << "Не все учителя работают ! Обсудите время с преподавателями или уволят !\n";
    }

    Schedule = {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
    return Schedule;
}

void Group::print_schedule() {
    cout << "Schedule:\n";
    cout << "Group — " << name << "\n\n";


    for(int i = 0; i < Schedule.size(); ++i) {
        if(i == 0)
            cout << "Monday\n";
        if(i == 1)
            cout << "\nTuesday\n";
        if(i == 2)
            cout << "\nWednesday\n";
        if(i == 3)
            cout << "\nThursday\n";
        if(i == 4)
            cout << "\nFriday\n";
        if(i == 5)
            cout << "\nSaturday\n";

        for(int j = 0; j < Schedule[i].size(); ++j) {
            if(Schedule[i][j].second) { //Если назначена пара
                cout << j + 1 << ": " << Schedule[i][j].first.name << '\n';
            } else {
                cout << j + 1 << ": ——\n";
            }
        }
    }
}

void Group::print_schedule(const string &file_name) {
    ofstream file(file_name, ios_base::trunc);
    if(!file.is_open()) {
        cerr << "Не удалось открыть файл: "<< file_name << '\n';
        exit(1);
    }

    file << "Schedule:\n";
    file << "Group — " << name << "\n\n";


    for(int i = 0; i < Schedule.size(); ++i) {
        if(i == 0)
            file << "Monday\n";
        if(i == 1)
            file << "\nTuesday\n";
        if(i == 2)
            file << "\nWednesday\n";
        if(i == 3)
            file << "\nThursday\n";
        if(i == 4)
            file << "\nFriday\n";
        if(i == 5)
            file << "\nSaturday\n";

        for(int j = 0; j < Schedule[i].size(); ++j) {
            if(Schedule[i][j].second) { //Если назначена пара
                file << j + 1 << ": " << Schedule[i][j].first.name << '\n';
            } else {
                file << j + 1 << ": ——\n";
            }
        }
    }
}



Group::~Group() = default;
