#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

// класс для хранения информации про студентов
class student
{
    int rollno;
    char name[50];
    int eng_marks, math_marks, oaip_marks, opi_marks, alovs_marks;
    double average;
    char grade;

public:
    void getdata();
    void showdata() const;
    void calculate();
    int retrollno() const;
};

void student::calculate()
{
    average = (eng_marks + math_marks + oaip_marks + opi_marks + alovs_marks) / 5.0;
    if (average >= 9)
        grade = 'S';
    else if (average >= 7)
        grade = 'A';
    else if (average >= 5)
        grade = 'B';
    else if (average >= 3)
        grade = 'C';
    else
        grade = 'D';
}

void student::getdata()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    bool equal = true;
    cout << "\n Введите номер студента ";
    cin >> rollno;
    cout << "\n\n Введите ФИО студента ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nОбщая сумма оценок не должна превышать 50";
    cout << "\nВведите Итоговую оценку за предмет 'Англиский' ";
    while (equal) {
        if (eng_marks > 10 || eng_marks < 0) {
            cin >> eng_marks; cout << "Вы ввели неверное число" << endl;
        }
        else {
            equal = false;
        }
    }


    cout << "\nВведите Итоговую оценку за предмет 'Математический анализ'  ";
    do { cin >> math_marks; cout << "Вы ввели неверное число" << endl; } while (math_marks > 10 || math_marks < 0);
    cout << "\nВведите Итоговую оценку за предмет 'ОАИП'  ";
    do { cin >> oaip_marks; cout << "Вы ввели неверное число" << endl; } while (oaip_marks > 10 || oaip_marks < 0);
    cout << "\nВведите Итоговую оценку за предмет 'ОПИ'  ";
    do { cin >> opi_marks; cout << "Вы ввели неверное число" << endl; } while (opi_marks > 10 || opi_marks < 0);
    cout << "\nВведите Итоговую оценку за предмет 'АЛОВС'  ";
    do { cin >> alovs_marks; cout << "Вы ввели неверное число" << endl; } while (alovs_marks > 10 || alovs_marks < 0);
    calculate();
}
void student::showdata() const
{
    setlocale(LC_CTYPE, "RUSSIAN");
    cout << "\nНомер студента : " << rollno;
    cout << "\nФИО студента : " << name;
    cout << "\nАнглийский : " << eng_marks;
    cout << "\nМатематический анализ : " << math_marks;
    cout << "\nОАИП : " << oaip_marks;
    cout << "\nОПИ : " << opi_marks;
    cout << "\nАЛОВС :" << alovs_marks;
    cout << "\nСредняя оценка :" << average;
    cout << "\nУровень студента :" << grade;
}
int  student::retrollno() const
{
    return rollno;
}
//function declaration
void create_student();
void display_sp(int);//display particular record
void display_all(); // display all records
void delete_student(int);//delete particular record
void change_student(int);//edit particular record
//MAIN
int main()
{
    char ch = 0;
    cout << setprecision(2);
    do
    {
        setlocale(LC_CTYPE, "RUSSIAN");
        char ch;
        int num;
        system("cls");
        cout << "\n\n\n\tМЕНЮ";
        cout << "\n\n\t1.Созать карточку студента";
        cout << "\n\n\t2.Поиск студенческой карточки";
        cout << "\n\n\t3.Показать все карточки студентов ";
        cout << "\n\n\t4.Удалить карточку студента";
        cout << "\n\n\t5.Изменить карточку студента";
        cout << "\n\n\t6.Выйти";
        cout << "\n\n\ Сделайте выбор (1/2/3/4/5/6) ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1': create_student(); break;
        case '2': cout << "\n\n\t Введите номер студента: ";
            cin >> num;
            display_sp(num); break;
        case '3': display_all(); break;
        case '4': cout << "\n\n\t Введите номер студента: ";
            cin >> num;
            delete_student(num); break;
        case '5': cout << "\n\n\tВведите номер студента: "; cin >> num;
            change_student(num); break;
        case '6': cout << "Выход, спасибо что использовали нас!"; exit(0);
        }
    } while (ch != '6');
    return 0;
}
//write student details to file
void create_student()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    student stud;
    ofstream oFile;
    oFile.open("student.dat", ios::binary | ios::app);
    stud.getdata();
    oFile.write(reinterpret_cast<char*> (&stud), sizeof(student));
    oFile.close();
    cout << "\n\n Студенческая карточка была создана ";
    cin.ignore();
    cin.get();
}
// read file records
void display_all()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    student stud;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "Файл не получается открыть!! Нажмите любую клавишу чтобы выйти";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tДЕМОНСТРАЦИЯ ВСЕХ КАРТОЧЕК\n\n";
    while (inFile.read(reinterpret_cast<char*> (&stud), sizeof(student)))
    {
        stud.showdata();
        cout << "\n\n====================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}
//read specific record based on roll number
void display_sp(int n)
{
    setlocale(LC_CTYPE, "RUSSIAN");
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile)
    {
        cout << "Файл не получается открыть... Нажмите любую клавишу чтобы выйти";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (iFile.read(reinterpret_cast<char*> (&stud), sizeof(student)))
    {
        if (stud.retrollno() == n)
        {
            stud.showdata();
            flag = true;
        }
    }
    iFile.close();
    if (flag == false)
        cout << "\n\n Не удается найти карточку";
    cin.ignore();
    cin.get();
}
// modify record for specified roll number
void change_student(int n)
{
    setlocale(LC_CTYPE, "RUSSIAN");
    bool found = false;
    student stud;
    fstream fl;
    fl.open("student.dat", ios::binary | ios::in | ios::out);
    if (!fl)
    {
        cout << "Файл не получается открыть. Нажмите любую клавишу чтобы выйти...";
        cin.ignore();
        cin.get();
        return;
    }
    while (!fl.eof() && found == false)
    {
        fl.read(reinterpret_cast<char*> (&stud), sizeof(student));
        if (stud.retrollno() == n)
        {
            stud.showdata();
            cout << "\n\ Введите новую информацию об студенте:" << endl;
            stud.getdata();
            int pos = (-1) * static_cast<int>(sizeof(stud));
            fl.seekp(pos, ios::cur);
            fl.write(reinterpret_cast<char*> (&stud), sizeof(student));
            cout << "\n\n\t Карточка обновлена!";
            found = true;
        }
    }
    fl.close();
    if (found == false)
        cout << "\n\n Информация не найдена ";
    cin.ignore();
    cin.get();
}
//delete record with particular roll number
void delete_student(int n)
{
    setlocale(LC_CTYPE, "RUSSIAN");
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile)
    {
        cout << "Файл не получается открыть. Нажмите любую клавишу чтобы выйти...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat", ios::out);
    iFile.seekg(0, ios::beg);
    while (iFile.read(reinterpret_cast<char*> (&stud), sizeof(student)))
    {
        if (stud.retrollno() != n)
        {
            oFile.write(reinterpret_cast<char*> (&stud), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\n\tКарточка удалена ..";
    cin.ignore();
    cin.get();
}