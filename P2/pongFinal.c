#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000
#define PADDLE_HEIGHT 4
#define PADDLE_X 2
#define PADDLE2_X 76
#define MAX_GAMES 3

void show_welcome_screen(int max_y, int max_x) {
    clear();
    mvprintw(max_y / 4, max_x / 4, "Bienvenido al juego de Pong!");
    mvprintw(max_y / 4 + 1, max_x / 4, "Hecho por: María y Ruben");
    mvprintw(max_y / 4 + 2, max_x / 4, "Controles:");
    mvprintw(max_y / 4 + 3, max_x / 4, "w: Mover paleta izquierda arriba");
    mvprintw(max_y / 4 + 4, max_x / 4, "s: Mover paleta izquierda abajo");
    mvprintw(max_y / 4 + 5, max_x / 4, "i: Mover paleta derecha arriba");
    mvprintw(max_y / 4 + 6, max_x / 4, "k: Mover paleta derecha abajo");
    mvprintw(max_y / 4 + 7, max_x / 4, "q: Salir del juego");
    mvprintw(max_y / 4 + 9, max_x / 4, "Presiona cualquier tecla para comenzar...");

    refresh();
    getch();  // Espera una tecla para continuar
}

void show_game_result(int max_y, int max_x, int score1, int score2) {
    clear();
    mvprintw(max_y / 4, max_x / 4, "¡Juego Terminado!");
    mvprintw(max_y / 4 + 1, max_x / 4, "Marcador Final:");
    mvprintw(max_y / 4 + 2, max_x / 4, "Jugador 1: %d", score1);
    mvprintw(max_y / 4 + 3, max_x / 4, "Jugador 2: %d", score2);
    
    if (score1 > score2) {
        mvprintw(max_y / 4 + 4, max_x / 4, "¡Felicidades, Jugador 1! Has ganado.");
    } else if (score2 > score1) {
        mvprintw(max_y / 4 + 4, max_x / 4, "¡Felicidades, Jugador 2! Has ganado.");
    } else {
        mvprintw(max_y / 4 + 4, max_x / 4, "¡Es un empate!");
    }

    mvprintw(max_y / 4 + 6, max_x / 4, "Presiona 'r' para jugar de nuevo o 'q' para salir...");

    refresh();
}

void reset_game(int* score1, int* score2, int* game_count) {
    *score1 = 0;
    *score2 = 0;
    *game_count = 0;
}

int main() {
    int max_y, max_x;
    int ball_x = 10, ball_y = 10;
    int ball_dx = 1, ball_dy = 1;

    int paddle1_y = 5, paddle2_y = 5;
    int ch;
    int score1 = 0, score2 = 0;
    int game_count = 0;

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);  // Habilita las teclas especiales como las flechas

    getmaxyx(stdscr, max_y, max_x);

    // Mostrar pantalla de bienvenida
    show_welcome_screen(max_y, max_x);

    // Configurar la pantalla para que ya no sea en "nodelay" después de la pantalla de bienvenida
    nodelay(stdscr, TRUE);  // No bloquea con getch()

    while (1) {

        while (game_count < MAX_GAMES) {
            
            ball_x = max_x / 2;
            ball_y = max_y / 2;

            
            if(game_count == 0){
            ball_dx = 1;
            }
            ball_dy = 1;

          
            while (1) {
                clear();

                // Dibujar las paletas
                for (int i = 0; i < PADDLE_HEIGHT; i++) {
                    mvprintw(paddle1_y + i, PADDLE_X, "|");  // Paleta izquierda
                    mvprintw(paddle2_y + i, PADDLE2_X, "|"); // Paleta derecha
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

                if (ball_x >= max_x - 1) {
                    score1++;
                    ball_dx = -1;
                    break; // Salir del ciclo de juego
                }

                if (ball_x <= 0) {
                    score2++;
                    ball_dx = 1; 
                    break; // Salir del ciclo de juego
                }

                // Verificar colisión con la paleta izquierda
                if (ball_x == PADDLE_X + 1) {
                    if (ball_y >= paddle1_y && ball_y < paddle1_y + PADDLE_HEIGHT) {
                        ball_dx *= -1; // Rebota
                    }
                }

                // Verificar colisión con la paleta derecha
                if (ball_x == PADDLE2_X - 1) {
                    if (ball_y >= paddle2_y && ball_y < paddle2_y + PADDLE_HEIGHT) {
                        ball_dx *= -1; // Rebota
                    }
                }

                // Leer teclas (w y s para mover paleta izquierda, i y k para mover paleta derecha)
                ch = getch();
                if (ch == 'w' && paddle1_y > 0) {
                    paddle1_y--;
                } else if (ch == 's' && paddle1_y + PADDLE_HEIGHT < max_y) {
                    paddle1_y++;
                } else if (ch == 'i' && paddle2_y > 0) {
                    paddle2_y--;
                } else if (ch == 'k' && paddle2_y + PADDLE_HEIGHT < max_y) {
                    paddle2_y++;
                } else if (ch == 'q') {
                    endwin();
                    return 0; // Salir manualmente
                }
            }

    
            game_count++;

            
        }

        show_game_result(max_y, max_x, score1, score2);
 
        while (1) {
            ch = getch();
            if (ch == 'r') {
                reset_game(&score1, &score2, &game_count);
                break;
            } else if (ch == 'q') {
                break;
            }
        }

        if (ch == 'q') {
            break;
        }
    }

    endwin();
    return 0;
}

