# cs214-sorter1-Multi-processing-sorter
This project is a multi-process version of the previous sorter0 project.

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
    

