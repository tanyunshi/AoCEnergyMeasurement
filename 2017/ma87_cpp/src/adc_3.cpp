#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>


typedef enum
{
  UP = 0,
  DOWN,
  LEFT,
  RIGHT
} DIRECTION;

int get_shift(DIRECTION dir, int size_square)
{
  switch (dir)
  {
    case LEFT:
      return -size_square;
    case RIGHT:
      return size_square;
    case UP:
      return -1;
    case DOWN:
      return 1;
  }
}

void fill_mem_array(int * mem_array, int size_square, int data, int & pos_i, int & pos_j)
{
  int pos = size_square / 2;
  //std::cout << "int pos : " << pos << std::endl;

  for (int i = 0 ; i < size_square ; i++)
  {
    for (int j = 0 ; j < size_square ; j++)
    {
      mem_array[i + size_square * j] = 0;
    }
  }

  int * p_mem = &mem_array[pos + size_square * pos];
  pos_i = pos;
  pos_j = pos;
  int counter = 1;
  *p_mem = counter++;

  DIRECTION dir = RIGHT;

  while ((counter - 1) != data)
  {
    switch (dir)
    {
      case LEFT:
        pos_j--;
        break;
      case RIGHT:
        pos_j++;
        break;
      case UP:
        pos_i--;
        break;
      case DOWN:
        pos_i++;
        break;
    }
    int shift = get_shift(dir, size_square);
    //std::cout << "counter: " << counter << " goes dir " << dir << " and shift " << shift << std::endl;
    //std::cout << "current pos = " << pos_i << " , " << pos_j << std::endl;
    p_mem += shift;
    *p_mem = counter++;
    switch(dir)
    {
      case LEFT:
        if (mem_array[pos_i + 1 + pos_j * size_square] == 0)
        {
          dir = DOWN;
        }
        break;
      case RIGHT:
        if (mem_array[pos_i - 1 + pos_j * size_square] == 0)
        {
          dir = UP;
        }
        break;
      case UP:
        //std::cout << "nen_array[ " << (pos_i + (pos_j - 1) * size_square) << "] = " << mem_array[pos_i + (pos_j - 1) * size_square] << std::endl;
        if (mem_array[pos_i + (pos_j - 1) * size_square] == 0)
        {
          dir = LEFT;
        }
        break;
      case DOWN:
        if (mem_array[pos_i + (pos_j + 1) * size_square] == 0)
        {
          dir = RIGHT;
        }
        break;
    }
  }
}

void print_mem_array(int * mem_array, int size_square)
{
  for (int i = 0 ; i < size_square ; i++)
  {
    for (int j = 0 ; j < size_square ; j++)
    {
      //std::cout << mem_array[i + size_square * j] << " ";
    }
    //std::cout << std::endl;
  }
}

int get_number_steps(int * mem_array, int size_square, int pos_i, int pos_j)
{
  int counter = 0;

  while (mem_array[pos_i + size_square * pos_j] != 1)
  {
    int min = 999999;
    int shift_min_i = 0;
    int shift_min_j = 0;

    //LEFT
    int left = mem_array[pos_i + (pos_j - 1) * size_square];
    if ((left > 0) && (left < min))
    {
      min = left;
      shift_min_i = 0;
      shift_min_j = -1;
    }

    //RIGHT
    int right = mem_array[pos_i + (pos_j + 1) * size_square];
    if ((right > 0) && (right < min))
    {
      min = right;
      shift_min_i = 0;
      shift_min_j = 1;
    }

    //UP
    int up = mem_array[pos_i - 1 + pos_j * size_square];
    if ((up > 0) && (up < min))
    {
      min = up;
      shift_min_i = -1;
      shift_min_j = 0;
    }


    //DOWN
    int down = mem_array[pos_i + 1 + pos_j * size_square];
    if ((down > 0) && (down < min))
    {
      min = down;
      shift_min_i = 1;
      shift_min_j = 0;
    }

    counter ++;
    pos_i += shift_min_i;
    pos_j += shift_min_j;
  }

  return counter;
}

int adc_3_1(int data)
{
  // Generate square
  int size_square = (int)floor(sqrt((float)data));
  //std::cout << "size_square 1: " << size_square << std::endl;

  if (size_square % 2 == 0)
  {
    //std::cout << "size even" << std::endl;
    size_square += 3;
  }
  else
  {
    size_square += 2;
  }
  //std::cout << "size_square 2: " << size_square << std::endl;

  int * mem_array = (int *)malloc(size_square * size_square * sizeof(int));
  int pos_i;
  int pos_j;

  fill_mem_array(mem_array, size_square, data, pos_i, pos_j);

  print_mem_array(mem_array, size_square);

  return get_number_steps(mem_array, size_square, pos_i, pos_j);
}

int get_sum_near(int * mem_array, int size_square, int pos_i, int pos_j)
{
  int sum = 0;
  //std::cout << "get sum near" << std::endl;
  for (int i = -1 ; i < 2 ; i++)
  {
    for (int j = -1 ; j < 2 ; j++)
    {
      //std::cout << " i, j = " << i << " , " << j << std::endl;
      int value = mem_array[pos_i + i + (pos_j + j) * size_square];
      sum += value;
    }
  }
  return sum;
}

int fill_mem_array_2(int * mem_array, int size_square, int data, int & pos_i, int & pos_j)
{
  int value = 0;
  int pos = size_square / 2;
  //std::cout << "int pos : " << pos << std::endl;

  for (int i = 0 ; i < size_square ; i++)
  {
    for (int j = 0 ; j < size_square ; j++)
    {
      mem_array[i + size_square * j] = 0;
    }
  }

  int * p_mem = &mem_array[pos + size_square * pos];
  pos_i = pos;
  pos_j = pos;
  int counter = 1;
  *p_mem = 1;

  DIRECTION dir = RIGHT;

  while ((counter - 1) != data)
  {
    switch (dir)
    {
      case LEFT:
        pos_j--;
        break;
      case RIGHT:
        pos_j++;
        break;
      case UP:
        pos_i--;
        break;
      case DOWN:
        pos_i++;
        break;
    }
    int shift = get_shift(dir, size_square);
    p_mem += shift;

    *p_mem = get_sum_near(mem_array, size_square, pos_i, pos_j);

    value = *p_mem;
    if (value > data)
    {
      return value;
    }
    counter++;
    switch(dir)
    {
      case LEFT:
        if (mem_array[pos_i + 1 + pos_j * size_square] == 0)
        {
          dir = DOWN;
        }
        break;
      case RIGHT:
        if (mem_array[pos_i - 1 + pos_j * size_square] == 0)
        {
          dir = UP;
        }
        break;
      case UP:
        if (mem_array[pos_i + (pos_j - 1) * size_square] == 0)
        {
          dir = LEFT;
        }
        break;
      case DOWN:
        if (mem_array[pos_i + (pos_j + 1) * size_square] == 0)
        {
          dir = RIGHT;
        }
        break;
    }
  }

  return value;
}

int adc_3_2(int data)
{
  // Generate square
  int size_square = (int)floor(sqrt((float)data));
  //std::cout << "size_square 1: " << size_square << std::endl;

  if (size_square % 2 == 0)
  {
    //std::cout << "size even" << std::endl;
    size_square += 3;
  }
  else
  {
    size_square += 2;
  }
  //std::cout << "size_square 2: " << size_square << std::endl;

  int * mem_array = (int *)malloc(size_square * size_square * sizeof(int));
  int pos_i;
  int pos_j;

  int value = fill_mem_array_2(mem_array, size_square, data, pos_i, pos_j);

  //print_mem_array(mem_array, size_square);

  return value;
}


int main(int argc, char * argv[])
{
  adc_3_1(289326);
  adc_3_2(289326);
  return 0;
}
