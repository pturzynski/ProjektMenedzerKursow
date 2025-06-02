#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "BusinessLogic_global.h"
#include <stdexcept>
#include <string>
using namespace std;

class BUSINESSLOGIC_EXPORT FileOpenException : public runtime_error {
public:
    explicit FileOpenException(const string& exc);
};

class BUSINESSLOGIC_EXPORT FileReadException : public runtime_error {
public:
    explicit FileReadException(const string& exc);
};

class BUSINESSLOGIC_EXPORT FileWriteException : public runtime_error {
public:
    explicit FileWriteException(const string& exc);
};

class BUSINESSLOGIC_EXPORT LoginFailedException : public runtime_error {
public:
    explicit LoginFailedException(const string& exc);
};

class BUSINESSLOGIC_EXPORT CourseEmptyException : public runtime_error {
public:
    explicit CourseEmptyException(const string& exc);
};

#endif // EXCEPTIONS_H
