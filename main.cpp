#include <iostream>
#include <string>
#include <vector>
using namespace std;


enum ReservationStatus { SUCCESS, FAILED, CANCELLED };
enum MealType { BREAKFAST , LUNCH , DINNER};

class Student;
class Reservation;

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

class User{
    protected:
        static int last_user_id;
        int user_id;
        string name;
        string last_name;
        string hashband_password;

    public:
        User(string name, string last_name , string password)
            : name(name) , last_name(last_name), hashband_password(password){
                user_id = ++last_user_id;
            }
        void set_name(string n){
            name = n;
        }
        void set_lastName(string ln){
            last_name = ln;
        }
        void set_password(string pass){
            hashband_password = pass;
        }
    
        int get_user_id()const{
            return user_id;
        }
        string get_name()const{
            return name;
        }
        string get_last_name()const{
            return last_name;
        }
        string get_password()const{
            return hashband_password;
        }
        
        virtual void print()const{
            cout << "User_ID: " << user_id << "\nName: "<< name << " " << last_name << endl;
        }
        virtual string get_type()const{
            return "User";
        }
};

int User::last_user_id = 0;
class Meal {
    private:
        static int last_meal_id;
        int meal_id;
        string name;
        string date;
        MealType type;
        int capacity;
        float price;
        vector<string> side_items;
    public:
    Meal(string name, string date, MealType type, int capacity, float price) :
     name(name), date(date), type(type), capacity(capacity), price(price) {
        meal_id = ++last_meal_id;
     }

        bool is_available() const{
        return capacity > 0; }

        void reserve_one(){
            capacity --; }

        void cancel_reservation(){
            capacity ++; }

        void update_price(float new_price){
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

        string get_date() const{
            return date; }

        MealType get_type() const{
            return type; }

        float get_price() const{
            return price;
        }

        const vector<string>& get_side_item() const {
            return side_items;
        }
        void print() const {
            cout << "Meal ID: " << meal_id << "\nName: " << name << "/nDate: " << date << "\nType: ";
            if(type == BREAKFAST)
            {
                cout << "BreakFast";
            }
            else if(type == LUNCH){
                cout << "Lunch";
            }
            else{
                cout << "Dinner";
            }
            cout << "\nPrice: " << price << "\nCapacity: " << capacity << endl;
        }
    };
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

class Student;

class Reservation {
    private:
        static int last_reservation_id;
        int reservation_id;
        Student* student;
        Meal meal;
        DiningHall dining_hall;
        ReservationStatus status;
        time_t created_at;

    public:
        Reservation(Student* s, Meal m, DiningHall d, ReservationStatus stat)
        : student(s), meal(m), dining_hall(d), status(stat){
            reservation_id = ++last_reservation_id;
            created_at =  time(nullptr);
        }


        void set_status(ReservationStatus new_status){
        status = new_status; }

        int get_reservation_id() const{
            return reservation_id;
        }

        ReservationStatus get_status() const{
        return status; }

        Meal get_meal() const{
            return meal;
        }

        void print() const;//out of the class
    };
    class Student{
        private:
            static int last_user_id;
            int user_id;
            string student_id;
            string name;
            string email;
            float balance;
            bool is_active;
            vector<Reservation> reservations;
        public:
            Student(): balance(0.0) , is_active(true){
                user_id = ++last_user_id;
            }


    //Setters
            void set_student_id(const string& sid){
                student_id = sid;
            }
            void set_name(const string& n){
                name = n;
            }
            void set_email(const string& e){
                email = e;
            }
            void set_balance(float b){
                balance = b;
            }
            void set_is_active(bool active){
                is_active = active;
            }
            //Getters
            int get_user_id(){
                return user_id;
            }
            string get_student_id(){
                return student_id;
            }
            string get_name(){
                return name;
            }
            string get_email(){
                return email;
            }
            float get_balance(){
                return balance;
            }
            bool get_is_active(){
                return is_active;
            }
            vector <Reservation>&get_reservations(){
                return reservations;
            }
            void print(){
                cout << "User ID: " << user_id << endl;
                cout << "Student ID: " << student_id << endl;
                cout << "Name: " << name << endl;
                cout << "Email: " << email << endl;
                cout << "Balance: " << balance << endl;
                cout << "is_active: " << is_active << endl;
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
            for(const auto& r : reservations){
                if(r.get_meal().get_date() == meal.get_date() && r.get_meal().get_type() && r.get_status() == ReservationStatus::SUCCESS){
                    cout << "Already reserved for this meal type and date." << endl;
                }
            }

                meal.reserve_one();
                balance -= meal.get_price();
                reservations.emplace_back(this, meal, hall, SUCCESS);
                cout << "Meal reserved successfully!" << endl;
            }

            bool cancel_reservation(int reservation_id) {
                for (auto& res : reservations) {
                    if (res.get_reservation_id() == reservation_id && res.get_status() == ReservationStatus::SUCCESS) {
                        res.set_status(ReservationStatus::CANCELLED);
                        balance += res.get_meal().get_price();
                        return true;
                    }
                }
                cout << "NO active reservtion found for this id." << endl;
                return false;
            }

    };


    // print reservaton out of the class for using studnt name;
    void Reservation::print() const {
        cout << "Reservation ID: " << reservation_id << "\nStudent: " << student->get_name()
        << "\nMeal: " << meal.get_name() << "Dining Hall: " << dining_hall.get_name() << endl;
        cout << "status:";
        switch (status){
        case SUCCESS:
            cout << "success";
            break;
        case FAILED:
            cout << "failed";
            break;
            case CANCELLED:
            cout << "cancelled";
            break;
    }
    cout << endl;
    }

    //Assigning identifiers
    int Student::last_user_id = 0;
    int Meal::last_meal_id = 0;
    int DiningHall::last_hall_id = 0;
    int Reservation::last_reservation_id = 0;


// testing main for showing classes working;
int main() {
    Student student;
    student.set_name("Ali");
    student.set_balance(100.0);

    Meal meal("kebab", "2025_04_25" , MealType::LUNCH , 10 , 50);
    DiningHall hall("pardis" , "brijand univercity" , 200);

    student.reserve_meal(meal , hall);
    student.print();

}
