import curses
from curses import wrapper
"""
Note that the coordinate system used in curses is unusual.
Coordinates are always passed in the order y,x, and the top-left corner of a window is coordinate (0,0). This
breaks the normal convention for handling coordinates where the x coordinate comes first.
"""

"""
Attribute	Description
A_BLINK	Blinking text
A_BOLD	Extra bright or bold text
A_DIM	Half bright text
A_REVERSE	Reverse-video text
A_STANDOUT	The best highlighting mode available
A_UNDERLINE	Underlined text
"""

"""
Legal coordinates will then extend from (0,0) to (curses.LINES - 1, curses.COLS - 1).
"""

def main(stdscr):
    # Clear screen
    stdscr.clear()
    # stdscr.addstr(int(curses.LINES / 2), int(curses.COLS / 2), "CURRENT MODE: TYPING MODE", curses.A_UNDERLINE)
    c = 4
    stdscr.addstr(10, 10, "-----------", curses.color_pair(c))
    stdscr.addstr(12, 10, "-----------", curses.color_pair(c))

    for i in range(9, 14, 1):
        stdscr.addstr(i, 13, "|", curses.color_pair(c))

    for i in range(9, 14, 1):
        stdscr.addstr(i, 17, "|", curses.color_pair(c))

    # This raises ZeroDivisionError when i == 10.
    # for i in range(0, 11):
    #     v = 10
    #     stdscr.addstr(i, 0, '10 divided by {} is {}'.format(v, 10/v))

    stdscr.refresh()
    stdscr.getkey()

wrapper(main)
