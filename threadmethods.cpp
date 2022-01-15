#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#include "threadmethods.h"

mutex common_doctor_mutex;
mutex dentist_mutex;
mutex surgeon_mutex;
mutex therapist_mutex;

int current_patient=-1;
int* patients_array;

// Общая метрика работы клиники.
int cured_by_dentist = 0;
int cured_by_therapist = 0;
int cured_by_surgeon = 0;
int sent_by_first = 0;
int sent_by_second = 0;

void InitializePatientArray(int* patients) {
    patients_array = patients;
}

/*
 * Метод врача-распределителя (общего врача).
 */
void CommonMethod(int patients_count, int doctor_id) {
    common_doctor_mutex.lock();
    cout << "Doctor " << doctor_id << " have started working!\n";
    common_doctor_mutex.unlock();
    while(current_patient < patients_count-1) {
        // Этот мьютекс защищает данные, общие для врачей-распределителей.
        common_doctor_mutex.lock();
        current_patient++;
        common_doctor_mutex.unlock();
        // Случайное число, определяющее пациента к одному из врачей.
        int doctor_choice = rand()%3;
        switch(doctor_choice) {
            case 0: {
                std::thread dentist_thread(DentistMethod, patients_array[current_patient]);
                common_doctor_mutex.lock();
                std::cout << "Doctor " << doctor_id << " have send a patient to the dentist.\n";
                cured_by_dentist++;
                common_doctor_mutex.unlock();
                dentist_thread.join();
                break;
            }
            case 1: {
                std::thread surgeon_thread(SurgeonMethod, patients_array[current_patient]);
                common_doctor_mutex.lock();
                std::cout << "Doctor " << doctor_id << " have send a patient to the surgeon.\n";
                cured_by_surgeon++;
                common_doctor_mutex.unlock();
                surgeon_thread.join();
                break;
            }
            case 2: {
                std::thread therapist_thread(TherapistMethod, patients_array[current_patient]);
                common_doctor_mutex.lock();
                std::cout << "Doctor " << doctor_id << " have send a patient to the therapist.\n";
                cured_by_therapist++;
                common_doctor_mutex.unlock();
                therapist_thread.join();
                break;
            }


        }
        if(doctor_id==1) {
            ++sent_by_first;
        } else {
            ++sent_by_second;
        }
    }
    // Вывод окончательной метрики
    if(doctor_id == 1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        cout << endl << "Final data:" << endl << endl;
        cout << "Patients served by the first doctor: " << sent_by_first << endl;
        cout << "Patients served by the second doctor: " << sent_by_second << endl << endl;
        cout << "Patients cured by the dentist: " << cured_by_dentist << endl;
        cout << "Patients cured by the surgeon: " << cured_by_surgeon << endl;
        cout << "Patients cured by the therapist: " << cured_by_therapist << endl;
    }
}

// Множество однотипных методов. Каюсь, не нашёл способа передать mutex в метод.
static void DentistMethod(int time) {
    dentist_mutex.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "Dentist has cured a patient.\n";
    dentist_mutex.unlock();
}

static void TherapistMethod(int time) {
    therapist_mutex.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "Therapist has cured a patient.\n";
    therapist_mutex.unlock();
}

static void SurgeonMethod(int time) {
    surgeon_mutex.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "Surgeon has cured a patient.\n";
    surgeon_mutex.unlock();
}

