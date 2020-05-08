#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
using std::vector;

class Processor 
{
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:

long PrevIdle_{0};
long PrevNonIdle_{0};
long PrevTotal_{0};
long Idle_{0};
long Nonidle_{0};
long Total_{0};
float totaled_{0};
float idled_{0};

};

#endif