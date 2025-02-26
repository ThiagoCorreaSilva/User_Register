#include <fstream>
#include <cstdlib>
#include <memory>
#include <list>
#include <thread>
#include <chrono>
#include "person.hpp"

void create_user();
void save_in_csv( std::shared_ptr<std::ofstream>, Person );
void transfer_csv_to_dataBase( std::shared_ptr<std::ifstream>, const char * );
void visualize_dataBase();

std::list<Person> dataBase;
char answer;

int main()
{
    auto file_IN = std::make_shared<std::ifstream>();
    auto file_OUT = std::make_shared<std::ofstream>();
    const char *fileName {"files.csv"};

    std::cout << "Want to reset the data? [y/n]\n";
    std::cin >> answer;

    //To delet the file
    if (answer == 'y' || answer == 'Y') remove(fileName);

    //To not rewrite the files
    file_OUT->open(fileName, std::ios::app);

    //Pick all the data in CSV and transfer to dataBase
    transfer_csv_to_dataBase( file_IN, fileName);

    bool repeat {true};
    while(repeat)
    {
        system("cls");

        std::cout << "What you want to do?\n\n";
        std::cout << "Create a user_______________________: TYPE 1\n";
        std::cout << "Visualize the data base_____________: TYPE 2\n";
        std::cout << "Exit________________________________: TYPE 3\n\n";
        std::cin >> answer;

        //To create a new user
        if (answer == '1')
        {
            create_user();
            save_in_csv(file_OUT, dataBase.front());
        }

        else if (answer == '2') visualize_dataBase();

        else if (answer == '3') repeat = false;
    }

    system("cls");

    std::cout << "Thanks!\n";
    system("pause");

    return 0;
}

void create_user()
{
    std::string userName;
    int userAge;

    restartName:

    system("cls");
    std::cout << "Type the name of user\n";

    if (std::cin.peek() == '\n') std::cin.ignore();
    std::getline(std::cin, userName);

    //Verify if the userName already exist in dataBase
    if (!dataBase.empty())
    {
        for (Person user : dataBase)
        {
            if (user.getName() == userName)
            {
                std::cout << "\n\033[31mNAME ALREADY EXIST IN DATA BASE!\033[0m\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                goto restartName;
            }
        }
    }

    for (char letter : userName)
    {
        //To check if the letter is a digit or a symbol
        if (isdigit(letter) || ispunct(letter))
        {
            system("cls");
            std::cout << "\033[31mPLEASE, ONLY INSERT LETTERS!\033[0m\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));

            goto restartName;
        }
    }

    system("cls");
    std::cout << "Insert a age!\n";
    std::cin >> userAge;

    Person user;
    user.setName(userName);
    user.setAge(userAge);

    dataBase.push_front(user);

    system("cls");
    std::cout << "\033[32mUSER CREATED WITH SUCESS!\033[0m\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void save_in_csv( std::shared_ptr<std::ofstream> file_OUT, Person userToSave )
{
    if (!file_OUT->is_open())
    {
        system("cls");
        std::cout << "\033[31mSAVING FILE CANT BE OPEN!\033[0m!\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        //Fatal error
        exit(2);
    }

    //Save the user info in CSV FILE
    *file_OUT << userToSave.getName() + "," + std::to_string(userToSave.getAge()) + '\n';

    system("cls");
    std::cout << "\033[32mFILE SAVED WITH SUCESS!\033[0m\n";
}

void transfer_csv_to_dataBase( std::shared_ptr<std::ifstream> file_IN, const char *fileName )
{
    file_IN->open(fileName);

    if (!file_IN->is_open())
    {
        system("cls");

        std::cout << "\033[31mERROR IN OPENING THE SAVE FILE!\033[0m\n";
        std::cout << "\033[31mTHE PROGRAM GONNA BE CLOSED SOON!\033[0m\n";

        std::this_thread::sleep_for(std::chrono::seconds(4));

        //Fatal error
        exit(2);
    }

    const char delimiter {','};
    std::string word, userName, userAge;

    while(std::getline(*file_IN, word))
    {
        for (char letter : word)
        {
            //If the letter is the delimiter
            if (letter == delimiter) continue;

            //Check if letter is a number
            if (isdigit(letter))
            {
                //Append to string of age
                userAge += letter;
                continue;
            }

            //Append to string of name
            userName += letter;
        }

        //End of the line
        Person user;
        user.setName(userName);
        user.setAge(stoi(userAge));
        dataBase.push_front(user);

        //Reset the name and age to not append with the next name
        userName = "";
        userAge = "";
    }

    file_IN->close();
}

void visualize_dataBase()
{
    system("cls");

    if (dataBase.empty())
    {
        std::cout << "\033[31mDATA BASE IS EMPTY!\033[0m\n";

        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    for (Person user : dataBase)
    {
        std::cout << "+---------------------------------------------+\n";
        std::cout << "Name______________: " << user.getName() << '\n';
        std::cout << "Age_______________: " << user.getAge() << '\n';
        std::cout << "+---------------------------------------------+\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(4));
}