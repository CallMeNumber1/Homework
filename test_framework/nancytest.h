/*************************************************************************
	> File Name: nancytest.h
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月06日 星期六 15时12分32秒
 ************************************************************************/

class TestCase
{
public:
    TestCase(const char* case_name) : testcase_name(case_name){}

    // 执行测试案例的方法
    virtual void Run() = 0;

    int nTestResult; // 测试案例的执行结果 
    const char* testcase_name; // 测试案例名称
};
class UnitTest
{
public:
    // 获取单例
    static UnitTest* GetInstance(); 

    // 注册测试案例
    TestCase* RegisterTestCase(TestCase* testcase);
    
    // 执行单元测试
    int Run();

    TestCase* CurrentTestCase; // 记录当前执行的测试案例
    int nTestResult; // 总的执行结果
    int nPassed; // 通过案例数
    int nFailed; // 失败案例数
protected:
    std::vector<TestCase*> testcases_; // 案例集合
};
UnitTest* UnitTest::GetInstance()
{
    static UnitTest instance;
    return &instance;
}

TestCase* UnitTest::RegisterTestCase(TestCase* testcase)
{
    testcases_.push_back(testcase);
    return testcase;
}

int UnitTest::Run()
{
    nTestResult = 1;
    for (std::vector<TestCase*>::iterator it = testcases_.begin();
        it != testcases_.end(); ++it)
    {
        TestCase* testcase = *it;
        CurrentTestCase = testcase;
        std::cout << "======================================" << std::endl;
        printf("Run TestCase: %s\n", testcase->testcase_name);
        testcase->Run();
        printf("End TestCase: %s\n", testcase->testcase_name);
        if (testcase->nTestResult)
        {
            nPassed++;
        }
        else
        {
            nFailed++;
            nTestResult = 0;
        }
    }

    std::cout << "green " << "======================================" << std::endl;
    std::cout << "Total TestCase : " << nPassed + nFailed << std::endl;
    std::cout << "Passed : " << nPassed << std::endl;
    std::cout << "Failed : " << nFailed << std::endl;
    return nTestResult;
}
#define TESTCASE_NAME(testcase_name) \
    testcase_name##_TEST

#define NANCY_TEST_(testcase_name) \
class TESTCASE_NAME(testcase_name) : public TestCase \
{ \
public: \
    TESTCASE_NAME(testcase_name)(const char* case_name) : TestCase(case_name){}; \
    virtual void Run(); \
private: \
    static TestCase* const testcase_; \
}; \
\
TestCase* const TESTCASE_NAME(testcase_name) \
    ::testcase_ = UnitTest::GetInstance()->RegisterTestCase( \
        new TESTCASE_NAME(testcase_name)(#testcase_name)); \
void TESTCASE_NAME(testcase_name)::Run()

#define TEST(testcase_name) \
    NANCY_TEST_(testcase_name)

#define RUN_ALL_TESTS() \
    UnitTest::GetInstance()->Run();
//原本Unitest::GetInstance()->CurrentTestCase->nTestResult = 0
#define EXPECT(m, n) \
    if (m != n) \
    { \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0; \
        printf("\033[31m Failed \033[0m"); \
        printf("Expect:%d ", m); \
        printf("Actual:%d\n", n); \
    } else { \
        printf("\033[32m Pass \033[0m\n"); \
    }
