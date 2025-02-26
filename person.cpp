#include "person.hpp"

void Person::setName( std::string name )
{
    m_name = name;
}

void Person::setAge( int age )
{
    m_age = age;
}

std::string Person::getName()
{
    return m_name;
}

int Person::getAge()
{
    return m_age;
}