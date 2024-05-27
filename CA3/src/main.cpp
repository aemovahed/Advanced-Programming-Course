#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define NUM_OF_PRESENTABLE_DAYS 2
#define LIMITATION_POINTS 2
#define NUM_OF_CLASSES 2
#define NUM_OF_CLASS_TIMES 3
#define NUM_OF_DAYS 5

struct FreeDay {
	string name;
	int class_times[NUM_OF_CLASS_TIMES] = {};
};
struct Teacher {
	string name;
	vector<FreeDay> free_days;
	vector<string> courses;
};
struct Course {
	string name;
	vector<string> presentable_days;
	vector<string> presentable_interval;
	int num_of_times_selection[NUM_OF_CLASSES] = {};
};
struct Schedule {
	string name_of_course;
	string name_of_teachers[NUM_OF_CLASSES];
	int holding_times[LIMITATION_POINTS];
};

string class_start_times[NUM_OF_CLASS_TIMES] = {"07:30", "09:30", "11:30"};
string class_end_times[NUM_OF_CLASS_TIMES] = {"09:00", "11:00", "13:00"};
string days_of_the_week[NUM_OF_DAYS] = {"Saturday", 
										"Sunday", 
										"Monday", 
										"Tuesday", 
										"Wednesday"};

int findTeacher(vector<Teacher>& list_of_teachers, string teacher)
{
	for (int i = 0; i < list_of_teachers.size(); i++)
		if (list_of_teachers[i].name == teacher)
			return i;
	return -1;
}

int findSecondFreeDay(Course course, string first_free_day, Teacher teacher)
{
	string result;
	for (int i = 0; i < NUM_OF_PRESENTABLE_DAYS; i++)
		if (first_free_day != course.presentable_days[i])
			result = course.presentable_days[i];
	for (int i = 0; i < teacher.free_days.size(); i++)
		if (result == teacher.free_days[i].name)
			return i;
	return -1;
}

void removeFromFreeDays(vector<Teacher>& list_of_teachers, 
						string teacher,
						Course course,  
						int day, 
						int time)
{
	int result;
	result = findTeacher(list_of_teachers, teacher);
	for (int i = 0; i < list_of_teachers[result].free_days.size(); i++)
		if (list_of_teachers[result].free_days[i].name == days_of_the_week[day]) 
		{
			list_of_teachers[result].free_days[i].class_times[time] = 1;
			int second_free_day;
			second_free_day = findSecondFreeDay(course, 
												list_of_teachers[result].free_days[i].name, 
												list_of_teachers[result]);
			list_of_teachers[result].free_days[second_free_day].class_times[time] = 1;
			return;
		}
}

string alphabetically_smaller(vector<string> presentable_courses)
{
	string temp = presentable_courses[0];
	for (int i = 1; i < presentable_courses.size(); i++) 
		if (temp > presentable_courses[i])
			temp = presentable_courses[i];
	return temp;
}

bool isAvailable(vector<string> presentable_days, int day)
{
	for (int i = 0; i < presentable_days.size(); i++)
		if (presentable_days[i] == days_of_the_week[day])
			return true;
	return false;
}

vector<string> findFewerDays(vector<Teacher> providers)
{
	vector<int> num_of_days_of_attendance;
	vector<string> final_providers;
	for (int i = 0; i < providers.size(); i++)
	{
		int result = providers[i].free_days.size();
		num_of_days_of_attendance.push_back(result);
	}
	int min = num_of_days_of_attendance[0];
	for (int i = 1; i < num_of_days_of_attendance.size(); i++)
		if (min > num_of_days_of_attendance[i])
			min = num_of_days_of_attendance[i];
	for (int i = 0; i < num_of_days_of_attendance.size(); i++)
		if (min == num_of_days_of_attendance[i]) 
			final_providers.push_back(providers[i].name);
	return final_providers;
}

bool checkPresentableDays(vector<FreeDay> free_days, 
								 Course course,
								 vector<int>& index_desired_days)
{
	// Checking whether the teacher has free time in all the times when the lesson should be presented
	for (int i = 0; i < course.presentable_days.size(); i++)
		for (int j = 0; j < free_days.size(); j++)
			if (course.presentable_days[i] == free_days[j].name)
				index_desired_days.push_back(j);
	if (index_desired_days.size() == NUM_OF_PRESENTABLE_DAYS)
		return true;
	return false;
}

bool isFreeDay(vector<FreeDay> free_days, Course course, int time)
{
	vector<int> index_desired_days;
	int result = 0;
	if (checkPresentableDays(free_days, course, index_desired_days))
		for (int i = 0; i < NUM_OF_PRESENTABLE_DAYS; i++)
		{
			int index = index_desired_days[i];
			if (free_days[index].class_times[time] == 0)
				++result;
		}
	if (result == NUM_OF_PRESENTABLE_DAYS)
		return true;
	else
		return false;
}

bool isProvider(Teacher teacher, Course course, int day, int time)
{
	for (int i = 0; i < teacher.courses.size(); i++)
		if (teacher.courses[i] == course.name)
			if (isFreeDay(teacher.free_days, course, time))
				return true;
	return false;
}

string findProviderTeacher(vector<Teacher>& list_of_teachers, 
						   Course course, 
						   int day, 
						   int time)
{
	bool result;
	vector<Teacher> providers;
	for (int i = 0; i < list_of_teachers.size(); i++)
	{
		result = isProvider(list_of_teachers[i], course, day, time);
		if (result)
			providers.push_back(list_of_teachers[i]);
	}
	if (providers.size() < 1)
		return "Not Found";
	else
	{
		vector<string> final_providers;
		string teacher;
		final_providers = findFewerDays(providers);
		if (final_providers.size() > 1)
			teacher = alphabetically_smaller(final_providers);
		else
			teacher = final_providers[0];
		removeFromFreeDays(list_of_teachers, teacher, course, day, time);
		return teacher;
	}
}

bool checkTime(vector<string> presentable_interval, int time)
{
	if (class_start_times[time] >= presentable_interval[0])
		if (class_end_times[time] <= presentable_interval[1])
			return true;
	return false;
}

bool isPresentable(Course course, int day, int time, int num_of_class)
{
	bool result;
	result = isAvailable(course.presentable_days, day);
	if (result)
		if (checkTime(course.presentable_interval, time))
			if (course.num_of_times_selection[num_of_class - 1] == 0)
				return true;
	return false;
}

void removeFromSelectedCourses(vector<Course>& list_of_courses, 
							   string course,
							   int num_of_class)
{
	for (int i = 0; i < list_of_courses.size(); i++)
		if (list_of_courses[i].name == course)
			list_of_courses[i].num_of_times_selection[num_of_class - 1] = 1;
}

string findPresentableCourse(vector<Course>& list_of_courses, 
							 int day, 
							 int time, 
							 int num_of_class)
{
	vector<string> presentable_courses;
	for (int i = 0; i < list_of_courses.size(); i++)
	{
		bool result;
		result = isPresentable(list_of_courses[i], day, time, num_of_class);
		if (result)
			presentable_courses.push_back(list_of_courses[i].name);
	}
	if (presentable_courses.size() < 1)
		return "Not Found";
	else
	{
		if (presentable_courses.size() > 1)
			return alphabetically_smaller(presentable_courses);
		else
			return presentable_courses[0];
	}
}

int searchInSchedules(vector<Schedule>& total_schedule, string course)
{
	for (int i = 0; i < total_schedule.size(); i++)
		if (total_schedule[i].name_of_course == course)
			return i;
	return -1;
}

void addToTotalSchedule(vector<Schedule>& total_schedule, 
						string course, 
						string teacher, 
						int time)
{
	int result;
	result = searchInSchedules(total_schedule, course);
	if (result > -1)
	{
		// Add the schedule of second class to the total schedule
		total_schedule[result].name_of_teachers[1] = teacher;
		total_schedule[result].holding_times[1] = time;
	}
	else
	{
		// Add the schedule of first class to the total schedule
		Schedule schedule;
		schedule.name_of_course = course;
		schedule.name_of_teachers[0] = teacher;
		schedule.holding_times[0] = time;
		total_schedule.push_back(schedule);
	}
}

Course findCourse(vector<Course>& list_of_courses, string course)
{
	Course temp;
	for (int i = 0; i < list_of_courses.size(); i++)
		if (list_of_courses[i].name == course)
			return list_of_courses[i];
	return temp; 
}

void emptySchedule(vector<FreeDay>& class_free_days)
{
	for (int i = 0; i < NUM_OF_DAYS; i++)
		class_free_days[i].name = days_of_the_week[i];
}

void removeFromClassFreeDays(vector<FreeDay>& class_free_days, 
							 vector<string> presentable_days, 
							 int time)
{
	for (int i = 0; i < NUM_OF_DAYS; i++)
		for (int j = 0; j < NUM_OF_PRESENTABLE_DAYS; j++)
			if (class_free_days[i].name == presentable_days[j])
				class_free_days[i].class_times[time] = 1;
}

void writeTheClassSchedule(vector<Schedule>& total_schedule,
						   vector<Teacher>& list_of_teachers,
				   		   vector<Course>& list_of_courses,
				   		   int num_of_class)
{
	vector<FreeDay> class_free_days(NUM_OF_DAYS);
	emptySchedule(class_free_days);
	for (int i = 0; i < NUM_OF_DAYS; i++) 
		for (int j = 0; j < NUM_OF_CLASS_TIMES; j++)
		{
			if (class_free_days[i].class_times[j] == 0)
			{
				string course, teacher;
				course = findPresentableCourse(list_of_courses, i, j, num_of_class);
				if (course != "Not Found")
				{
					Course desired_course;
					desired_course = findCourse(list_of_courses, course);
					teacher = findProviderTeacher(list_of_teachers, desired_course, i, j);
					if (teacher != "Not Found")
					{
						removeFromSelectedCourses(list_of_courses, course, num_of_class);
						removeFromClassFreeDays(class_free_days, desired_course.presentable_days, j);
						addToTotalSchedule(total_schedule, course, teacher, j);
					}
				}
			}
		}
}

void readCoursesInfo(vector<Course>& list_of_courses)
{
	int num_of_courses;
	cin >> num_of_courses;
	for (int i = 0; i < num_of_courses; i++)
	{
		Course course;
		cin >> course.name;
		for (int j = 0; j < NUM_OF_PRESENTABLE_DAYS; j++)
		{
			string day;
			cin >> day;
			course.presentable_days.push_back(day);
		}
		for (int j = 0; j < LIMITATION_POINTS; j++)
		{
			string time;
			cin >> time;
			course.presentable_interval.push_back(time);
		}
		list_of_courses.push_back(course);
	}
}

void readTeachersInfo(vector<Teacher>& list_of_teachers) 
{
	int num_of_teachers;
	cin >> num_of_teachers;
	for (int i = 0; i < num_of_teachers; i++)
	{
		Teacher teacher;
		cin >> teacher.name;
		int num_of_free_days;
		cin >> num_of_free_days;
		for (int j = 0; j < num_of_free_days; j++)
		{
			FreeDay free_day;
			cin >> free_day.name;
			teacher.free_days.push_back(free_day);
		}
		int num_of_courses;
		cin >> num_of_courses;
		for (int j = 0; j < num_of_courses; j++)
		{
			string course;
			cin >> course;
			teacher.courses.push_back(course);
		}
		list_of_teachers.push_back(teacher);
	}

}

void readInput(vector<Teacher>& list_of_teachers,
			   vector<Course>& list_of_courses)
{
	readTeachersInfo(list_of_teachers);
	readCoursesInfo(list_of_courses);
}

void alphabetically_sort(vector<Schedule>& total_schedule)
{
	Schedule temp;
	for (int i = 0; i < total_schedule.size() - 1; i++)
		for (int j = 0; j < total_schedule.size() - i - 1; j++)
			if (total_schedule[j].name_of_course > total_schedule[j + 1].name_of_course)
			{
				temp = total_schedule[j];
				total_schedule[j] = total_schedule[j + 1];
				total_schedule[j + 1] = temp;
			}
}

void printTotalSchedule(vector<Schedule>& total_schedule)
{
	alphabetically_sort(total_schedule);
	for (int i = 0; i < total_schedule.size(); i++)
	{
		cout << total_schedule[i].name_of_course << endl;
		for (int j = 0; j < NUM_OF_CLASSES; j++)
		{
			cout << total_schedule[i].name_of_teachers[j];
			if (total_schedule[i].name_of_teachers[j] != "Not Found")
			{
				int class_time = total_schedule[i].holding_times[j];
				cout << ": " << class_start_times[class_time] 
					 << ' ' << class_end_times[class_time];
			}
			cout << endl;
		}
	}	
}

bool checkCourse(vector<Schedule> total_schedule, string course)
{
	for (int i = 0; i < total_schedule.size(); i++)
		if (course == total_schedule[i].name_of_course)
			return true;
	return false;
}

void checkTeacher(vector<Schedule>& total_schedule)
{
	for (int i = 0; i < total_schedule.size(); i++)
		for (int j = 0; j < NUM_OF_CLASSES; j++)
			if (total_schedule[i].name_of_teachers[j] == "\0")
				total_schedule[i].name_of_teachers[j] = "Not Found";
}

void createNotFound(vector<Schedule>& total_schedule, vector<Course> list_of_courses)
{
	for (int i = 0; i < list_of_courses.size(); i++)
		if (!checkCourse(total_schedule, list_of_courses[i].name))
		{
			Schedule schedule;
			schedule.name_of_course = list_of_courses[i].name;
			for (int j = 0; j < NUM_OF_CLASSES; j++)
				schedule.name_of_teachers[j] = "Not Found"; 
			total_schedule.push_back(schedule);
		}		
}

int main()
{
	vector<Teacher> list_of_teachers;
	vector<Course> list_of_courses;
	vector<Schedule> total_schedule;
	// read input
	readInput(list_of_teachers, list_of_courses);
	// process
	writeTheClassSchedule(total_schedule, list_of_teachers, list_of_courses, 1);
	writeTheClassSchedule(total_schedule, list_of_teachers, list_of_courses, 2);
	createNotFound(total_schedule, list_of_courses);
	checkTeacher(total_schedule);
	// generate output
	printTotalSchedule(total_schedule);
}