#include <stdlib.h>
#include <string.h>
 
typedef enum benefit {
    NO_QUOTA,
    SPECIAL_QUOTA,
    SEPARATE_QUOTA,
    TARGET_RECEPTION,
    BVI,
    ANY_QUOTA
} benefit_t;
 
typedef struct student {
    char* course;
    char* surname;
    char* name;
    char* middleName;
    int russian;
    int math;
    int physics;
    int computerScience;
    benefit_t benefit;
} student_t;
 
typedef struct studentList {
    student_t* students;
    int count;
    int capacity;
} studentList_t;
 
void appendStudent(studentList_t* self, student_t student);
 
typedef struct studentsByCourses {
    studentList_t* studentsByCourses;
    int count;
} studentsByCourses_t;
 
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
);
 
void freeStudent(student_t* student);
 
typedef enum subject {
    RUSSIAN,
    MATH,
    PHYSICS,
    COMPUTER_SCIENCE,
} subject_t;
 
double calculateAverageScore(studentList_t students, benefit_t benefit);
double findMinScore(studentList_t students, benefit_t benefit);
double findMaxScore(studentList_t students, benefit_t benefit);
int countBenefitStudents(studentList_t students);
double calculateAverageScoreBySubject(studentList_t students, subject_t subject);
double calculateAverageScoreByPassing(studentList_t students);
double calculateAverageScoreWithBenefits(studentList_t students);
double calculateMinSumScores(studentList_t students);
double calculateMaxSumScores(studentList_t students);
int countStudentsByBenefit(studentList_t students, benefit_t benefit);
 
studentList_t* generateStudents( char** courses, int courseCount);
studentsByCourses_t* groupStudentsByCourse(studentList_t* students, char** courses, int courseCount);
 
void freeStudentList(studentList_t* list);
void freeStudentsByCourse(studentsByCourses_t* studentsByCourses);
 
typedef struct analyticsResult {
    double averageScore;
    double minScore;
    double maxScore;
    int benefitNumber;
    double averageScoreByRussian;
    double averageScoreByMath;
    double averageScoreByPhysics;
    double averageScoreByComputerScience;
    double averageScoreByPassing;
    double averageScoreWithBenefits;
    double minSumScores;
    double maxSumScores;
    int numberOfSpecial;
    int numberOfSeparate;
    int numberOfTargeted;
    int numberOfBviExams;
} analyticsResult_t;
 
analyticsResult_t calculateAnalytics(studentList_t students);