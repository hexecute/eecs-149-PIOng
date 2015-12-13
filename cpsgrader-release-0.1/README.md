# Overview

CPSGrader is an *automatic grading cum feedback generation tool (auto-grader) for laboratory
courses* developed at the University of California, Berkeley.  CPSGrader uses Signal Temporal
Logic (STL) based _test benches_ to monitor simulation traces of student solutions for
faults. It is designed to work with any black-box simulator. The test benches in CPSGrader are
"parametriezed" to be robust to certain allowed variations in student solutions. Each test bench
serves as a classifier to detect presence/absence of a particular kind of fault and we automatically
synthesize the classification boundaries (in terms of ranges of test bench parameters) using a
sample set of previously known correct and faulty solutions. The auto-grader is an independent
library written in C++ that can plug into any simulator via an API

# Download and Install

The latest releases of CPSGrader can be downloaded from [cpsgrader.org][cpsgrader.org]
website. Alternatively, the development version is accessible through the anonymous svn repository
at the following address:

https://repo.eecs.berkeley.edu/svn-anon/users/donze/CPSGrader/trunk/

## Folder Organization

├── README.md:        This file. 
├── STLDriver:        CPSGrader main source code and library 
├── Simulators        Simulators interfaced with CPSGrader  
│   ├── CPSFileGrader A simple program using CPSGrader library with trace files  
│   └── EECS149lab    Simulator (CyberSim) and material used for EECS149 on-campus and MOOC offerings 

## Compiling the CPSGrader library

Go into STLDriver and type make. This will create STLDriver/lib/libcpsgrader.a (or a bunch of
error messages you'd be well advised to send to cpsgrader-dev@lists.eecs.berkeley.edu).

## Testing the CPSGrader library

1. Go into Simulators/CPSFileGrader
2. Type make. This will create a binary called CPSFileGrader (or a bunch of errors etc).
3. Test first with ./CPSFileGrader simple_test.stl
4. If you don't see a bunch of errors (which you'd be well advised to send to donze@berkeley.edu),
try the more involved ./CPSFileGrader grading_nav_hill.stl. Note that if everything went well, this
will create a file named test\_log.txt. Compare this with traces/0001/test\_log.txt. If the results
are consistent, CPSGrader probably works as intended.

## Compiling/testing using Visual Studio 

TODO

# Using CPSGrader with a custom simulator

We propose currently three methods:

1. File interface
The simplest method is to have the custom simulator write traces into files and grade them using the
program CPSFileGrader.

2. C++ API interface
CPSGrader main class is STLDriver, which exposes a simple API to run tests
defined in a test plan. The easiest way to get started with the C++ API is to modify
CPSFileGrader.cpp by replacing the call to the read_data function by a call to the simulator, or a
wrapper function which will run a simulation and write the result in a simple vector of vector of
double.  

3. CPSGrader authors interface
Write (emails) to the CPSGrader team, and they will figure out a way to interface your simulator to
CPSGrader.  


# Using/Extending CyberSim+CPSGrader

CPSGrader comes with a robotic simulator based on NI LabView Robotics which was used in the MOOC
EECS149.1x on edX. Instructions on how use CyberSim+CPSGrader are still available in the virtual lab 
section of the MOOC page:
<https://courses.edx.org/courses/BerkeleyX/EECS149.1x/2T2014/info>

[cpsgrader.org]: http://www.cpsgrader.org






