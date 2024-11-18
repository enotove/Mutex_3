// Mutex_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mutex>
#include <string>

class Data
{
private:
    std::mutex mtx_;
    std::string first_string;
    std::string second_string;

public:

    Data();
    Data& operator = (const Data& data)
    {
        first_string = data.first_string;
        second_string = data.second_string;
        return *this;
    }
    Data(std::string first_string, std::string second_string)
    {
        this->first_string = first_string;
        this->second_string = second_string;
    }
    void swap_scoped_lock(Data& data1, Data& data2)
    {
        std::scoped_lock sl(data1.mtx_, data2.mtx_);
        Data temp;
        temp = data1;
        data1 = data2;
        data2 = temp;
        
        

    }
    void swap_locked_lock(Data& data1, Data& data2)
    {
        std::lock(data1.mtx_, data2.mtx_);
        std::lock_guard<std::mutex> lk1(data1.mtx_, std::adopt_lock);
        Data temp;
        temp = data1;
        data1 = data2;
        std::lock_guard<std::mutex> lk2(data2.mtx_, std::adopt_lock);
        data2 = temp;

        
        

    }
    void swap_unique_lock(Data& data1, Data& data2)
    {
        std::unique_lock <std::mutex> lk1(data1.mtx_,std::defer_lock);
        Data temp;
        temp = data1;
        data1 = data2;
        std::unique_lock <std::mutex> lk2(data2.mtx_, std::defer_lock);
        data2 = temp;
        std::lock(data1.mtx_, data2.mtx_);

    }
    
};
int main()
{
    std::cout << "Hello World!\n";
}
