#include <iostream>
#include <vector>
#include "Group.h"
using namespace std;

int main() {
//    string file_name;
//    cin >>file_name;
//
//    Group group(file_name);
    Group group("input.txt");

    auto tmp = group.create_schedule();

    group.print_schedule("output.txt");

    return 0;
}

//vector<vector<pair<Teacher, bool>>> Group::create_schedule() {
////    bool window = false;
////    int quantity_cls = 0;   //Количество пар в один день (<4)
////
////    vector<Teacher> techs;      //Преподаватели, ведущие пары в данный день
////    vector<Teacher> tmp_techs;  ////Преподаватели, ведущие определённую пару в данный день
////
////    //Выделяем преподователей, могущих вести в понедельник
////    for(auto & teacher : teachers) {
////        if(!teacher.empty("Monday")) {
////            techs.push_back(teacher);
////        }
////    }
////    /*
////    while(quantity_cls < 4) {
////        window = false;
//////        int k = 0;
////        if(!Monday[0].second) {
////            //Заполняем tmp_tech
////            for(Teacher &teacher : techs) {
////                if(teacher.Monday[0]) {
////                    tmp_techs.push_back(teacher);
////                }
////            }
////            //Выбрать преподавателя
////            for(Teacher &teacher : tmp_techs) {
////                if(teacher.Monday[0]) {
////                    Monday[0] = make_pair(teacher, true);
////                    teacher.Monday[0] = false;
////                }
////            }
////
////            ++quantity_cls;
////        }
////
////
////    }
////    */
////
////    int current_cls = 0; //Номер текущей пары (<6)
////    //Выделяем преподавателей, могущих вести первую пару
////    for(Teacher &teacher: techs) {
////        if(teacher.Monday[current_cls /*первая пара*/]) {
////            tmp_techs.push_back(teacher);
////        }
////    }
////
////    //Выделяем преподавателей, могущих вести только в один день
////    /*
////    for(Teacher &teacher: tmp_techs) {
////        if(teacher.quan == 1)
////            specific_techs.push_back(teacher);
////    }
////*/
////
////    bool st = false; //Проверка на то, что препод может вести только одну пару
////
////    Teacher tmp_teach;
////    //Составляем расписание на понедельник
////    vector<Teacher> specific_techs;
////    for(const Teacher &teacher: tmp_techs) {
////        if(teacher.quan == 1)           //Те, кто ведут 1 день в неделю
////            specific_techs.push_back(teacher);
////    }
////    while(quantity_cls < 4 || current_cls < 6) {
////        if(tmp_techs.empty()){  //Если никто не может вести в этот день
////            if (!window) {
////                ++current_cls;
////            }
////        }
////
////        if(!specific_techs.empty()) {
////            for(int i = 0; i < specific_techs.size(); ++i) {
////                if(specific_techs[i].num_of_classes("Monday", current_cls) == 1){
////                    //Поставили препода, который может вести только эту пару
////                    Monday[current_cls] = make_pair(specific_techs[i], true);
////                    tmp_teach = specific_techs[i];
////                    specific_techs.erase(specific_techs.begin() + i);
////                    st = true;
////                    break;
////                }
////            }
////            if(st){
////                tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
////            } else {
////                /*
////                if(current_cls == 0 || (current_cls == 1 && !Monday[current_cls - 1].second)
////                    || (current_cls >= 2 && !Monday[current_cls - 2].second && Monday[current_cls - 1].second)) {
////                    ++current_cls;
////                }
////                */
////
////                for(int i = 0; i < specific_techs.size(); ++i) {
////                    if(specific_techs[i].num_of_classes("Monday", current_cls) == 2){
////                        //Поставили препода, который может вести только эту пару
////                        Monday[current_cls] = make_pair(specific_techs[i], true);
////                        tmp_teach = specific_techs[i];
////                        specific_techs.erase(specific_techs.begin() + i);
////                        st = true;
////                        break;
////                    }
////                }
////                if(st){
////                    tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
////                } else {
////                    for(int i = 0; i < specific_techs.size(); ++i) {
////                        if(specific_techs[i].num_of_classes("Monday", current_cls) == 3){
////                            //Поставили препода, который может вести только эту пару
////                            Monday[current_cls] = make_pair(specific_techs[i], true);
////                            tmp_teach = specific_techs[i];
////                            specific_techs.erase(specific_techs.begin() + i);
////                            st = true;
////                            break;
////                        }
////                    }
////                    if(st){
////                        tmp_teachers.erase(find(tmp_teachers.begin(), tmp_teachers.end(), tmp_teach));
////                    }
////                    else {
////                        for(int i = 0; i < specific_techs.size(); ++i) {
////                            //Поставили препода, который может вести только эту пару
////                            Monday[current_cls] = make_pair(specific_techs[i], true);
////                            tmp_teach = specific_techs[i];
////                            specific_techs.erase(specific_techs.begin() + i);
////                            st = true;
////                            break;
////                        }
////                    }
////                }
////
////            }
////
////            ++quantity_cls;
////            ++current_cls;
////        }
////        else {
////            //Смотрим тех, кто может вести только 2 дня в неделю
////
////
////        }
////    }
//
//
//    return vector<vector<pair<Teacher, bool>>>();
//}