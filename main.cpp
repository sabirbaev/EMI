#include <iostream>
#include <vector>
#include <numeric> // Для accumulate
#include <string>

struct Record {
    std::string date;
    double income;
    double expense;
};

std::vector<Record> records;

void addRecord() {
    std::string date;
    double income, expense;

    std::cout << "Введите дату (например, 2024-10-24): ";
    std::cin >> date;
    std::cout << "Введите доход (например, 349.919): ";
    std::cin >> income;
    std::cout << "Введите расход (например, 349.919): ";
    std::cin >> expense;

    records.push_back({date, income, expense});
    std::cout << "Запись добавлена.\n";
}

void showAllRecords() {
    if (records.empty()) {
        std::cout << "Нет доступных записей. Сначала добавьте данные.\n";
        return;
    }

    std::cout << "Все записи:\n";
    for (size_t i = 0; i < records.size(); ++i) {
        std::cout << "Запись " << i + 1 << ": Дата = " << records[i].date 
                  << ", Доход = " << records[i].income 
                  << ", Расход = " << records[i].expense << "\n";
    }
}

void calculateAverage() {
    if (records.empty()) {
        std::cout << "Нет данных для расчета. Пожалуйста, сначала введите запись.\n";
        return;
    }

    double totalIncome = 0;
    double totalExpense = 0;

    for (const auto& record : records) {
        totalIncome += record.income;
        totalExpense += record.expense;
    }

    double avgIncome = totalIncome / records.size();
    double avgExpense = totalExpense / records.size();

    std::cout << "Средний доход: " << avgIncome << "\n";
    std::cout << "Средний расход: " << avgExpense << "\n";
}

void forecast() {
    if (records.empty()) {
        std::cout << "Нет данных для прогноза. Пожалуйста, сначала введите запись.\n";
        return;
    }

    int n = records.size();
    double sumIncomeX = 0, sumIncomeY = 0, sumIncomeXY = 0, sumIncomeXX = 0;
    double sumExpenseX = 0, sumExpenseY = 0, sumExpenseXY = 0, sumExpenseXX = 0;

    // Построим линейную регрессию по месяцам (предположим, что каждая запись - это один месяц)
    for (int i = 1; i <= n; ++i) {
        sumIncomeX += i;
        sumIncomeY += records[i - 1].income;
        sumIncomeXY += i * records[i - 1].income;
        sumIncomeXX += i * i;

        sumExpenseX += i;
        sumExpenseY += records[i - 1].expense;
        sumExpenseXY += i * records[i - 1].expense;
        sumExpenseXX += i * i;
    }

    double incomeSlope = (n * sumIncomeXY - sumIncomeX * sumIncomeY) / (n * sumIncomeXX - sumIncomeX * sumIncomeX);
    double incomeIntercept = (sumIncomeY - incomeSlope * sumIncomeX) / n;

    double expenseSlope = (n * sumExpenseXY - sumExpenseX * sumExpenseY) / (n * sumExpenseXX - sumExpenseX * sumExpenseX);
    double expenseIntercept = (sumExpenseY - expenseSlope * sumExpenseX) / n;

    std::cout << "Прогноз на следующие 6 месяцев:\n";
    for (int i = n + 1; i <= n + 6; ++i) {
        double predictedIncome = incomeIntercept + incomeSlope * i;
        double predictedExpense = expenseIntercept + expenseSlope * i;
        std::cout << "Месяц " << i - n << ": Прогнозируемый доход = " << predictedIncome 
                  << ", Прогнозируемые расходы = " << predictedExpense << "\n";
    }
}

int main() {
    int choice;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить запись\n";
        std::cout << "2. Показать все записи\n";
        std::cout << "3. Рассчитать средний доход и расход\n";
        std::cout << "4. Сделать прогноз на 6 месяцев\n";
        std::cout << "5. Выйти\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                showAllRecords();
                break;
            case 3:
                calculateAverage();
                break;
            case 4:
                forecast();
                break;
            case 5:
                std::cout << "Выход...\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 5);

    return 0;
}