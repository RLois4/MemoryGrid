#include <iostream>
#include <iomanip>
#include <random>
#include <unistd.h>
#include <ncurses.h>
#include <csignal>
#include <cstring>
#include <sstream>

#define SEC 1
using namespace std;

void keybint_handler() {
    endwin();
    exit(1);
}

int main() {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<long long> dist(0, 9999);

    int row, col;
    initscr();
    curs_set(0);
    noecho();
    getmaxyx(stdscr, row, col);

    int pts = 0;
    char res[5];
    char num[5];

    while (1) {
        ostringstream oss;
        oss << setw(4) << setfill('0') << dist(mt);

        strncpy(num, oss.str().c_str(), 4);
        num[4] = '\0';  // Correção no terminador nulo

        mvprintw(row - 2, col - 12, "Points: %d", pts);

        move(row / 2, (col - 5) / 2);
        for (int i = 0; i < 4; i++) {
            addch(' ');
            addch(num[i]);
        }

        refresh();
        sleep(SEC);
        move(row / 2, 0);
        clrtoeol();

        echo();
        curs_set(1);

        mvscanw(row / 2 + 5, (col - 4) / 2, "%4s", res);  
        move(row / 2 + 5, 0);
        clrtoeol();

        noecho();
        curs_set(0);

        if (strcmp(res, num) == 0) {
            mvprintw(row - 2, col - 3, "+1");
            pts++;
        } else {
            mvprintw(row - 2, col - 3, "+0");
        }

        refresh();  // Garante que o resultado seja mostrado antes do próximo loop
        sleep(1);   // Dá um tempo antes de exibir o próximo número
    }

    getch();
    endwin();
    cout << res << endl << num << endl << pts << endl;
    return 0;
}

