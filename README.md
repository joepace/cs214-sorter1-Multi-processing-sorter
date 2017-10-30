# cs214-sorter1-Multi-processing-sorter
This project is a multi-process version of the previous sorter0 project.

team: !failing
members: Joseph Redling-Pace and Xiaopeng (Jake) Zhou

Before we even began our project, we modified our code from last assignment to work more efficiently. We got rid of the static sized  buffers in our structs keeping track of each line, instead we replaced them with character pointers that go to a dynamically allocated size of memory suited for each string.

Steps for this project:

-Read directory name

-Walk through sub-directories to find all csv files

-fork to sort each csv file

    -output to differnt file each time
    
-prevent zombies

-check for proper input

-output metadata to standard out

  -metadata includes: total number of processes created and their pids
  
    -each new file, we should fork to do the actual sorting
    
    -each new directory, we should fork to process the directory
    
  -should print:
  
    -Initial PID: XXXXX
    
    -PIDS of all child processes: AAA, BBB, CCC, ...
    
    -Total number of processes: ZZZZ
    
The first difficulty we ran into was trying to figure out how to change our code to print not to STDOUT, but to a file instead. Since this problem did not affect the rest of our code to begin with, we decided to postpone trying to find a solution to this issue until the rest of our code was working as intended.

Firstly, for this project, we had to figure out how to search a directory to find a CSV file. After sometime of research and discussion, we were able to implement that fairly easily. We were now able to began testing. We decided to start by just searching the current directory we were in (the one the executable is located in). Originally, we had the movie_metadata.csv in this directory, but we made a much smaller test case in order to more quickly see the results of our program (due to the time inefficiency of IO).

Meanwhile, the other partner changed the formating of the code such as changing the printf to fprintf. He also worked on figuring out how to keep track of the total amount of processes created without a shared memory between processes. Eventually, after some research, we realized we can very easily do this by returning the amount of processes created per child upon the termination of the child, and keeping a sum counter in the initial function that incremented by the exit status of each child.

We were also able to make more progress into figuring out the traversal of directories. After some more work, we were able to correctly make our processes fork and sort files in a directory and sub-directory. However, strangely, we ran into an issue where our program was going UP a directory and actually sorting the files located in there! So our next set of objects were to figure the cause of this bug, implement the process counter (mentioned in the paragraph above), and figure out how to write to new files in the output directory.
