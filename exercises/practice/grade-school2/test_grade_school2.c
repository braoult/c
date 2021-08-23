#include "test-framework/unity.h"
#include "grade_school2.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
   clear_roster();
}

static void check_roster_names(roster_t expected, roster_t actual)
{
   for (size_t i = 0; i < expected.count; ++i)
      TEST_ASSERT_EQUAL_STRING(expected.students[i].name,
                               actual.students[i].name);
}

static void check_rosters(roster_t expected, roster_t actual)
{
   TEST_ASSERT_EQUAL_size_t_MESSAGE(expected.count, actual.count,
                                    "Incorrect number of students");
   check_roster_names(expected, actual);
}

static void test_roster_is_empty_when_no_students_added(void)
{
   roster_t actual = get_roster();

   TEST_ASSERT_EQUAL(0, actual.count);
}

static void test_adding_student(void)
{
   TEST_IGNORE();               // delete this line to run test
   TEST_ASSERT_TRUE(add_student("Aimee", 2));
}

static void test_student_is_added_to_roster(void)
{
   TEST_IGNORE();
   roster_t expected = { 1, {(student_t) {2, "Aimee"}} };

   add_student("Aimee", 2);

   roster_t actual = get_roster();

   check_rosters(expected, actual);
}

static void test_adding_multiple_students_in_same_grade(void)
{
   TEST_IGNORE();
   TEST_ASSERT_TRUE(add_student("Blair", 2));
   TEST_ASSERT_TRUE(add_student("James", 2));
   TEST_ASSERT_TRUE(add_student("Paul", 2));
}

static void test_multiple_students_in_same_grade_are_added_roster(void)
{
   TEST_IGNORE();
   roster_t expected = {
      3, {
          (student_t) {2, "Blair"},
          (student_t) {2, "James"},
          (student_t) {2, "Paul"}}
   };

   add_student("Blair", 2);
   add_student("James", 2);
   add_student("Paul", 2);;

   roster_t actual = get_roster();

   check_rosters(expected, actual);
}

static void test_cannot_add_student_to_same_grade_more_than_once(void)
{
   TEST_IGNORE();
   roster_t expected = { 1, {(student_t) {2, "Aimee"}} };

   TEST_ASSERT_TRUE(add_student("Aimee", 2));
   TEST_ASSERT_FALSE(add_student("Aimee", 2));

   roster_t actual = get_roster();

   check_rosters(expected, actual);
}

static void test_adding_students_in_multiple_grades(void)
{
   TEST_IGNORE();
   TEST_ASSERT_TRUE(add_student("Chelsea", 3));
   TEST_ASSERT_TRUE(add_student("Logan", 7));
}

static void test_students_in_multiple_grades_are_added_to_roster(void)
{
   TEST_IGNORE();
   roster_t expected = {
      2, {
          (student_t) {3, "Chelsea"},
          (student_t) {7, "Logan"}},
   };

   add_student("Chelsea", 3);
   add_student("Logan", 7);

   roster_t actual = get_roster();

   check_rosters(expected, actual);
}

static void test_cannot_add_same_student_to_multiple_grades(void)
{
   TEST_IGNORE();
   roster_t expected = { 1, {(student_t) {2, "Aimee"}} };

   TEST_ASSERT_TRUE(add_student("Aimee", 2));
   TEST_ASSERT_FALSE(add_student("Aimee", 1));

   roster_t actual = get_roster();

   check_rosters(expected, actual);
}

static void test_students_are_sorted_by_grades_and_names_in_roster(void)
{
   // TODO: Ideally this should be split to 2 tests (perhaps more):
   // TODO:  - test_students_are_sroted_by_grades
   // TODO:  - test_students_are_sroted_by_name_in_grades

   TEST_IGNORE();
   roster_t expected = {
      7, {
          (student_t) {1, "Anna"},
          (student_t) {1, "Barb"},
          (student_t) {1, "Charlie"},
          (student_t) {2, "Alex"},
          (student_t) {2, "Peter"},
          (student_t) {2, "Zoe"},
          (student_t) {3, "Jim"}}
   };

   add_student("Peter", 2);
   add_student("Anna", 1);
   add_student("Barb", 1);
   add_student("Zoe", 2);
   add_student("Alex", 2);
   add_student("Jim", 3);
   add_student("Charlie", 1);

   roster_t actual = get_roster();

   check_rosters(expected, actual);
}

static void test_grade_is_empty_if_no_students_in_grade(void)
{
   // TODO: To properly test this, there should be students present in other grades
   TEST_IGNORE();
   uint8_t desired_grade = 1;

   roster_t actual = get_grade(desired_grade);

   TEST_ASSERT_EQUAL(0, actual.count);
}

static void test_students_are_sorted_by_names_in_grade(void)
{
   TEST_IGNORE();
   uint8_t desired_grade = 5;
   roster_t expected = {
      2, {
          (student_t) {5, "Bradley"},
          (student_t) {5, "Franklin"}}
   };

   add_student("Franklin", 5);
   add_student("Bradley", 5);
   add_student("Jeff", 1);

   roster_t actual = get_grade(desired_grade);

   check_rosters(expected, actual);
}

int main(void)
{
   UnityBegin("test_grade_school2.c");

   RUN_TEST(test_roster_is_empty_when_no_students_added);
   RUN_TEST(test_adding_student);
   RUN_TEST(test_student_is_added_to_roster);
   RUN_TEST(test_adding_multiple_students_in_same_grade);
   RUN_TEST(test_multiple_students_in_same_grade_are_added_roster);
   RUN_TEST(test_cannot_add_student_to_same_grade_more_than_once);
   RUN_TEST(test_adding_students_in_multiple_grades);
   RUN_TEST(test_students_in_multiple_grades_are_added_to_roster);
   RUN_TEST(test_cannot_add_same_student_to_multiple_grades);
   RUN_TEST(test_students_are_sorted_by_grades_and_names_in_roster);
   RUN_TEST(test_grade_is_empty_if_no_students_in_grade);
   RUN_TEST(test_students_are_sorted_by_names_in_grade);

   return UnityEnd();
}
