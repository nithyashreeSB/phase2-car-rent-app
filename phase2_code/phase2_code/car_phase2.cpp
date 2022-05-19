#pragma once

#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include <exception>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using namespace std;

class log
{
public:
    string user_name, pass_word, name_user, mail, address;
    void insert();
    int login_check();
    void edit_details();
    void delete_user();
}lo;
class car
{
public:
    string reg_num, brand, seat, status,r="resevered";
    int rent;
    void car_boking();
    void car_display();
    void remove_car();
    void car_reserve();
    void car_edit();
    void car_insert();
}ca;

int log :: login_check()
{
    string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";
    cout << "Enter your user id" << endl;
    cin >> user_name;
    cout << "Enter your password" << endl;
    cin >> pass_word;
    int f1 = 0, f2 = 0;
    pqxx::connection connectionObject(connectionString.c_str());
    pqxx::work login(connectionObject);

    string sql = "SELECT *FROM login WHERE user_name='" + user_name + "'";
    pqxx::result response = login.exec(sql);

    for (int i = 0; i < response.size(); i++)
    {
        f1 = 1;
    }
    string sql1 = "SELECT *FROM login WHERE pass_word='" + pass_word + "'";
    pqxx::result response1 = login.exec(sql);

    for (int i = 0; i < response1.size(); i++)
    {
        f2 = 1;
    }
    if (f1 == 1&& f2==1)
    {
        cout << "Login sucessful" << endl;
        return 1;
    }
    else
    {
        cout << "Invalid user id/password" <<endl;
        return 0;
        
    }
}
void log::insert()
{
    try
    {
        string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work student(connectionObject);
        cout << "Please enter your user id" << endl;
        cin >> user_name;
        cout << "Please enter your password" << endl;
        cin >> pass_word;
        cout << "Please enter your name" << endl;
        cin >> name_user;
        cout << "Please enter your email id" << endl;
        cin >> mail;
        cout << "Please enter your address" << endl;
        cin >> address;
        pqxx::result response = student.exec("INSERT INTO login (user_name,pass_word,name_user,mail,address) VALUES('" +user_name + "','" + pass_word + "','" + name_user + "','" + mail+ "','" + address + "')");
        student.commit();
        cout << "sign up sucessful" << endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
void log:: edit_details()
{
    try
    {
        string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work student(connectionObject);
        cout << "Please enter your user id" << endl;
        cin >> user_name;
        cout << "Please enter your password" << endl;
        cin >> pass_word;
        cout << "Please enter your name" << endl;
        cin >> name_user;
        cout << "Please enter your email id" << endl;
        cin >> mail;
        cout << "Please enter your address" << endl;
        cin >> address;
        string sql = "UPDATE login SET pass_word='" + pass_word + "', name_user='" + name_user + "', mail='" + mail + "',address='" + address + "' WHERE user_name='" + user_name + "'";
        pqxx::result response = student.exec(sql);
        student.commit();
        cout << "details updated" << endl;
        
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    
}
void log::delete_user()
{
    try
    {
        string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";

        cout << "Type the uesr name of the user you need to delete" << endl;
        cin >> user_name;
        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work students(connectionObject);

        pqxx::result response = students.exec("DELETE FROM login WHERE user_name = '" + user_name + "'");

        students.commit();

        cout << "Deleted an entry" << endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

}
void car::car_boking()
{
    int k3,k6;
    cout << "Press 1 to view all cars" << endl;
    cout << "Press 2 to search a car based on brand" << endl;
    cin >> k3;
    if (k3 == 1)
    {
        string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";

        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work car_details(connectionObject);
        pqxx::result response = car_details.exec("SELECT * FROM car_details");

        cout << "reg_no" << "\t" << "Brand" << "\t" << "rent"<<"\t"<<"  status  "<<"\t"<<"seat" << endl;

        for (int i = 0; i < response.size(); i++)
        {
            cout << response[i][0] << "\t" << response[i][1] << "\t" << response[i][2] << "\t" << response[i][3] <<"\t"<<response[i][4]<< endl;
        }
    }
    else if (k3 == 2)
    {
        cout << "Type the brand of the car you are searching for (please type using capital letters)" << endl;
        cin >> brand;
        string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";

        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work car_details(connectionObject);

        string sql = "SELECT *FROM car_details WHERE brand='" + brand + "'";
        pqxx::result response = car_details.exec(sql);
        cout << "reg_no" << "\t" << "Brand" << "\t" << "rent" << "\t" << "  status " <<"\t"<<"seat"<< endl;

        for (int i = 0; i < response.size(); i++)
        {
            cout << response[i][0] << "\t" << response[i][1] << "\t" << response[i][2] << "\t" << response[i][3] << "\t" << response[i][4] << endl;
        }
    }
    cout << "Press 1 to rent car" << endl;
    cout << "Press 2 to reserve car" << endl;
    cin >> k6;
    if (k6 == 1)
    {
        ca.remove_car();
    }
    else if (k6 == 2)
    {
        ca.car_reserve();
    }
    cout << "Thankyou" << endl;
}
void car::remove_car()
{
    string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";

    cout << "Please type the register number of the car you had selected" << endl;
    cin >> reg_num;
    pqxx::connection connectionObject(connectionString.c_str());

    pqxx::work car_details(connectionObject);

    pqxx::result response = car_details.exec("DELETE FROM car_details WHERE reg_num = '" + reg_num + "'");

    car_details.commit();
}
void car::car_reserve()
{
    string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";
    cout << "Type the register number of the car you had selected" << endl;
    cin >> reg_num;
    pqxx::connection connectionObject(connectionString.c_str());

    pqxx::work car_details(connectionObject);

    pqxx::result response = car_details.exec("UPDATE car_details SET status='"+r+"' WHERE reg_num = '" + reg_num + "'");

    car_details.commit();
}
void car::car_edit()
{
    try
    {
        string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";
        cout << "Type the reg num of the car" << endl;
        cin >> reg_num;
        cout << "Type the brand of the car" << endl;
        cin >> brand;
        cout << "Type the number of seats"<<endl;
        cin >> seat;
        cout << "Type the status of the car" << endl;
        cin >> status;
        cout << "Type the rent" << endl;
        cin >> rent;
        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work car_details(connectionObject);

        string sql = "UPDATE car_details SET brand='" + brand + "', rent=" +to_string(rent) + ", status='" + status + "',seat='" + seat + "' WHERE reg_num='" + reg_num + "'";
        pqxx::result response = car_details.exec(sql);
        car_details.commit();
        cout << "sucessfully edited" << endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }


}
void car::car_insert()
{
    try
    {
        string connectionString = "host=localhost port=5432 dbname=car_rent user=postgres password =1312";
        cout << "Type the reg num of the car" << endl;
        cin >> reg_num;
        cout << "Type the brand of the car" << endl;
        cin >> brand;
        cout << "Type the number of seats" << endl;
        cin >> seat;
        cout << "Type the status of the car" << endl;
        cin >> status;
        cout << "Type the rent" << endl;
        cin >> rent;
        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work car_details(connectionObject);
        
        pqxx::result response = car_details.exec("INSERT INTO car_details (reg_num,brand,rent,status,seat) VALUES('" + reg_num + "','" + brand + "','" + to_string(rent) + "','" + status + "','" + seat + "')");
        car_details.commit();
        cout << "Sucessfully inseterted" << endl;
    }

    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

}
int main()
{
    int k1,k2,l;
    cout << "Press 1 for sign in" << endl;
    cout << "Press 2 for sign up/new user" << endl;
    cout << "Press 3 for receptionist" << endl;
    cin >> k1;
    if (k1 == 1)
    {
        l=lo.login_check();
        if (l == 0)
        {
            return 0;
        }
        cout << "Press 1 to book or reserve car" << endl;
        cout << "Press 2 to edit details" << endl;
        cin >> k2;
        if (k2 == 1)
        {
            ca.car_boking();
        }
        if (k2 == 2)
        {
            lo.edit_details();
        }
    }
    else if (k1 == 2)
    {
        lo.insert();
    }
    else if (k1 == 3)
    {
        int p,k4;
        cout << "Please enter your password" << endl;
        cin >> p;
        if (p == 1234)
        {
            cout << "Press 1 to edit a user" << endl;
            cout << "Press 2 to delete a user" << endl;
            cout << "Press 3 to book/reserve car" << endl;
            cout << "Press 4 to edit car" << endl;
            cout << "Press 5 to add a car" << endl;
            cout << "Press 6 to delete a car" << endl;
            cin >> k4;
            switch (k4)
            {
                case 1:
                {
                    lo.edit_details();
                    break;
                }
                case 2:
                {
                    lo.delete_user();
                    break;
                }
                case 3:
                {
                    ca.car_boking();
                    break;
                }
                case 4:
                {
                    ca.car_edit();
                    break;
                }
                case 5:
                {
                    ca.car_insert();
                    break;
                }
                case 6:
                {
                    ca.remove_car();
                    cout << "Sucessfully deleted" << endl;
                    break;
                }
                default:
                {
                    cout << "Invalid Key" << endl;
                    return 0;
                }
                
            }

        }
        else
        {
            cout << "INVALID KEY" << endl;
        }
        
       
    }

}