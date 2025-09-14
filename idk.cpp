#include <iostream>
using namespace std;

class Person {
private:
    char* fullName;
    int age;
    char* job;

public:
    Person() {
        fullName = new char[1];
        fullName[0] = '\0';
        age = 0;
        job = new char[1];
        job[0] = '\0';
    }

    Person(const char* name, int a, const char* j) {
        fullName = new char[strlen(name) + 1];
        (fullName, name);
        age = a;
        job = new char[strlen(j) + 1];
        (job, j);
    }

    Person(const Person& other) {
        fullName = new char[strlen(other.fullName) + 1];
        (fullName, other.fullName);
        age = other.age;
        job = new char[strlen(other.job) + 1];
        (job, other.job);
    }

    ~Person() {
        delete[] fullName;
        delete[] job;
    }

    Person& operator=(const Person& other) {
        if (this != &other) {
            delete[] fullName;
            delete[] job;
            fullName = new char[strlen(other.fullName) + 1];
            (fullName, other.fullName);
            age = other.age;
            job = new char[strlen(other.job) + 1];
            (job, other.job);
        }
        return *this;
    }

    const char* getName() const { return fullName; }
    int getAge() const { return age; }
    const char* getJob() const { return job; }

    void setName(const char* name) {
        delete[] fullName;
        fullName = new char[strlen(name) + 1];
        (fullName, name);
    }

    void setAge(int a) { age = a; }

    void setJob(const char* j) {
        delete[] job;
        job = new char[strlen(j) + 1];
        (job, j);
    }

    void printInfo() const {
        cout << "ПІБ: " << fullName << ", Вік: " << age << ", Професія: " << job << endl;
    }
};

class Apartment {
private:
    int apartmentNumber;
    int roomCount;
    Person* residents;
    int residentCount;
    int capacity;

public:
    Apartment() {
        apartmentNumber = 0;
        roomCount = 1;
        residentCount = 0;
        capacity = 2;
        residents = new Person[capacity];
    }

    Apartment(int number, int rooms) {
        apartmentNumber = number;
        roomCount = rooms;
        residentCount = 0;
        capacity = 2;
        residents = new Person[capacity];
    }

    Apartment(const Apartment& other) {
        apartmentNumber = other.apartmentNumber;
        roomCount = other.roomCount;
        residentCount = other.residentCount;
        capacity = other.capacity;
        residents = new Person[capacity];
        for (int i = 0; i < residentCount; i++) {
            residents[i] = other.residents[i];
        }
    }

    ~Apartment() {
        delete[] residents;
    }

    Apartment& operator=(const Apartment& other) {
        if (this != &other) {
            delete[] residents;
            apartmentNumber = other.apartmentNumber;
            roomCount = other.roomCount;
            residentCount = other.residentCount;
            capacity = other.capacity;
            residents = new Person[capacity];
            for (int i = 0; i < residentCount; i++) {
                residents[i] = other.residents[i];
            }
        }
        return *this;
    }

    int getApartmentNumber() const { return apartmentNumber; }
    int getRoomCount() const { return roomCount; }
    int getResidentCount() const { return residentCount; }

    void setApartmentNumber(int number) { apartmentNumber = number; }
    void setRoomCount(int rooms) { roomCount = rooms; }

    void resize() {
        capacity *= 2;
        Person* newResidents = new Person[capacity];
        for (int i = 0; i < residentCount; i++) {
            newResidents[i] = residents[i];
        }
        delete[] residents;
        residents = newResidents;
    }

    void addResident(const Person& person) {
        if (residentCount >= capacity) {
            resize();
        }
        residents[residentCount] = person;
        residentCount++;
    }

    void removeResident(int index) {
        if (index < 0 || index >= residentCount) {
            cout << "Неправильний індекс мешканця!" << endl;
            return;
        }
        for (int i = index; i < residentCount - 1; i++) {
            residents[i] = residents[i + 1];
        }
        residentCount--;
    }

    void printApartmentInfo() const {
        cout << "Квартира " << apartmentNumber << " кімнат: " << roomCount
            << " Мешканців: " << residentCount << endl;
        if (residentCount > 0) {
            cout << "Мешканці " << endl;
            for (int i = 0; i < residentCount; i++) {
                cout << "  " << i + 1 << ". ";
                residents[i].printInfo();
            }
        }
        else {
            cout << "Квартира порожня" << endl;
        }
    }

    Person* getResident(int index) {
        if (index >= 0 && index < residentCount) {
            return &residents[index];
        }
        return nullptr;
    }
};

class Building {
private:
    char* address;
    int apartmentCount;
    Apartment* apartments;

public:
    Building() {
        address = new char[1];
        address[0] = '\0';
        apartmentCount = 0;
        apartments = nullptr;
    }

    Building(const char* addr, int count) {
        address = new char[strlen(addr) + 1];
        (address, addr);
        apartmentCount = count;
        apartments = new Apartment[count];
        for (int i = 0; i < count; i++) {
            apartments[i].setApartmentNumber(i + 1);
            apartments[i].setRoomCount(2);
        }
    }

    Building(const Building& other) {
        address = new char[strlen(other.address) + 1];
        (address, other.address);
        apartmentCount = other.apartmentCount;
        apartments = new Apartment[apartmentCount];
        for (int i = 0; i < apartmentCount; i++) {
            apartments[i] = other.apartments[i];
        }
    }

    ~Building() {
        delete[] address;
        if (apartments != nullptr) {
            delete[] apartments;
        }
    }

    Building& operator=(const Building& other) {
        if (this != &other) {
            delete[] address;
            delete[] apartments;
            address = new char[strlen(other.address) + 1];
            (address, other.address);
            apartmentCount = other.apartmentCount;
            apartments = new Apartment[apartmentCount];
            for (int i = 0; i < apartmentCount; i++) {
                apartments[i] = other.apartments[i];
            }
        }
        return *this;
    }

    const char* getAddress() const { return address; }
    int getApartmentCount() const { return apartmentCount; }

    void setAddress(const char* addr) {
        delete[] address;
        address = new char[strlen(addr) + 1];
        (address, addr);
    }

    Apartment* getApartment(int number) {
        if (number > 0 && number <= apartmentCount) {
            return &apartments[number - 1];
        }
        return nullptr;
    }

    void printBuildingInfo() const {
        cout << "Будинок за адресою: " << address << endl;
        cout << "Кількість квартир: " << apartmentCount << endl;
        cout << "Інформація по квартирах:" << endl;
        for (int i = 0; i < apartmentCount; i++) {
            apartments[i].printApartmentInfo();
            cout << endl;
        }
    }

    void printOccupancySummary() const {
        int totalResidents = 0;
        int occupiedApartments = 0;

        for (int i = 0; i < apartmentCount; i++) {
            totalResidents += apartments[i].getResidentCount();
            if (apartments[i].getResidentCount() > 0) {
                occupiedApartments++;
            }
        }

        cout << "Статистика будинку:" << endl;
        cout << "Всього мешканців: " << totalResidents << endl;
        cout << "Заселених квартир: " << occupiedApartments << " з " << apartmentCount << endl;
        cout << "Порожніх квартир: " << apartmentCount - occupiedApartments << endl;
    }
};

int main() {
    setlocale(0, "");
    Building building("вул. Шевченка, 15", 5);

    Person person1("Іванов Іван Іванович", 35, "Інженер");
    Person person2("Петрова Марія Петрівна", 28, "Лікар");
    Person person3("Сидоренко Олег Михайлович", 42, "Вчитель");
    Person person4("Коваленко Анна Сергіївна", 31, "Програміст");
    Person person5("Мельник Петро Васильович", 39, "Бухгалтер");

    Apartment* apt1 = building.getApartment(1);
    apt1->setRoomCount(3);
    apt1->addResident(person1);
    apt1->addResident(person2);

    Apartment* apt2 = building.getApartment(2);
    apt2->setRoomCount(2);
    apt2->addResident(person3);

    Apartment* apt3 = building.getApartment(3);
    apt3->setRoomCount(4);
    apt3->addResident(person4);
    apt3->addResident(person5);

    building.printBuildingInfo();

    cout << "==========================================" << endl;
    building.printOccupancySummary();

    cout << "\nТестування конструктора копіювання:" << endl;
    Building buildingCopy = building;
    buildingCopy.setAddress("вул. Франка, 20");
    cout << "Копія будинку:" << endl;
    buildingCopy.printOccupancySummary();

    cout << "\nДодавання нового мешканця в квартиру 4:" << endl;
    Person newPerson("Шевченко Тарас Григорович", 45, "Поет");
    Apartment* apt4 = building.getApartment(4);
    apt4->addResident(newPerson);
    apt4->printApartmentInfo();

    cout << "\nВидалення мешканця з квартири 1:" << endl;
    apt1->removeResident(0);
    apt1->printApartmentInfo();

    cout << "\nФінальна статистика будинку:" << endl;
    building.printOccupancySummary();

    return 0;
}
