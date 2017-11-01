# cs214-sorter1-Multi-processing-sorter
This project is a multi-process version of the previous sorter0 project.

team: !failing
members: Joseph Redling-Pace and Xiaopeng (Jake) Zhou

Instructions for use:
After compiling the C files with the included Makefile, execute ./sorter with the two required parameters: "-c <category_name>". Further parameters: "-d <inputDirectory>" and "-o <outputDirectory>" are optional. One may be included without the other, but if both are included, "-d <inputDirectory>" must come before "-o <outputDirectory>". Any errors with the command line prompt will result in an error message and termination of the running program. Any errors occured during execution of the program will also result in an error message and termination of the program. Metadata results from processes terminated before completion should not be considered valid as they are not guaranteed to have finished the intended process.

Documentation:
Before we even began our project, we modified our code from last assignment to work more efficiently. We got rid of the static sized  buffers in our structs keeping track of each line, instead we replaced them with character pointers that go to a dynamically allocated size of memory suited for each string.
    
The first difficulty we ran into was trying to figure out how to change our code to print not to STDOUT, but to a file instead. Since this problem did not affect the rest of our code to begin with, we decided to postpone trying to find a solution to this issue until the rest of our code was working as intended.

Firstly, for this project, we had to figure out how to search a directory to find a CSV file. After sometime of research and discussion, we were able to implement that fairly easily. We were now able to began testing. We decided to start by just searching the current directory we were in (the one the executable is located in). Originally, we had the movie_metadata.csv in this directory, but we made a much smaller test case in order to more quickly see the results of our program (due to the time inefficiency of IO).

Meanwhile, the other partner changed the formating of the code such as changing the printf to fprintf. He also worked on figuring out how to keep track of the total amount of processes created without a shared memory between processes. Eventually, after some research, we realized we can very easily do this by returning the amount of processes created per child upon the termination of the child, and keeping a sum counter in the initial function that incremented by the exit status of each child.

We were also able to make more progress into figuring out the traversal of directories. After some more work, we were able to correctly make our processes fork and sort files in a directory and sub-directory. However, strangely, we ran into an issue where our program was going UP a directory and actually sorting the files located in there! So our next set of objects were to figure the cause of this bug, implement the process counter (mentioned in the paragraph above), and figure out how to write to new files in the output directory.

After realizing our previous implementation of the traversal was wrong (it worked but it wasn't recursive), we recreated the code in a function, which we could then use for recursive directory traversal. The previous bug was pretty easy to fix, we just made sure we ignored .. from readdir. However, with our new code, we ran into the issue of printing out the same pid twice. We were able to fix this... only to have it be an issue again quite soon. We were able to implement a way to keep track of the total amount of processes per execution call (by using the exit status of process), but due to some issue in the order of simultaneous processes, we would print out the same pid twice. We now had to handle this bug. We created another few test cases at this point to see how our code would act with more csvs to sort and csv in different levels.

After a few different approaches, we were able to solve this issue by keeping track of a single printed pid per process. We were also able to implement the -o feature leading to a desired output directory by passing an intended path to our file sorting function, which also outputs sorted files.

After a fair share of time bug fixing and patching the all-too-frequent minor mistakes we would find throughout the code, we felt confident enough that our program works properly and avoids ungraceful errors.
