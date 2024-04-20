#include "Worker.h"

double Worker::m_yieldAmount = 111.25;
double Worker::m_freeAmount = 556.02;

Worker::Worker(const std::string &wName, int wAge, double salaryGross, int sYears) noexcept
                : Person(wName, wAge)
{
    setWorker(salaryGross, sYears);
}
