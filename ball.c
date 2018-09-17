#include <ncurses.h>
#include <unistd.h>

#define DELAY 50000

int main(int argc, char *argv[]) {
  int max_x;
  int max_y;
  int x = 0, y = 0;
  int vx = 1, vy = -1;

  int pad_length = 5;
  int pad_x = 0;
  int pad_velocity = 0;
  int input;

  bool running = true;

  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(FALSE);
  nodelay(stdscr, TRUE);

  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);

  while (running) {
    max_x = getmaxx(stdscr);
    max_y = getmaxy(stdscr);

    // Draw
    clear();


    attron(COLOR_PAIR(1));
    mvprintw(y, x, "o");
    attron(COLOR_PAIR(2));
    mvprintw(max_y-1, pad_x, "------------------------");
    attroff(COLOR_PAIR(2));
    mvprintw(max_y-1, 0, "X: %d, Y: %d, pad: %d", x, y, pad_velocity);
    refresh();

    // Get input
    input = 0;
    input = wgetch(stdscr);

    if (input == 27) break;

    if (input == KEY_LEFT) pad_velocity = -2;
    else if (input == KEY_RIGHT) pad_velocity = 2;
    else pad_velocity = 0;

    flushinp();

    // Move ball and pad
    x += vx;
    y += vy;
    pad_x += pad_velocity;

    // Logic
    if (x >= max_x-1) {
      vx = -1;
    } else if (x <= 0) {
      vx = 1;
    }
    if (y >= max_y-1) {
      vy = -1;
    } else if (y <= 0) {
      vy = 1;
    }

    usleep(DELAY);
  }

  // sleep(1);

  endwin();

}
