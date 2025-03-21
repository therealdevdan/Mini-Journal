#ifndef JOURNAL_HPP
#define JOURNAL_HPP


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



using unor_map_vec = std::unordered_map<std::string, std::pair<std::string, std::unordered_map<std::string, std::vector<std::string>>>>;
using unor_map_lst = std::unordered_map<std::string, std::pair<std::string, std::unordered_map<std::string, std::list<std::string>>>>;

auto timeSleep_oneSec = []() { std::this_thread::sleep_for(std::chrono::seconds(1)); };
auto ignoreEnter = []() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); };


//turn off all spaces ... (выключение всех пространств)
using std::cerr;
using std::string;
using std::unordered_map;
using std::vector;
using std::list;
using std::pair;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::make_pair;
using std::time;
using std::exception;
using std::any_of;
using std::isdigit;
using std::ispunct;
using std::isupper;
using std::numeric_limits;
using std::streamsize;
using std::chrono::seconds;
using std::this_thread::sleep_for;
using std::ctime;



#ifdef _WIN32 
#define CLEAR_SCREEN "cls" /* for win */
#else
#define CLEAR_SCREEN "clear" /* for linux */
#endif

/* for clear Console */ 
// (для очистки консоли)

void clearConsole() 
{
    system(CLEAR_SCREEN);
}


class User 
{
protected:
    string log;
    string pwd;
public:
    User(const string& log, const string& pwd) 
    : 
    log(log), 
    pwd(pwd) 
    { }

    virtual void showMenu(void) = 0;

    void personalAccount(void) 
    {
        clearConsole();
        cout << "---------------------" << endl;
        cout << "Your details" << endl;
        cout << "---------------------" << endl;
        cout << "Your login: " << log << endl;
        cout << "Your password: " << pwd << endl;
        cout <<endl;

        cout << "Do you want to change your details?" << endl;
        cout << endl;

        bool correctAnswer = false;

        while(!correctAnswer)
        {
            string op;
            cout << "(yes/no) -";
            cin >> op;

            if(op == "yes")
            {
                updateData();
                correctAnswer = true;
            }
            else if(op == "no")
            {
                cout << "\nLogging out of your personal account..." << endl;
                timeSleep_oneSec();
                clearConsole();
                correctAnswer = true;
            }
            else
            {
                cout << "\nInvalid command, please try again and enter the correct command. Thank you" << endl;
                correctAnswer = false;
            }
        }
    }

    User* updateData(void)
    {
        clearConsole();
        string NewLog;
        string NewPwd;
        cout << "Write your new login: ";
        cin >> NewLog;
        cout << "Write your new password: ";
        cin >> NewPwd;

        if (NewLog.size() < 5 || NewPwd.size() < 5) {
            cout << "--- VIOLATION--- Login and password must contain at least 5 characters!" << endl;
            return this;
        }
    
        log = NewLog; // data overwriting (перезапись данных)
        pwd = NewPwd;

        cout << endl;
        cout << "Data updated successfully!";
        cout << endl;
        timeSleep_oneSec();
        clearConsole();

        return this;
    }   

    virtual ~User()
    { }
};

class Admin : public User 
{
protected: // // Admin DATABASE (база данных для админов)
    std::unordered_map<std::string, std::pair<std::string, std::string>>& msgAdmin;
private:    
    unordered_map<string, pair<string, unordered_map<string, vector<string>>>> & data_st;
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> &reviews;
    std::unordered_map<string, string> &homeworks;
public:

    Admin() noexcept = default;

    Admin(const string& log, const string& pwd, std::unordered_map<std::string, std::pair<std::string, 
    std::unordered_map<std::string, std::vector<std::string>>>> &data_student, 
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> & rev,
    std::unordered_map<string, string>& hw, std::unordered_map<std::string, std::pair<std::string, std::string>>& msg) 
    : 
    User(log, pwd),
    data_st(data_student),
    reviews(rev),
    homeworks(hw),
    msgAdmin(msg)
    { }

    void showMenu() override 
    {
        clearConsole();

        bool inMenu = true;
        while(inMenu) 
        {
            cout << endl;
            cout << "--------------------------Admin menu--------------------------" << endl;
            cout << endl;
            cout << "1. Add schedule" << endl; // Добавить расписание
            cout << "2. Write a review about a student" << endl; // Написать отзыв об студенте
            cout << "3. Write homework" << endl; // Написать домашнее задание
            cout << "4. Personal account" << endl; // Персональные данные (личный кабинет)
            cout << "5. Show list of all students" << endl; // Показать список всех зарегестрированных студенческих аккаунтов
            cout << "6. View personal message box" << endl; // Показать персональные сообщения от студентов адресованные админам
            cout << "7. Proceed to role selection" << endl; // Перейти к выбору роли (студент/админ)

            cout << "\nEnter the number: "; 
            int action;

            cin >> action;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(action) 
            {
                case 1:
                    editScheduleStudent();
                    break;
                case 2:
                    writeReview();
                    break;
                case 3:
                    writeHWStudent();
                    break;
                case 4:
                    personalAccount();
                    break;
                case 5:
                    listStudents();
                    break;
                case 6:
                    readMessages();
                    break;
                case 7:
                    inMenu = false;

                    clearConsole();
                    break;
                default:
                    cout << "Wrong command!" << endl;

                    break;
            }
        }
    }

    // unordered_map<string, pair<string, unordered_map<string, vector<string>>>> & data_st;
    // lNameAndMsg.first
    // lNameAndMsg.second
    // lNameAndMsg (msg) msg.first


    void readMessages(void)
    {
        clearConsole();

        cout << "Your message/s" << endl;

        for(const auto& [fname, lNameAndMsg] : msgAdmin)
        {
            cout << endl;
            cout << "*You received 1 message from a student" << endl;
            cout << endl;
            cout << "Student name:";
            cout << fname << endl;
            
            cout << "Student's last name: ";
            cout << lNameAndMsg.first << endl;
            cout << "\n";

            cout << "His letter" << endl;
            cout << "- ";
            cout << lNameAndMsg.second << endl;
        }
        cout << endl;
        cout << endl;
    }

    void listStudents(void)
    {
        clearConsole();
        cout << "List of all students" << endl;

        cout << endl;

        int count_student = 1;
        for(const auto &[log, pwd] : data_st)
        {
            cout << "Login " << count_student << " of the student: " << log << endl;
            count_student++;
        }
    }

    void editScheduleStudent(void)
    {
        string UserLogin;
        bool logIsCorrect = false;
        cout << "Below, correctly provide the Login of the student to whom you want to add a schedule" << endl;
        while(!logIsCorrect)
        {
            cout << "\nWrite here ->";
            getline(cin, UserLogin);
            cout << endl;

            auto it = data_st.find(UserLogin);
            if(it != data_st.end())
            {
                logIsCorrect = true;
            }
            else
            {
                cout << "Student login found or not registered. Try again." << endl;
                logIsCorrect = false;

            }
        }

        cout << "\nWrite the days of the week where you want to add or change the schedule. To finish the survey of a day or schedule, simply write 'end'" << endl;
        cout << endl;

        unordered_map<string, std::vector<string>> schedule;

        while(true)
        {
            string day;
            cout << "Day of the week: ";
            getline(cin, day);
            cout << endl;
            if(day == "end")
            {
                break;
            }

            std::vector<std::string> lessons;
            while(true)
            {
                string lesson;
                cout << "Write a subject: ";
                getline(std::cin, lesson);
                if(lesson == "end")
                {
                    break;
                }
                lessons.push_back(lesson);
            }
            schedule[day] = lessons;
            lessons.clear();
        }
        data_st[UserLogin].second = schedule;

        string ans;
        cout << "Would you like to view the schedule you added?? (yes/no)" << endl;
        cout << "- ";
        getline(cin, ans);

        if(ans == "yes")
        {
            for(const auto &[day, lessons] : data_st[UserLogin].second) 
            {
                cout << "\aDay: " << day << endl;
                for(const auto &lesson : lessons) 
                {
                    cout << " -" << lesson << endl;
                }
            }
        }
        else if(ans=="no")
        {
            cout << "Exiting option..." << endl; 
        }
        else
        {
            cout << "Invalid command." << endl;
        }

    }

    void writeReview(void)
    {
        clearConsole();
        cout << "Please write your name and the title of the subject you teach so that the student understands what you are talking about." <<endl;
        cout << endl;

        string nameTeacher;
        string nameLesson;
        cout << "   Your name -";
        getline(cin, nameTeacher);

        cout << "   The name of your subject that you teach -";
        getline(cin, nameLesson);
        cout << endl;

        bool logIsCorrect = false;
        string reviewText;
        string studentLogin;

        while(!logIsCorrect)
        {
            cout << "Write Student Login -> ";
            getline(cin, studentLogin);
            auto it = data_st.find(studentLogin);
            if(it != data_st.end())
            {
                cout << "\nBelow, write a review " << log << endl;
                getline(cin, reviewText);
                reviews[studentLogin].push_back(make_pair(nameTeacher + " (" + nameLesson + ")", reviewText));
                logIsCorrect = true;
            }
            else
            {
                cout << "\nStudent login is not registered or not found, try again!" << endl;
                clearConsole();
            }
        }
        clearConsole();
        
        cout << "Feedback is being sent..." << endl;
        
        reviews[nameTeacher].push_back(make_pair(nameLesson, reviewText)); // std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& reviews;

        timeSleep_oneSec();
        cout << "Feedback sent!" << endl;
        timeSleep_oneSec();
        clearConsole();
    }  

    void writeHWStudent(void)   
    {
        clearConsole();

        bool stopped = true;
        while(stopped)
        {
            string lesson;
            string hw;

            cout << "Write a lesson you teach: ";
            getline(std::cin, lesson);
            
            cout << "Below, write your assignment: ";
            getline(cin, hw);

            cout << "\n";
            string cont;
            cout << "Would you like to write more? (yes/no) -> ";
            getline(cin, cont);
            cout << endl;

            homeworks[lesson] = hw;

            if(cont == "yes")
            {
                stopped = true;
            }
            else
            {
                stopped = false;
            }
        }

        cout << endl;
        cout << endl;
        cout << "Your task is being sent, please wait a second..." << endl;

        

        timeSleep_oneSec();
        cout << "SENT!" << endl;
        clearConsole();
    }
    
    ~Admin()
    { }
};

class Student : public User 
{
protected: // Student Data base (База данных студентов для хранения логинов, паролей, дз и отзывов от админов и сообщения для них)
    std::unordered_map<std::string, std::pair<std::string, std::unordered_map<std::string, std::vector<std::string>>>>& data_st;
private:
    std::unordered_map<string, std::pair<string, string>> & msgAdmin; // сообщениях которые адресованные администрации
    std::unordered_map<string, string> & homeworks; // ДЗ от админов
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& reviews; // отзывы от админов
public:
    Student() noexcept = default;

    Student(const std::string& log, const std::string& pwd, std::unordered_map<std::string, 
    std::pair<std::string, std::unordered_map<std::string, 
    std::vector<std::string>>>>& data_student, std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> &rev, 
    std::unordered_map<string, string> &hw, std::unordered_map<string, std::pair<std::string, std::string>> & msg) 
    : 
    User(log, pwd),
    data_st(data_student),
    reviews(rev),
    homeworks(hw),
    msgAdmin(msg)
    { }

    void showMenu() override 
    {
        clearConsole();

        bool inMenu = true;

        while(inMenu) 
        {
            cout << "------------------------Student menu------------------------" << endl;
            cout << endl;
            cout << "1. View schedule" << endl; // Показать расписание
            cout << "2. View homework" << endl; // Показать ДЗ
            cout << "3. View educational materials" << endl; // Показать учебные материалы
            cout << "4. View reviews" << endl; // Показать отзывы обо мне (адресованные лично на мой логин)
            cout << "5. Personal account" << endl; // Персональные данные (Личный кабинет)
            cout << "6. Write to the administration" << endl; // Написать администрации
            cout << "7. Proceed to role selection" << endl; // Перейти к выбору роли (студент/админ)

            cout << "\nEnter the number: ";

            int action;

            cin >> action;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(action) 
            {
                case 1:
                    viewSchedule();
                    break;
                case 2:
                    readHWStudent();
                    break;
                case 3:
                    SchoolsMaterial();
                    break;
                case 4:
                    ReadReview();
                    break;
                case 5:
                    personalAccount();
                    break;
                case 6:
                    writeMessageAdmin();
                    break;
                case 7:
                    inMenu = false;
                    clearConsole();
                    break;
                default:
                    invalidCommand();
                    break;
            }
        }
    }

    void invalidCommand(void)
    {
        cout << endl;
        cout << "Invalid command, please try again later..." << endl;
    }

    void HomeWorkStudent(void)
    {
        clearConsole();
        cout << "The teacher has not provided homework yet." << endl;
    }

    void SchoolsMaterial(void)
    {
        clearConsole();
        cout << endl;

        cout << "It's empty here for now!" << endl;

        cout << endl;
    }
    // unordered_map<string, pair<string, string>> reviews;

    void ReadReview(void)
    {
        clearConsole();
        auto it = reviews.find(log);
        if (it != reviews.end() && !it->second.empty())
        {
            cout << "You have received feedback:" << endl;
            for (const auto& review : it->second)
            {
                cout << "From: " << review.first << endl;
                cout << "Review text: " << review.second << endl;
                cout << endl;
            }
        }
        else
        {
            cout << "You don't have any reviews yet." << endl;
        }
    }

    void writeMessageAdmin(void)
    {
        clearConsole();

        string fname;
        cout << "Write your name" << endl;
        cout << "- ";
        getline(cin, fname);

        string lname;
        cout << "Write your last name" << endl;
        cout << "- ";
        getline(cin, lname);

        cout << "\n";
        string msg;
        cout << "Please write your message below in a respectful manner." << endl;
        cout << "Your message -";
        getline(cin, msg);

        msgAdmin[fname] = make_pair(lname, msg);
        cout << endl;
        cout << "Your message is being sent..." << endl;
        timeSleep_oneSec();

        cout << "Your message has been sent!" << endl; 
        cout << endl;
        cout << endl; 

        std::this_thread::sleep_for(std::chrono::seconds(2));

        clearConsole();              
    }

    void readHWStudent(void)
    {
        clearConsole();

        cout << "Your task/s below" << endl;

        cout << "\n";

        for(const auto &[lesson, hw] : homeworks)
        {
            cout << "Lesson " << lesson << endl;
            cout << "- " << hw;
            cout << endl;
        }
        cout << "\n";
    }

    void viewSchedule(void)
    {
        auto it = data_st.find(log);
        if(it != data_st.end())
        {
            // std::unordered_map<std::string, std::pair<std::string, std::unordered_map<std::string, std::vector<std::string>>>>
            //                         .first           .second                           .second.second (3)        
            for(auto &[day, lessons] : it->second.second /*unor map опция 3*/ )
            {
                cout << "--- Your schedule is for " << day << " ---" << endl;
                cout << endl;
                for(const auto &lesson : lessons)
                {
                    cout << " -" << lesson << endl;
                }
            }
            return;
        }
        cout << "\nYour schedule was not found" << endl;
        
        return;
    }

    ~Student()
    { } 

};

class SystemManager /* management of the entire system of data structures */
{
private:
    std::unordered_map<std::string, std::string> data_admin; // Database for administration (admin) (База данных админов)
    std::unordered_map<std::string, std::pair<std::string, std::unordered_map<std::string, std::vector<std::string>>>> data_st;// Database for student (База данных студентов)
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> reviews; // Database for using reviews (for both admins and students) (База данных для хранения отзывов)

    std::unordered_map<string ,string> homeworks; // Storing homework (Хранение ДЗ)
    std::unordered_map<std::string, std::pair<std::string, std::string>> msgAdmin; // Storing messages for both admins and students (Хранения сообщений)
    
    // Restrictions on filling in fields (login and password) (Правила верного заполнения регистрации и входа)
    bool containsDigit(const string& str) 
    {
        return any_of(str.begin(), str.end(), [](char ch) {
            return isdigit(ch);
        });
    }

    bool containsSpecialChar(const string& str) 
    {
        return any_of(str.begin(), str.end(), [](char ch) {
            return ispunct(ch);
        });
    }

    bool isFirstCharacterUppercase(const string& str) 
    {
        if (str.empty()) 
        {
            return false;
        }
        return isupper(static_cast<unsigned char>(str[0]));
    }

public:
    // Create your login and password (Создание своего логина и пароля)
    void registration(bool isAdmin)
    {
        clearConsole();
        string log;
        string pwd;

        cout << "\nIf you want to see the rule for filling in the data correctly, enter the symbol 'H'" << endl;
        cout << "To continue, enter any character" << endl;
        cout << endl;
        cout << "Enter the command -> ";

        char help;
        cin >> help;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(help == 'h' || help == 'H')
        {
            cout << endl;
            cout << "--- REGISTRATION RULES ---" << endl;
            cout << endl;
            cout << "---> Login or password must NOT be less than 5 characters long <---" << endl;
            cout << "---> Login or password must NOT contain spaces <---" << endl;
            cout << "---> Login MUST contain the first letter in capital letters <---" << endl;
            cout << "---> Your Login MUST contain at least one number. <---" << endl;
            cout << "---> Your password MUST contain at least one special character. (@#$&) <---" << endl;
            cout << endl;
        }
        bool SizeIsTrue = false;
        bool isUpperFChar = false;
        bool isDigit = false;
        bool megChar = false;

        while(SizeIsTrue != true || isUpperFChar != true || isDigit != true || megChar != true) 
        {
            cout << "\nPlease create your Login correctly: ";
            getline(cin, log);

            if(log.size() < 5) 
            {
                cout << "VIOLATION OF RULES! ->> Your Login MUST be at least 5 characters long!" << endl;
                SizeIsTrue = false;
            } 
            else 
            {
                SizeIsTrue = true;
            }

            // Rules for filling in fields correctly (login and password) (Корректировка создания своего логина и пароля)
            if(!isFirstCharacterUppercase(log)) 
            {
                cout << "VIOLATION OF RULES! ->> Login MUST contain the first capital letter" << endl;
                isUpperFChar = false;
            } 
            else 
            {
                isUpperFChar = true;
            }

            if(!containsDigit(log)) 
            {
                cout << "VIOLATION OF RULES! ->> Your Login MUST contain at least one digit" << endl;
                isDigit = false;
            } 
            else 
            {
                isDigit = true;
            }

            if(log.find(' ') != string::npos) 
            {
                cout << "VIOLATION OF RULES! ->> Login must NOT contain spaces!" << endl;
                megChar = false;
            } 
            else 
            {
                megChar = true;
            }
        }
 
        bool p_SizeIsTrue = false;
        bool p_isUpperFChar = false;
        bool p_isDigit = false;
        bool p_megChar = false;

        while(p_SizeIsTrue != true || p_isUpperFChar != true || p_isDigit != true || p_megChar != true) 
        {
            cout << "\nCreate your own password: ";
            getline(cin, pwd);

            if(pwd.size() < 5) 
            {
                cout << "VIOLATION OF RULES! ->> Your password MUST be at least 5 characters long!" << endl;
                p_SizeIsTrue = false;
            } 
            else 
            {
                p_SizeIsTrue = true;
            }

            if(!isFirstCharacterUppercase(pwd)) 
            {
                cout << "VIOLATION OF RULES! ->> Password MUST contain the first letter in capital letters" << endl;
                p_isUpperFChar = false;
            } 
            else 
            {
                p_isUpperFChar = true;
            }

            if(!containsDigit(pwd)) 
            {
                cout << "VIOLATION OF RULES! ->> Your password MUST contain at least one number" << endl;
                p_isDigit = false;
            } 
            else 
            {
                p_isDigit = true;
            }

            if(!containsSpecialChar(pwd)) 
            {
                cout << "VIOLATION OF RULES! ->> Your password MUST contain at least one special character (@#$&)" << endl;
                p_megChar = false;
            } 
            else 
            {
                p_megChar = true;
            }
        }

        if(isAdmin) 
        {
            data_admin[log] = pwd; 
        } 
        else 
        {
            data_st[log] = make_pair(pwd, unordered_map<string, vector<string>>()); 
        }

        cout<< endl;
        cout<< "Registration was SUCCESSFUL!" << endl;
        cout<<endl;

        timeSleep_oneSec();
        clearConsole();
    }
    // Entrance
    User* login(bool isAdmin) 
    {
        clearConsole();

        string log;
        string pwd;

        int attempts = 10;
        while(attempts > 0) 
        {
            cout << "\nEnter your Login: ";
            cin >> log;

            cout << "Enter your password: ";
            cin >> pwd;
            if(isAdmin) 
            {
                auto it = data_admin.find(log);
                if(it != data_admin.end() && it->second == pwd) 
                {
                    cout << "You have successfully logged into your account." << endl;
                    return new Admin(log, pwd, data_st, reviews, homeworks, msgAdmin); 
                }
            } 
            else 
            {
                auto it = data_st.find(log);
                if(it != data_st.end() && it->second.first == pwd) 
                {
                    cout << "You have successfully logged into your account." << endl;
                    return new Student(log, pwd, data_st, reviews, homeworks, msgAdmin); 
                }
            }

            attempts--;
            cout << endl;
            cout << "Incorrect Login or Password. Remaining attempts: " << attempts << endl;
            timeSleep_oneSec();
            clearConsole();
        }

        cout << "The number of login attempts has been exceeded." << endl;
        return nullptr;
    }

    ~SystemManager()
    { }
};

#endif // JOURNAL_HPP
