// tetris(final).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <time.h>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;


const int M = 20;
const int N = 10; 

int field[M][N] = { 0 };

struct Point
{
    int x, y;
} a[4], b[4];


int figures[7][4] =
{
    1,3,5,7,
    2,4,5,7,
    3,5,4,6,
    3,5,4,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
}; 

bool check()
{
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
        else if (field[a[i].y][a[i].x]) return 0;

    return 1;
};


int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(320, 480), "The Game!");

    Texture t1, t2, t3;
    t1.loadFromFile("tiles.png");
   

    Sprite s(t1), background(t2), frame(t3);

    int dx = 0; bool rotate = 0; int colorNum = 1;
    float timer = 0, delay = 0.3;

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Up) rotate = true;
                else if (e.key.code == Keyboard::Left) dx = -1;
                else if (e.key.code == Keyboard::Right) dx = 1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.15;

        //// <- Move -> ///
        for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
        if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

        //////Rotate//////
        if (rotate)
        {
            Point p = a[1]; //center of rotation
            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
        }

        ///////Tick//////
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }

            if (!check())
            {
                for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;

                colorNum = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0; i < 4; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer = 0;
        }

        ///////check lines//////////
        int k = M - 1;
        for (int i = M - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < N; j++)
            {
                if (field[i][j]) count++;
                field[k][j] = field[i][j];
            }
            if (count < N) k--;
        }

        dx = 0; rotate = 0; delay = 0.3;

        /////////draw//////////
        window.clear(Color::Transparent);
        window.draw(background);

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                if (field[i][j] == 0) continue;
                s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                s.setPosition(j * 18, i * 18);
                s.move(28, 31); //offset
                window.draw(s);
            }

        for (int i = 0; i < 4; i++)
        {
            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            s.setPosition(a[i].x * 18, a[i].y * 18);
            s.move(28, 31); //offset
            window.draw(s);
        }

        window.draw(frame);
        window.display();
    }

    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
