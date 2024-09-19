#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

char ch;
char arrow;
int x = 0;
int y = 0;
struct termios original_settings;

int main(int argc, char **argv)
{
  printf("ovim Works!\n");
  int ch;
  int x = 0;
  int y = 0;
  initscr();

  keypad(stdscr, TRUE);
  do
  {
    ch = getch();
    switch (ch)
    {
    case KEY_DOWN:
      printf("down");
      x++;
      break;
    case KEY_UP:
      x--;
      break;
    case KEY_LEFT:
      y++;
      break;
    case KEY_RIGHT:
      y--;
    default:
      char str[2] = { (char)ch, '\0' };
      addstr(str);
      break;
    }
    refresh();
  } while (ch != '~');

  endwin();

  return EXIT_SUCCESS;
}