/*
[4] (*3) Modify the program from the previous exercise to print the number of comment lines,
the number of non-comment lines, and the number of non-comment, whitespace-separated
words for each file #included.
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

bool is_comment(Token t)
{
  return (t == Token::comment_begin) || (t == Token::multicomment_begin);
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

struct FileStats
{
  std::vector<std::string> includes;
  int comm_lines = 0;
  int empty_lines = 0;
  int code_lines = 0;
  int code_words = 0;

  int total_lines() const
  {
    return comm_lines + empty_lines + code_lines;
  }

  void print(std::ostream& os, const std::string& indent, bool summary) const
  {
    if (!summary)
    {
      os << indent << "code lines: " << code_lines << "\n";
      os << indent << "comment lines : " << comm_lines << "\n";
      os << indent << "empty lines: " << empty_lines << "\n";
      os << indent << "total lines: " << total_lines() << "\n";
    }
    os << indent << "code words: " << code_words << "\n";
    os << indent << "includes: " << includes.size() << "\n";
  }
};

FileStats collect_stats(const std::string& file_name)
{
  std::ifstream is(file_name);
  if (!is)
    return{};

  FileStats stats;
  std::vector<std::string> files;
  bool include = false;
  bool empty_line = true;
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
      if (empty_line)
        ++stats.empty_lines;
      else if (is_comment(state))
        ++stats.comm_lines;
      else
        ++stats.code_lines;
      if (state == Token::comment_begin)
        state = Token::end;
      empty_line = true;
    }
    else if (t == Token::hash)
    {
      empty_line = false;
      if (!is_comment(state))
      {
        state = Token::hash;
        ++stats.code_words;
      }
    }
    else if (t == Token::multicomment_end)
    {
      if (state == Token::multicomment_begin)
        state = Token::end;
    }
    else if (t == Token::word)
    {
      empty_line = false;
      if (include)
      {
        stats.includes.push_back(str);
        include = false;
      }
      else
      {
        if ((state == Token::hash) && (str == "include"))
          include = true;
      }
      if (!is_comment(state))
      {
        ++stats.code_words;
      }
    }
  }
  return stats;
}

using string_set = std::unordered_set<std::string>;

void process_file(const std::string& file_name, string_set& visited_files,
                  const std::string& indent = {})
{
  const char std_include_path[] = "e:\\Software\\Microsoft Visual Studio 14.0\\VC\\include\\";

  auto file_stats = collect_stats(file_name);
  file_stats.print(std::cout, indent, !indent.empty());

  for (const auto& include : file_stats.includes)
  {
    if (visited_files.insert(include).second)
    {
      auto file = include.substr(1, include.length() - 2); // strip <...> or "..."
      std::cout << indent << "  file: " << file << "\n";
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
  std::string file_name = argv[1];
  std::cout << "file: " << file_name << "\n";
  process_file(file_name, visited_files);

  return 0;
}
