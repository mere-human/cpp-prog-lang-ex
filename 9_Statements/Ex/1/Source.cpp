/*
[1] (∗1) Rewrite the following for-statement as an equivalent while-statement:
for (i=0; i!=max_length; i++)
if (input_line[i] == '?')
quest_count++;
Rewrite it to use a pointer as the controlled variable, that is, so that the test is of the form
∗p=='?'. Rewrite it to use a range-for.
*/

#include <iostream>
#include <string>

int main()
{
  std::cout << "Enter a line: ";
  std::string input_line;
  std::getline(std::cin, input_line);

  int quest_count = 0;
  int i;
  auto max_length = input_line.length();

  //for (i = 0; i != max_length; i++)
  //  if (input_line[i] == '?')
  //    quest_count++;

  //i = 0;
  //while (i != max_length)
  //  if (input_line[i++] == '?')
  //    quest_count++;

  //for (auto p = input_line.begin(); p != input_line.end(); ++p)
  //  if (*p == '?')
  //    quest_count++;

  for (const auto c : input_line)
    if (c == '?')
      quest_count++;

  std::cout << "Quest count: " << quest_count << "\n";
}