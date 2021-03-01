#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vec)
{
    os << '{';
    bool first = true;
    for (const auto &item : vec)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << item;
    }
    return os << '}';
}

template <typename T>
ostream &operator<<(ostream &os, const set<T> &s)
{
    os << '{';
    bool first = true;
    for (const auto &item : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << item;
    }
    return os << '}';
}

template <typename Key, typename Value>
ostream &operator<<(ostream &os, const map<Key, Value> &m)
{
    os << '{';
    bool first = true;
    for (const auto &item : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << item.first << ": " << item.second;
    }
    return os << '}';
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {})
{
    if (!(t == u))
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty())
        {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

inline void Assert(bool b, const string &hint)
{
    AssertEqual(b, true, hint);
}

class TestRunner
{
public:
    template <typename TestFunc>
    void RunTest(TestFunc func, const string &test_name)
    {
        try
        {
            func();
            cerr << test_name << "OK" << endl;
        }
        catch (exception &e)
        {
            std::cerr << e.what() << '\n';
            ++fail_count;
        }
        catch (...)
        {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }
    ~TestRunner()
    {
        if (fail_count > 0)
        {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

#define ASSERT_EQUAL(x, y)                                               \
    {                                                                    \
        ostringstream os;                                                \
        os << #x << " != " << #y << ", " << __FILE__ << ":" << __LINE__; \
        AssertEqual(x, y, os.str());                                     \
    }

#define ASSERT(x)                                                 \
    {                                                             \
        ostringstream os;                                         \
        os << #x << " is false, " << __FILE__ << ":" << __LINE__; \
        Assert(x, os.str());                                      \
    }

#define RUN_TEST(tr, func) \
    tr.RunTest(func, #func);
