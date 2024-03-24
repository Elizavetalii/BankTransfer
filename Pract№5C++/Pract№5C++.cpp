#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <locale>
#include <cmath>

class BankAccount {
private:
    int accountNumber; // Частное поле для хранения номера банковского счета
    double balance; // Частное поле для хранения баланса на счете
    double interestRate; // Частное поле для хранения процентной ставки

public:
    // Конструктор класса BankAccount, инициализирует номер счета, баланс и процентную ставку
    BankAccount(int accNum, double initBalance) : accountNumber(accNum), balance(initBalance), interestRate(0.0) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Депозит успешно выполнен. Новый баланс: " << this->balance << std::endl;
        }
        else {
            std::cout << "Ошибка: некорректная сумма для депозита." << std::endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && this->balance >= amount) {
            this->balance -= amount;
            std::cout << "Снятие средств успешно выполнено. Новый баланс: " << this->balance << std::endl;
            return true;
        }
        else {
            std::cout << "Ошибка: недостаточно средств для снятия." << std::endl;
            return false;
        }
    }

    int getAccountNumber() {
        static int count = 1;
        std::cout << "Номер счета (" << count++ << "): " << this->accountNumber << std::endl;
        return this->accountNumber;
    }

    double getBalance(int accountNumber) {
        if (accountNumber == this->accountNumber) {
            std::cout << "Баланс счета " << accountNumber << ": " << this->balance << std::endl;
            return balance;
            
        }
        else {
            std::cout << "Ошибка: неверный номер счета." << std::endl;
            return 0.0;
        }
    }

    double getInterest() {
        double interest = this->balance * this->interestRate * (1.0 / 12);
        std::cout << "Проценты за месяц: " << std::fixed << std::setprecision(3) << interest << std::endl;
        return 0.0;
    }

    void setInterestRate(double rate) {
        this->interestRate = rate;
        std::cout << "Процентная ставка обновлена: " << this->interestRate << std::endl;
    }

 
    friend bool transfer(BankAccount& from, BankAccount& to, double amount) {
        if (from.balance >= amount) {
            from.balance -= amount;
            to.balance += amount;
            std::cout << "Перевод успешно выполнен." << std::endl;
            return true;
        }
        else {
            std::cout << "Ошибка: недостаточно средств для перевода." << std::endl;
            return false;
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    setlocale(0, "");

    //Создание счетов и их баланса
    BankAccount account1(12345, 2000.0);
    BankAccount account2(54321, 500.0);

    account1.getAccountNumber();
    account2.getAccountNumber();

    account1.getBalance(12345);
    account2.getBalance(54321);

    account1.deposit(200.0);
    account1.withdraw(100.0);

    account2.setInterestRate(0.05);
    account2.getInterest();

    transfer(account1, account2, 300.0);

    account1.getBalance(12345);
    account2.getBalance(54321);
   
    return 0;
}