// // #include <ncurses.h>
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <unistd.h>
// // #include <termios.h>
// // #include <time.h>

// // char ch;
// // char arrow;
// // int x = 0;
// // int y = 0;
// // struct termios original_settings;

// // // Function to move cursor to (row, col) position
// // void move_cursor(int row, int col)
// // {
// //   // Escape sequence to move the cursor: "\e[row;colH"
// //   printf("\e[%d;%dH", row, col);
// //   fflush(stdout);
// // }

// // void clear_screen()
// // {
// //   clear();
// //   refresh();
// //   fflush(stdout);
// // }

// // int main(int argc, char **argv)
// // {
// //   initscr();
// //   int ch;
// //   int x = 40;
// //   int y = 10;
// //   clear_screen();
// //   move_cursor(x, y);
// //   printf("ovim Works!\n");

// //   // keypad(stdscr, TRUE);
// //   // do
// //   // {
// //   //   ch = getch();
// //   //   switch (ch)
// //   //   {
// //   //   case KEY_DOWN:
// //   //     printf("down");
// //   //     x++;
// //   //     break;
// //   //   case KEY_UP:
// //   //     x--;
// //   //     break;
// //   //   case KEY_LEFT:
// //   //     y++;
// //   //     break;
// //   //   case KEY_RIGHT:
// //   //     y--;
// //   //   default:
// //   //     char str[2] = {(char)ch, '\0'};
// //   //     addstr(str);
// //   //     break;
// //   //   }
// //   //   refresh();
// //   // } while (ch != '~');
// //   MEVENT event;

// //   while (1)
// //   {
// //     int ch = getch(); // Wait for user input

// //     if (ch == KEY_MOUSE)
// //     { // Check if the input is a mouse event
// //       printf("works");
// //       if (getmouse(&event) == OK)
// //       { // Get the mouse event
// //         // Now you can use event.x and event.y
// //         int mouse_x = event.x;
// //         int mouse_y = event.y;

// //         // Print the coordinates or use them as needed
// //         mvprintw(0, 0, "Mouse X: %d, Mouse Y: %d", mouse_x, mouse_y);
// //         refresh(); // Refresh to show changes
// //       }
// //     }

// //     // Optionally, add a condition to break the loop
// //     if (ch == 'q')
// //     { // Exit on 'q' key
// //       break;
// //     }
// //   }

// //   endwin();

// //   return EXIT_SUCCESS;
// // }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <termios.h>
// #include <fcntl.h>

// void enable_mouse_tracking() {
//     // Enable mouse tracking
//     printf("\e[?1000h"); // Enable X10 mouse tracking
//     fflush(stdout);
// }

// void disable_mouse_tracking() {
//     // Disable mouse tracking
//     printf("\e[?1000l"); // Disable X10 mouse tracking
//     fflush(stdout);
// }

// int kbhit() {
//     struct termios oldt, newt;
//     int ch;
//     int oldf;

//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;
//     newt.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//     oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
//     fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

//     ch = getchar();

//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     fcntl(STDIN_FILENO, F_SETFL, oldf);

//     if(ch != EOF) {
//         ungetc(ch, stdin);
//         return 1;
//     }

//     return 0;
// }

// int main() {
//     enable_mouse_tracking();

//     printf("Mouse tracking enabled. Move the mouse or click.\n");
//     fflush(stdout);

//     while (1) {
//       int key_event = kbhit();
//         if (key_event) {
//             char buffer[10];
//             int n = read(STDIN_FILENO, buffer, sizeof(buffer));

//             // Check for mouse events (basic check for mouse button or motion)
//             if (n > 0 && buffer[0] == '\e' && buffer[1] == '[') {
//                 printf("works\n");
//                 break;
//             }
//            if(buffer[0]== 'q'){
//                 disable_mouse_tracking();
//                 return 0;
//            }
//         }
//         usleep(100000); // Sleep for 100 ms to prevent busy waiting
//     }

//     disable_mouse_tracking();
//     return 0;
// }
#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>

// Define a struct to hold mouse coordinates
struct Pos
{
  int x;
  int y;
};

// Wrap mouse_trafo to return a struct
struct Pos get_mouse_position(int x, int y, bool to_screen)
{
  struct Pos mouse;

  // Apply the mouse_trafo transformation
  if (mouse_trafo(&x, &y, to_screen))
  {
    mouse.x = x;
    mouse.y = y;
  }
  else
  {
    mouse.x = -1; // Indicate an error in transformation
    mouse.y = -1;
  }

  return mouse;
}

void cursor_print_placeholder(struct Pos mouse)
{
  /*
  Move cursor to X, Y location
  "\e[s" saves the curent locatin of the cursor (push)
  Print  "#" which moves cursor automatically forward 1
  \e[u puts the cursour back to the saved location (pop)
  */
  // note: the +1 offset is only to make the text print right underneath the cursor location
  // othersie it looks bad
  printf("\e[%d;%dH\e[s#\e[u", mouse.x + 1, mouse.y + 1);
  fflush(stdout);
}
void cursor_print(struct Pos mouse, char *text)
{
  /*
 Move cursor to X, Y location
  "\e[s" saves the curent locatin of the cursor (push)
  Print  <text> which moves cursor automatically forward 1
  \e[u puts the cursour back to the saved location (pop)
  */
  // note: the +1 offset is only to make the text print right underneath the cursor location
  // othersie it looks bad
  printf("\e[%d;%dH\e[s%s\e[u", mouse.x + 1, mouse.y + 1, text);
  fflush(stdout);
}

// Function to move cursor to (row, col) position
void move_cursor(struct Pos mouse)
{
  // Escape sequence to move the cursor: "\e[<X>;<Y>H"
  printf("\e[%d;%dH", mouse.x, mouse.y);
  fflush(stdout);
}

int main()
{
  // WINDOW *win;
  // Initialize ncurses
  initscr();
  cbreak();
  noecho(); // stops the termial from printing any character, helpfull because otherwise default is to p
  // print all controll characters. this is not the default behavor of the terminal
  keypad(stdscr, TRUE);

   

  // Enable mouse tracking
  mousemask(ALL_MOUSE_EVENTS, NULL);
  MEVENT event;

  // win = newwin(LINES, COLS, 0, 0);
  int x = 0;
  int y = 0;
  // Loop to capture mouse events
  getyx(curscr,x, y);
  while (1)
  {
    struct Pos mouse;

    int ch = getch();
    getyx(curscr, y, x);
    // Detect if a mouse event occurs
    if (ch == KEY_MOUSE)
    {
      if (getmouse(&event) == OK)
      {
        // Get current mouse position with mouse_trafo transformation
        mouse = get_mouse_position(event.y, event.x, TRUE);

        // If valid position, print it
        if (mouse.x != -1 && mouse.y != -1)
        {
          // move_cursor(mouse);
          // printf("#");
          // mvprintw(0, 0, "Mouse Position - X: %d, Y: %d", mouse.x, mouse.y);
          // mvprintw(mouse.x, mouse.y, "#");
          // move_cursor(mouse,"hi");
          cursor_print(mouse, "");
          refresh();
          ch = '\0';
        }
      }
    }

    if (ch != KEY_MOUSE)
    {
      printf("%c", ch);
      fflush(stdout);
    }
    if (ch == KEY_UP)
    {
      // cur.x += 1;
      // move_cursor(cur);
      printf("KEY_UP");
      fflush(stdout);
    }
    if (ch == KEY_LEFT)
    {
      printf("\e[I");
      fflush(stdout);
    }

    // Exit on 'q' key press
    if (ch == 'q')
    {
      break;
    }
  }

  // End ncurses mode
  endwin();

  return 0;
}
