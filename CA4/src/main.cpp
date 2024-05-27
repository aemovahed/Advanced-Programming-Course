#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define CSV_FOLDER_NUM 1

const vector<string> list_of_files = {"../assets/employees.csv",
									  "../assets/working_hours.csv", 
									  "../assets/teams.csv", 
									  "../assets/salary_configs.csv"};

class SalaryConfigs {
public:
	SalaryConfigs(string lev, 
				   int base_sal, 
				   int sal_per_hour, 
				   int sal_ext, 
				   int official, 
				   int tax) 
	{
		level = lev;
		base_salary = base_sal;
		salary_per_hour = sal_per_hour;
		salary_per_extra_hour = sal_ext;
		official_working_hours = official;
		tax_percentage = tax;
	}





	void display() 
	{
		cout << level << 
			' ' << base_salary <<
			' ' << salary_per_hour <<
			' ' << salary_per_extra_hour <<
			' ' << official_working_hours <<
			' ' << tax_percentage << endl;
	}




private:
	string level;
	int base_salary;
	int salary_per_hour;
	int salary_per_extra_hour;
	int official_working_hours;
	int tax_percentage;
};

class Employee {
public:
	Employee(int emp_id, string emp_name, int emp_age, string emp_level) 
	{
		id = emp_id;
		name = emp_name;
		age =  emp_age;
		level = emp_level;
	}
	int get_id() { return id;}





	void display() 
	{
		cout<< id << ' '
			<< name << ' '
			<< age << ' '
			<< level << endl;
	}



private:
	int id;
	string name;
	int age;
	string level;
};

class Team {
public:
	Team(int team, 
		 Employee* head, 
		 vector<Employee*> mems, 
		 int bonus_min, 
		 double bonus_max) 
	{
		team_id = team;
		team_head = head;
		members = mems;
		bonus = 0;
		bonus_min_working_hours = bonus_min;
		bonus_working_hours_max_variance = bonus_max;
	}



	void display() 
	{
		cout << team_id << ' '
			<< team_head->get_id() << ' ';
		for (Employee* mem : members)
			cout << mem->get_id() << ' ';
		cout << bonus << ' '
			<< bonus_min_working_hours << ' '
			<< bonus_working_hours_max_variance << endl;
	}



private:
	int team_id;
	Employee* team_head;
	vector<Employee*> members;
	int bonus;
	int bonus_min_working_hours;
	double bonus_working_hours_max_variance;
};

class WorkingHour {
public:
	WorkingHour(Employee* emp, int emp_day, string emp_work_intv) 
	{
		employee = emp;
		day = emp_day;
		working_intervals.push_back(emp_work_intv);
	}

	void add_working_interval(string next_work_intv) 
	{
		working_intervals.push_back(next_work_intv);
	}
	
	Employee* get_emp() { return employee; }
	int get_day() { return day; }





	void display() 
	{
		cout << employee->get_id() << ' '
			<< day << ' ';
		for (string work : working_intervals)
			cout << work << ' ';
		cout << endl;
	}



private:
	Employee* employee;
	int day;
	vector<string> working_intervals;
};

class EmpsSalary {
public:
	void read_folder_info(string folder);
	string gen_file_path(string folder, string file);
	vector<string> split_by_commas(string line);
	vector<int> split_by_dollars(string line);
	void gen_employee(vector<string> fields);
	void gen_working_hour(vector<string> fields);
	void gen_team(vector<string> fields);
	void gen_salary_configs(vector<string> fields);
	void read_file_info(string file, string line);
	Employee* find_employee_by_id(int id);
	WorkingHour* find_working_hour(Employee* emp, int day);
private:

	vector<Employee*> employees;
	vector<WorkingHour*> working_hours;
	vector<Team*> teams;
	vector<SalaryConfigs*> vec_salary_configs;
};

void EmpsSalary::read_folder_info(string folder) 
{
	for (string file : list_of_files) 
	{
		ifstream input_csv(gen_file_path(folder, file));
		string line;
		getline(input_csv, line);
		while (getline(input_csv, line))
			read_file_info(file, line);
	}
}

string EmpsSalary::gen_file_path(string folder, string file) 
{
	ostringstream oss;
	oss << folder << '/' << file;
	return oss.str();
}

vector<string> EmpsSalary::split_by_commas(string line) 
{
	line.append(",");
	int start_pos = 0;
	vector<string> result;
	while (start_pos < line.length()) 
	{
		int comma_pos = line.find(',', start_pos);
		result.push_back(line.substr(start_pos, comma_pos - start_pos));
		start_pos = comma_pos + 1;
	}
	return result;
}

vector<int> EmpsSalary::split_by_dollars(string line) 
{
	line.append("$");
	int start_pos = 0;
	vector<int> result;
	while (start_pos < line.length()) 
	{
		int dollar_pos = line.find('$', start_pos);
		int number = stoi(line.substr(start_pos, dollar_pos - start_pos));
		result.push_back(number);
		start_pos = dollar_pos + 1;
	}
	return result;
}

void EmpsSalary::gen_employee(vector<string> fields) 
{
	auto emp = new Employee(stoi(fields[0]), fields[1], stoi(fields[2]), fields[3]);
	employees.push_back(emp);
	emp->display(); ///////////////////////////////////////////////////////
}

void EmpsSalary::gen_working_hour(vector<string> fields) 
{
	Employee* emp = find_employee_by_id(stoi(fields[0]));
	WorkingHour* temp = find_working_hour(emp, stoi(fields[1]));
	if (temp == NULL) 
	{
		auto working_hour = new WorkingHour(emp, stoi(fields[1]), fields[2]);
		working_hours.push_back(working_hour);
		working_hour->display();  ///////////////////////////////////////////////////////////////////
	}
	else 
	{
		temp->add_working_interval(fields[2]);
		temp->display(); //////////////////////////////////////////////////////////////////////////
	}
}

void EmpsSalary::gen_team(vector<string> fields) 
{
	Employee* head_emp = find_employee_by_id(stoi(fields[1]));
	vector<int> mem_ids;
	mem_ids = split_by_dollars(fields[2]);
	vector<Employee*> members;
	for (int mem_id : mem_ids) 
	{
		Employee* emp = find_employee_by_id(mem_id);
		members.push_back(emp);
	}
	auto team = new Team(stoi(fields[0]), head_emp, members, stoi(fields[3]), stod(fields[4]));
	teams.push_back(team);
	team->display(); ////////////////////////////////////////////////////////////////////////////
}

void EmpsSalary::gen_salary_configs(vector<string> fields) 
{
	auto salary_configs = new SalaryConfigs(fields[0], 
									 	   stoi(fields[1]), 
										   stoi(fields[2]), 
										   stoi(fields[3]), 
										   stoi(fields[4]), 
										   stoi(fields[5]));
	vec_salary_configs.push_back(salary_configs);
	salary_configs->display(); ////////////////////////////////////////////////////////////////////////
}

void EmpsSalary::read_file_info(string file, string line) 
{
	vector<string> fields = split_by_commas(line);
	if (file == list_of_files[0])
		gen_employee(fields);
	else if (file == list_of_files[1])
		gen_working_hour(fields);
	else if(file == list_of_files[2])
		gen_team(fields);
	else
		gen_salary_configs(fields);
}

Employee* EmpsSalary::find_employee_by_id(int id) 
{
	for (Employee* employee : employees)
		if (employee->get_id() == id)
			return employee;
	return NULL;
}

WorkingHour* EmpsSalary::find_working_hour(Employee* emp, int day) 
{
	for (WorkingHour* working_hour : working_hours)
		if (working_hour->get_emp() == emp && working_hour->get_day() == day)
			return working_hour;
	return NULL;
}

int main(int argc, const char *argv[]) {
	EmpsSalary emps_salary;
	emps_salary.read_folder_info(argv[CSV_FOLDER_NUM]);



	
}