#include <iostream>
#include <string>
#include <vector>
using namespace std;

// وضعیت رزرو
enum ReservationStatus { SUCCESS, FAILED, CANCELLED };

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
