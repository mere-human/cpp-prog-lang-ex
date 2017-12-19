/*
[3] (*2.5) Write a program that reads a source file and writes out the names of files #included.
Indent file names to show files #included by included files. Try this program on some real
source files (to get an idea of the amount of information included).
*/

#include <iostream>
# include <fstream>
#include <string>
#include <unordered_set>

// Note that #include in comments should not be analyzed

enum class Token
{
  end,
  word,
  newline,
  comment_begin,
  multicomment_begin,
  multicomment_end,
  hash
};

Token read_token(std::istream& is, std::string& str)
{
  // skip whitespaces except '\n'
  char ch;
  do
  {
    if (!is.get(ch))
      return Token::end;
  }
  while (ch != '\n' && isspace(ch));

  switch (ch)
  {
  case '\n':
    return Token::newline;
  case '/':
    if (is.get(ch))
    {
      if (ch == '*')
        return Token::multicomment_begin;
      else if (ch == '/')
        return Token::comment_begin;
      str += '/';
      is.putback(ch);
    }
    break;
  case '*':
    if (is.get(ch))
    {
      if (ch == '/')
        return Token::multicomment_end;
      str += '*';
      is.putback(ch);
    }
  case '#':
    return Token::hash;
  default:
    is.putback(ch);
    break;
  }
  is >> str;
  return Token::word;
}

const char* to_string(Token t)
{
  switch (t)
  {
  case Token::word:
    return "<W>";
  case Token::newline:
    return "<NL>";
  case Token::comment_begin:
    return "//";
  case Token::multicomment_begin:
    return "/*";
  case Token::multicomment_end:
    return "*/";
  case Token::hash:
    return "#";
  default:
    return "<unknown>";
  }
}

std::vector<std::string> collect_includes(const std::string& file_name)
{
  std::ifstream is(file_name);
  if (!is)
    return{};

  std::vector<std::string> files;
  bool include = false;
  Token state = Token::end;
  while (true)
  {
    std::string str;
    auto t = read_token(is, str);

    //std::cout << to_string(t) << ":" << str;
    //if (t == Token::newline)
    //  std::cout << "\n";

    if (t == Token::end)
    {
      break;
    }
    else if (t == Token::comment_begin)
    {
      if (state != Token::multicomment_begin)
        state = Token::comment_begin;
    }
    else if (t == Token::multicomment_begin)
    {
      if (state != Token::comment_begin)
        state = Token::multicomment_begin;
    }
    else if (t == Token::newline)
    {
      if (state == Token::comment_begin)
        state = Token::end;
    }
    else if (t == Token::hash)
    {
      if ((state != Token::comment_begin) && (state != Token::multicomment_begin))
        state = Token::hash;
    }
    else if (t == Token::multicomment_end)
    {
      if (state == Token::multicomment_begin)
        state = Token::end;
    }
    else if (t == Token::word)
    {
      if (include)
      {
        files.push_back(str);
        include = false;
      }
      else
      {
        if ((state == Token::hash) && (str == "include"))
          include = true;
      }
    }
  }
  return files;
}

using string_set = std::unordered_set<std::string>;

void process_file(const std::string& file_name, string_set& visited_files,
                  const std::string& indent = {})
{
  const char std_include_path[] = "e:\\Software\\Microsoft Visual Studio 14.0\\VC\\include\\";

  auto includes = collect_includes(file_name);
  for (const auto& include : includes)
  {
    std::cout << indent << include << "\n";
    if (visited_files.insert(include).second)
    {
      auto file = include.substr(1, include.length() - 2); // strip <...> or "..."
      process_file((include[0] == '<') ? (std_include_path + file) : file,
                   visited_files, indent + "  ");
    }
  }
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error: expected file name\n";
    return 1;
  }

  string_set visited_files;
  process_file(argv[1], visited_files);

  return 0;
}
