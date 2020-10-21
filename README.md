# Simple Profiler Example
Simple profiler library to use in the future projects.

# Build
Open the project in Visual Studio 2019, choose the Platform and Configuration and hit Build.

The output goes to `bin/{Platform}/{Configuration}/` and it will contain two files:
- include\: Contains all __header__ files
- lib\: Contains the __.lib__ file

# Usage
All your profiling must be done in a session, creationg and deletion of a session is done manually:
```c++
Benchmark::Profiler::getInstance().beginSession(name /*, filePath*/);
// Do some profiling
Benchmark::Profiler::getInstance().endSession();
```
To benchmark a specific section just instantiate the Timer:
```c++
void foo()
{
  Benchmark::Timer timer("Function foo");
  // Do some funny stuff
  timer.stop();   // If you dont call stop() then the timer will do it for you at the end if its lifetime
}
```
You can also use some Macros if you define `PPROFILE` in your project:
```c++
void foo()
{
  PPROFILE_SCOPE("Function foo"); // This is the same as instantiatine Benchmark::Timer and let it call stop() at the end if its lifetime
  // Do some funny stuff
}

void bar(int a, int b, int c)
{
  PPROFILE_FUNCTION();  // This is the same as calling PPROFILE_SCOPE("void bar(int a, int b, int c)")
  // Do some funny stuff
}
```
The output of the profiler goes to a `.json` file at the path specified in the `filePath` when the session is created. If the path is not specified then the output goes to `result.json` file in the directory where the project is running.
# Credits
Credits goes to [The Cherno](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw)

This project is based on The Cherno's [video](https://www.youtube.com/watch?v=xlAH4dbMVnU) on benchmarking.
