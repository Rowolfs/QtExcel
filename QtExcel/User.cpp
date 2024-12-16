#include "User.h"


QMap<int, QList<QString>> User::usedUsers;
static QMap<int, QList<QString>> usedUsers = QMap<int, QList<QString>>();

using ng = dasmig::ng;

User::User(int id, QString name, QString surname, QString family, QString phoneNumber, QString email)
    : id(id), name(name), surname(surname), family(family), phoneNumber(phoneNumber), email(email) {
    User::usedUsers.insert(id, { name, surname, family, phoneNumber, email });
}

User::User(int id)
    : id(id) {
    this->name = QString::fromStdWString(ng::instance().get_name(ng::gender::any, ng::culture::russian));
    this->surname = QString::fromStdWString(ng::instance().get_surname(ng::culture::russian));
    this->family = QString::fromStdWString(ng::instance().get_surname(ng::culture::russian));
    this->email = QString::fromStdString(emailGenerator::generateEmail());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 9999999999);
    this->phoneNumber = "+79" + QString::number(dis(gen));

    User::usedUsers.insert(id, { name, surname, family, phoneNumber, email });
}

User::~User() {
	User::usedUsers.remove(id);
}

int User::getId() { return id; }
QString User::getName() { return name; }
QString User::getSurname() { return surname; }
QString User::getFamily() { return family; }
QString User::getPhoneNumber() { return phoneNumber; }
QString User::getEmail() { return email; }

void User::setId(int id) { this->id = id; }
void User::setName(QString name) { this->name = name; }
void User::setSurname(QString surname) { this->surname = surname; }
void User::setFamily(QString family) { this->family = family; }
void User::setPhoneNumber(QString phoneNumber) { this->phoneNumber = phoneNumber; }
void User::setEmail(QString email) { this->email = email; }


