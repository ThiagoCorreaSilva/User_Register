#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

class Person
{
    private:
        std::string m_name;
        int m_age;

    public:
        void setName( std::string );
        void setAge( int );
        std::string getName();
        int getAge();
};

#endif