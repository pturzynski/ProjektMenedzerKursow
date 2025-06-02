#include "user.h"

User::User(const QString &username, const QString &password)
    : username(username), password(password) {}


QString User::getNick() const {
    return username;
}

bool User::checkPassword(const QString &p) const {
    return p == password;
}
