<<<<<<< HEAD
=======
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// وضعیت رزرو
enum ReservationStatus { SUCCESS, FAILED, CANCELLED };
enum MealType { BREAKFAST , LUNCH , DINNER};

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
>>>>>>> 09596a9ace6495e75ca20b4c8ae8635ca2e83a0c
