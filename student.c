#include <limits.h>
#include <stdlib.h>
#include<stdio.h>
#include "student.h"
 
int findMax(int a, int b) {
    if (a >= b) {
        return a;
    }
    return b;
}
 
int findMin(int a, int b) {
    if (a <= b) {
        return a;
    }
    return b;
}
 
student_t* createStudent(
    char* course,
    char* surname,
    char* name,
    char* middleName,
    int russian,
    int math,
    int physics,
    int computerScience,
    benefit_t benefit
) {
    student_t* newStudent = (student_t*)malloc(sizeof(student_t));
    if(newStudent==NULL){
        printf("Ошибка выделения памяти");
    }
    newStudent->course = course;
    newStudent->surname = surname;
    newStudent->name = name;
    newStudent->middleName = middleName;
    newStudent->russian = russian;
    newStudent->math = math;
    newStudent->physics = physics;
    newStudent->computerScience = computerScience;
    newStudent->benefit = benefit;
    return newStudent;
}
 
 
void appendStudent(studentList_t* self, student_t student) {
    if (self->count >= self->capacity) {
        self->capacity *= 2;
        self->students = (student_t*)realloc(self->students, self->capacity * sizeof(student_t));
        if(self->students==NULL){
        printf("Ошибка выделения памяти");
        }
    }
    self->students[self->count] = student;
    self->count++;
}
 
double calculateAverageScore(studentList_t studentList, benefit_t benefit) {
    double average = 0.0;
    for (int i = 0; i < studentList.count; i++) {
        student_t current = studentList.students[i];
        if (benefit == ANY_QUOTA) {
            average += (current.russian + current.math + findMax(current.computerScience, current.physics)) / 3.0;
        }
        if (benefit == NO_QUOTA) {
            average += (current.russian + current.math + findMax(current.computerScience, current.physics)) / 3.0;
        }
    }
    return average / studentList.count;
}
 
double findMinScore(studentList_t studentList, benefit_t benefit) {
    int minimum = INT_MAX;
    for (int i = 0; i < studentList.count; i++) {
        student_t current = studentList.students[i];
        minimum = findMin(minimum, current.russian);
        minimum = findMin(minimum, current.math);
        minimum = findMin(minimum, current.physics);
        minimum = findMin(minimum, current.computerScience);
    }
    return minimum;
}
 
double findMaxScore(studentList_t studentList, benefit_t benefit) {
    int maximum = -1;
    for (int i = 0; i < studentList.count; i++) {
        student_t current = studentList.students[i];
        maximum = findMax(maximum, current.russian);
        maximum = findMax(maximum, current.math);
        maximum = findMax(maximum, current.physics);
        maximum = findMax(maximum, current.computerScience);
    }
    return maximum;
}
 
int countBenefitStudents(studentList_t studentList) {
    int count = 0;
    for (int i = 0; i < studentList.count; i++) {
        student_t current = studentList.students[i];
        if (current.benefit != NO_QUOTA) {
            count++;
        }
    }
    return count;
}
 
double calculateAverageScoreBySubject(studentList_t studentList, subject_t subject) {
    double average = 0.0;
    for (int i = 0; i < studentList.count; i++) {
        student_t current = studentList.students[i];
        switch(subject) {
            case RUSSIAN:
                average += current.russian;
                break;
            case MATH:
                average += current.math;
                break;
            case PHYSICS:
                average += current.physics;
                break;
            case COMPUTER_SCIENCE:
                average += current.computerScience;
                break;
            default:
                break;
        }
    }
    return average / studentList.count;
}
 
double calculateAverageScoreByPassing(studentList_t studentList) {
    return calculateAverageScore(studentList, NO_QUOTA);
}
 
double calculateAverageScoreWithBenefits(studentList_t studentList) {
    double average = 0.0;
    for (int i = 0; i < studentList.count; i++) {
        student_t current = studentList.students[i];
        if (current.benefit == BVI) {
            average += 100.0;
        } else {
            average += (current.russian + current.math + findMax(current.computerScience, current.physics)) / 3.0;
        }
    }
    return average / studentList.count;
}
 
double calculateMinSumScores(studentList_t studentList) {
    double minSum = 0.0;
    for (int i = 0; i < studentList.count; i++) {
        student_t current = studentList.students[i];
        int minimum = current.russian;
        minimum = findMin(minimum, current.math);
        minimum = findMin(minimum, current.physics);
        minimum = findMin(minimum, current.computerScience);
        minSum += minimum;
    }
    return minSum;
}
 
double calculateMaxSumScores(studentList_t studentList) {
    double maxSum = 0.0;
    for (int i = 0; i < studentList.count; i++) {
        student_t current = studentList.students[i];
        int maximum = current.russian;
        maximum = findMax(maximum, current.math);
        maximum = findMax(maximum, current.physics);
        maximum = findMax(maximum, current.computerScience);
        maxSum += maximum;
    }
    return maxSum;
}
 
int countStudentsByBenefit(studentList_t studentList, benefit_t benefit) {
    int count = 0;
    for (int i = 0; i < studentList.count; i++) {
        student_t current = studentList.students[i];
        if (current.benefit == benefit) {
            count++;
        }
    }
    return count;
}
 
void freeStudentList(studentList_t* list) {
    for (int i = 0; i < list->count; i++) {
        student_t current = list->students[i];
        free(current.course);
        free(current.name);
        free(current.surname);
        free(current.middleName);
    }
    free(list->students);
}
 
void freeStudentsByCourse(studentsByCourses_t* studentsByCourses) {
    for (int i = 0; i < studentsByCourses->count; i++) {
        freeStudentList(&studentsByCourses->studentsByCourses[i]);
    }
    free(studentsByCourses->studentsByCourses);
}
 
analyticsResult_t calculateAnalytics(studentList_t students) {
    analyticsResult_t result = {
        .averageScore = calculateAverageScore(students, ANY_QUOTA),
        .minScore = findMinScore(students, ANY_QUOTA),
        .maxScore = findMaxScore(students, ANY_QUOTA),
        .benefitNumber = countBenefitStudents(students),
        .averageScoreByRussian = calculateAverageScoreBySubject(students, RUSSIAN),
        .averageScoreByMath = calculateAverageScoreBySubject(students, MATH),
        .averageScoreByPhysics = calculateAverageScoreBySubject(students, PHYSICS),
        .averageScoreByComputerScience = calculateAverageScoreBySubject(students, COMPUTER_SCIENCE),
        .averageScoreByPassing = calculateAverageScoreByPassing(students),
        .minSumScores = calculateMinSumScores(students),
        .maxSumScores = calculateMaxSumScores(students),
        .averageScoreWithBenefits=calculateAverageScoreWithBenefits(students),
        .numberOfSpecial = countStudentsByBenefit(students, SPECIAL_QUOTA),
        .numberOfSeparate = countStudentsByBenefit(students, SEPARATE_QUOTA),
        .numberOfTargeted = countStudentsByBenefit(students, TARGET_RECEPTION),
        .numberOfBviExams = countStudentsByBenefit(students, BVI)
    };
    return result;
}
 
studentList_t* generateStudents(char** courses, int courseCount) {
    char* name = "Name";
    char* surname = "Surname";
    char* middleName = "Middlename";
 
    int studentCount = 25 + rand() % 76;
    studentList_t* studentList = (studentList_t*)malloc(sizeof(studentList_t));
    if(studentList==NULL){
        printf("Ошибка выделения памяти");
    }
    studentList->count = studentCount;
    studentList->capacity = studentCount;
    studentList->students = (student_t*)malloc(studentCount * sizeof(student_t));
    if(studentList->students==NULL){
        printf("Ошибка выделения памяти");
    }
 
    for (int i = 0; i < studentCount; i++) {
        student_t* current = &studentList->students[i];
        const char* course = courses[rand() % courseCount];
        current->course = strdup(course);
        current->name = strdup(name);
        current->surname = strdup(surname);
        current->middleName = strdup(middleName);
        current->russian = rand() % 101;
        current->math = rand() % 101;
        current->physics = rand() % 101;
        current->computerScience = rand() % 101;
        current->benefit = rand() % 6;
    }
    return studentList;
}
 
studentsByCourses_t* groupStudentsByCourse(studentList_t* students, char** courses, int courseCount) {
    studentsByCourses_t* result = (studentsByCourses_t*)malloc(sizeof(studentsByCourses_t));
    result->count = courseCount;
    result->studentsByCourses = (studentList_t*)calloc(courseCount, sizeof(studentList_t));
    if(result->studentsByCourses==NULL){
        printf("Ошибка выделения памяти");
    }
 
    for (int i = 0; i < courseCount; i++) {
        char* course = courses[i];
        for (int j = 0; j < students->count; j++) {
            student_t current = students->students[j];
            if (strcmp(course, current.course) == 0) {
                if (result->studentsByCourses[i].capacity == 0) {
                    result->studentsByCourses[i].students = (student_t*)malloc(2 * sizeof(student_t));
                    if(result->studentsByCourses[i].students==NULL){
                        printf("Ошибка выделения памяти");
                    }
                    result->studentsByCourses[i].capacity = 2;
                    result->studentsByCourses[i].count = 0;
                }
                student_t copy = current;
                copy.course = strdup(current.course);
                copy.name = strdup(current.name);
                copy.surname = strdup(current.surname);
                copy.middleName = strdup(current.middleName);
                appendStudent(&result->studentsByCourses[i], copy);
            }
        }
    }
    return result;
}