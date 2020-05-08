#include "processor.h"
#include "linux_parser.h"
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{
    vector<string> utilisation_vector;
    vector<long> utilisation_vector_calc;

    utilisation_vector = LinuxParser::CpuUtilization();
  
    for( int i = 0; i < (int)utilisation_vector.size(); i++)
    {
        utilisation_vector_calc.push_back(std::stol(utilisation_vector[i]));
    }

    Idle_ = utilisation_vector_calc[3] + utilisation_vector_calc[4];
    Nonidle_ = utilisation_vector_calc[0] + utilisation_vector_calc[1] + utilisation_vector_calc[2]
                + utilisation_vector_calc[5] +  utilisation_vector_calc[6] + utilisation_vector_calc[7];       
    
    Total_ = Idle_ + Nonidle_; 
    totaled_ = Total_ - PrevTotal_;
    idled_ = Idle_ - PrevIdle_;

    PrevTotal_ = Total_;
    PrevIdle_ = Idle_;

    return (totaled_ - idled_)/ totaled_; 
}