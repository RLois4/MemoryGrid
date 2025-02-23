#include <iostream>
#include <iomanip>
#include <random>
#include <unistd.h>
#include <ncurses.h>
#include <csignal>
#include <cstring>
#include <sstream>
#include "chartoi.hpp"

using namespace std;


void show_help(const char* command) {
	cout << "Usage: " << command << " [options]\n\n"
			 << "Options:\n"
			 << "\t-t <time>      Time in seconds that the numbers stay on the screen (default: 3)\n"
			 << "\t-q <quantity>  Number of digits of the number (default: 7)\n"
			 << "\t--help         Displays this help\n\n"
			 << "Example:\n"
			 << "\t" << command << " -t 5 -q 4\n";
}


void keybint_handler(int sig) {
	endwin();
	exit(1);
}

int main(int argc, char** argv) {

	int SEC = 3;
  int QNUM = 7;
	
	if(argc > 1) {
		for(int i=1; i<argc; i++) {
			if( strcmp(argv[i], "--help") == 0 ) {
				show_help(argv[0]);
				exit(0);
			}
			else if( strcmp(argv[i], "-q") == 0 ) {
				QNUM = chartoi(argv[++i]);
				if(QNUM < 0) {
				cout << argv[0] << " invalid argument for -q \"" << argv[i] << "\"\n"
						 << "\ntry 'numemory --help' for more information\n";
					return 0;
				}
			}
			else if( strcmp(argv[i], "-t") == 0 ) {
				SEC = chartoi(argv[++i]);
				if(SEC < 0) {
					cout << argv[0] << " invalid argument for -t \"" << argv[i] << "\"\n"
							 << "\ntry 'numemory --help' for more information\n";
					return 0;
				}
			} else {			
				cout << "numemory: invalid option: " << argv[1] << "\ntry 'numemory --help' for more information\n";
				exit(1);
			}
		}
	}

	cout << endl << SEC << endl << QNUM;
	
	return 0;

	signal(SIGINT, keybint_handler);
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<long long> dist(0, 9999999);

	int row, col;
	initscr();
	curs_set(0);
	noecho();
	getmaxyx(stdscr, row, col);

	int pts = 0;
	char res[8];
	char num[8];

	mvprintw(row/2 - 1, (col - 8) / 2, "NUMEMORY");
	mvprintw(row/2 + 1, (col - 22) / 2, "Press any key to enter");
	getch();
	clear();

	while(1) {

		ostringstream oss;
	  oss << setw(7) << setfill('0') << dist(mt);

		strncpy(num, oss.str().c_str(), 7);
		num[7] = 0;

		mvprintw(row - 2, 2, "Ctrl C to exit");
		mvprintw(row - 2, col - 20, "points: %d", pts);

		move(row/2, (col - 13)/2);
		for(int i=0; i<7; i++) {
			addch(' ');
			addch(num[i]);
		}
		
		refresh();
		sleep(SEC);
		move(row/2, 0);
		clrtoeol();
		move(row/2, 0);
		clrtoeol();
		echo();
		curs_set(1);

		mvscanw(row/2 + 5, (col-7)/2, "%7s", res);
		res[7] = 0;
		move(row/2 + 5, 0);
		clrtoeol();
		
		noecho();
		curs_set(0);
		
		if( strcmp(res, num) == 0 ) {
			mvprintw(row - 2, col - 3, "+1");
			pts++;		
		}
		else {
			mvprintw(row - 2, col - 3, "+0");
		}
	}

end:

	getch();
	endwin();
	cout << res << endl << num << endl << pts << endl;
	return 0;
}
