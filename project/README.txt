group members:
Victor Mercado vmercado29@csu.fullerton.edu

I used c++ 17

To run Shell use g++ to compile:

g++ -std=c++17 shell.cpp -o shell

then run the command in the terminal: ./shell

To run Serial use g++ to compile:

g++ -std=c++17 serial.cpp -o serial

then run the command in the terminal: ./serial

To run Parallel use g++ to compile:

g++ -std=c++17 parallel.cpp -o parallel

then run the command in the terminal:  ./parallel


Execution times for serial:
0.06s user 
0.04s system 
2.545s real
3% cpu 

Execution times for parallel:
0.06s user 
0.04s system 
0.519 real
20% cpu


1. In the output of time, what is the difference between real, user, and sys times?
- user time is the time spent running code on behalf of the user, 
  like executing the command "time" from the terminal
- sys time is the time spent running system calls and kernel code
- real time is the actual time spent running the program specified in the command prompt

2. Which is longer: user time or sys time? Use your knowledge to explain why.
-  sys time is very short as system calls tend to be very quick therefore 
   user time is longer where there tends to be more code to execute. 

3. When fetching all of the locations in the file, which fetcher finishes faster? Why do you
think that is?
- The parallel fetcher is faster as it spends 1/5 the time to fetch all locations, 
this is because the parent process isnt sitting around waiting for the child process
to complete to start up a new child process to fetch data.

4. Suppose one of the fetcher children crashes. Will this affect other children? Explain.
What is your conclusion regarding the benefits or disadvantages of isolating each fetch
task within a different process?
- This wouldn't affect the other children since they are isolated with their own memory
  and execution. Benefits from placing each fetcher function in its own process allows them
  to run in parallel for quicker execution of the program. Some disadvantages would be
  overhead in managing the processes as it requires memory and time to spawn a process.
  Another disadvantage would be managing communication between the processes and ensuring
  they aren't accessing the same device without precautions.