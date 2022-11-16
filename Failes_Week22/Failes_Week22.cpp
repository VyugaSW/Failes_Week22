
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;
//Задание 1. Напишите информационную систему «Сотрудники». Программа должна обеспечивать ввод данных,
//редактирование данных сотрудника, удаление сотрудника,
//поиск сотрудника по фамилии, вывод информации обо
//всех сотрудниках, указанного возраста, или фамилия
//которых начинается на указанную букву.Организуйте
//возможность сохранения найденной информации в файл.
//Также весь список сотрудников сохраняется в файл(при
//выходе из программы — автоматически, в процессе исполнения программы — по команде пользователя).При
//старте программы происходит загрузка списка сотрудников из указанного пользователем файла.

HANDLE outConsole = GetStdHandle(STD_OUTPUT_HANDLE);
char* path = new char[125]; //Сохраняет ранее введёный путь пользователя (если таковой имеется)
bool pathFlag = false; // Если путь ещё не введён, то false, если уже вводился (имеется старый путь), то false

struct Employee {
    char* name = new char[125]{NULL};
    char* surname = new char[125]{NULL};
    int age = NULL;
};


Employee* UpdateArr(Employee* oldArr, int& size); //Увеличение списка
Employee* DeleteElement(Employee* oldArr, int& size, int number); //Удаление элемента (сотрудника)
void InputData(Employee* arrEm, int size); //Ввод сотрудника
void EditingData(Employee* arrEm, int size); //Редактирование сотрудника
void PrintData(Employee* arrEm, int size); //Вывод всех сотрудников
void PrintDataAge(Employee* arrEm, int size); //Вывод всех сотрудников заданного возраста
void PrintDataSurnameFirstLetter(Employee* arrEm, int size); //Вывод всех сотрудинков по первой букве фамилии
void SearchEmployeeOnSurname(Employee* arrEm, int size); //Вывод сотрудник(а/ов) по фамилии
void SaveInFile(Employee* arrEm, int size); //Сохранение в файл
void AutomaticSaveInFile(Employee* arrEm, int size); //Автоматическое сохранение в файл
void FileUnpackingData(Employee* arrEm, int &size); //Ввод данных из файла (распаковка)

//Увеличение массива
Employee* UpdateArr(Employee* oldArr, int &size) {
    size++;
    Employee* newArr = new Employee[size]; //Новый массив с новым размером
    for (int i = 0; i < size - 1; i++) {   //Копируем старый в новый
        newArr[i].age = oldArr[i].age;
        strcpy_s(newArr[i].name, 125, oldArr[i].name);
        strcpy_s(newArr[i].surname, 125, oldArr[i].surname);
    }
    delete[] oldArr; //Удаляем старый
    return newArr;
}
//Удаление сотрудника
Employee* DeleteElement(Employee* oldArr, int &size, int number) {
    size--; 
    Employee* newArr = new Employee[size];  //Новый массив с новым размером
    for (int i = 0, k = 0; i < size + 1; i++) { //Копируем кроме одного элемента под индексом number
        if (i + 1 != number) {
            newArr[k] = oldArr[i];
            k++;
        }
            
    }
    delete[] oldArr; //Удаляем старый
    return newArr;
}
//Ввод данных (одного сотрудника)
void InputData(Employee* arrEm, int size) {
    system("cls");
    if (size > 1)
        cin.ignore(256, '\n');
    cout << "Enter a name of Employee " << size << " :" << endl;
    gets_s(arrEm[size-1].name, 126); //Ввод имени

    cout << "Enter a surname of Employee " << size << " :" << endl;
    gets_s(arrEm[size - 1].surname, 126); //Ввод фамилии

    cout << "Enter a age of Employee " << size << " :"  << endl;
    cin >> arrEm[size-1].age; //Ввод возраста
}
//Редактирование данных сотрудника
void EditingData(Employee* arrEm,int size) {
    system("cls");
    int number; //Выбор пользователя (номер сотрудника)
    cin.ignore(256, '\n');
    cout << "Number of editing employee: \n";
    for (int i = 0; i < size; i++) { //Список (по номерам) всех сотрудников
        cout << "- " << i+1 << endl;
    }
    cout << endl;
    number = _getch() - 48; //Код клавиши "1" - 49 => 49 - 48 = 1 (Номер сотрудника) и так соот.
    InputData(arrEm, number); //Просто и незатейливо заполняем данные заново, где number номер соотрудника
}
//Вывод информации
void PrintData(Employee* arrEm, int size) {
    system("cls");
    //Вывод всех
    for (int i = 0; i < size; i++) {
        cout << "||Number of Employee - " << i + 1 << " ||" << endl;
        cout << "Employee's name: " << arrEm[i].name << endl;
        cout << "Employee's surname: " << arrEm[i].surname << endl;
        cout << "Employee's age: " << arrEm[i].age << endl << endl;
    }
    cout << "Press any key to return";
    _getch();
}
//Вывод сотрудников с указанным возрастоим
void PrintDataAge(Employee* arrEm, int size) {
    system("cls");
    int age; //Искомый возраст
    cout << "Enter a searching age: \n";
    cin >> age;
    for (int i = 0; i < size; i++) {
        if (age == arrEm[i].age) { //Если нашлись совпадения
            cout << "||Number of Employee - " << i + 1 << " ||" << endl;
            cout << "Employee's name: " << arrEm[i].name << endl;
            cout << "Employee's surname: " << arrEm[i].surname << endl;
            cout << "Employee's age: ";
            SetConsoleTextAttribute(outConsole, 12); //Меняем цвет текста на красный
            cout << arrEm[i].age << endl << endl;
            SetConsoleTextAttribute(outConsole, 15); //И обратно
        }
    }
    cout << "Press any key to return";
    _getch();
}
//Вывод сотрудников по первой букве фамилии
void PrintDataSurnameFirstLetter(Employee* arrEm, int size) {
    system("cls");
    char litera; //Первая буква фамилии
    cout << "Enter a first symbol of surname: \n";
    cin >> litera;
    for (int i = 0; i < size; i++) {
        if (litera == arrEm[i].surname[0]) { //Вновь: если найдены были совпадения
            cout << "||Number of Employee - " << i + 1 << " ||" << endl;
            cout << "Employee's name: " << arrEm[i].name << endl;
            cout << "Employee's surname: ";
            SetConsoleTextAttribute(outConsole, 12); //Меняем цвет текста на красный
            cout << arrEm[i].surname[0];
            SetConsoleTextAttribute(outConsole, 15); //И обратно
            cout << arrEm[i].surname + 1 << endl;
            cout << "Employee's age: ";
            cout << arrEm[i].age << endl << endl;
        }
    }
    cout << "Press any key to return";
    _getch();
}
//Поиск сотрудника по фамилии
void SearchEmployeeOnSurname(Employee* arrEm, int size) {
    system("cls");
    cin.ignore(256, '\n');
    char* buff = new char[125]; //Искомая фамилия
    cout << "Enter a searching surname: \n";
    gets_s(buff, 126);

    for (int i = 0; i < size; i++) {
        if (strcmp(buff, arrEm[i].surname) == 0) { //Если есть совпадения
            cout << "||Number of Employee - " << i + 1 << " ||" << endl;
            cout << "Employee's name: " << arrEm[i].name << endl;
            cout << "Employee's surname: ";
            SetConsoleTextAttribute(outConsole, 12); //Меняем цвет текста на красный
            cout << arrEm[i].surname << endl;
            SetConsoleTextAttribute(outConsole, 15); //И обратно
            cout << "Employee's age: " << arrEm[i].age << endl << endl;
        }
    }
    delete[] buff; //Очищаем память
    cout << "Press any key to return";
    _getch();
}
//Сохранение списка сотрудников в файл
void SaveInFile(Employee* arrEm, int size) {
    system("cls");
    FILE* in;
    int us;
    char* path = new char[125]; //Стезя к файлу
    if (pathFlag) { //Если ранее введёный путь наличествует
        cout << "Use old path or new? (0 - old, 1 - new)\n";
        us = _getch();
        switch (us) {
        case 49: //1
            cout << "Enter file path (Example: \"C:\\Test\\test.txt\"):\n\n";
            gets_s(path, 126);
            break;
        case 48: //0
            strcpy_s(path,126,::path);
            break;
        }

    }
    else { //Если оного нет
        cin.ignore(256, '\n');
        cout << "Enter file path (Example: \"C:\\Test\\test.txt\"):\n\n";
        gets_s(path, 126);
        pathFlag = true;
    }

    if (!fopen_s(&in, path, "w")) {
        for (int i = 0; i < size; i++) {
            fputs(arrEm[i].name,in);
            fputs("\n", in);
            fputs(arrEm[i].surname, in);
            fputs("\n", in);
            fprintf(in, "%d", arrEm[i].age);
            fputs("\n\n", in);
        }
        fclose(in);
        cout << "Saved successfully!\n";
    }
    else {
        cout << "WRONG!\n";
    }
    cout << "Press any key to continue\n";
    _getch();
    strcpy_s(::path,126,path); //Сохраняем ранее введёный пользователем путь
    //delete[] path; //К сожалению, удаление массива вызывает исключительную ошибку (Не смог исправить)
}
//Автоматическое сохранение в файл
void AutomaticSaveInFile(Employee* arrEm, int size) {
    system("cls");
    FILE* in;
    cin.ignore(256, '\n');
    char* path = new char[125];    
    if (!pathFlag && size >= 1) { //Если пользователь не указывал ранее куда сохранять
        cout << "You didn' sptcify file path\n\n";
        cout << "Please enter file path (Example: \"C:\\Test\\test.txt\"):\n\n";
        gets_s(path, 126);
        system("cls");
    }
    else //Если путь есть
        strcpy_s(path,126,::path);

    if (!fopen_s(&in, path, "w")) {
        for (int i = 0; i < size; i++) {
            fputs(arrEm[i].name, in);
            fputs("\n", in);
            fputs(arrEm[i].surname, in);
            fputs("\n", in);
            fprintf(in, "%d", arrEm[i].age);
            fputs("\n\n", in);
        }
        fclose(in);
    }
}
//Ввод данных из файла
void FileUnpackingData(Employee* arrEm, int &size) {
    system("cls");
    FILE* out;
    Employee p;
    char* path = new char[125];
    char* buff = new char[125];
    cout << "Enter file path (Example: \"C:\\Test\\test.txt\"):\n\n";
    gets_s(path, 126);
    if (!fopen_s(&out, path, "r")) {
        arrEm = UpdateArr(arrEm, size);
        while (!feof(out)) {                        
            fscanf_s(out, "%s", &p.name,200);                  //Через объект структуры - не вышло
            fscanf_s(out, "%s", &p.surname,200);               //Через buff - нет
            fscanf_s(out, "%d", &p.age, sizeof(int));          //И всё ошибка чтения символов
                                                              //Но задумка такова: в файл информация вноситься
            strcpy_s(arrEm[size-1].name, 125, p.name);        //Одной структурой, что позволяет через счетчик
            strcpy_s(arrEm[size-1].surname, 125, p.surname);  //Считать информацию о каждом сотруднике и сохранить её
            arrEm[size-1].age = p.age;                        //Увеличивая массив на сотрудника функцией UpdateArr
        }
        fclose(out);
        cout << "Load successfully!\n";
    }
    cout << "Press any key to return";
    _getch();
}

int main()
{
    SetConsoleTextAttribute(outConsole, 15);
    int size = 0;
    Employee* arrEm = new Employee[size];
    int userCh;
    bool flag = true;
    while (flag) {
        system("cls");
        cout << "\t||Employees||\n\n";
        cout << "1 - Input employee\n";
        cout << "2 - Editing employee\n";
        cout << "3 - Print all employees\n";
        cout << "4 - Search employees on age\n";
        cout << "5 - Search employees on first letter of surname\n";
        cout << "6 - Search employee on surname\n";
        cout << "7 - Save in file\n";
        cout << "8 - Load data from file\n";
        cout << "9 - Exit\n\n";
        cout << "Enter option - ";
        userCh = _getch();
        switch (userCh) {
        case 49: //1
            arrEm = UpdateArr(arrEm, size);
            InputData(arrEm, size);
            break;
        case 50: //2
            EditingData(arrEm, size);
            break;
        case 51: //3
            PrintData(arrEm, size);
            break;
        case 52: //4
            PrintDataAge(arrEm, size);
            break;
        case 53: // 5  
            PrintDataSurnameFirstLetter(arrEm, size);
            break;
        case 54: // 6
            SearchEmployeeOnSurname(arrEm, size);
            break;
        case 55: //7
            system("cls");
            int s;
            cout << "Are you sure you want to save the list(yes - 1,not - 0)?\n";
            s = _getch();
            switch (s) {
            case 49:
                SaveInFile(arrEm, size);
                break;
            case 48:
                break;
            }
            break;
        case 56:
            FileUnpackingData(arrEm, size);
            break;
        case 57:
            system("cls");
            AutomaticSaveInFile(arrEm, size);
            cout << "\n\n Good bye!\n\n";
            Sleep(1000);
            flag = false;
            break;
        default:
            SetConsoleTextAttribute(outConsole, 12);
            cout << "\t\nWRONG!\n";
            SetConsoleTextAttribute(outConsole, 15);
            cout << "Try one more time\n";
            Sleep(1500);
        }
    }

}


