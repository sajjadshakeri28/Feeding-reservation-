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
    Meal(const string& name, float price, MealType type)
        : name(name), price(price), meal_type(type), is_active(true) {
        meal_id = ++last_meal_id;
    }

    void set_meal_type(MealType type) {
        meal_type = type;
    }

    void set_name(const string& n) {
        name = n;
    }

    void set_price(float p) {
        price = p;
    }

    bool get_is_active() const {
        return is_active;
    }

    void activate() {
        is_active = true;
    }

    void deactivate() {
        is_active = false;
    }

    bool is_available() const {
        return is_active;
    }

    void add_price(float new_price) {
        price = new_price;
    }

    void add_side_item(const string& item) {
        side_items.push_back(item);
    }

    int get_meal_id() const {
        return meal_id;
    }

    string get_name() const {
        return name;
    }

    MealType get_type() const {
        return meal_type;
    }

    float get_price() const {
        return price;
    }

    const vector<string>& get_side_items() const {
        return side_items;
    }

    void print() const {
        cout << "Meal ID: " << meal_id << "\nName: " << name << "\nPrice: " << price
             << "\nStatus: " << (is_active ? "Active" : "Inactive") << endl;
        cout << "Meal Type: ";
        switch (meal_type) {
            case MealType::BREAKFAST:
                cout << "Breakfast";
                break;
            case MealType::LUNCH:
                cout << "Lunch";
                break;
            case MealType::DINNER:
                cout << "Dinner";
                break;
        }
        cout << endl;
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
    DiningHall(const string& name, const string& address, int capacity)
        : name(name), address(address), capacity(capacity) {
        hall_id = ++last_hall_id;
    }

    void set_name(const string& n) {
        name = n;
    }

    void set_address(const string& a) {
        address = a;
    }

    void set_capacity(int c) {
        capacity = c;
    }

    int get_hall_id() const {
        return hall_id;
    }

    string get_name() const {
        return name;
    }

    string get_address() const {
        return address;
    }

    int get_capacity() const {
        return capacity;
    }

    void print() const {
        cout << "Hall ID: " << hall_id << "\nName: " << name << "\nAddress: " << address
             << "\nCapacity: " << capacity << endl;
    }
};

int DiningHall::last_hall_id = 0;

class Student;

class Reservation {
private:
    static int last_reservation_id;
    int reservation_id;
    shared_ptr<Student> student;
    shared_ptr<const DiningHall> dining_hall;
    shared_ptr<Meal> meal;
    RStatus status;
    time_t created_at;

public:
    Reservation(shared_ptr<Student> s,shared_ptr<Meal> m, shared_ptr<const DiningHall> h)
        : student(s), meal(m),dining_hall(h), status(RStatus::NOT_PAID) {
        reservation_id = ++last_reservation_id;
        created_at = time(nullptr);
    }

    void set_status(RStatus new_status) {
        status = new_status;
    }

    void set_meal(shared_ptr<Meal> m) {
        meal = m;
    }

    void set_dining_hall(shared_ptr<const DiningHall> h) {
        dining_hall = h;
    }

    void set_created_at(time_t t) {
        created_at = t;
    }

    int get_reservation_id() const {
        return reservation_id;
    }

    RStatus get_status() const {
        return status;
    }

    shared_ptr<Meal> get_meal() const {
        return meal;
    }

    shared_ptr<const DiningHall> get_dining_hall() const {
        return dining_hall;
    }

    shared_ptr<Student> get_student() const {
        return student;
    }

    void print() const;
};

int Reservation::last_reservation_id = 0;

class Student : public User {
private:
    string student_id;
    string phone;
    string email;
    float balance;
    bool is_active;
    vector<shared_ptr<Reservation>> reservations;

public:
    Student(const string& name, const string& last_name, const string& password,
            const string& student_id, const string& email, const string& phone)
        : User(name, last_name, password), student_id(student_id), email(email),
          phone(phone), balance(0.0), is_active(true) {}

    void set_student_id(const string& sid) {
        student_id = sid;
    }

    void set_name(const string& n) {
        name = n;
    }

    void set_email(const string& e) {
        email = e;
    }

    void set_phone(const string& ph) {
        phone = ph;
    }

    void set_balance(float b) {
        balance = b;
    }

    void set_is_active(bool active) {
        is_active = active;
    }

    // Getters
    string get_student_id() const {
        return student_id;
    }

    string get_email() const {
        return email;
    }

    string get_phone() const {
        return phone;
    }

    float get_balance() const {
        return balance;
    }

    void activate() {
        is_active = true;
    }

    void deactivate() {
        is_active = false;
    }

    vector<shared_ptr<Reservation>> get_reservations() {
        return reservations;
    }

    void reserve_meal(shared_ptr<Meal> meal, shared_ptr<DiningHall> hall) {
        if (!is_active) {
            cout << "Account inactive. Cannot reserve meal." << endl;
            return;
        }

        if (balance < meal->get_price()) {
            cout << "Insufficient balance!" << endl;
            return;
        }

        if (!meal->is_available()) {
            cout << "Meal is not available!" << endl;
            return;
        }

        balance -= meal->get_price();
        reservations.push_back(make_shared<Reservation>(shared_ptr<Student>(this), meal , hall));
        cout << "Meal reserved successfully!" << endl;
    }

       bool cancel_reservation(int reservation_id) {
        for (auto& res : reservations) {
            if (res->get_reservation_id() == reservation_id && res->get_status() == RStatus::SUCCESS) {
                res->set_status(RStatus::CANCELLED);
                balance += res->get_meal()->get_price();
                cout << "Reservation cancelled successfully." << endl;
                return true;
            }
        }
        cout << "No active reservation found for this ID." << endl;
        return false;
    }

    void print() const override {
        cout << "Student ID: " << student_id << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Balance: " << balance << endl;
        cout << "Active: " << (is_active ? "Yes" : "No") << endl;
    }
};

class Admin : public User {
public:
    Admin(const string& name, const string& last_name, const string& password)
        : User(name, last_name, password) {}

    void print() const override {
        cout << "Admin Account\n";
        User::print();
    }

    string get_type() const override {
        return "Admin";
    }
};

class ShoppingCart {
private:
    vector<shared_ptr<Reservation>> _reservations;

public:
    void addReservation(shared_ptr<Reservation> reservation) {
        _reservations.push_back(reservation);
        cout << "Added to shopping cart" << endl;
    }

    void removeReservation(int reservationID) {
        _reservations.erase(remove_if(_reservations.begin(), _reservations.end(),[reservationID](const shared_ptr<Reservation>& r) { return r->get_reservation_id() == reservationID;}),_reservations.end());
        }

    void viewShoppingCartItems() const {
        for (const auto& r : _reservations) {
            r->print();
        }
    }


    void clear() {
        _reservations.clear();
        cout << "Shopping cart is empty." << endl;
    }

    vector<shared_ptr<Reservation>> getReservations() const {
        return _reservations;
    }
};


class Storage {
private:
    static unique_ptr<Storage> _instance;

    Storage() = default;
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;

public:
    vector<shared_ptr<Student>> students;
    vector<shared_ptr<class Meal>> all_meals;
    vector<shared_ptr<class DiningHall>> all_dining_halls;

    static Storage& instance() {
        if (!_instance)
            _instance = unique_ptr<Storage>(new Storage());
        return *_instance;
    }
};

unique_ptr<Storage> Storage::_instance = nullptr;

class SessionBase {
protected:
    time_t _createdAt;
    time_t _lastLoginTime;
    SessionStatus _status;

public:
    SessionBase() : _createdAt(time(nullptr)), _lastLoginTime(time(nullptr)), _status(SessionStatus::ANONYMOUS) {}

    virtual void load_session() = 0;
    virtual void save_session() = 0;
    virtual void login(const string& username, const string& password) = 0;
    virtual void logout() = 0;

    time_t get_created_at() const {
        return _createdAt;
    }

    time_t get_last_login_time() const {
        return _lastLoginTime;
    }

    SessionStatus get_status() const {
        return _status;
    }

    void set_status(SessionStatus status) {
        _status = status;
    }
};

namespace StudentSession {

class SessionManager : public SessionBase {
private:
    static unique_ptr<SessionManager> _instance;

    shared_ptr<Student> _currentStudent = nullptr;
    shared_ptr<ShoppingCart> _shopping_cart = nullptr;

    SessionManager() = default;

public:
    static SessionManager& instance() {
        if (!_instance)
            _instance = unique_ptr<SessionManager>(new SessionManager());
        return *_instance;
    }

    void load_session() override {}
    void save_session() override {}
    void login(const string& username, const string& password) override {}
    void logout() override {}

    shared_ptr<Student> currentStudent() const {
        return _currentStudent;
    }

    shared_ptr<ShoppingCart> shoppingCart() const {
        return _shopping_cart;
    }

    void set_current_student(shared_ptr<Student> s) {
        _currentStudent = s;
    }

    void set_shopping_cart(shared_ptr<ShoppingCart> cart) {
        _shopping_cart = cart;
    }
};

unique_ptr<SessionManager> SessionManager::_instance = nullptr;

}

namespace AdminSession {

class SessionManager : public SessionBase {
private:
    static unique_ptr<SessionManager> _instance;

    Admin* _currentAdmin = nullptr;

    SessionManager() = default;

public:
    static SessionManager& instance() {
        if (!_instance)
            _instance = unique_ptr<SessionManager>(new SessionManager());
        return *_instance;
    }

    void load_session() override {}
    void save_session() override {}
    void login(const string& username, const string& password) override {}
    void logout() override {}

    Admin* currentAdmin() const {
        return _currentAdmin;
    }

    void setCurrentAdmin(Admin* a) {
        _currentAdmin = a;
    }
};

unique_ptr<SessionManager> SessionManager::_instance = nullptr;

}
class Panel {
private:
    StudentSession::SessionManager& session;

public:
    Panel() : session(StudentSession::SessionManager::instance()){}
    void action(int choice) {
        switch (choice) {
            case 1:
                showStudentInfo();
                break;
            case 2:
                checkBalance();
                break;
            case 3:
                viewReservations();
                break;
            case 4:
                viewShoppingCart();
                break;
            case 5:
                addToShoppingCart();
                break;
            case 6:
                removeShoppingCartItem();
                break;
            case 7:
                void confirmShoppingCart();
                break;
            case 8:
                increaseBalance();
                break;
            case 9:
                void viewRecentTransactions();
                break;
            case 10: {
                int rid;
                cout << "Enter Reservation ID: ";
                cin >> rid;
                break;
            }
            case 0:
                exit();
                break;
            default:
                cout << "Invalid choice. Please try again" << endl;
        }
    }

    void show_menu() {
        int choice;
        do {
            cout << "--- Student Panel Menu --- \n";
            cout << "1. Show Student Info\n";
            cout << "2. Check Balance\n";
            cout << "3. View Reservations\n";
            cout << "4. View Shopping Cart\n";
            cout << "5. Add To Shopping Cart\n";
            cout << "6. Remove Shopping Cart Item\n";
            cout << "7. Confirm Shopping Cart\n";
            cout << "8. Increase Balance\n";
            cout << "9. View Recent Transactions\n";
            cout << "10. Cancel Reservations\n";
            cout << "0. Exit\n";
            cout << "-------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;
            action(choice);
        } while (choice != 0);
    }

    void showStudentInfo() {
        if(auto student = session.currentStudent()){
            student->print();
        }
            
    }

    void checkBalance() {
        if(auto student = session.currentStudent()){
            cout << "Balance: " << session.currentStudent()->get_balance() << " toman\n";
        }
        
    }

    void viewReservations() {
        for (const auto& r : session.currentStudent()->get_reservations())
            r->print();
    }

    void viewShoppingCart() {
        session.shoppingCart()->viewShoppingCartItems();
    }

    void addToShoppingCart() {
    int meal_id;
    cout << "Enter Meal ID: ";
    cin >> meal_id;

    shared_ptr<Meal> selected = nullptr;
    for (auto& m : Storage::instance().all_meals) {
        if (m->get_meal_id() == meal_id) {
            selected = m;
            break;
        }
    }
    if (!selected) {
        cout << "Did not find food" << endl;
        return;
    }

    auto& halls = Storage::instance().all_dining_halls;
    if (halls.empty()) {
        cout << "No dining hall found." << endl;
        return;
    }

    auto dininghallPtr = halls[0];
    auto studentPtr = shared_ptr<Student>(session.currentStudent());
    
    auto reservation = make_shared<Reservation>(studentPtr , selected , dininghallPtr);
    reservation->set_status(RStatus::NOT_PAID);
    session.shoppingCart()->addReservation(reservation);
}


    void removeShoppingCartItem() {
        int rid;
        cout << "Enter ID: ";
        cin >> rid;
        session.shoppingCart()->removeReservation(rid);
    }

    void increaseBalance() {
        float amount;
        cout << "Deposit amount: ";
        cin >> amount;
        session.currentStudent()->set_balance(session.currentStudent()->get_balance() + amount);
        cout << "Deposit increased." << endl;
    }

    void exit() {
        cout << "Exiting panel..." << endl;
        std::exit(0);
    }
};

class Transaction {
private:
    static int last_transaction_id;

    int _transactionID;
    string _trackingCode;
    float _amount;
    TransactionType _type;
    TransactionStatus _status;
    time_t _createdAt;

public:
    Transaction(float amount = 0.0, TransactionType type = TransactionType::PAYMENT,
                TransactionStatus status = TransactionStatus::PENDING,
                string tracking = "")
        : _amount(amount), _type(type), _status(status), _trackingCode(tracking) {
        _transactionID = ++last_transaction_id;
        _createdAt = time(nullptr);
    }

    int get_transaction_id() const {
        return _transactionID;
    }

    string get_tracking_code() const {
        return _trackingCode;
    }

    float get_amount() const {
        return _amount;
    }

    TransactionType get_type() const {
        return _type;
    }

    TransactionStatus get_status() const {
        return _status;
    }

    time_t get_created_at() const {
        return _createdAt;
    }

    void set_tracking_code(const string& code) {
        _trackingCode = code;
    }

    void set_amount(float amt) {
        _amount = amt;
    }

    void set_type(TransactionType type) {
        _type = type;
    }

    void set_status(TransactionStatus status) {
        _status = status;
    }

    void print() const {
        cout << "Transaction ID: " << _transactionID << "\nAmount: " << _amount
             << "\nTracking Code: " << _trackingCode << "\nStatus: " << static_cast<int>(_status)
             << "\nCreated At: " << ctime(&_createdAt);
    }
};



void Reservation::print() const {
    cout << "Reservation ID: " << reservation_id << "\nStudent: " << student->get_name()
         << "\nMeal: " << meal->get_name() << "\nDining Hall: " << dining_hall->get_name() << endl;
    cout << "Status: ";
    switch (status) {
        case RStatus::NOT_PAID:
            cout << "Pending";
            break;
        case RStatus::CANCELLED:
            cout << "Cancelled";
            break;
        case RStatus::SUCCESS:
            cout << "Confirmed";
            break;
    }
    cout << endl;
}


   int main() {
    // Initialize sample data
    auto& storage = Storage::instance();

    // Create sample dining halls
    storage.all_dining_halls.push_back(make_shared<DiningHall>("Main Dining Hall", "Central Campus", 200));
    storage.all_dining_halls.push_back(make_shared<DiningHall>("North Dining Hall", "North Campus", 150));


    storage.all_meals.push_back(make_shared<Meal>("Breakfast Combo", 15.0, MealType::BREAKFAST));
    storage.all_meals.push_back(make_shared<Meal>("Lunch Special", 20.0, MealType::LUNCH));
    storage.all_meals.push_back(make_shared<Meal>("Dinner Package", 25.0, MealType::DINNER));


    auto student = make_shared<Student>("Ali", "Mohammadi", "password123",  "9821001", "ali@university.com", "09123456789");
    student->set_balance(100.0);
    storage.students.push_back(student);

    auto& session = StudentSession::SessionManager::instance();
    session.set_current_student(student);
    session.set_shopping_cart(make_shared<ShoppingCart>());
    session.set_status(SessionStatus::AUTHENTICATED);

    // Start the panel
    Panel panel;
    panel.show_menu();

    return 0;
}
