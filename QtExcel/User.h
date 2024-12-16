#pragma once
#include <QString>
#include "dasmig/namegen.hpp"
#include <QRandomGenerator>
#include <random> 
#include <qlist.h>
#include "emailGenerator.h"
#include <QMap>
class User
{
private:
    int id;
    QString name;
    QString surname;
    QString family;
    QString phoneNumber;
    QString email;

	static QMap<int,QList<QString>> usedUsers;
public:
   

    User(int id);
    User(int id, QString name, QString surname, QString family, QString phoneNumber, QString email);
    int getId();
    QString getName();
    QString getSurname();
    QString getFamily();
    QString getPhoneNumber();
    QString getEmail();
    void setId(int id);
    void setName(QString name);
    void setSurname(QString surname);
    void setFamily(QString family);
    void setPhoneNumber(QString phoneNumber);
    void setEmail(QString email);
    ~User();

	
    static QList<QString> SetAttributeList(int index) {
        QList<QString> temp;
        for (size_t i = 0; i < usedUsers.size(); i++)
        {
            temp.append(usedUsers[i][index]);
        }
		return temp;
    }

    static QMap<int, QList<QString>> getUsedUsers() { return usedUsers; };
	static QList<int> getUsedIds() { return usedUsers.keys(); };
	static QList<QString> getUsedNames() {
		return SetAttributeList(0);
		
    };
	static QList<QString> getUsedSurnames() {   
		return SetAttributeList(1);
	};
	static QList<QString> getUsedFamilies() {
		return SetAttributeList(2);
	};
	static QList<QString> getUsedPhoneNumbers() {
		return SetAttributeList(3);
	};
	static QList<QString> getUsedEmails() {
		return SetAttributeList(4);
	};

    

};
