#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <algorithm>

using namespace std;

enum class MealType { BREAKFAST, LUNCH, DINNER };
enum class RStatus { SUCCESS, CANCELLED, FAILED, NOT_PAID };
enum class TransactionType { TRANSFER, PAYMENT };
enum class TransactionStatus { PENDING, COMPLETED, FAILED };
enum class SessionStatus { AUTHENTICATED, ANONYMOUS };

class User;
class Student;
class Admin;
class Meal;
class DiningHall;
class Reservation;
class ShoppingCart;
class Transaction;


class User {
protected:
    static int last_user_id;
    int user_id;
    string name;
    string last_name;
    string hashed_password;

public:
    User(const string& name, const string& last_name, const string& password)
        : name(name), last_name(last_name), hashed_password(password) {
        user_id = ++last_user_id;
    }

    void set_name(const string& n) {
        name = n;
    }

    void set_last_name(const string& ln) {
        last_name = ln;
    }

    void set_password(const string& pass) {
        hashed_password = pass;
    }

    int get_user_id() const {
        return user_id;
    }

    string get_name() const {
        return name;
    }

    string get_last_name() const {
        return last_name;
    }

    string get_password() const {
        return hashed_password;
    }

    virtual void print() const {
        cout << "User  ID: " << user_id << "\nName: " << name << " " << last_name << endl;
    }

    virtual string get_type() const {
        return "User ";
    }
};

int User::last_user_id = 0;


class Panel {
    public:
    void show_menu(){
        cout << "--- Student Panel Menu --- \n";
        cout << "1. Show Student Info\n";
        cout << "2. check Balance\n";
        cout << "3. View Reservations\n";
        cout << "4. Exit\n";
        "-------------------------------------\n";
        cout << "Enter your choice: ";

    }
    void exit(){
        cout << "Exiting panel..." << endl;
        std::exit(0);
    }
    void action(int choice) {
        switch(choice){
            case 1:
                cout << "//void show_student_info()"<< endl;
                break;
            case 2:
                cout <<"//void check_balance()" << endl;
                break;
            case 3:
                cout <<"//void view_resevations()"<< endl;
                break;
            case 4:
                exit();
                break;
            default:
                cout << "Invalid choice.Please try again" << endl;

        }

    }



    //void show_student_info();
    //void check_balance();
    //void view_resevations();
    //void add_reservation(Reservaion);
    //void add_to_shop_cart();
    //void confirm_shoppig_cart();
    //vlid remove_shoppig_cart();
    //void increace_balance();
    //void view_recent_transactions();
    //void cancle_reservation(int);
};
class Storage{
    private:
        int meal_ID_counter;
        int diningHall_ID_counter;
        static unique_ptr<Storage> _instance;
        Storage() = default;
        Storage(const Storage&) = delete;
        Storage& operator=(const Storage&) = delete;
    public:
        vector<shared_ptr<Student>> students;
        vector<shared_ptr<class Meal>> all_meals;
        vector<shared_ptr<class DiningHall>> all_dining_halls;

        static Storage& instance() {
            if(!_instance)
                _instance = unique_ptr<Storage>(new Storage());
            return *_instance;
        }

};
unique_ptr<Storage> Storage::_instance =nullptr;



class Admin : public User {
    public:
        Admin(string name , string last_name , string password)
            : User(name , last_name , password) {}

        void print() const override {
            cout << "Admin Account\n";
            User::print();
        }
        string get_type()const override{
            return "Admin";
        }
};

class Meal {
    private:
        static int last_meal_id;
        int meal_id;
        string name;
        float price;
        bool is_active;
        MealType meal_type;
        
        vector<string> side_items;
    public:
    Meal(string name,float price, MealType type) :
     name(name), price(price), meal_type(type), is_active(true) {
        meal_id = ++last_meal_id;
     }
        void set_meal_type(MealType type){
            meal_type = type;
        }
        void set_name(string n){
            name = n;
        }
        void set_price(float p){
            price = p;
        }
        bool get_is_active(){
            return is_active;
        }
        void active(){
            is_active = true;
        }
        void deactive(){
            is_active = false;
        }
        bool is_available() const{
            return is_active;
        }
        void add_price(float new_price){
            price = new_price;
        }
        void add_side_item(const string& item){
            side_items.push_back(item);
        }

        int get_meal_id() const{
            return meal_id;
        }
        string get_name() const{
            return name; }

        MealType get_type() const{
            return meal_type; }

        float get_price() const{
            return price;
        }

        const vector<string>& get_side_item() const {
            return side_items;
        }
        void print() const {
          cout << "Meal ID: " << meal_id << "\nName: " << name << "\nPrice: " << price << "\nStatus: " << (is_active ? "active": "deactive") << endl;
          cout << "Meal Type: ";
          if(meal_type == MealType::BREAKFAST)
          {
              cout << "BreakFast";
          }
          else if(meal_type == MealType::LUNCH){
              cout << "Lunch";
          }
          else{
              cout << "Dinner";
          }
        
        }
    };
    int Meal::last_meal_id = 0;


    class DiningHall {
        private:
            static int last_hall_id;
            int hall_id;
            string name;
            string address;
            int capacity;

        public:
            DiningHall(string name , string adress , int capacity):
                name(name) , address(adress) , capacity(capacity){
                    hall_id = ++last_hall_id;
                }
            void set_nema(string n){
                name = n;
            }
            void set_address(string a){
                address = a;
            }
            void set_capacity(int c){
                capacity = c;
            }

            int get_hall_id() const{
                return hall_id;
            }

            string get_name() const{
                return name;
            }

            string get_adderss() const{
                return address;
            }

            int get_capacity() const{
                return capacity;
            }
            void print() const{
                cout << "Hall ID: " << hall_id << "\nName: " << name << "\naddress: " << address << "\ncapacity: " << capacity << endl;
            }
        };
int DiningHall::last_hall_id = 0;

class Student;

class Reservation {
    private:
        static int last_reservation_id;
        int reservation_id;
        Student* student;
        const DiningHall *dining_hall;
        Meal* meal;
        RStatus status;
        time_t created_at;

    public:
        Reservation(Student* s, Meal* m,const DiningHall* d)
        : student(s), meal(m), dining_hall(d), status(RStatus::NOT_PAID){
            reservation_id = ++last_reservation_id;
            created_at =  time(nullptr);
        }


        void set_status(RStatus new_status){
        status = new_status;
        }
        void set_meal(Meal* m){
            meal = m;
        }
        void set_dining_hall(const DiningHall* h){
            dining_hall = h;
        }
        void set_created_at(time_t t){
            created_at = t;
        }

        int get_reservation_id() const{
            return reservation_id;
        }

        RStatus get_status() const{
        return status; }

        Meal* get_meal() const{
            return meal;
        }
        const DiningHall* get_dininghall()const{
            return dining_hall;
        }
        Student* get_student()const{
            return student;
        }
        void print()const;
    };


int Reservation::last_reservation_id = 0;
    class Student : public User{
        private:
            string student_id;
            string phone;
            string email;
            float balance;
            bool is_active;
            vector<Reservation> reservations;
        public:
            Student(string name , string last_name , string password , string student_id , string email , string phone)
            : User(name , last_name , password) , student_id(student_id) , email(email), phone(phone), balance(0.0), is_active(true) {}

            void set_student_id(const string& sid){
                student_id = sid;
            }
            void set_name(const string& n){
                name = n;
            }
            void set_email(const string& e){
                email = e;
            }
            void set_phone(const string& ph){
                phone = ph;
            }
            void set_balance(float b){
                balance = b;
            }
            void set_is_active(bool active){
                is_active = active;
            }
            //Getters

            string get_student_id()const{
                return student_id;
            }
            string get_email()const{
                return email;
            }
            string get_phone()const{
                return phone;
            }
            float get_balance()const{
                return balance;
            }
            void active(){
                is_active = true;
            }
            void deactive(){
                is_active = false;
            }
            vector <Reservation>&get_reservations(){
                return reservations;
            }

            void reserve_meal(Meal& meal, const DiningHall& hall) {
                if (!is_active) {
                    cout << "Account inactive. Cannot reserve meal." << endl;
                    return;
                }

                if (balance < meal.get_price()) {
                    cout << "Insufficient balance!" << endl;
                    return;
                }
            if (!meal.is_available()) {
                    cout << "Meal is not available!" << endl;
                    return;
                }
            // for(const auto& res : reservations){
            //     if(res.get_meal()->get_type() == meal.get_type() && res.get_meal()->getReservday() == meal.getReservday() && res.get_status() == ReservationStatus::CONFIRMED){
            //         cout << "Already reserved for this meal type and date." << endl;
            //         return;
            //     }
            // }


                balance -= meal.get_price();
                reservations.emplace_back(this, &meal, &hall);
                cout << "Meal reserved successfully!" << endl;
            }

            // bool cancel_reservation(int reservation_id) {
            //     for (auto& res : reservations) {
            //         if (res.get_reservation_id() == reservation_id && res.get_status() == ReservationStatus::CONFIRMED) {
            //             res.set_status(ReservationStatus::CANCELLED);
            //             balance += res.get_meal()->get_price();
            //             return true;
            //         }
            //     }
            //     cout << "NO active reservtion found for this id." << endl;
            //     return false;
            // }
            void print()const override{
                cout << "Student ID: " << student_id << endl;
                cout << "Email: " << email << endl;
                cout << "Phone: " << phone << endl;
                cout << "Balance: " << balance << endl;
                cout << "Active: " << (is_active ? "Yes" : "No")<< endl;
            }


    };
 void Reservation::print() const {
        cout << "Reservation ID: " << reservation_id << "\nStudent: " << student->get_name()
        << "\nMeal: " << meal->get_name() << "Dining Hall: " << dining_hall->get_name() << endl;
        cout << "status:";
        switch (status){
        case RStatus::FAILED:
            cout << "pending";
            break;
        case RStatus::CANCELLED:
            cout << "cancelled";
            break;
            case RStatus::SUCCESS:
            cout << "confirmed";
            break;
    }
    cout << endl;
    }

int main(){
    Panel panel;
    int choice;

    while(true){
        panel.show_menu();
        cin >> choice;
        panel.action(choice); 
    }
}    
