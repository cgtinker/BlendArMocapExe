#pragma once

// https://www.drdobbs.com/cpp/logging-in-c/201804215
#include <iostream>
#include <ctime>
#include <chrono>

// Log, version 0.1: a simple logging class
enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG};


class Log
{
public:
   Log();
   virtual ~Log();
   std::ostringstream& Get(TLogLevel level = logINFO);
public:
   static TLogLevel& ReportingLevel();
protected:
   std::ostringstream os;
private:
   Log(const Log&);
   Log& operator =(const Log&);
private:
   TLogLevel messageLevel;
};
std::ostringstream& Log::Get(TLogLevel level)
{
   os << "- " << NowTime();
   os << " " << ToString(level) << ": ";
   os << std::string(level > logDEBUG ? 0 : level - logDEBUG, '\t');
   messageLevel = level;
   return os;
}
Log::~Log()
{
   if (messageLevel >= Log::ReportingLevel())
   {
      os << std::endl;
      fprintf(stderr, "%s", os.str().c_str());
      fflush(stderr);
   }
}