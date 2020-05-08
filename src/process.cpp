#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include<iostream>
#include<fstream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::stof;

Process::Process(int pid):pid_(pid) 
{
  cpu_utilization_ = Process::CpuUtilization();
}

// Returns this process's ID
int Process::Pid() 
{ 
  return pid_; 
}

// Returns this process's CPU utilization

 float Process::CpuUtilization()
{
  float total_time = LinuxParser::ActiveJiffies(pid_);   
  float uptime = LinuxParser::UpTime(pid_);

  float total_elapsed_time = total_time /sysconf(_SC_CLK_TCK);

  return total_elapsed_time/ uptime;
}
//Return the command that generated this process
string Process::Command() 
{
   return LinuxParser::Command(pid_); 
}

// Returns this process's memory utilization
string Process::Ram() 
{
  long mem_MB;
  mem_MB = std::stol(LinuxParser::Ram(pid_)) / 1000;

  return to_string(mem_MB); 
}

//Return the user (name) that generated this process
string Process::User() 
{
  return LinuxParser::User(pid_); 
}

// Returns the age of this process (in seconds)
long int Process::UpTime() 
{ 
  return LinuxParser::UpTime(pid_); 

}

// overloading the "<" operator
bool Process::operator < (Process const& a) const 
{ 
  return cpu_utilization_ > a.cpu_utilization_;
}