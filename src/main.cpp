#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <limits>
#include <chrono>
#include <thread>
#include <exception>
#include <utility>
#include <list>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include "exception.hpp"
#include "journal.hpp" 

using namespace std;

signed int main(void) 
{
    SystemManager systemM;
    bool exitProgram = false;

    try
    {
        while(!exitProgram) 
        {
            clearConsole();
            cout <<"<<< To select one of the items, write the number below >>>" << endl; // Для выбора, ниже напиши номер указывающий на пункт справа
            cout << "\n";
            cout <<"\t1 *Admin registration" << endl; // Регистрация для админов и преподавателей
            cout <<"\t2 *Admin login" << endl; // Вход для админов
            cout <<"\t3 *Student registration" << endl; // Регистрация для студентов
            cout <<"\t4 *Student login" << endl; // Вход для студентов
            cout <<"\t5 *Exit" << endl; // Выход

            int choice;

            cout <<"\nNumber #";
            cin >> choice;
            cin.ignore();

            User* currentUser = nullptr;

            switch(choice) 
            {
                case 1:
                    systemM.registration(true);
                    break;
                case 2:
                    currentUser= systemM.login(true);
                    if(currentUser) 
                    {
                        currentUser->showMenu();
                        delete currentUser;
                    }
                    break;
                case 3:
                    systemM.registration(false);
                    break;
                case 4:
                    currentUser=systemM.login(false);
                    if(currentUser) 
                    {
                        currentUser->showMenu();
                        delete currentUser;
                    }
                    break;
                case 5:
                    exitProgram=true;
                    break;
                default:
                    cout << "Invalid command!" << endl; // Неверная команда
            }
        }
    }
    catch(const MyExceptions::ErrorAnswerAdmin & e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const MyExceptions:: ErrorAnswerUser & e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
