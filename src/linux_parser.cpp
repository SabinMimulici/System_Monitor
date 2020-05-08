#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() 
{
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") 
        {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() 
{
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) 
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >>version >>kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() 
{
  vector<int> pids;

  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) 
  {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);

      if (std::all_of(filename.begin(), filename.end(), isdigit)) 
      {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{
  string line, key, value, unit;
  float mem_total, mem_free;
  float used_memory;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if(stream.is_open())
  {
    while(getline(stream, line))
    {
      std::istringstream linestream (line);
      while(linestream >> key >> value >> unit)
      {
        if(key == "MemTotal:")
        {
          mem_total = std::stol(value);
        }
        if(key == "MemFree:")
        {
          mem_free = std::stol(value);
        }
      }
    }
  }
  used_memory = (mem_total - mem_free)/ mem_total;
  return used_memory; 
}

// Read and return the system uptime
long LinuxParser::UpTime() 
{ 
  string line, uptime_s, iddle_uptime;
  long uptime;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime_s >> iddle_uptime;
    uptime = std::stol(uptime_s);
  }
    
    return uptime; 
}  


long LinuxParser::ActiveJiffies(int pid) 
{
  std::vector<string>jiffies_vector;
  string line, key, value;
  long jiffies_total_time;


  string pid_string = to_string(pid);
  std::ifstream stream (kProcDirectory + pid_string + kStatFilename);
  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream (line);
    while(linestream >> key)
    {
      if(key == pid_string)
      {
        while(linestream >> value)
        {
          jiffies_vector.push_back(value);
        }
      }
    }
  }
  jiffies_total_time = stol(jiffies_vector[12]) + stol(jiffies_vector[13]) + 
                          stol(jiffies_vector[14]) +stol(jiffies_vector[15]);
  return jiffies_total_time; 
}

// Reads and returns CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{
  vector<string>cpu_utilisation_print;
  string line;
  string key, value;

  std::ifstream stream (kProcDirectory + kStatFilename);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      while(linestream >> key)
      {
        if(key == "cpu")
        {
          while(linestream >> value)
          {
            cpu_utilisation_print.push_back(value);
          }
          
        }
      }
    }
  }
  return cpu_utilisation_print; 
}

// Reads and returnes the total number of processes
int LinuxParser::TotalProcesses() 
{
  string line, key, value;
  int val = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);

      while(linestream >> key >> value)
      {
        if(key == "processes")
        {
            val = std::stoi(value);
        }
      }
    } 
  }
  return val;
}

//Reads and returns the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  string line, key, value;
  int val = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);

      while(linestream >> key >> value)
      {
        if(key == "procs_running")
        {
            val = std::stoi(value);
        }
      }
    } 
  }
  return val;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) 
{
  string line, value, command;
  string pid_string = to_string(pid);

  std::ifstream stream (kProcDirectory + pid_string + kCmdlineFilename);
  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream (line);
    while(linestream >> value)
    {
      command = value;
    }

  } 
  return command; 
}

//Reads and returns the memory used by a process
string LinuxParser::Ram(int pid) 
{
  string line, key, value, mem_size;
  string pid_string = to_string(pid);

  std::ifstream stream (kProcDirectory + pid_string + kStatusFilename);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      while(linestream >> key >> value)
      {
        if(key == "VmSize:")
        {
          mem_size = value;
        }
      }
    }
  }
  return mem_size; 
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) 
{
  string line, key, value, uid;
  string pid_string = to_string(pid);

  std::ifstream stream (kProcDirectory + pid_string + kStatusFilename);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      while(linestream >> key >> value)
      {
        if(key == "Uid:")
        {
          uid = value;
        }
      }
    }
  }
  return uid; 
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) 
{
  string line, key, x,  value, user, uid;

  string pid_string = to_string(pid);
  uid = LinuxParser::Uid(pid);

  std::ifstream stream (kPasswordPath);
  if(stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
  
      while(linestream >> key >> x >> value)
      {
        if(value == uid)
        {
          user = key;
        }
      }
    }
  }
  return user;  
}

// Reads and returns the uptime of a process
long LinuxParser::UpTime(int pid) 
{ 
  std::vector<string>jiffies_vector;
  string line, value;

  string pid_string = to_string(pid);
  std::ifstream stream (kProcDirectory + pid_string + kStatFilename);

  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream (line);
    while(linestream >> value)
    {
      jiffies_vector.push_back(value);
    }
  }
  long starttime =  std::stol(jiffies_vector[21]) / sysconf(_SC_CLK_TCK);
  return LinuxParser::UpTime() - starttime;
}
