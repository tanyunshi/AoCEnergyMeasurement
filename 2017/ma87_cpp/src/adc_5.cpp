#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

int adc_5_1(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  std::vector<int> jumps;
  int jump;
  while (f >> jump)
  {
      jumps.push_back(jump);
  }

  int current_jump = 0;
  int number_jumps = jumps.size();
  int step = 0;
  while (current_jump < number_jumps)
  {
    jumps[current_jump]++;
    current_jump += jumps[current_jump] - 1;
    step++;
  }

  return step;
}

int adc_5_2(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  std::vector<int> jumps;
  int jump;
  while (f >> jump)
  {
      jumps.push_back(jump);
  }

  int current_jump = 0;
  int number_jumps = jumps.size();
  int step = 0;
  int offset;
  while (current_jump < number_jumps)
  {
    if (jumps[current_jump] > 2)
    {
      offset = -1;
    }
    else
    {
      offset = 1;
    }
    jumps[current_jump] += offset;
    current_jump += jumps[current_jump] - offset;
    step++;
  }

  return step;
}

int main(int argc, char * argv[])
{
  adc_5_1(argv[1]);
  adc_5_2(argv[1]);
  return 0;
}
