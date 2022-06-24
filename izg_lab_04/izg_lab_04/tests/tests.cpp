#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <gtest/gtest.h>
#include <memory>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

GTEST_API_ int main(int argc, char **argv)
{

    int customArgc = argc + 1;
    std::shared_ptr<char*> customArgv(new char*[customArgc], std::default_delete<char*[]>());

    const char* const filter = "--gtest_filter=*";

    for (int i = 0; i < argc; ++i)
    {
        customArgv.get()[i] = argv[i];
    }
    customArgv.get()[argc] = const_cast<char*>(filter);

    testing::InitGoogleTest(&customArgc, customArgv.get());
    return RUN_ALL_TESTS();
}
