#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
// create a editor
// write to screen with any a-z characrer
// ctrl + s saves it to 'saved_output.txt
//  gcc -o ovim ovim.c -lncurses  ;./ovim

// Function to move cursor to (row, col) position
// void move_cursor(int row, int col)
// {
//     // Escape sequence to move the cursor: "\033[row;colH"
//     printf("\033[%d;%dH", row, col);
//     fflush(stdout);
// }

// int get_pos(int *y, int *x)
// {

//     char buf[30] = {0};
//     int ret, i, pow;
//     char ch;

//     *y = 0;
//     *x = 0;

//     struct termios term, restore;

//     tcgetattr(0, &term);
//     tcgetattr(0, &restore);
//     term.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(0, TCSANOW, &term);

//     write(1, "\033[6n", 4);

//     for (i = 0, ch = 0; ch != 'R'; i++)
//     {
//         ret = read(0, &ch, 1);
//         if (!ret)
//         {
//             tcsetattr(0, TCSANOW, &restore);
//             fprintf(stderr, "getpos: error reading response!\n");
//             return 1;
//         }
//         buf[i] = ch;
//         // printf("buf[%d]: \t%c \t%d\n", i, ch, ch);
//     }

//     if (i < 2)
//     {
//         tcsetattr(0, TCSANOW, &restore);
//         // printf("i < 2\n");
//         return (1);
//     }

//     for (i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
//         *x = *x + (buf[i] - '0') * pow;

//     for (i--, pow = 1; buf[i] != '['; i--, pow *= 10)
//         *y = *y + (buf[i] - '0') * pow;

//     tcsetattr(0, TCSANOW, &restore);
//     return 0;
// }
char ch;
char arrow;
int x = 0;
int y = 0;
struct termios original_settings;

// void printing();
// void moving_and_printing();
// void coloring();

// void center(int row, char *title)
// {   
//     int len,indent,y,width;

//     /* get screen width */
//     getmaxyx(stdscr,y,width);
//     /* get title length */
//     len = strlen(title);
//     /* calculate indent */
//     indent = (width - len)/2;
//     /* show the string */
//     mvaddstr(row,indent,title);
//     refresh();
// }
// void marquee(char *text){
//     char *t;
//     int len;

//     len = strlen(text);
//     t = text;           /* initialize pointer */
//     while(len)
//     {
//         move(5,5);      /* insert same spot */
//         insch(*(t+len-1));  /* work backwards */
//         refresh();
//         napms(100);         /* .1 sec. delay */
//         len--;
//     }
//     getch();
// }

// void delete_line(int row, int col){
//     move(row, col);
//     deleteln();
//     refresh();      
//     getch();
// }

// void delete_char(int row, int col){
//     move(row, col);
//     delch();
//     refresh();
// }

// void insert_char(int row, int col, char ch){
//     move(row, col);
//     insch(ch);
//     refresh();
// }
// void clear_screen(){
//     clear();
//     refresh();
// }

int main(int argc, char **argv)
{
    // initscr();

    // addstr("----------------------\n| oransblog.com \n| nsursor ovim |\n ------\n\n");
    // // refresh();

    // addstr("\npress any key to exit..");

    // refresh();

    //  while((ch = getch()) != '~'){}
    // getch();

    // endwin();
 ////   getmaxyx(stdscr,y,x);
// napms(500);
//  mvaddch(5,5,"#");
    // center(1, "Penguin Soccer Finals");
    // getyx(stdscr,row,col);
        //  char name[32];
        //  getnstr(name,31);
//    nodelay(stdscr,TRUE); //turn off blocking 
// while(getch() == ERR){//works when not key is pressed}
 //    noecho(); 
//  ungetch(ch);//return key to queue
//    keypad(stdscr,TRUE); //            case KEY_DOWN: https://c-for-dummies.com/ncurses/source_code/08-06_arrowkeys.php
//start_color();
//bkgd(win, )
//  border(0,0,0,0, 0,0,0,0);
//    border('|', '|', '-', '-', '+', '+', '+', '+');
// quartersub=subwin(stdscr,slines,scols,sposy,sposx);
//    scroll(stdscr);
//scrl(3);
//    scrl(-3);
// scrollok(stdscr,TRUE);
//     MEVENT mort;            if( ch == KEY_MOUSE )         getmouse(&mort);
//  hline(0,maxx-x);
// vline(0,maxy-y);
//    int r = scr_dump("dump.win");
   int ch;
    int x= 0;
    int y = 0;
    initscr();
    
    keypad(stdscr,TRUE);
    do
    {
        ch = getch();
        switch(ch)
        {
            case KEY_DOWN:
                // addstr("Down\n");
                x ++;
                break;
            case KEY_UP:
                // addstr("Up\n");
                x --;
                break;
            case KEY_LEFT:
                // addstr("Left\n");
                y++;
                break;
            case KEY_RIGHT:
                // addstr("Right\n");
                y--;
            default:
            // addstr(ch);
                break;
        }
        refresh();
    } while(ch != '~');
    
    endwin();
 
    return EXIT_SUCCESS;
    // puts("\033[?1049h");
    // puts("\e[2J");
    // printf("\e[n;mR");

    // tcgetattr(STDIN_FILENO, &original_settings);
    // // Modify terminal settings to disable canonical mode and local echo
    // struct termios new_settings = original_settings;
    // new_settings.c_lflag &= ~(ICANON | ECHO);
    // tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    // move_cursor(5,5);
    // get_pos(&x,&y);
    //  printf("x:%d, y:%d\n", x, y);

    //     while(1){
    //         ch = getchar();
    //         if(ch < 'a' || ch > 'z'){
    //             // move_cursor(x,y);
    //             printf("%c",ch);
    //             // y++;
    //             // move_cursor(x,y);

    //         }
    //         if( ch == 27){//the escape key
    //             getchar();//skip '['
    //             ch  = getchar();

    //             switch(ch){
    //                 case 'A':
    //                     x--;
    //                          move_cursor(x,y);   ch = "";
    //                 break;
    // ch = "";
    //                 case 'B':
    //                 x++;
    //                             move_cursor(x,y);ch = "";
    //                 break;

    //                 case 'C':
    //                 y++;
    //                             move_cursor(x,y); ch = "";
    //                 break;

    //                 case 'D':
    //                 y--;
    //                             move_cursor(x,y);
    //                             ch = "";
    //                 break;
    //                 default:
    //                             ch = "";

    //             }

    //         }

    //         printf("%c",ch);
    //         // ch = "";

    //     }

    //     tcsetattr(STDERR_FILENO, TCSANOW, &original_settings);

    //     puts("\033[?1049l");

    // return 0;
}
