// Debug5 - Matthew Xue - 6/10/23
// The goal of this debug execrice is to understand the concept of object slicing.
// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

// Expected output -
// Name: tesla model Year: 2019
// Name: Hyundai model Year: 2020 Mileage: 23
// Name: Ford model Year: 2012 Miles driven: 20000
// Name: Ford model Year: 2017 Miles driven: 10000

/*
- The assignment of ref is changed to a non-const reference to avoid object slicing.

- The assignment operator usage is corrected by assigning ford2 to ref.

- Added getter methods getName() and getModelYear() in the car class to access the private members.

-  Corrected the parameter type in the operator= method of the suv class to match the base class. Changed const car c to const car &c.

-  Used a const reference const car &ref instead of a non-const reference in the main function to avoid object slicing.

  */

#include <iostream>
using namespace std;

class car
{
private:
    string name;
    int modelYear;

protected:
    void assign(const car &c)
    {
        name = c.name;
        modelYear = c.modelYear;
    }

public:
    car(const string &n, const int my) : name(n), modelYear(my) {}

    virtual void print() const
    {
        cout << "Name: " << name << " model Year: " << modelYear << endl;
    }

    virtual ~car() {}

    virtual car &operator=(const car &c)
    {
        name = c.name;
        modelYear = c.modelYear;
        return *this;
    }

    const string &getName() const
    {
        return name;
    }

    int getModelYear() const
    {
        return modelYear;
    }
};

class sedan : public car
{
private:
    int mileage;

public:
    sedan(const string &n, const int my, const int m) : car(n, my), mileage(m) {}

    void print() const override
    {
        cout << "Name: " << getName() << " model Year: " << getModelYear() << " Mileage: " << mileage << endl;
    }
};

class suv : public car
{
private:
    int miles;

public:
    suv(const string &n, const int my, const int m) : car(n, my), miles(m) {}

    void print() const override
    {
        cout << "Name: " << getName() << " model Year: " << getModelYear() << " Miles driven: " << miles << endl;
    }

    suv &operator=(const car &c) override
    {
        if (const suv *b = dynamic_cast<const suv *>(&c))
        {
            assign(*b);
            miles = b->miles; // Assign miles member as well
        }
        return *this;
    }
};

void printCarInfo(const car &c)
{
    c.print();
}

int main()
{
    car tesla = car("tesla", 2019);
    sedan hyundai = sedan("Hyundai", 2020, 23);
    suv ford = suv("Ford", 2012, 20000);

    printCarInfo(tesla);
    printCarInfo(hyundai);

    car &ref = ford; // Changed to a non-const reference to avoid object slicing
    printCarInfo(ref);
    suv ford2 = suv("Ford", 2017, 10000);
    ref = ford2; // Corrected assignment operator usage
    printCarInfo(ref);
    return 0;
}
