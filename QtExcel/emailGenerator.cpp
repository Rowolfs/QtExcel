#include "emailGenerator.h"
// Функция для генерации случайной строки заданной длины
std::string emailGenerator::generateRandomString(size_t length) {
    const std::string chars = "abcdefghijklmnopqrstuvwxyz0123456789";
    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += chars[rand() % chars.size()];
    }
    return result;
}

// Функция для генерации email-адреса
std::string emailGenerator::generateEmail() {
    // Список доменов
    std::vector<std::string> domains = { "gmail.com", "yahoo.com", "outlook.com", "mail.ru", "yandex.ru" };

    // Генерация случайной длины для имени пользователя
    size_t usernameLength = 5 + rand() % 10; // от 5 до 15 символов

    // Генерация имени пользователя
    std::string username = generateRandomString(usernameLength);

    // Выбор случайного домена
    std::string domain = domains[rand() % domains.size()];

    return username + "@" + domain;
}

// Функция инициализации генератора случайных чисел
void emailGenerator::initializeRandomSeed() {
    srand(static_cast<unsigned>(time(0)));
}

