#ifndef THREADMETHODS_H
#define THREADMETHODS_H

#include <iostream>
#include <mutex>

using std::mutex;
using std::cout;
using std::endl;

void CommonMethod(int patients_count, int doctor_id);
void InitializePatientArray(int* patients);
static void DentistMethod(int time);
static void TherapistMethod(int time);
static void SurgeonMethod(int time);

#endif //MULTITHREADINGHW_THREADMETHODS_H
