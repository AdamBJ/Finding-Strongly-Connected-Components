Finding-Strongly-Connected-Components
=====================================

Assignment 4, Standford Algorithms MOOC #1

Two very important notes about this assignment. The sheer number of nodes combined with the recursive solution that was utilized
caused a stack overflow to occur. The default stack size in VS2013 is 1MB. To change this, go to Project Properties -> Linker -> System and change the Stack Reserve size to something larger. I used a 100MB stack and so entered 100,000,000 since the field is measured in bytes (100 bytes * 10^6 = 100 MB). 

The second very important note is on the differences between running a program in release mode vs debug mode, and also on the use of compiler optimization. First, code will always execute faster if it is compiled in Release mode since Release mode includes various enhancements meant to produce a final product. Second, the compiler can be tweaked to optimize compiled code for speed/size. To enable optimizations go to Project Properties -> C/C++ -> Optimization and select from the dropdown menu.

Finally, note that when you're changing project properties for Debug/Release versions of your project *YOU NEED TO SELECT WHICH CONFIGURATION YOU WANT TO MODIFY, IE RELEASE OR DEBUG. THEY ARE MODIFIED SEPERATELY (unless you select All Configurations)*.

Note that debug with no optimization took an HOUR to compute the result. With optimization and compiled in release mode it took a bit more than a minute finish.
