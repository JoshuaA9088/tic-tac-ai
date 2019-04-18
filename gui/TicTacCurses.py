import curses
from curses import wrapper
import time
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

"""
1 4 7
2 5 8
3 6 9
"""

valid_move_coords = {1 : (9, 11),
                    2: (11, 11),
                    3: (13, 11),
                    4: (9, 15),
                    5: (11, 15),
                    6: (13, 15),
                    7: (9, 19),
                    8: (11, 19),
                    9: (13, 19)}

def main(stdscr):
    curses.init_color(0, 0, 0, 0)
    curses.curs_set(False)
    stdscr.clear()
    c = 1
    curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLACK)
    stdscr.addstr(10, 10, "-----------", curses.color_pair(1))
    stdscr.addstr(12, 10, "-----------", curses.color_pair(1))

    for i in range(9, 14, 1):
        stdscr.addstr(i, 13, "|", curses.color_pair(1))

    for i in range(9, 14, 1):
        stdscr.addstr(i, 17, "|", curses.color_pair(1))

    for move in valid_move_coords:
        stdscr.addstr(valid_move_coords[move][0], valid_move_coords[move][1], "X", curses.color_pair(1))
        stdscr.refresh()
        time.sleep(0.5)

    # This raises ZeroDivisionError when i == 10.
    # for i in range(0, 11):
    #     v = 10
    #     stdscr.addstr(i, 0, '10 divided by {} is {}'.format(v, 10/v))

    stdscr.getkey()

wrapper(main)
