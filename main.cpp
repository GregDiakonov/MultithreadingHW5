#include <iostream>
#include <thread>

#include "threadmethods.h"

int InviteMessage();
int ReadInt(int min, int max);
int GeneratePatient();


/*
 * Алгоритм работы программы:
 * 1. Пользователю выводится приветственное сообщение.
 * 2. Пользователь вводит количество пациентов.
 * 3. Программа генерирует у каждого пациента время приёма у врача.
 * 4. Запускаются два потока - врачи-распределители.
 * 5. Врачи-распределители случайно посылают к врачам-специалистам: дантисту, хирургу или терапевту.
 *    Эти врачи - тоже потоки. У них пациенты сидят своё время, потом выходят.
 *    Этот процесс сопровождается печатью выкладок в консоль.
 * 6. Распределив всех пациентов по врачам, первый врач-распределитель ждёт, пока последний пациент закончит свой приём.
 *    Затем он выводит информацию о рабочем дне: кто сколько человек распределил и вылечил.
 */
int main() {
    int patients_count = InviteMessage();
    int patients_array[patients_count];
    InitializePatientArray(patients_array);
    srand(time(nullptr));
    for(int i=0; i<patients_count; i++) {
        patients_array[i] = GeneratePatient();
    }

    std::thread doctor_1(CommonMethod, patients_count, 1);
    std::thread doctor_2(CommonMethod, patients_count, 2);

    doctor_1.join();
    doctor_2.join();

    return 0;
}

// Сообщение-приветствие. Тут же пользователь вводит число пациентов.
int InviteMessage() {
    cout << "Welcome!" << std::endl;
    cout << "This program is a wierd one: all you need is to input a number." << std::endl;
    cout << "After that, the program will generate a virtual hospital with patients." << std::endl;
    cout << "Program's output will be three numbers: who saw the dentist, the surgeon and the therapist." << std::endl << std::endl;
    cout << "How many patients should the program generate?" << std::endl;
    cout << "Integers from 1 to 10000 are allowed!" << std::endl;
    int answer = ReadInt(1, 10000);
    return answer;
}

// Метод, возвращающий введённое с консоли целое число в диапозоне от min до max включительно.
int ReadInt(int min, int max) {
    char string_input[100];
    scanf("%s", string_input);
    int input;
    while(true) {
        input = atoi(string_input);
        if(input >= min && input <= max) {
            return input;
        } else {
            printf("Sorry, wrong input! Please, correct it.\n");
            scanf("%s", &string_input);
        }
    }
}

// Метод генерирует пациенту время приёма.
int GeneratePatient() {
    int visit_time = rand() % 100;
    visit_time += 50;
    return visit_time;
}
