#include "file_utils_tests.h"
#include "test_assert.h"

#define FILE_UTILS_IMPLEMENTATION
#include "../file_utils.h"

namespace {
  using namespace fu;

  void csv_write_and_read()
    {
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> line1, line2;
    line1.emplace_back("The");
    line1.emplace_back("first");
    line1.emplace_back("line");
    line2.emplace_back("And");
    line2.emplace_back("the");
    line2.emplace_back("second");
    line2.emplace_back("line");

    data.push_back(line1);
    data.push_back(line2);

    TEST_ASSERT(csv_write(data, "csvfile.csv", ";"));

    data.clear();

    TEST_ASSERT(csv_read(data, "csvfile.csv", ";"));
    TEST_EQ(2, (int)data.size());
    TEST_EQ(3, (int)data[0].size());
    TEST_EQ(4, (int)data[1].size());
    TEST_EQ(std::string("The"), data[0][0]);
    TEST_EQ(std::string("first"), data[0][1]);
    TEST_EQ(std::string("line"), data[0][2]);
    TEST_EQ(std::string("And"), data[1][0]);
    TEST_EQ(std::string("the"), data[1][1]);
    TEST_EQ(std::string("second"), data[1][2]);
    TEST_EQ(std::string("line"), data[1][3]);
#ifdef _WIN32
    TEST_EQ(37, file_size("csvfile.csv"));
#else
    TEST_EQ(35, file_size("csvfile.csv"));
#endif    
    }

  void test_conversions_wstring_string()
    {
    std::wstring w = convert_string_to_wstring(std::string("A simple conversion"));
    TEST_ASSERT(w == std::wstring(L"A simple conversion"));
    std::string s = convert_wstring_to_string(std::wstring(L"A simple conversion"));
    TEST_ASSERT(s == std::string("A simple conversion"));

    std::wstring pi;
    pi.push_back((wchar_t)960);
    s = convert_wstring_to_string(pi);
    TEST_ASSERT(s.length() == 2);
    //0xCF 0x80
    TEST_ASSERT((unsigned char)s[0] == 0xCF);
    TEST_ASSERT((unsigned char)s[1] == 0x80);

    w = convert_string_to_wstring(s);
    TEST_ASSERT(w.length() == 1);
    TEST_ASSERT(w[0] == (wchar_t)960);
    }

  void print_executable_path()
    {
    auto exepath = get_executable_path();
    printf("Executable path: %s\n", exepath.c_str());
    }

  void test_put_get_env() {
    fu::putenv("file_utils_test_value", "hello world!");
    std::string value = fu::getenv("file_utils_test_value");
    TEST_EQ_STR("hello world!", value.c_str());
    }

  } // anonymous namespace

void run_file_utils_tests()
  {
  csv_write_and_read();
  test_conversions_wstring_string();
  print_executable_path();
  test_put_get_env();
  }
