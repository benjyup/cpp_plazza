# cpp_plazza
The purpose of this project is to make you realize a scrapper, which is composed of a main program, with an user interface, that accepts new commands, of several process, themselves with several threads, themselves looking for mails inside several files.

Two versions of your program must be done. The first one is the default one: a pure
text mode program that read commands on STDIN.
This version
MUST
fully compile even if there is no graphic, gui or curses library
installed on the system. It
MUST
write every extracted data on STDOUT, with a new
line between every data, so the following command must work well:

cat commands | ./plazza 5 > datas

The second one is build by specifying "ui" to the Makefile. It builds your project with
a user interface. Your UI must propose the following functionnalities:

•Ask to browse file by the user through command line.

•Displays the scrapper status, including the current occupancy of the threads, as
well as their unachieved work..
