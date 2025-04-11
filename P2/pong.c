#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000
#define PADDLE_HEIGHT 4
#define PADDLE_X 2

int main() {
    int max_y, max_x;
    int ball_x = 10, ball_y = 10;
    int ball_dx = 1, ball_dy = 1;

    int paddle_y = 5;
    int ch;

    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE); // No bloquea con getch()
    keypad(stdscr, TRUE);  // Habilita flechas

    getmaxyx(stdscr, max_y, max_x);

    while (1) {
        clear();

        // Dibujar la paleta
        for (int i = 0; i < PADDLE_HEIGHT; i++) {
            mvprintw(paddle_y + i, PADDLE_X, "|");
        }

        // Dibujar la pelota
        mvprintw(ball_y, ball_x, "o");

        refresh();
        usleep(DELAY);

        // Mover la pelota
        ball_x += ball_dx;
        ball_y += ball_dy;

        // Rebote en bordes verticales
        if (ball_y <= 0 || ball_y >= max_y - 1)
            ball_dy *= -1;

        // Rebote en el borde derecho
        if (ball_x >= max_x - 1)
            ball_dx *= -1;

        // Verificar colisión con paleta
        if (ball_x == PADDLE_X + 1) {
            if (ball_y >= paddle_y && ball_y < paddle_y + PADDLE_HEIGHT) {
                ball_dx *= -1; // Rebota
            } else if (ball_x <= 0) {
                break; // La pelota pasó la paleta: game over
            }
        }

        // Leer teclas (w y s para mover paleta)
        ch = getch();
        if (ch == 'w' && paddle_y > 0) {
            paddle_y--;
        } else if (ch == 's' && paddle_y + PADDLE_HEIGHT < max_y) {
            paddle_y++;
        } else if (ch == 'q') {
            break; // Salir manualmente
        }
    }

    endwin();
    return 0;
}
