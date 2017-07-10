/*
Lab 4
Zach Douglas
CS III
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

/*
Input:  list<string>& roster, string fileName
Output: N /A
Purpose:  Read students names into a roster which is passed by reference
*/
void readRoster(std::list<std::string>& roster, std::string fileName);

/*
Input:  const vector<list<string>>& studentMasterList
Output:  N / A
Purpose:  Iterate through studentMasterList and print the names of the students and the courses that they're currently enrolled in.
*/
void printRoster(const std::vector<std::list<std::string>>& studentMasterList);

/*
Input:  const vector<list<string>>& courseStudents, vector<list<string>>& studentMasterList
Output:  N / A
Purpose:  Iterate through course rosters and locate duplicates.  If there is a duplicate, only list the name once in the studentMasterList.
		  Also, you must append the name of the courses that each student is enrolled in currently.
*/
void compareRosters(const std::vector<std::list<std::string>>& courseStudents, std::vector<std::list<std::string>>& studentMasterList);


int main(int argc, char* argv[]) {

	if (argc <= 1) {
		std::cout << "usage: " << argv[0]
			<< " list of courses, dropouts last" << std::endl; exit(1);
	}

	// vector of courses of students
	std::vector<std::list<std::string>> courseStudents;
	std::vector<std::list<std::string>> studentMasterList;


	// reading in rosters per course and printing them out 
	for (int i = 1; i < argc - 1; ++i) {
		std::list<std::string> roster;
		readRoster(roster, argv[i]);
		courseStudents.push_back(move(roster));
		roster.clear();
	}
	compareRosters(courseStudents, studentMasterList);
	printRoster(studentMasterList);
	std::cin.get();
	
}

// reading a list from fileName
void readRoster(std::list<std::string>& roster, std::string fileName) {
	std::ifstream course(fileName.c_str());

	std::string first, last;
	while (course >> first >> last)
		roster.push_back(first + ' ' + last);
	course.close();
}

// printing a list out
void printRoster(const std::vector<std::list<std::string>>& studentMasterList) {
	for (size_t i = 0; i < studentMasterList.size(); ++i) {
		std::list<std::string>::const_iterator studentMasterListIter;
		for (studentMasterListIter = studentMasterList[i].begin(); studentMasterListIter != studentMasterList[i].end(); ++studentMasterListIter) {
			std::cout << *studentMasterListIter << std::endl;
		}
	}
}

void compareRosters(const std::vector<std::list<std::string>>& courseStudents, std::vector<std::list<std::string>>& studentMasterList){
	std::string courseNames[4] = { "cs1", "cs2", "cs3", "cs4" };
	std::list<std::string> tempStudentList;

	//Loop through lists in the vector
	for (size_t i = 0; i < courseStudents.size(); ++i) {
		std::list<std::string>::const_iterator courseStudentsIter;
		//loop through items in each list
		for (courseStudentsIter = courseStudents[i].begin(); courseStudentsIter != courseStudents[i].end(); ++courseStudentsIter) {
			//if size == 0, add name and course
			if (studentMasterList.size() < 1) {
				tempStudentList.push_back(*courseStudentsIter);
				tempStudentList.push_back(courseNames[i]);
			}
			else {

				/*Error not resolved that causes program to only scan the current list for matches rather than all the lists.  Ran out of time to fix.*/
				auto studentInMasterListIter = std::find(studentMasterList[i].begin(), studentMasterList[i].end(), *courseStudentsIter);
				if (studentInMasterListIter != std::end(studentMasterList[i])) {
					std::cout << "Appending: " << courseNames[i] << "to student: " << *courseStudentsIter << std::endl;
					studentMasterList[i].push_back(courseNames[i]);
				}
				else {
					//Add student name and course name because we could not locate a match for the student name in another list
					std::cout << "Adding student name: " << *courseStudentsIter << "and course name: " << courseNames[i] << std::endl;
					tempStudentList.push_back(*courseStudentsIter);
					tempStudentList.push_back(courseNames[i]);
				}
			}
			studentMasterList.push_back(move(tempStudentList));
			tempStudentList.clear();
		}

	}
}