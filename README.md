## ASSIGNMENT 1: SPORTS COMPLEX PLANNING
Goal: The goal of this assignment is to take a complex new problem and formulate and solve it as search. Formulation as search is an integral skill of AI that will come in handy whenever you are faced with a new problem. Heuristic search will allow you to find optimal solutions. Local search may not find the optimal solution, but is usually able to find good solutions for really large problems. 
### Scenario: optimization of a new planned city
A new large sports complex is being built in Delhi. It will have all the highest end equipment and courts with lots of zones. A zone will house one type of court/equipment. Example, there will be different zones for basketball courts, table tennis rooms, cardio gym, weight training, yoga center, swimming pool and so on. Different sportspersons will have different typical schedules of when they do swimming and when they practice in a court and so on.
Based on typical interest of sports persons and children in Delhi (example, more people want to be cricketers than volleyball players), some zones will be used more and some will be used less. Moreover, because it is a large complex, the zones are far from each other, so there will be walking times involved from one zone to the other based on a user’s personalized schedule. Our goal is to identify which zone should be at which part of the complex so that (on average) time spent walking can be reduced.
For that, we assume that we have Z: a set of z zones numbered {1,2,...,z} and L: a set of l locations numbered {1,2,..,l} such that (z<=l). We define two matrices T (lxl) and N (zxz). An entry tij will represent the time taken to walk from location i to location j. On the other hand, the entry nxy will represent the number of daily walks from zone x to zone y. Note that tij =tji , though this is not true for matrix N. Also, tij =0 if i=j. 
Your goal is to output a mapping from Z to L such that the total time walking in a day is minimized.
## Input:
The first line has total processing time available in minutes. The second line has z: the number of zonesThe third line has l: the number of locations 
Starting fourth line we have the matrix N one row at a time. Assume all times are non-negative integers. Starting line 4+z, we have the matrix T one row at a time. Assume all entries to be non-negative integers. Here is a sample input2 
3425 3 24 1 34 5 034 1 304 1 440 8 118 0 
## Output:
Your algorithm should return the best allocation of zones to locations, such that one zone is in one location and one location has only one zone. The output format is a sequence of Z unique numbers, all less than equal to L. Example, if you decided that in the above problem zone 1 goes to location 2, zone 2 goes to location 4 and zone 3 goes to location 1, you should output: 
24 1The total time to walk for this permutation is 30. 
## Basic Algorithms you can try:
1. Heuristic Search: Design a state space and transition function for this problem. Define a heuristic function for evaluating a state. Implement A* (or variants) and measure quality of solutions found (and scalability). If heuristic is admissible – quality is optimal but algorithm may be slower. Test a couple of heuristics if you can design them. 
2. Branch and Bound: Design a state space and transition function for this problem. Optionally define a heuristic function for evaluating a partial walk. Also, optionally, define a ranking to pick the next successor. Implement Depth First Branch and Bound (or variants) and measure scalability. 
3. Local search: Implement a neighbor function for this problem. Implement local search (or variants). Measure of quality of best solution found as a function of time or other model parameters. 

⠀Recommended: start with local search as your base algorithm. 
## Sample Code:
You are being provided sample code that can take in the input and generate the output in C++. You may choose to not use this code. You may program the software in any of C++, Java or Python. The versions of the compilers/interpreters that will be used to test your code are 
JAVA: java version "11.0.20" (OpenJDK) Python 3.9.17g++ 9.4.0 
The sample code (written in cpp) can be downloaded here. This code reads in an input file and computes the cost of the allocation. You need to write the additional logic for allocation of resources. Here, we have allocated the resources sequentially. The allocation is then written in the output file. You may or may not use the sample code. Note that you need to implement logic to compute allocation in given time. You can compile and run the sample code as follows: 
make./main <input_filename> <output_filename> 
We have even supplied formatchecker.jar which checks the format of the output file generated and gives the cost (if the format is valid). To run the format checker, use the following command: 
./format_checker <input_filename> <output_filename> 
We have provided three input files representing easy problems. We recommend you experiment with other problems as well. 
## What to submit?
1. Submit your code in a .zip file named in the format <EntryNo>.zip. If there are two members in your team it should be called <EntryNo1>_<EntryNo2>.zip. Make sure that when we run “unzip yourfile.zip” the following files are produced in the working directory:compile.sh run.sh writeup.txt You will be penalized for any submissions that do not conform to this requirement. Your code must compile and run on our VMs. They run amd64 Linux version ubuntu 20.04. You are already provided information on the compilers on those VMs. They have RAM of 8 GB Your run.sh should take 2 inputs, someinputfile.txt and someoutputfile.txt. It should read the first input as input and output the answer in the outputfile../run.sh input.txt output.txt ( please note any name could be given to the two files). 
