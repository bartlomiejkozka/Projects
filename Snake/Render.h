#ifndef SNAKEG_RENDER_H
#define SNAKEG_RENDER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Board.h"

class Render {
private:
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    Board *game;

public:
    Render(int width, int height) : game{new Board(width,height)}
    {
        al_init();
        al_install_keyboard();
        al_init_primitives_addon();

        display = al_create_display(width*50,height*50);
        queue = al_create_event_queue();
        timer = al_create_timer(1.0/10);

        al_register_event_source(queue, al_get_keyboard_event_source());
        al_register_event_source(queue, al_get_display_event_source(display));
        al_register_event_source(queue, al_get_timer_event_source(timer));
    }
    ~Render()
    {
        delete game;
    }

    void drawEmpty(int x, int y)
    {
        al_draw_filled_rectangle(x,y,x+50,y+50, al_map_rgb(0,0,0));
    }

    void drawSnake(int x, int y)
    {
        al_draw_filled_rectangle(x,y,x+50,y+50, al_map_rgb(96, 242, 34));
    }

    void drawApple(int x, int y)
    {
        al_draw_filled_circle(x+25, y+25, 25, al_map_rgb(255, 0, 25));
    }

    void run()
    {
        al_start_timer(timer);
        bool running = true;

        while(running)
        {
            ALLEGRO_EVENT event;
            al_wait_for_event(queue, &event);
            if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) running = false;

            ALLEGRO_KEYBOARD_STATE keyState;
            al_get_keyboard_state(&keyState);
            if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)) game->setOrientation(LEFT);
            else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) game->setOrientation(RIGHT);
            else if(al_key_down(&keyState, ALLEGRO_KEY_UP)) game->setOrientation(UP);
            else if(al_key_down(&keyState, ALLEGRO_KEY_DOWN)) game->setOrientation(DOWN);

            if(event.type == ALLEGRO_EVENT_TIMER)
            {
                if(!game->advance()) running = false;

                al_clear_to_color(al_map_rgb(0,0,0));

                int level = 0;
                for(int i=0; i<(game->getWidth()*game->getHeight()); ++i)
                {
                    if (i % game->getWidth() == 0 && i != 0) {
                        level += 1;
                    }
                    if (game->getCell(i)->getCellType() == EMPTY)
                        drawEmpty(i*50 - level*game->getWidth()*50,level*50);
                    if (game->getCell(i)->getCellType() == SNAKE)
                        drawSnake(i*50 - level*game->getWidth()*50,level*50);
                    else if (game->getCell(i)->getCellType() == APPLE)
                        drawApple(i*50 - level*game->getWidth()*50,level*50);
                }

                al_flip_display();
            }
        }
    }

    void clean()
    {
        al_destroy_display(display);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
        al_uninstall_keyboard();
    }

};

#endif
