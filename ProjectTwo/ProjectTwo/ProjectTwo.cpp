// ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <fstream> //read file
#include <sstream> //for parsing


using namespace std;


const unsigned int DEFAULT_SIZE = 179;


struct Course
{
    string courseName;
    string title;
    string requirement;
    vector<string> requirements;
};

// last element is taken as pivot
int Partition(vector<Course>& v, int start, int end) {

    int pivot = end;
    int j = start;
    for (int i = start;i < end;++i) {
        if (v.at(i).courseName < v.at(pivot).courseName) {
            swap(v[i], v[j]);
            ++j;
        }
    }
    swap(v[j], v[pivot]);
    return j;

}

void quickSort(vector<Course>& v, int start, int end) {

    if (start < end) {
        int p = Partition(v, start, end);
        quickSort(v, start, p - 1);
        quickSort(v, p + 1, end);
    }

}

void printVector(vector<Course> v) {
    for (int i = 0;i < v.size();++i) {
        cout << i + 1 << ". " << v[i].courseName << " " << v[i].title << " ";
        for (int j = 0;j < v[i].requirements.size();++j) {
            cout << v[i].requirements[j] << " ";
        }

        cout << endl;
    }
}

void printCourse(vector<Course> v, int course) {
    cout << course - 1 << ". " << v[course - 1].courseName << " " << v[course - 1].title << " ";
        for (int i = 0;i < v[course - 1].requirements.size();++i) {
            cout << v[course - 1].requirements[i] << " ";
        }

    cout << endl;
}




vector<Course> loadCourse() 
{
    cout << "Loading CSV file " << endl;
    //opens stream for file reading
    ifstream inputFile;
    string csvFile;
    cout << "Input File Name: ";
    cin >> csvFile;
    cout << endl;
    //opens file
    inputFile.open(csvFile);

    //this will hold all courses
    vector<Course> courses;
    string line = "";

    while (getline(inputFile, line)) {
        string courseName;
        string title;
        string requirement;
        int commas;
        vector<string> requirements;

       stringstream inputString(line);

       commas = count(line.begin(), line.end(), ',');

        //gets course and title string and reads it towards Course object named course
        getline(inputString, courseName, ',');
        getline(inputString, title, ',');\
        //iterates until the input string turns bad
        if (commas >= 2) {
            for (int i = 0; i < commas - 1; i++) {
                //course.requirement is a temp string
                getline(inputString, requirement, ',');
                //pushes temp string course.requirement to course.requirements which is a vector to hold requirements
                requirements.push_back(requirement);
                requirement = "";
            }
        }
        //pushes course object into the courses vector
        Course course = {
            courseName,
            title,
            requirement,
            requirements
        };        
       
        courses.push_back(course);

    }
    return courses;
}

int main()
{
    int selection;
    string csvPath;
    //this vector holds the course
    vector<Course> courses;

    //for process timing
    clock_t ticks;

    int choice = 0;
    while (choice != 9)
    {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display Course List" << endl;
        cout << "  3. Display Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1:
            ticks = clock();

            // Complete the method call to load the bids
            courses = loadCourse();

            cout << courses.size() << " courses read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
        case 2:
            ticks = clock();
            quickSort(courses, 0, static_cast<int>(courses.size()) - 1);
            printVector(courses);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
        case 3:
            quickSort(courses, 0, static_cast<int>(courses.size()) - 1);
            cout << "Input Course Number" << endl;
            cin >> selection;
            ticks = clock();
            printCourse(courses, selection);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
        }

    }
}