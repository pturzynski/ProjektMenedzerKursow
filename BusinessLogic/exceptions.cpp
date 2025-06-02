#include "exceptions.h"

FileOpenException::FileOpenException(const string& exc)
    : runtime_error("Nie można otworzyć pliku: " + exc) {}

FileReadException::FileReadException(const string& exc)
    : runtime_error("Błąd podczas wczytywania pliku: " + exc) {}

FileWriteException::FileWriteException(const string& exc)
    : runtime_error("Błąd podczas zapisu pliku: " + exc) {}

LoginFailedException::LoginFailedException(const string &exc)
    : runtime_error("Błąd logowania: " + exc) {}

CourseEmptyException::CourseEmptyException(const string &exc)
    : runtime_error("Pusty kurs: "+ exc) {}
