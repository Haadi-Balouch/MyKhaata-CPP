#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include "Header Files\Person.h"
#include "Header Files\Admin.h"
#include "Header Files\User.h"
#include "Header Files\Accounts.h"
#include "Header Files\Transactions.cpp"
#include "Header Files\Loan.cpp"

int getValidInt(std::string message);
void waitForKeypress();
void pressToContinue();
void FK_in_Acc_User(User &u, Account &a);
void FK_in_Acc_Trans(Account &a, Transaction &t);
void userRegistration(int adminID, std::vector<Admin> &admins, std::vector<User> &users, std::vector<Account> &accounts);
void viewAllUsers(std::vector<User> &users);
void viewAllAccounts(const std::vector<User> &users, const std::vector<Account> &accounts);
void viewAllTransactions(const std::vector<Transaction> &transactions);
void viewSpecificUser(int id, std::vector<User> &users, const std::vector<Account> &accounts, const std::vector<Transaction> &transactions, const std::vector<Loan> &loans);
void deleteUser(int id, std::vector<User> &users, std::vector<Account> &accounts);
int findUser(const std::vector<User> &users);
void viewStatistics(const std::vector<User> &users, const std::vector<Account> &accounts, const std::vector<Transaction> &transactions);
void addTransaction(int id, std::vector<Account> &accounts, std::vector<Transaction> &transactions);
void removeLoan(int id, std::vector<Account> &accounts, std::vector<Loan> &loans);
void addLoan(int id, std::vector<Account> &accounts, std::vector<Loan> &loans);
void editProfile(User &user, std::vector<User> &users);
bool userConfirmation(User user);
bool adminConfirmation(const Admin &admin);
void resetAcc(int id, std::vector<Account> accounts);
void viewInsights(int id, const std::vector<Account> &accounts, const std::vector<Transaction> &transactions);
void saveToFiles(const std::vector<Admin> &admins, const std::vector<User> &users, const std::vector<Account> &accounts, const std::vector<Transaction> &transactions, const std::vector<Loan> &loans);
void readFromFiles(std::vector<Admin> &admins, std::vector<User> &users, std::vector<Account> &accounts, std::vector<Transaction> &transactions, std::vector<Loan> &loans);

int main()
{
    std::vector<Admin> admins;
    std::vector<User> users;
    std::vector<Account> accounts;
    std::vector<Transaction> transactions;
    std::vector<Loan> loans;
    int choice, retry, find;
    bool loop1 = true, loop2 = true, loop3 = true, confirm;
    std::string username01, password01;
    readFromFiles(admins, users, accounts, transactions, loans);
    while (loop1)
    {
        system("CLS");
        choice = getValidInt("*********** Welcome To MyKhaata ***********\n\n 1) Admin \n 2) User Login \n 3) Register \nHow do you want to proceed : ");
        if (choice == 1)
        {
            loop2 = true;
            while (loop2)
            {
                loop3 = true;
                system("CLS");
                std::cout << "    ADMIN LOGIN     \n\n"
                          << "Enter username = ";
                std::cin >> username01;
                std::cout << "Enter password = ";
                std::cin >> password01;
                for (int i = 0; i < admins.size(); i++)
                {
                    if (username01 == admins[i].get_Username() && password01 == admins[i].get_Usercode())
                    {
                        loop2 = false;
                        while (loop3)
                        {
                            system("CLS");
                            choice = getValidInt("********** Admin Menu **********\n 1) View All Users\n 2) View All Accounts\n 3) View All Transactions\n 4) View Information of a Specific User\n 5) Delete User\n 6) Register Another Admin\n 7) View System Statistics\n 8) Logout\nEnter your choice:");
                            if (choice == 1)
                            {
                                viewAllUsers(users);
                            }
                            else if (choice == 2)
                            {
                                viewAllAccounts(users, accounts);
                            }
                            else if (choice == 3)
                            {
                                viewAllTransactions(transactions);
                            }
                            else if (choice == 4)
                            {
                                find = findUser(users);
                                if (find != -1)
                                    viewSpecificUser(find, users, accounts, transactions, loans);
                            }
                            else if (choice == 5)
                            {
                                find = findUser(users);
                                if (find != -1)
                                {
                                    confirm = adminConfirmation(admins[i]);
                                    if (confirm)
                                    {
                                        deleteUser(find, users, accounts);
                                        saveToFiles(admins, users, accounts, transactions, loans);
                                    }
                                }
                            }
                            else if (choice == 6)
                            {
                                userRegistration(admins[i].get_adminID(), admins, users, accounts);
                                saveToFiles(admins, users, accounts, transactions, loans);
                            }
                            else if (choice == 7)
                            {
                                viewStatistics(users, accounts, transactions);
                            }
                            else if (choice == 8)
                            {
                                system("CLS");
                                std::cout << "Logged out Successfuly.\n";
                                waitForKeypress();
                                loop3 = false;
                            }
                        }
                    }
                }
                if (loop2 != false)
                {
                    std::cout << "Incorrect username or password!!\n";
                    retry = getValidInt("Would you like to try again (1 for yes, 0 for no): ");
                    if (retry == 0)
                        loop2 = false;
                }
            }
        }
        else if (choice == 2)
        {
            loop2 = true;
            while (loop2)
            {
                system("CLS");
                std::cout << "    User LOGIN     \n\n"
                          << "Enter username = ";
                std::cin >> username01;
                std::cout << "Enter password = ";
                std::cin >> password01;
                for (int i = 0; i < users.size(); i++)
                {
                    if (username01 == users[i].get_Username() && password01 == users[i].get_Usercode())
                    {
                        loop3 = true;
                        while (loop3)
                        {
                            system("CLS");
                            choice = getValidInt("********** Welcome to User PAGE **********\n\n 1) View Profile\n 2) Add Transaction\n 3) Loan \n 4) Edit Profile\n 5) Delete User\n 6) View Insights\n 7) Reset Account\n 8) Logout \nEnter your choice:");
                            if (choice == 1)
                            {
                                viewSpecificUser(users[i].get_UserID(), users, accounts, transactions, loans);
                            }
                            else if (choice == 2)
                            {
                                addTransaction(users[i].get_UserID(), accounts, transactions);
                                saveToFiles(admins, users, accounts, transactions, loans);
                            }
                            else if (choice == 3)
                            {
                                while (true)
                                {
                                    system("CLS");
                                    choice = getValidInt("Choose an option : \n 1)Add Loan\n 2)Remove Loan\nPlease choose one : ");
                                    if (choice == 1)
                                    {
                                        addLoan(users[i].get_UserID(), accounts, loans);
                                        saveToFiles(admins, users, accounts, transactions, loans);
                                        break;
                                    }
                                    else if (choice == 2)
                                    {
                                        removeLoan(users[i].get_UserID(), accounts, loans);
                                        saveToFiles(admins, users, accounts, transactions, loans);
                                        break;
                                    }
                                    else
                                    {
                                        std::cout << "Invalid choice.\n";
                                        retry = getValidInt("Would you like to try again (1 for yes, 0 for no): ");
                                        if (retry == 0)
                                            break;
                                    }
                                }
                            }
                            else if (choice == 4)
                            {
                                confirm = userConfirmation(users[i]);
                                if (confirm)
                                {
                                    editProfile(users[i], users);
                                    saveToFiles(admins, users, accounts, transactions, loans);
                                }
                            }
                            else if (choice == 5)
                            {
                                confirm = userConfirmation(users[i]);
                                if (confirm)
                                {
                                    deleteUser(users[i].get_UserID(), users, accounts);
                                    saveToFiles(admins, users, accounts, transactions, loans);
                                    loop3 = false;
                                }
                            }
                            else if (choice == 6)
                            {
                                viewInsights(users[i].get_UserID(), accounts, transactions);
                            }
                            else if (choice == 7)
                            {
                                resetAcc(users[i].get_UserID(), accounts);
                                std::cout<<"Account reset Successfully.\n";
                                waitForKeypress();
                                loop3 = false;
                            }
                            else if (choice == 8)
                            {
                                std::cout<<"Logged out Successfully.\n";
                                waitForKeypress();
                                loop3 = false;
                            }
                        }
                        loop2 = false;
                    }
                }
                if (loop2 != false)
                {
                    std::cout << "Incorrect username or password!!\n";
                    retry = getValidInt("Would you like to try again (1 for yes, 0 for no): ");
                    if (retry == 0)
                        loop2 = false;
                }
            }
        }
        else if (choice == 3)
        {
            userRegistration(0, admins, users, accounts);
            saveToFiles(admins, users, accounts, transactions, loans);
        }
        else if (choice == 0)
        {
            loop1 = false;
            system("CLS");
            std::cout << "Thank you for using MyKhaata.\n";
            waitForKeypress();
        }
    }
}

int getValidInt(std::string message)
{
    int value;
    while (true)
    {
        std::cout << message;
        std::cin >> value;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input! Please enter a number.\n";
        }
        else
        {
            std::cin.ignore(1000, '\n');
            return value;
        }
    }
}

void waitForKeypress()
{
    std::cin.ignore();
    std::cin.get();
}
void pressToContinue()
{
    std::string q;
    while (true)
    {
        std::cout << "Press 'Q' to continue...";
        std::cin >> q;
        if (q == "Q" || q == "q")
        {
            break;
        }
    }
}
void FK_in_Acc_User(User &u, Account &a)
{
    a.user_ID = u.userID;
    u.account_id = a.accID;
}
void FK_in_Acc_Trans(Account &a, Transaction &t)
{
    t.acc_ID = a.accID;
    a.trans_ID.push_back(t.transID);
}
void userRegistration(int adminID, std::vector<Admin> &admins, std::vector<User> &users, std::vector<Account> &accounts)
{
    std::string name00;
    std::string phone_no00;
    int age00;
    std::string username00;
    std::string usercode00;
    system("CLS");
    std::cout << "**** Registration ****\n\n"
              << "Please enter the following details to register;\n"
              << "Enter your Name : ";
    std::getline(std::cin, name00);
    while (true)
    {
        std::cout << "Enter your Phone Number : ";
        std::cin >> phone_no00;

        if (phone_no00.length() == 11 && phone_no00.substr(0, 2) == "03")
        {
            break;
        }
        else
        {
            std::cout << "Please Enter a valid phone number.\n";
        }
    }
    while (true)
    {
        age00 = getValidInt("Enter your age : ");

        if (age00 > 15)
        {
            break;
        }
        else
        {
            std::cout << "You must older than 15 years.\n";
        }
    }
    while (true)
    {
        bool exists = false;
        std::cout << "Enter your username : ";
        std::cin >> username00;
        for (int i = 0; i < users.size(); i++)
        {
            if (username00 == users[i].get_Username())
            {
                std::cout << "Username already exists. Please try another one.\n";
                exists = true;
                break;
            }
        }
        if (exists == false)
        {
            break;
        }
    }
    std::cout << "Enter your password : ";
    std::cin >> usercode00;

    if (adminID == 0)
    {
        users.emplace_back(name00, phone_no00, age00, username00, usercode00);
        accounts.emplace_back(0, 0, 0, 0, 0);
        FK_in_Acc_User(users[users.size() - 1], accounts[accounts.size() - 1]);
    }
    else
    {
        admins.emplace_back(name00, phone_no00, age00, username00, usercode00);
        admins[admins.size() - 1].set_accesser(adminID);
    }

    std::cout << "******** Welcome to MyKhaata Family. ********\n\n Please login to proceed.";
    waitForKeypress();
    system("CLS");
}

void viewAllUsers(std::vector<User> &users)
{
    system("CLS");
    std::cout << "******** List of All User **********\n\n";
    for (int i = 0; i < users.size(); i++)
    {
        std::cout << "\n******************************************\n";
        users[i].Display();
    }
    pressToContinue();
}
void viewAllAccounts(const std::vector<User> &users, const std::vector<Account> &accounts)
{
    system("CLS");
    std::cout << "******** List of All Accounts ********\n\n";
    for (int i = 0; i < accounts.size(); i++)
    {
        for (int j = 0; j < users.size(); j++)
        {
            if (accounts[i].get_accountID() == users[j].get_accountID())
            {
                std::cout << "\n******************************************\n";
                accounts[i].Display();
            }
        }
    }
    pressToContinue();
}
void viewAllTransactions(const std::vector<Transaction> &transactions)
{
    system("CLS");
    std::cout << "******** List of All Transactions ********\n\n";
    for (int i = 0; i < transactions.size(); i++)
    {
        std::cout << "\n*********************************\n";
        transactions[i].Display();
    }
    pressToContinue();
}
void viewSpecificUser(int id, std::vector<User> &users, const std::vector<Account> &accounts, const std::vector<Transaction> &transactions, const std::vector<Loan> &loans)
{
    bool loop1 = true;
    int choice, retry;
    system("CLS");
    std::cout << "******** List of Information about a Specific User ********\n\n";
    for (int i = 0; i < users.size(); i++)
    {
        if (id == users[i].get_UserID())
        {
            system("CLS");
            while (loop1)
            {
                system("CLS");
                choice = getValidInt("What would you like to view\n 1) Personal Information\n 2) Account Information\n 3) Transaction History\n 4) Loan History\n 5) Go Back\nPlease Enter your choice(1-4) : ");
                if (choice == 1)
                {
                    system("CLS");
                    std::cout << "\n******** Personal Information *********\n";
                    users[i].Display();
                    pressToContinue();
                }
                else if (choice == 2)
                {
                    for (int j = 0; j < accounts.size(); j++)
                    {
                        if (users[i].get_UserID() == accounts[j].get_userID())
                        {
                            system("CLS");
                            std::cout << "\n********* Account Information *********\n";
                            accounts[j].Display();
                            break;
                        }
                    }
                    pressToContinue();
                }
                else if (choice == 3)
                {
                    for (int j = 0; j < accounts.size(); j++)
                    {
                        if (users[i].get_UserID() == accounts[j].get_userID())
                        {
                            system("CLS");
                            std::cout << "\n********* Transaction History *********\n";
                            for (int k = 0; k < accounts[i].trans_ID.size(); k++)
                            {
                                for (int l = 0; l < transactions.size(); l++)
                                {
                                    if (accounts[j].trans_ID[k] == transactions[l].get_transID())
                                    {
                                        std::cout << "\n*********************************\n";
                                        transactions[l].Display();
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    pressToContinue();
                }
                else if (choice == 4)
                {
                    system("CLS");
                    std::cout << "\n*********** Loans History ************\n\n";
                    for (int j = 0; j < accounts.size(); j++)
                    {
                        if (users[i].get_UserID() == accounts[j].get_userID())
                        {
                            for (int k = 0; k < accounts[i].loan_ID.size(); k++)
                            {
                                for (int l = 0; l < loans.size(); l++)
                                {
                                    if (accounts[j].loan_ID[k] == loans[l].get_loanID())
                                    {
                                        std::cout << "\n*********************************\n";
                                        loans[l].Display();
                                        break;

                                        
                                    }
                                }
                            }
                        }
                    }
                    pressToContinue();
                }
                else if (choice == 5)
                {
                    break;
                }
            }
            loop1 = false;
        }
        
    }
    if(loop1){
            std::cout << "Incorrect User ID\n";
            retry = getValidInt("Would you like to try again (1 for yes, 0 for no): ");
            if (retry == 0)
                loop1 = false;
        }
    pressToContinue();
}
void deleteUser(int id, std::vector<User> &users, std::vector<Account> &accounts)
{
    system("CLS");
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].get_UserID() == id)
        {
            users.erase(users.begin() + i);
            break;
        }
    }
    for (int j = 0; j < accounts.size(); j++)
    {
        if (accounts[j].get_userID() == id)
        {
            accounts.erase(accounts.begin() + j);
            break;
        }
    }
    pressToContinue();
}
int findUser(const std::vector<User> &users)
{
    system("CLS");
    int id, retry;
    bool loop1 = true;
    while (loop1)
    {
        id = getValidInt("Enter the User ID : ");
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].get_UserID() == id)
            {
                return id;
            }
            else
            {
                std::cout << "Incorrect User ID\n";
                retry = getValidInt("Would you like to try again (1 for yes, 0 for no): ");
                if (retry == 0)
                    loop1 = false;
            }
        }
    }
    return -1;
}
void viewStatistics(const std::vector<User> &users, const std::vector<Account> &accounts, const std::vector<Transaction> &transactions)
{
    system("CLS");
    std::cout << "************* Statistics *************\n\n"
              << "Total number of Users : " << users.size() << "\n"
              << "Total number of Accounts : " << accounts.size() << "\n"
              << "Total number of transaction : " << transactions.size() << "\n\n";

    pressToContinue();
}
void addTransaction(int id, std::vector<Account> &accounts, std::vector<Transaction> &transactions)
{
    bool loop1 = true, loop2 = true, valid = false;
    int choice;
    float amount;
    std::string category, type, date, note;
    while (loop1)
    {
        system("CLS");
        std::cout << "\n************ Transaction in Progress **************\n";
        amount = getValidInt("Enter the amount of Money : ");

        loop2 = true;
        while (loop2)
        {
            loop2 = false;
            choice = getValidInt("Please enter the type of transaction \n 1)Income\n 2)Expense\nSelect any one : ");
            if (choice == 1)
            {
                type = "Income";
            }
            else if (choice == 2)
            {
                type = "Expense";
            }
            else
            {
                std::cout << "Please enter a valid choice.\n";
                loop2 = true;
                valid = false;
            }
        }
        loop2 = true;
        while (loop2)
        {
            loop2 = false;
            if (type == "Expense")
            {
                choice = getValidInt("Please enter the category of transaction \n 1)Food & Dine In\n 2)General Expense\n 3)Fuel & Transport\nSelect any one : ");
                if (choice == 1)
                {
                    category = "Food & Dine In";
                }
                else if (choice == 2)
                {
                    category = "General Expense";
                }
                else if (choice == 3)
                {
                    category = "Fuel & Transport";
                }
                else
                {
                    std::cout << "Please enter a valid choice.\n";
                }
            }
            else if (type == "Income")
            {
                choice = getValidInt("Please enter the category of transaction \n 1)Salary\n 2)Business\n 3)Side Hustle\n 4)Free Lancing\n 5)Gift\nSelect any one : ");
                if (choice == 1)
                {
                    category = "Salary";
                }
                else if (choice == 2)
                {
                    category = "Business";
                }
                else if (choice == 3)
                {
                    category = "Side Hustle";
                }
                else if (choice == 4)
                {
                    category = "Free Lancing";
                }
                else if (choice == 5)
                {
                    category = "Gift";
                }
                else
                {
                    std::cout << "Please enter a valid choice.\n";
                    loop2 = true;
                }
            }
            else
            {
                loop1 = false;
                loop2 = false;
                valid = false;
            }
        }
        loop2 = true;
        while (loop2)
        {
            std::cout << "Enter the Date (DD-MM-YYYY) : ";
            std::cin >> date;
            if (date.length() == 10 && date[2] == '-' && date[5] == '-' && std::stoi(date.substr(0, 2)) < 32 && std::stoi(date.substr(3, 2)) < 13 && std::stoi(date.substr(6, 4)) < 2026)
            {
                break;
            }
            else
            {
                std::cout << "Invalid Format of date. Please try again.\n";
            }
        }
        std::cout << "Write any Note: ";
        std::getline(std::cin, note);
        valid = true;
        if (valid)
        {
            for (int i = 0; i < accounts.size(); i++)
            {
                if (accounts[i].get_userID() == id)
                {
                    transactions.emplace_back(amount, category, type, date, note);
                    FK_in_Acc_Trans(accounts[i], transactions[transactions.size() - 1]);
                    transactions[transactions.size() - 1].transRecord_in_Account(accounts[i]);
                    break;
                }
            }
            loop1 = false;
            system("CLS");
            std::cout << "Transaction Successful.\n\n";

            pressToContinue();
        }
    }
    if (!valid)
    {
        system("CLS");
        std::cout << "An Error occured during the transaction.\n";
        pressToContinue();
    }
}
void addLoan(int id, std::vector<Account> &accounts, std::vector<Loan> &loans)
{
    bool loop1 = true, loop2 = true, valid = false;
    int choice;
    float amount;
    std::string l_name, type, date, note;
    while (loop1)
    {
        system("CLS");
        std::cout << "\n************ Loan in Progress **************\n";
        amount = getValidInt("Enter the amount of Money : ");

        std::cout << "Enter the Loaner's Name : ";
        std::getline(std::cin, l_name);

        loop2 = true;
        while (loop2)
        {
            loop2 = false;
            choice = getValidInt("Please enter the type of transaction \n 1)To Give\n 2)To Recieve\nSelect any one : ");
            if (choice == 1)
            {
                type = "To Give";
            }
            else if (choice == 2)
            {
                type = "To Recieve";
            }
            else
            {
                std::cout << "Please enter a valid choice.\n";
                loop2 = true;
                valid = false;
            }
        }
        loop2 = true;
        while (loop2)
        {
            std::cout << "Enter the Date (DD-MM-YYYY) : ";
            std::cin >> date;
            if (date.length() == 10 && date[2] == '-' && date[5] == '-' && std::stoi(date.substr(0, 2)) < 32 && std::stoi(date.substr(3, 2)) < 13 && std::stoi(date.substr(6, 4)) < 2026)
            {
                break;
            }
            else
            {
                std::cout << "Invalid Format of date. Please try again.\n";
            }
        }
        std::cout << "Write any Note: ";
        std::getline(std::cin, note);

        valid = true;
        if (valid)
        {
            for (int i = 0; i < accounts.size(); i++)
            {
                if (accounts[i].get_userID() == id)
                {
                    loans.emplace_back(l_name, amount, type, date, note);
                    loans[loans.size() - 1].Addition_of_AccID_in_Loans(accounts[i]);
                    loans[loans.size() - 1].Addition_of_LoanID_in_Account(accounts[i]);
                    loans[loans.size() - 1].LoanRecord_in_Account(accounts[i]);
                    break;
                }
            }
            loop1 = false;
            system("CLS");
            std::cout << "Transaction Successful.\n\n";
            pressToContinue();
        }
    }
    if (!valid)
    {
        system("CLS");
        std::cout << "An Error occured during the transaction.\n";
        pressToContinue();
    }
}

void removeLoan(int id, std::vector<Account> &accounts, std::vector<Loan> &loans)
{
    int loan_id = getValidInt("Enter the Loan ID you want to remove : ");
    bool found = false;

    for (int i = 0; i < loans.size(); i++)
    {
        if (loans[i].get_loanID() == loan_id)
        {
            for (int j = 0; j < accounts.size(); j++)
            {
                if (accounts[j].get_userID() == id)
                {
                    for (int k = 0; k < accounts[j].loan_ID.size(); k++)
                    {
                        if (accounts[j].loan_ID[k] == loan_id)
                        {
                            loans[i].removal_of_LoanRecord(accounts[j]);
                            accounts[j].loan_ID.erase(accounts[j].loan_ID.begin() + k);
                            loans.erase(loans.begin() + i);
                            std::cout << "Loan successfully removed.\n";
                            found = true;
                            break;
                        }
                    }
                }
                if (found)
                {
                    break;
                }
            }
        }
        if (found)
        {
            break;
        }
    }

    if (!found)
    {
        std::cout << "Loan with ID " << loan_id << " not found or not linked to this user.\n";
    }
}

void editProfile(User &user, std::vector<User> &users)
{
    system("CLS");
    int age, choice;
    std::string name, phone_no, username00, password00;
    bool loop1 = true;

    while (loop1)
    {
        loop1 = false;
        std::cout << "\n********** Profile Edit ***********\n\n";
        choice = getValidInt("What do you want to change\n 1) Name\n 2) Phone Number\n 3) Username\n 4) Password\nEnter the choice : ");
        system("CLS");
        if (choice == 1)
        {
            std::cout << "Please enter your new name : ";
            std::getline(std::cin, name);
            user.set_name(name);
        }
        else if (choice == 2)
        {
            while (true)
            {
                std::cout << "Enter your Phone Number : ";
                std::cin >> phone_no;

                if (phone_no.length() == 11 && phone_no.substr(0, 2) == "03")
                {
                    user.set_phoneNo(phone_no);
                    break;
                }
                else
                {
                    std::cout << "Please Enter a valid phone number.\n";
                }
            }
        }
        else if (choice == 3)
        {
            while (true)
            {
                bool exists = false;
                std::cout << "Enter your username : ";
                std::cin >> username00;
                for (int i = 0; i < users.size(); i++)
                {
                    if (username00 == users[i].get_Username())
                    {
                        std::cout << "Username already exists. Please try another one.\n";
                        exists = true;
                        break;
                    }
                }
                if (exists == false)
                {
                    user.set_Username(username00);
                    break;
                }
            }
        }
        else if (choice == 4)
        {
            std::cout << "Enter new Password : ";
            std::cin >> password00;
            user.set_Usercode(password00);
        }
        else
        {
            std::cout << "Please choice a correct option.\n";
            loop1 = true;
        }
    }
    std::cout << "Changes saved successfully.\n";
    waitForKeypress();
}
bool userConfirmation(User user)
{
    int retry;
    std::string username01, password01;
    while (true)
    {
        system("CLS");
        std::cout << "\n*********** Confiramtion ***********\n";
        std::cout << "Enter username = ";
        std::cin >> username01;
        std::cout << "Enter password = ";
        std::cin >> password01;
        if (username01 == user.get_Username() && password01 == user.get_Usercode())
        {
            return true;
        }
        else
        {
            std::cout << "Incorrect Username or Password\n";
            retry = getValidInt("Would you like to try again (1 for yes, 0 for no): ");
            if (retry == 0)
                return false;
        }
    }
}
bool adminConfirmation(const Admin &admin)
{
    int retry;
    std::string username01, password01;
    while (true)
    {
        system("CLS");
        std::cout << "\n*********** Confiramtion ***********\n";
        std::cout << "Enter username = ";
        std::cin >> username01;
        std::cout << "Enter password = ";
        std::cin >> password01;
        if (username01 == admin.get_Username() && password01 == admin.get_Usercode())
        {
            return true;
        }
        else
        {
            std::cout << "Incorrect Username or Password\n";
            retry = getValidInt("Would you like to try again (1 for yes, 0 for no): ");
            if (retry == 0)
                return false;
        }
    }
}

void resetAcc(int id, std::vector<Account> accounts){
        for(Account acc : accounts){
            if(acc.get_userID()==id){
                acc.set_totalIncome(0);
                acc.set_totalExpense(0);
                acc.set_Balance(0);

                break;
            }
        }
    }

void viewInsights(int id, const std::vector<Account> &accounts, const std::vector<Transaction> &transactions)
{
    int choice, year, month, date, retry;
    bool loop1 = true;
    float expense = 0, Food = 0, General_Expense = 0, Fuel = 0, Income = 0, salary = 0, Business = 0, Side_Hustle = 0, freeLancing = 0, gift = 0;

    while (loop1)
    {
        system("CLS");
        choice = getValidInt("Choose how to order : \n 1)By Year\n 2)By Month and Year \n 3)By Specific Date\nPlease Choose an option : ");
        if (choice == 1)
        {
            year = getValidInt("Enter the Year : ");
        }
        else if (choice == 2)
        {
            year = getValidInt("Enter the Year : ");
            month = getValidInt("Enter the Month : ");
        }
        else if (choice == 3)
        {
            year = getValidInt("Enter the Year : ");
            month = getValidInt("Enter the Month : ");
            date = getValidInt("Enter the Date : ");
        }
        else
        {
            std::cout << "Incorrect Username or Password\n";
            retry = getValidInt("Would you like to try again (1 for yes, 0 for no): ");
            if (retry == 0)
                loop1 = false;
            continue;
        }

        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].get_userID() == id)
            {
                for (int j = 0; j < accounts[i].trans_ID.size(); j++)
                {
                    for (int k = 0; k < transactions.size(); k++)
                    {
                        if (accounts[i].trans_ID[j] == transactions[k].get_transID())
                        {
                            if (choice == 1 && stoi(transactions[k].get_date().substr(6, 4)) == year)
                            {
                                if (transactions[k].get_type() == "Income")
                                {
                                    Income += transactions[k].get_amount();
                                    if (transactions[k].get_category() == "Salary")
                                    {
                                        salary += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Business")
                                    {
                                        Business += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Side Hustle")
                                    {
                                        Side_Hustle += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Free Lancing")
                                    {
                                        freeLancing += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Gift")
                                    {
                                        gift += transactions[k].get_amount();
                                    }
                                }
                                else if (transactions[k].get_type() == "Expense")
                                {
                                    expense += transactions[k].get_amount();
                                    if (transactions[k].get_category() == "Food & Dine In")
                                    {
                                        Food += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "General Expense")
                                    {
                                        General_Expense += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Fuel & Transport")
                                    {
                                        Fuel += transactions[k].get_amount();
                                    }
                                }
                            }
                            else if (choice == 2 && stoi(transactions[k].get_date().substr(6, 4)) == year && stoi(transactions[k].get_date().substr(3, 2)) == month)
                            {
                                if (transactions[k].get_type() == "Income")
                                {
                                    Income += transactions[k].get_amount();
                                    if (transactions[k].get_category() == "Salary")
                                    {
                                        salary += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Business")
                                    {
                                        Business += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Side Hustle")
                                    {
                                        Side_Hustle += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Free Lancing")
                                    {
                                        freeLancing += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Gift")
                                    {
                                        gift += transactions[k].get_amount();
                                    }
                                }
                                else if (transactions[k].get_type() == "Expense")
                                {
                                    expense += transactions[k].get_amount();
                                    if (transactions[k].get_category() == "Food & Dine In")
                                    {
                                        Food += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "General Expense")
                                    {
                                        General_Expense += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Fuel & Transport")
                                    {
                                        Fuel += transactions[k].get_amount();
                                    }
                                }
                            }
                            else if (choice == 3 && stoi(transactions[k].get_date().substr(6, 4)) == year && stoi(transactions[k].get_date().substr(3, 2)) == month && stoi(transactions[k].get_date().substr(0, 2)) == date)
                            {
                                if (transactions[k].get_type() == "Income")
                                {
                                    Income += transactions[k].get_amount();
                                    if (transactions[k].get_category() == "Salary")
                                    {
                                        salary += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Business")
                                    {
                                        Business += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Side Hustle")
                                    {
                                        Side_Hustle += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Free Lancing")
                                    {
                                        freeLancing += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Gift")
                                    {
                                        gift += transactions[k].get_amount();
                                    }
                                }
                                else if (transactions[k].get_type() == "Expense")
                                {
                                    expense += transactions[k].get_amount();
                                    if (transactions[k].get_category() == "Food & Dine In")
                                    {
                                        Food += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "General Expense")
                                    {
                                        General_Expense += transactions[k].get_amount();
                                    }
                                    else if (transactions[k].get_category() == "Fuel & Transport")
                                    {
                                        Fuel += transactions[k].get_amount();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        loop1 = false;
        system("CLS");
        std::cout << "\n******** Insights *********\n"
                  << "INCOME : " << Income << "\n"
                  << " a) Salary : " << salary << "\n"
                  << " b) Business : " << Business << "\n"
                  << " c) Side Hustle : " << Side_Hustle << "\n"
                  << " d) Free Lancing : " << freeLancing << "\n"
                  << " e) Gift : " << gift << "\n\n"
                  << "Expense : " << expense << "\n"
                  << " a) Food & Dine In : " << Food << "\n"
                  << " b) General Expense : " << General_Expense << "\n"
                  << " c) Fuel & Transport : " << Fuel << "\n\n";

        pressToContinue();
    }
}

void saveToFiles(const std::vector<Admin> &admins, const std::vector<User> &users, const std::vector<Account> &accounts, const std::vector<Transaction> &transactions, const std::vector<Loan> &loans)
{
    std::ofstream adminFile, userFile, accFile, transFile, loanFile, accTransFile, accLoanFile;
    adminFile.open("Data Files/Admins.txt");
    userFile.open("Data Files/Users.txt");
    accFile.open("Data Files/Accounts.txt");
    transFile.open("Data Files/Transactions.txt");
    loanFile.open("Data Files/Loans.txt");
    accTransFile.open("Data Files/AccountTransaction.txt");
    accLoanFile.open("Data Files/AccountLoan.txt");

    for (int i = 0; i < admins.size(); i++)
    {
        adminFile << admins[i].get_adminID() << "|"
                  << admins[i].get_name() << "|"
                  << admins[i].get_PhoneNumber() << "|"
                  << admins[i].get_Age() << "|"
                  << admins[i].get_Username() << "|"
                  << admins[i].get_Usercode() << "|"
                  << admins[i].get_accesser() << "\n";
    }
    for (int i = 0; i < users.size(); i++)
    {
        userFile << users[i].get_UserID() << "|"
                 << users[i].get_name() << "|"
                 << users[i].get_PhoneNumber() << "|"
                 << users[i].get_Age() << "|"
                 << users[i].get_Username() << "|"
                 << users[i].get_Usercode() << "|"
                 << users[i].get_accountID() << "\n";
    }
    for (int i = 0; i < accounts.size(); i++)
    {
        accFile << accounts[i].get_accountID() << "|"
                << accounts[i].get_userID() << "|"
                << accounts[i].getBalance() << "|"
                << accounts[i].get_TotalIncome() << "|"
                << accounts[i].get_TotalExpense() << "|"
                << accounts[i].get_ToGive() << "|"
                << accounts[i].get_ToRecieve() << "\n";
        for (int j = 0; j < accounts[i].trans_ID.size(); j++)
        {
            accTransFile << accounts[i].get_accountID() << "|" << accounts[i].trans_ID[j] << "\n";
        }
        for (int j = 0; j < accounts[i].loan_ID.size(); j++)
        {
            accLoanFile << accounts[i].get_accountID() << "|" << accounts[i].loan_ID[j] << "\n";
        }
    }
    for (int i = 0; i < transactions.size(); i++)
    {
        transFile << transactions[i].get_transID() << "|"
                  << transactions[i].get_accID() << "|"
                  << transactions[i].get_amount() << "|"
                  << transactions[i].get_category() << "|"
                  << transactions[i].get_type() << "|"
                  << transactions[i].get_date() << "|"
                  << transactions[i].get_note() << "\n";
    }
    for (int i = 0; i < loans.size(); i++)
    {
        loanFile << loans[i].get_loanID() << "|"
                 << loans[i].get_lname() << "|"
                 << loans[i].get_amount() << "|"
                 << loans[i].get_type() << "|"
                 << loans[i].get_date() << "|"
                 << loans[i].get_note() << "|"
                 << loans[i].get_accID() << "\n";
    }

    adminFile.close();
    userFile.close();
    accFile.close();
    transFile.close();
    loanFile.close();
    accTransFile.close();
    accLoanFile.close();
}

void readFromFiles(std::vector<Admin> &admins, std::vector<User> &users, std::vector<Account> &accounts, std::vector<Transaction> &transactions, std::vector<Loan> &loans)
{
    admins.clear();
    users.clear();
    accounts.clear();
    transactions.clear();
    loans.clear();
    std::ifstream adminFile("Data Files/Admins.txt");
    std::ifstream userFile("Data Files/Users.txt");
    std::ifstream accFile("Data Files/Accounts.txt");
    std::ifstream transFile("Data Files/Transactions.txt");
    std::ifstream loanFile("Data Files/Loans.txt");
    std::ifstream accTransFile("Data Files/AccountTransaction.txt");
    std::ifstream accLoanFile("Data Files/AccountLoan.txt");

    int maxAdminID = 10000, maxUserID = 10000, maxAccID = 10000, maxTransID = 100000, maxLoanID = 100000;

    if (!adminFile || !userFile || !accFile || !transFile || !loanFile || !accTransFile || !accLoanFile)
    {
        std::cout << "Error opening one or more files.\n";
        return;
    }

    std::string line;

    while (std::getline(adminFile, line))
    {
        std::istringstream iss(line);
        std::string adminIDStr, name, phone_no, ageStr, username, usercode, accesserStr;

        std::getline(iss, adminIDStr, '|');
        std::getline(iss, name, '|');
        std::getline(iss, phone_no, '|');
        std::getline(iss, ageStr, '|');
        std::getline(iss, username, '|');
        std::getline(iss, usercode, '|');
        std::getline(iss, accesserStr, '|');

        int adminID = std::stoi(adminIDStr);
        int age = std::stoi(ageStr);
        int accesser = std::stoi(accesserStr);

        admins.emplace_back(name, phone_no, age, username, usercode);
        admins.back().set_adminID(adminID);
        admins.back().set_accesser(accesser);
        if (adminID > maxAdminID)
            maxAdminID = adminID;
    }

    while (std::getline(userFile, line))
    {
        std::istringstream iss(line);
        std::string userIDStr, name, phone_no, ageStr, username, usercode, accountIDStr;

        std::getline(iss, userIDStr, '|');
        std::getline(iss, name, '|');
        std::getline(iss, phone_no, '|');
        std::getline(iss, ageStr, '|');
        std::getline(iss, username, '|');
        std::getline(iss, usercode, '|');
        std::getline(iss, accountIDStr, '|');

        int userID = std::stoi(userIDStr);
        int age = std::stoi(ageStr);
        int accID = std::stoi(accountIDStr);

        users.emplace_back(name, phone_no, age, username, usercode);
        users.back().set_userID(userID);
        users.back().set_accId(accID);
        if (userID > maxUserID)
            maxUserID = userID;
    }

    while (std::getline(accFile, line))
    {
        std::istringstream iss(line);
        std::string accIDStr, userIDStr, balanceStr, incomeStr, expenseStr, giveStr, receiveStr;

        std::getline(iss, accIDStr, '|');
        std::getline(iss, userIDStr, '|');
        std::getline(iss, balanceStr, '|');
        std::getline(iss, incomeStr, '|');
        std::getline(iss, expenseStr, '|');
        std::getline(iss, giveStr, '|');
        std::getline(iss, receiveStr, '|');

        int accID = std::stoi(accIDStr);
        int userID = std::stoi(userIDStr);
        float balance = std::stof(balanceStr);
        float income = std::stof(incomeStr);
        float expense = std::stof(expenseStr);
        float give = std::stof(giveStr);
        float receive = std::stof(receiveStr);

        accounts.emplace_back(balance, income, expense, give, receive);
        accounts.back().set_accId(accID);
        accounts.back().set_userID(userID);
        if (accID > maxAccID)
            maxAccID = accID;
    }

    while (std::getline(transFile, line))
    {
        std::istringstream iss(line);
        std::string transIDStr, accIDStr, amountStr, category, type, date, note;

        std::getline(iss, transIDStr, '|');
        std::getline(iss, accIDStr, '|');
        std::getline(iss, amountStr, '|');
        std::getline(iss, category, '|');
        std::getline(iss, type, '|');
        std::getline(iss, date, '|');
        std::getline(iss, note, '|');

        int transID = std::stoi(transIDStr);
        int accID = std::stoi(accIDStr);
        float amount = std::stof(amountStr);

        transactions.emplace_back(amount, category, type, date, note);
        transactions.back().set_transID(transID);
        transactions.back().set_accId(accID);
        if (transID > maxTransID)
            maxTransID = transID;
    }

    while (std::getline(loanFile, line))
    {
        std::istringstream iss(line);
        std::string loanIDStr, lname, amountStr, type, date, note, accIDStr;

        std::getline(iss, loanIDStr, '|');
        std::getline(iss, lname, '|');
        std::getline(iss, amountStr, '|');
        std::getline(iss, type, '|');
        std::getline(iss, date, '|');
        std::getline(iss, note, '|');
        std::getline(iss, accIDStr, '|');

        int loanID = std::stoi(loanIDStr);
        int accID = std::stoi(accIDStr);
        float amount = std::stof(amountStr);

        loans.emplace_back(lname, amount, type, date, note);
        loans.back().set_loanId(loanID);
        loans.back().set_accID(accID);
        if (loanID > maxLoanID)
            maxLoanID = loanID;
    }

    while (std::getline(accTransFile, line))
    {
        std::istringstream iss(line);
        std::string accIDStr, transIDStr;
        std::getline(iss, accIDStr, '|');
        std::getline(iss, transIDStr, '|');

        int accID = std::stoi(accIDStr);
        int transID = std::stoi(transIDStr);

        for (auto &acc : accounts)
        {
            if (acc.get_accountID() == accID)
            {
                acc.trans_ID.push_back(transID);
                break;
            }
        }
    }

    while (std::getline(accLoanFile, line))
    {
        std::istringstream iss(line);
        std::string accIDStr, loanIDStr;
        std::getline(iss, accIDStr, '|');
        std::getline(iss, loanIDStr, '|');

        int accID = std::stoi(accIDStr);
        int loanID = std::stoi(loanIDStr);

        for (auto &acc : accounts)
        {
            if (acc.get_accountID() == accID)
            {
                acc.loan_ID.push_back(loanID);
                break;
            }
        }
    }
    Admin::set_admin_count(maxAdminID + 1);
    User::set_user_count(maxUserID + 1);
    Account::set_acc_count(maxAccID + 1);
    Transaction::set_user_count(maxTransID + 1);
    Loan::set_user_count(maxLoanID + 1);

    adminFile.close();
    userFile.close();
    accFile.close();
    transFile.close();
    loanFile.close();
    accTransFile.close();
    accLoanFile.close();
}