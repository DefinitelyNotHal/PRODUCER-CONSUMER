# PRODUCER-CONSUMER
# Producer-Consumer Problem
# Description: This project demonstrates the producer and consumer problem; it requires the programmer to use standard counting semaphores to represent empty and full, and a mutex lock rather than a binary semaphore, to represent mutex. The course's Operating System 9th editon textbook has detailed information about this project between pages 253 and 258. By following its instructions, programmers should be able to create a code template and complete the program for this project. For this project, it includes a table of test cases, users can use these test cases to see what happens when changing the length of sleeping time, number of producers and consumers. At the end, the program generates an output file, producer-consumer-output.txt, users can based on the results they see and learn the producer and consumer problem.
# How to run this code:
# For windows, way 1: in windows CMD, change current directory to the directory of the file by using "cd", without quotes. Then input "main.exe", without quotes.
# For example:
# cd C:\Users\nameofUser\Desktop\CS471\CS471PROJECT\PRODUCER-CONSUMER
# main.exe
# Way 2: Double click the main.exe. (If Way 1 and 2 do not work properly, please use Way 3.)
# Way 3: Simply use CodeBlock to import the project, click build and run the program.
# Note: 1. I created a pdf file to tabulate the result, with a summary of the results.
# Result Summary:
# Based on the table, we can see that the number of producers always greater than or equal to a number of consumers. In order for a consumer to consume an item in the buffer, the buffer must be not empty. And in order for a producer to produce an item and send it to the buffer, the buffer must be not full. Therefore, for all the test cases, the consumer tends to wait until producer produces the item to the buffer, then it starts to consume the item when the buffer has item. The producer stops producing any more items to the buffer when the buffer is full, and wait till the consumer to consume the item, which frees up space for the buffer again.
# Overall, the longer the sleeping time, the more items will be produced and consumed. If the sleeping time maintains at a constant, and there are a lot more consumers than producers, the consumers must wait for a long time for an item. This works vice versa for the producer. Therefore, only increasing number of producers or consumers, and not caring about the others, does not help the system process. The difference between the number of producers and consumers should be kept as small as possible.
# Sample input:
# Test Case    Sleep time     #producers    #consumers
# 1             2               1               1
# 2             5               4               1
# 3             10              16              1
# 4             2               1               2
# 5             5               4               2
# 6             10              16              2
# 7             2               1               4
# 8             5               4               4
# 9             10              16              4
# 10            2               1               16
# 11            5               4               16
# 12            10              16              16
#
# Sample output:
# Length of Sleeping Time: 2
# Number of Producer Threads: 1
# Number of Consumer Threads: 1
#
# producer produced 18602
# consumer consumed 18602
# producer produced 20666
# consumer consumed 20666
