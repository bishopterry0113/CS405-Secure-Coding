// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <typeinfo>

struct newException : public std::exception {
    const char* what() const throw () {
        return "Exception";
    }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception

    std::cout << "Running Even More Custom Application Logic." << std::endl;
    char test1[] = "LearningToSecureCodeIsImportant";
    if (sizeof(test1) >= 10) {
        throw std::length_error("Exceeded the number of Characters");
    }
    return true;
}
void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;
    try {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }

    catch (std::exception& exception1) {
        std::cout << exception1.what() << std::endl;
        throw newException();
    }
    

    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if (den == 0) {
        throw std::runtime_error("Error, cannot divide by Zero");
    }
    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::exception& exception2) {
        std::cerr << "Exception Caught: " << typeid(exception2).name() << std::endl;
        std::cerr << "Description: " << exception2.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // TODO: Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.
    std::cout << "Testing" << std::endl;
    try {
        do_division();
        do_custom_application_logic();
    }
    catch (newException& exception) {
        std::cout << exception.what() << std::endl;
    }
    catch (const char* message) {
        std::cerr << message << std::endl;
    }
    catch (...) {  //If you do not know the throw type used in the try block, you can use the "three dots" syntax (...) inside the catch block, which will handle any type of exception (https://www.w3schools.com/cpp/cpp_exceptions.asp)
        std::cout << "Default" << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu