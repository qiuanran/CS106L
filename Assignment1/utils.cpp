/*
 * CS106L SimpleEnroll Assignment Part 1
 * Created by Fabio Ibanez
 * Please complete each STUDENT TODO in this file.
 *
 * Students must implement: parse_csv, write_courses_offered,
 * write_courses_not_offered
 */

// (FIRST) STUDENT TODO: change how variables are passed into the functions you
// must complete

#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
#include <algorithm>

// STUDENT TODO: add paths
std::string COURSES_OFFERED_CSV_PATH = "/home/lx/Downloads/CS106L/Assignment1/student_output/courses_offered.csv";

std::string COURSES_NOT_OFFERED_CSV_PATH = "/home/lx/Downloads/CS106L/Assignment1/student_output/courses_not_offered.csv";

struct Course {
  std::string title;
  std::string number_of_units;
  std::string quarter;

  // ignore this!
  bool operator==(const Course &other) const {
    return title == other.title && number_of_units == other.number_of_units &&
           quarter == other.quarter;
  }
};

// forward declarations
void delete_elem_from_vector(std::vector<Course> &v, Course &elem);
std::vector<std::string> split(std::string s, char delim);

/*
 * This function should populate the vector_of_courses with structs of type
 * Class We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * Hints:
 * 1) Take a look at the split function we provide
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 */
void parse_csv(std::string filename, std::vector<Course> &vector_of_courses) {
  // STUDENT TODO: Implement this function
  std::ifstream file(filename);
  std::string line;
  if (!file.is_open()) {
    std::cerr << "File not found" << std::endl;
    return;
  }
  for (int i = 0; std::getline(file, line); ++i) {
    if (i == 0) {
      continue;
    }
    std::vector<std::string> tokens = split(line, ',');
    Course course;
    course.title = tokens[0];
    course.number_of_units = tokens[1]; 
    course.quarter = tokens[2];
    vector_of_courses.push_back(course);
  }
  file.close();
}

/*
 * This function has TWO requirements.
 * 1) Write the courses that are offered to the file courses_offered.csv inside
 * the student_output folder
 *
 * 2) Delete classes that are offered from vector_of_courses.
 * IMPORTANT: do this after you write out to the file!
 *
 * HINTS:
 * 1) Keep track of the classes that you need to delete!
 * 2) Use the delete_elem_from_vector function we give you!
 */
void write_courses_offered(std::vector<Course> &vector_of_courses) {
  // STUDENT TODO: implement this function
  std::ofstream file(COURSES_OFFERED_CSV_PATH);
  if (!file.is_open()) {
    std::cerr << "File not found" << std::endl;
    return;
  }
  for (int i = 0; i < vector_of_courses.size(); ++i) {
    if (vector_of_courses[i].quarter != "null") {
      file << vector_of_courses[i].title << ","
           << vector_of_courses[i].number_of_units << ","
           << vector_of_courses[i].quarter << std::endl;
    }
  }
  // Delete classes that are offered from vector_of_courses
  for (int i = 0; i < vector_of_courses.size(); ++i) {
    if (vector_of_courses[i].quarter != "null") {
      delete_elem_from_vector(vector_of_courses, vector_of_courses[i]);
      i--;
    }
  }
 
  file.close();
}

/*
 * This function writes the courses NOT offered to the file
 * courses_not_offered.csv inside of the student_output folder
 *
 * This function is ALWAYS called after the write_courses_offered function.
 * vector_of_courses will trivially contain classes that are not offered
 * since you delete offered classes from vector_of_courses in the
 * 'write_courses_offered' function.
 *
 * HINT: This should be VERY similar to write_courses_offered
 */
void write_courses_not_offered(std::vector<Course> &vector_of_courses) {
  // STUDENT TODO: implement this function
  std::ofstream file(COURSES_NOT_OFFERED_CSV_PATH);
  if (!file.is_open()) {
    std::cerr << "File not found" << std::endl;
    return;
  }

  for (int i = 0; i < vector_of_courses.size(); ++i) {
    if (vector_of_courses[i].quarter == "null" && file.is_open()) {
      file << vector_of_courses[i].title << ","
           << vector_of_courses[i].number_of_units << ","
           << vector_of_courses[i].quarter << std::endl;
    }
  }

  file.close();
}

/* ######## HEYA! DON'T MODIFY ANYTHING BEYOND THIS POINT THX ######## */

// TODO: ADD DOCUMENTATION COMMENTS
void print_vector(std::vector<Course> vector_of_courses) {
  for (int i = 1; i < vector_of_courses.size(); ++i) {
    std::cout << vector_of_courses[i].title << ","
              << vector_of_courses[i].number_of_units << ","
              << vector_of_courses[i].quarter << std::endl;
  }
}

void delete_elem_from_vector(std::vector<Course> &v, Course &elem) {
  auto it = std::find(v.begin(), v.end(), elem);
  v.erase(it);
}

std::vector<std::string> split(std::string s, char delim) {
  std::vector<std::string> return_vec;
  std::stringstream ss(s);
  std::string token;
  while (getline(ss, token, ',')) {
    return_vec.push_back(token);
  }
  return return_vec;
}
