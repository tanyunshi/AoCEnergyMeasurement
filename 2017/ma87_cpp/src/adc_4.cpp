#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

int adc_4_1(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  int number_valid = 0;
  for (std::string line; std::getline(f, line); )
  {
      std::vector<std::string> words;
      std::istringstream iss(line);
      std::string word;
      int duplicated_words = 0;
      while(iss >> word)
      {
        for(int i = 0 ; i < words.size() ; i++)
        {
          if (!word.compare(words[i]))
          {
            duplicated_words = 1;
            break;
          }
        }

        if (duplicated_words > 0)
        {
          break;
        }
        else
        {
          words.push_back(word);
        }
      }

      if (duplicated_words == 0)
      {
        number_valid++;
      }

  }
  return number_valid;
}

bool are_words_anagram(std::string & word_a, std::string & word_b)
{
  int chars[26];
  for (int i = 0 ; i < 26 ; i++)
  {
    chars[i] = 0;
  }

  if (word_a.length() != word_b.length())
  {
    return false;
  }

  for (int i = 0 ; i < word_a.length() ; i++)
  {
    chars[word_a[i] - 'a']++;
    chars[word_b[i] - 'a']--;
  }

  for (int i = 0 ; i < 26 ; i++)
  {
    if (chars[i] != 0)
    {
      return false;
    }
  }

  return true;
}

bool is_word_anagram(std::string & word, std::vector<std::string> & words)
{
  for (int i = 0 ; i < words.size() ; i++)
  {
    if (are_words_anagram(word, words[i]))
    {
      return true;
    }
  }
  return false;
}

int adc_4_2(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  int number_valid = 0;
  for (std::string line; std::getline(f, line); )
  {
      std::vector<std::string> words;
      std::istringstream iss(line);
      std::string word;
      bool is_anagram = false;
      while(iss >> word)
      {
        if (is_word_anagram(word, words))
        {
          is_anagram = true;
          break;
        }
        else
        {
          words.push_back(word);
        }
      }

      if (!is_anagram)
      {
        number_valid++;
      }

  }
  return number_valid;
}

int main(int argc, char * argv[])
{
  adc_4_1(argv[1]);
  adc_4_2(argv[1]);
  return 0;
}
