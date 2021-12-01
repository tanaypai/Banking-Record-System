#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ios;
using std::string;
using std::vector;

class account_details
{
public:
    long account_number;
    char firstName[20];
    char lastName[20];
    float total_Balance;
    void read_data();
    void show_data();
    void print_line();
};
void account_details::read_data()
{
    cout << "\nEnter Account Number: ";
    cin >> this->account_number;
    cout << "Enter First Name: ";
    cin >> this->firstName;
    cout << "Enter Last Name: ";
    cin >> this->lastName;
    cout << "Enter Balance: ";
    cin >> this->total_Balance;
}
void account_details::show_data()
{

    cout << "Account Number: " << this->account_number << endl;
    cout << "First Name: " << this->firstName << endl;
    cout << "Last Name: " << this->lastName << endl;
    cout << "Current Balance: Rs. " << this->total_Balance << endl;
}
void account_details::print_line()
{
    cout << "-------------------------------" << endl;
}
class account_query
{
private:
    vector<account_details> RecordList;

public:
    void write_rec();
    void read_from_file();
    void show_list();
    int search_rec(long);
    int search_rec(char[]);
    void edit_rec(int);
    void delete_rec(int);
    void write_to_file();
    void deposit(int);
    void withdraw(int);
    int searchMenu();
    int account_query_menu();
};
void account_query::write_rec()
{
    account_details record;
    record.read_data();
    cout << endl;
    RecordList.push_back(record);
}
void account_query::show_list()
{
    cout << "\n****Data from file****" << endl;
    for (auto item : RecordList)
    {
        item.show_data();
        item.print_line();
    }
}
void account_query::read_from_file()
{
    fstream fin;
    fin.open("BankRecords.csv", ios::in);
    string line, word;
    account_details rec;
    vector<string> row;
    int i = 0;
    while (getline(fin, line))
    {
        if (i == 0)
        {
            i++;
            continue;
        }
        row.clear();
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        trim(row[1]);
        trim(row[2]);
        rec.account_number = stol(row[0]);
        strcpy(rec.firstName, row[1].c_str());
        strcpy(rec.lastName, row[2].c_str());
        rec.total_Balance = stof(row[3]);
        RecordList.push_back(rec);
    }
}
void account_query::write_to_file()
{
    fstream fout;
    fout.open("BankRecords.csv", ios::out);
    fout << "Account Number"
         << ", "
         << "First Name"
         << ", "
         << "Last Name"
         << ", "
         << "Total Balance"
         << "\n";
    for (auto item : RecordList)
    {
        fout << item.account_number << ", "
             << item.firstName << ", "
             << item.lastName << ", "
             << item.total_Balance
             << "\n";
    }
    fout.close();
}
int account_query::search_rec(long acc)
{
    for (int i = 0; i < RecordList.size(); ++i)
    {
        if (RecordList[i].account_number == acc)
        {
            cout << "\nRecord Found!" << endl;
            RecordList[i].show_data();
            RecordList[i].print_line();
            return i;
        }
    }
    cout << "\nRecord doesn't exist!" << endl;
    return -1;
}
int account_query::search_rec(char name[])
{
    for (int i = 0; i < RecordList.size(); ++i)
    {
        if (strcmp(RecordList[i].firstName, name) == 0)
        {
            cout << "\nRecord Found!" << endl;
            RecordList[i].show_data();
            RecordList[i].print_line();
            return i;
        }
    }
    cout << "\nRecord doesn't exist!" << endl;
    return -1;
}
void account_query::edit_rec(int index)
{
    cout << "Enter the new details for this record below." << endl;
    RecordList[index].read_data();
    cout << endl;
    cout << "Record has been successfully modified." << endl;
}
void account_query::delete_rec(int index)
{
    RecordList.erase(RecordList.begin() + index);
    cout << "Record has been successfully deleted." << endl;
}
void account_query::deposit(int i)
{
    int deposit_amount;
    cout << "Enter the deposit amount: " << endl;
    cin >> deposit_amount;
    RecordList[i].total_Balance += deposit_amount;
    cout << "Specified Amount has been successfully deposited." << endl;
}
void account_query::withdraw(int i)
{
    int withdraw_amount;
    cout << "Enter the withdraw amount: " << endl;
    cin >> withdraw_amount;
    if (RecordList[i].total_Balance > withdraw_amount)
    {
        RecordList[i].total_Balance -= withdraw_amount;
        cout << "Specified Amount has been successfully withdrawn." << endl;
    }
    else
    {
        cout << "Not enough balance" << endl;
    }
}
int account_query::searchMenu()
{
    int searchmethod, ind;
    cout << "\n\t1-->Search by account number";
    cout << "\n\t2-->Search by first name";
    cout << "\n\nEnter your choice: ";
    cin >> searchmethod;
    switch (searchmethod)
    {
    case 1:
        long acc;
        cout << "Enter the account number you'd like to search for:  ";
        cin >> acc;
        ind = this->search_rec(acc);
        break;
    case 2:
        char name[20];
        cout << "Enter the first name of the account you'd like to search for:  ";
        cin >> name;
        ind = this->search_rec(name);
        break;
    default:
        cout << "\nEnter correct choice";
        exit(0);
    }
    return ind;
}
int account_query::account_query_menu()
{
    account_query A;
    int choice, ind;
    ind = 0;
    cout << "***Bank Account Information System***" << endl;
    A.read_from_file();
    while (true)
    {
        cout << "Select one option below ";
        cout << "\n\t1-->Add record to the file";
        cout << "\n\t2-->Show a list of all the Records on file";
        cout << "\n\t3-->Search Record from file";
        cout << "\n\t4-->Edit Record";
        cout << "\n\t5-->Delete Record";
        cout << "\n\t6-->Deposit Money into an account";
        cout << "\n\t7-->Withdraw Money from an account";
        cout << "\n\t8-->Quit";
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.show_list();
            break;
        case 3:
            cout << "Select one option below ";
            A.searchMenu();
            break;
        case 4:
            cout << "Select how you would like to search for the record to edit.";
            ind = A.searchMenu();
            if (ind != -1)
                A.edit_rec(ind);
            break;
        case 5:
            cout << "Select how you would like to search for the record to delete.";
            ind = A.searchMenu();
            if (ind != -1)
                A.delete_rec(ind);
            break;
        case 6:
            cout << "Select how you would like to search for the record to deposit money.";
            ind = A.searchMenu();
            if (ind != -1)
                A.deposit(ind);
            break;
        case 7:
            cout << "Select how you would like to search for the record to withdraw money.";
            ind = A.searchMenu();
            if (ind != -1)
                A.withdraw(ind);
            break;
        case 8:
            A.write_to_file();
            exit(0);
            break;
        default:
            cout << "\nEnter correct choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
class employee_account_details : public account_details
{
public:
    float salary;
    float rate;
    void read_data();
    void show_data();
};
void employee_account_details::read_data()
{
    this->account_details::read_data();
    cout << "Enter Salary: ";
    cin >> this->salary;
    cout << "Enter Hike rate: ";
    cin >> this->rate;
    cout << endl;
}
void employee_account_details::show_data()
{
    this->account_details::show_data();
    cout << "Salary: Rs. " << this->salary << endl;
    cout << "Rate: " << this->rate << "%" << endl;
    this->print_line();
}
class employee_account_query
{
private:
    vector<employee_account_details> EmployeeRecordList;

public:
    void write_rec();
    void read_from_file();
    void show_list();
    int search_rec(long);
    int search_rec(char[]);
    void edit_rec(int);
    void delete_rec(int);
    void write_to_file();
    void salaryHike();
    void paySalary();
    int searchMenu();
    int employee_account_query_menu();
};
void employee_account_query::write_rec()
{
    employee_account_details record;
    record.read_data();
    EmployeeRecordList.push_back(record);
}
void employee_account_query::show_list()
{
    cout << "\n****Data from file****" << endl;
    for (auto item : EmployeeRecordList)
    {
        item.show_data();
    }
}
void employee_account_query::read_from_file()
{
    fstream fin;
    fin.open("EmployeePayroll.csv", ios::in);
    string line, word;
    employee_account_details rec;
    vector<string> row;
    int i = 0;
    while (getline(fin, line))
    {
        if (i == 0)
        {
            i++;
            continue;
        }
        row.clear();
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        trim(row[1]);
        trim(row[2]);
        rec.account_number = stol(row[0]);
        strcpy(rec.firstName, row[1].c_str());
        strcpy(rec.lastName, row[2].c_str());
        rec.total_Balance = stof(row[3]);
        rec.salary = stof(row[4]);
        rec.rate = stof(row[5]);
        EmployeeRecordList.push_back(rec);
    }
}
void employee_account_query::write_to_file()
{
    fstream fout;
    fout.open("EmployeePayroll.csv", ios::out);
    fout << "Account Number"
         << ", "
         << "First Name"
         << ", "
         << "Last Name"
         << ", "
         << "Total Balance"
         << ", "
         << "Salary"
         << ", "
         << "Rate"
         << "\n";
    for (auto item : EmployeeRecordList)
    {
        fout << item.account_number << ", "
             << item.firstName << ", "
             << item.lastName << ", "
             << item.total_Balance << ", "
             << item.salary << ", "
             << item.rate
             << "\n";
    }
    fout.close();
}
int employee_account_query::search_rec(long acc)
{
    for (int i = 0; i < EmployeeRecordList.size(); ++i)
    {
        if (EmployeeRecordList[i].account_number == acc)
        {
            cout << "\nRecord Found!" << endl;
            EmployeeRecordList[i].show_data();
            return i;
        }
    }
    cout << "\nRecord doesn't exist!" << endl;
    return -1;
}
int employee_account_query::search_rec(char name[])
{
    for (int i = 0; i < EmployeeRecordList.size(); ++i)
    {
        if (strcmp(EmployeeRecordList[i].firstName, name) == 0)
        {
            cout << "\nRecord Found!" << endl;
            EmployeeRecordList[i].show_data();
            return i;
        }
    }
    cout << "\nRecord doesn't exist!" << endl;
    return -1;
}
void employee_account_query::edit_rec(int index)
{
    cout << "Enter the new details for this record below." << endl;
    EmployeeRecordList[index].read_data();
    cout << endl;
    cout << "Record has been successfully modified." << endl;
}
void employee_account_query::delete_rec(int index)
{
    EmployeeRecordList.erase(EmployeeRecordList.begin() + index);
    cout << "Record has been successfully deleted." << endl;
}
int employee_account_query::searchMenu()
{
    int searchmethod, ind;
    cout << "\n\t1-->Search by account number";
    cout << "\n\t2-->Search by first name";
    cout << "\n\nEnter your choice: ";
    cin >> searchmethod;
    switch (searchmethod)
    {
    case 1:
        long acc;
        cout << "Enter the account number you'd like to search for:  ";
        cin >> acc;
        ind = this->search_rec(acc);
        break;
    case 2:
        char name[20];
        cout << "Enter the first name of the account you'd like to search for:  ";
        cin >> name;
        ind = this->search_rec(name);
        break;
    default:
        cout << "\nEnter correct choice";
        exit(0);
    }
    return ind;
}
void employee_account_query::salaryHike()
{
    for (int i = 0; i < EmployeeRecordList.size(); ++i)
    {
        EmployeeRecordList[i].salary += EmployeeRecordList[i].salary * 0.01 * EmployeeRecordList[i].rate;
    }
}

void employee_account_query::paySalary()
{
    for (int i = 0; i < EmployeeRecordList.size(); ++i)
    {
        EmployeeRecordList[i].total_Balance += EmployeeRecordList[i].salary;
    }
}
int employee_account_query::employee_account_query_menu()
{
    employee_account_query A;
    int choice, ind;
    ind = 0;
    cout << "***Employee Payroll System***" << endl;
    A.read_from_file();
    while (true)
    {
        cout << "Select one option below ";
        cout << "\n\t1-->Add record to the file";
        cout << "\n\t2-->Show a list of all the Records on file";
        cout << "\n\t3-->Search Record from file";
        cout << "\n\t4-->Edit Record";
        cout << "\n\t5-->Delete Record";
        cout << "\n\t6-->Raise Salary";
        cout << "\n\t7-->Pay Salary";
        cout << "\n\t8-->Quit";
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.show_list();
            break;
        case 3:
            cout << "Select one option below ";
            A.searchMenu();
            break;
        case 4:
            cout << "Select how you would like to search for the record to edit.";
            ind = A.searchMenu();
            if (ind != -1)
                A.edit_rec(ind);
            break;
        case 5:
            cout << "Select how you would like to search for the record to delete.";
            ind = A.searchMenu();
            if (ind != -1)
                A.delete_rec(ind);
            break;
        case 6:
            A.salaryHike();
            cout << "Salaries raised" << endl;
            break;
        case 7:
            A.paySalary();
            cout << "Employee salaries paid" << endl;
            break;
        case 8:
            A.write_to_file();
            exit(0);
            break;
        default:
            cout << "\nEnter correct choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
int main()
{
    cout << "\nSelect one option below ";
    cout << "\n\t1-->Bank Management System";
    cout << "\n\t2-->Employee Payroll System";
    cout << "\n\nEnter your choice: ";
    int choice;
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
    {
        account_query obj;
        obj.account_query_menu();
        break;
    }
    case 2:
    {
        employee_account_query obj;
        obj.employee_account_query_menu();
        break;
    }
    default:
        cout << "\nEnter correct choice";
        exit(0);
    }
}