#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

int get_next_block(int idx, int size)
{
    if (idx < (size - 1))
    {
      return idx + 1;
    }
    else
    {
      return 0;
    }
}

int adc_6_1(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  std::vector<int> mem_banks;
  int count;
  while (f >> count)
  {
      mem_banks.push_back(count);
  }
  int mem_banks_size = mem_banks.size();
  std::cout << "size of mem_banks " << mem_banks_size << std::endl;
  for(int i = 0 ; i < mem_banks_size ; i++)
  {
    std::cout << mem_banks[i] << " ";
  }
  std::cout << std::endl;

  int step = 0;
  bool infinite_loop_detected = false;
  std::vector<std::vector<int>> recorded_mem_banks;
  recorded_mem_banks.push_back(std::vector<int>(mem_banks));

  do
  {
    step++;
    int max_index = -1;
    int max_blocks = -1;

    for(int i = 0 ; i < mem_banks_size ; i++)
    {
      if (mem_banks[i] > max_blocks)
      {
        max_index = i;
        max_blocks = mem_banks[i];
      }
    }

    int redistribute_blocks = max_blocks;
    mem_banks[max_index] = 0;
    int current_block = get_next_block(max_index, mem_banks_size);
    while(redistribute_blocks > 0)
    {
        mem_banks[current_block]++;
        redistribute_blocks--;
        current_block = get_next_block(current_block, mem_banks_size);
    }

    for (int i = 0 ; i < recorded_mem_banks.size() ; i++)
    {
      if (std::equal(mem_banks.begin(), mem_banks.begin() + mem_banks_size, recorded_mem_banks[i].begin()))
      {
          infinite_loop_detected = true;
      }
    }

    recorded_mem_banks.push_back(std::vector<int>(mem_banks));

  } while (!infinite_loop_detected);

  return step;
}

int adc_6_2(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  std::vector<int> mem_banks;
  int count;
  while (f >> count)
  {
      mem_banks.push_back(count);
  }
  int mem_banks_size = mem_banks.size();
  //std::cout << "size of mem_banks " << mem_banks_size << std::endl;
  for(int i = 0 ; i < mem_banks_size ; i++)
  {
    //std::cout << mem_banks[i] << " ";
  }
  //std::cout << std::endl;

  int step = 0;
  bool first_infinite_loop_detected = false;
  bool second_infinite_loop_detected = false;
  std::vector<std::vector<int>> recorded_mem_banks;
  recorded_mem_banks.push_back(std::vector<int>(mem_banks));

  do
  {
    if (first_infinite_loop_detected)
    {
      step++;
    }
    int max_index = -1;
    int max_blocks = -1;

    for(int i = 0 ; i < mem_banks_size ; i++)
    {
      if (mem_banks[i] > max_blocks)
      {
        max_index = i;
        max_blocks = mem_banks[i];
      }
    }

    int redistribute_blocks = max_blocks;
    mem_banks[max_index] = 0;
    int current_block = get_next_block(max_index, mem_banks_size);
    while(redistribute_blocks > 0)
    {
        mem_banks[current_block]++;
        redistribute_blocks--;
        current_block = get_next_block(current_block, mem_banks_size);
    }

    for (int i = 0 ; i < recorded_mem_banks.size() ; i++)
    {
      if (std::equal(mem_banks.begin(), mem_banks.begin() + mem_banks_size, recorded_mem_banks[i].begin()))
      {
          if (!first_infinite_loop_detected)
          {
            first_infinite_loop_detected = true;
            recorded_mem_banks.clear();
          }
          else
          {
            second_infinite_loop_detected = true;
          }
      }
    }

    recorded_mem_banks.push_back(std::vector<int>(mem_banks));

  } while (!second_infinite_loop_detected);

  return step;
}

int main(int argc, char * argv[])
{
  adc_6_1(argv[1]);
  adc_6_2(argv[1]);
  return 0;
}
