#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

/*TomatoGreenhouseBuilder и CucumberGreenhouseBuilder реализуют интерфейс GreenhouseBuilder.
Каждый из этих классов устанавливает условия для выращивания своей культуры (томаты или огурцы) в теплице.
Класс Director отвечает за последовательность вызова методов у строителей для создания теплиц для каждой культуры.
Функция ClientCode создает объекты строителей и директора, а затем использует директора для настройки условий в теплице для томатов и огурцов.
*/

//Класс Greenhouse - конечный продукт, который должен быть создан строителями.
//Он хранит условия в теплице в виде статического массива указателей на строки. 
class Greenhouse {
public:
    char* parts[4]; // массив, где храняться условия в теплице
    int partsCount; // счётчик количества добавленных условий

    Greenhouse() {
        // инициализируем счётчик и обнуляем все указатели в массиве
        partsCount = 0;
        for (int i = 0; i < 4; i++) {
            parts[i] = nullptr;
        }
    }

    // освобождаем память, занятую строками в массиве
    ~Greenhouse() {
        for (int i = 0; i < partsCount; i++) {
            delete[] parts[i];
        }
    }

    // выводит на экран все условия, установленные в теплице
    void ListParts() const {
        std::cout << "Greenhouse conditions: ";
        for (int i = 0; i < partsCount; i++) {
            if (i == partsCount - 1) {
                std::cout << parts[i];
            }
            else {
                std::cout << parts[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }

    // добавляет новое условие в теплицу
    void AddPart(const char* part) {
        parts[partsCount] = new char[strlen(part) + 1];
        strcpy(parts[partsCount], part);
        partsCount++;
    }
};

// Интерфейс GreenhouseBuilder объявляет методы для установки различных условий в теплице
class GreenhouseBuilder {
public:
    virtual ~GreenhouseBuilder() {}
    virtual void SetTemperature(int temp) const = 0;
    virtual void SetHumidity(int humidity) const = 0;
    virtual void SetLighting(int light) const = 0;
    virtual void SetIrrigation(int water) const = 0;
};

// Конкретный строитель TomatoGreenhouseBuilder реализует интерфейс GreenhouseBuilder 
// и устанавливает условия для выращивания томатов
class TomatoGreenhouseBuilder : public GreenhouseBuilder {
private:
    Greenhouse* greenhouse;

public:
    TomatoGreenhouseBuilder() {
        this->Reset();
    }

    ~TomatoGreenhouseBuilder() {
        delete greenhouse;
    }

    // создёт новый объект Greenhouse для следующей сборки
    void Reset() {
        this->greenhouse = new Greenhouse();
    }

    //Методы SetTemperature, SetHumidity, SetLighting и SetIrrigation добавляют
    //новые условия в теплицу, которые подходят для выращивания томатов
    void SetTemperature(int temp) const override {
        char* part = new char[50];
        sprintf(part, "Temperature: %d grad C", temp);
        this->greenhouse->AddPart(part);
    }

    void SetHumidity(int humidity) const override {
        char* part = new char[50];
        sprintf(part, "Humidity: %d%%", humidity);
        this->greenhouse->AddPart(part);
    }

    void SetLighting(int light) const override {
        char* part = new char[50];
        sprintf(part, "Lighting: %d lux", light);
        this->greenhouse->AddPart(part);
    }

    void SetIrrigation(int water) const override {
        char* part = new char[50];
        sprintf(part, "Irrigation: %d liters/day", water);
        this->greenhouse->AddPart(part);
    }

    // Метод GetGreenhouse возвращает созданную теплицу и сбрасывает состояние строителя
    Greenhouse* GetGreenhouse() {
        Greenhouse* result = this->greenhouse;
        this->Reset();
        return result;
    }
};

// Конкретный строитель CucumberGreenhouseBuilder реализует интерфейс GreenhouseBuilder
// и устанавливает условия, подходящие для выращивания огурцов
class CucumberGreenhouseBuilder : public GreenhouseBuilder {
private:
    Greenhouse* greenhouse;

public:
    CucumberGreenhouseBuilder() {
        this->Reset();
    }

    ~CucumberGreenhouseBuilder() {
        delete greenhouse;
    }

    void Reset() {
        this->greenhouse = new Greenhouse();
    }

    void SetTemperature(int temp) const override {
        char* part = new char[50];
        sprintf(part, "Temperature: %d grad C", temp);
        this->greenhouse->AddPart(part);
    }

    void SetHumidity(int humidity) const override {
        char* part = new char[50];
        sprintf(part, "Humidity: %d%%", humidity);
        this->greenhouse->AddPart(part);
    }

    void SetLighting(int light) const override {
        char* part = new char[50];
        sprintf(part, "Lighting: %d lux", light);
        this->greenhouse->AddPart(part);
    }

    void SetIrrigation(int water) const override {
        char* part = new char[50];
        sprintf(part, "Irrigation: %d liters/day", water);
        this->greenhouse->AddPart(part);
    }

    // возвращает созданную теплицу и сбрасывает состояние строителя
    Greenhouse* GetGreenhouse() {
        Greenhouse* result = this->greenhouse;
        this->Reset();
        return result;
    }
};

// Класс Director управляет процессом построения теплиц для различных культур
class Director {
private:
    GreenhouseBuilder* builder;

public:
    void SetBuilder(GreenhouseBuilder* builder) {
        this->builder = builder;
    }
    // Методы BuildTomatoGreenhouse и BuildCucumberGreenhouse задают настройки для
    // теплиц, подходящих для выращивания томатов и огурцов соответственно
    void BuildTomatoGreenhouse() {
        this->builder->SetTemperature(22);
        this->builder->SetHumidity(70);
        this->builder->SetLighting(8000);
        this->builder->SetIrrigation(5);
    }

    void BuildCucumberGreenhouse() {
        this->builder->SetTemperature(18);
        this->builder->SetHumidity(80);
        this->builder->SetLighting(6000);
        this->builder->SetIrrigation(8);
    }
};

// Клиентский код создает объекты-строители, передает их директору и получает
// готовые теплицы
void ClientCode(Director& director) {
    // Создаем строителя для томатов
    TomatoGreenhouseBuilder* tomatoBuilder = new TomatoGreenhouseBuilder();
    director.SetBuilder(tomatoBuilder);
    director.BuildTomatoGreenhouse();

    Greenhouse* tomatoGreenhouse = tomatoBuilder->GetGreenhouse();
    tomatoGreenhouse->ListParts();
    delete tomatoGreenhouse;

    // Создаем строителя для огурцов
    CucumberGreenhouseBuilder* cucumberBuilder = new CucumberGreenhouseBuilder();
    director.SetBuilder(cucumberBuilder);
    director.BuildCucumberGreenhouse();

    Greenhouse* cucumberGreenhouse = cucumberBuilder->GetGreenhouse();
    cucumberGreenhouse->ListParts();
    delete cucumberGreenhouse;

    delete tomatoBuilder;
    delete cucumberBuilder;
}

int main() {
    setlocale(LC_ALL, "");

    // Создаем директора, который будет управлять строителями
    Director director;
    ClientCode(director);
    return 0;
}