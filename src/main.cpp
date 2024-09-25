#include <iostream>
#include "raylib.h"
#include <deque>
#include "raymath.h"

int cellSize = 30;
int cellCount = 25;
int offset = 75;

double lastUpdateTime = 0;

bool TimePassed(double interval) {
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for(int i = 0; i < deque.size(); i++)
    {
        if(Vector2Equals(element, deque[i]))
        {
            return true;
        }
    }
    return false;
}

class Food {
    public:
        Vector2 position;
        Texture2D texture;

        Food(std::deque<Vector2> snakeBody) {
            Image img = LoadImage("graphics/apple.png");
            texture = LoadTextureFromImage(img);
            UnloadImage(img);
            position = GenerateRandomPos(snakeBody);
        }

        ~Food() {
            UnloadTexture(texture);
        }

        void Draw() {
            // DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, DARKGREEN);
            DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
        }

        Vector2 GenerateRandomCell() {
            float x = GetRandomValue(0, cellCount - 1);
            float y = GetRandomValue(0, cellCount - 1);
            return Vector2{x,y};
        }

        Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody) {
            Vector2 position = GenerateRandomCell();
            while(ElementInDeque(position, snakeBody))
            {
                position = GenerateRandomCell();
            }
            return position;
        }
};

class Snake {
    public:
        std::deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
        Vector2 direction = {1,0};
        bool addSegment = false;

        void Draw() {
            for(int i = 0; i < body.size(); i++)
            {
                float x = body[i].x;
                float y = body[i].y;
                Rectangle rec = Rectangle{offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize};
                DrawRectangleRounded(rec, 0.5, 6, DARKGREEN);
            }
        }

        void Update() {
            body.push_front(Vector2Add(body[0], direction));
            if(addSegment)
            {
                addSegment = false;
            }
            else {
                body.pop_back();
            }
        }

        void Reset() {
            body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
            direction = {1,0};
        }
};

class Game {
    public:
        Snake snake = Snake();
        Food food = Food(snake.body);
        bool isRunning = true;
        int score = 0;
        Sound eat;
        Sound wall;

        Game() {
            InitAudioDevice();
            eat = LoadSound("sounds/eat.mp3");
            wall = LoadSound("sounds/wall.mp3");
        }

        ~Game() {
            UnloadSound(eat);
            UnloadSound(wall);
            CloseAudioDevice();
        }

        void Draw() {
            food.Draw();
            snake.Draw();
        }

        void Update() {
            if(isRunning) {
                snake.Update();
                checkCollisionWithFood();
                checkCollisionWithEdge();
                checkCollisionWithItself();
            }
        }

        void checkCollisionWithFood() {
            if(Vector2Equals(snake.body[0], food.position))
            {
                food.position = food.GenerateRandomPos(snake.body);
                snake.addSegment = true;
                score++;
                PlaySound(eat);
            }
        }

        void checkCollisionWithEdge() {
            if(snake.body[0].x == cellCount || snake.body[0].x == -1
            || snake.body[0].y == cellCount || snake.body[0].y == -1)
            {
                GameOver();
            }
        }

        void checkCollisionWithItself() {
            std::deque<Vector2> headlessSnake = snake.body;
            headlessSnake.pop_front();
            if(ElementInDeque(snake.body[0], headlessSnake))
            {
                GameOver();
            }
        }

        void GameOver() {
            snake.Reset();
            food.position = food.GenerateRandomPos(snake.body);
            isRunning = false;
            score = 0;
            PlaySound(wall);
        }
};

int main() {
    InitWindow(2*offset + cellSize * cellCount, 2*offset + cellSize * cellCount, "Snake");
    SetTargetFPS(60);

    Game game = Game();
    
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if(TimePassed(0.2))
            game.Update();

        if(IsKeyPressed(KEY_W) && game.snake.direction.y != 1)
        {
            game.snake.direction = {0,-1};
            game.isRunning = true;
        }
        if(IsKeyPressed(KEY_A) && game.snake.direction.x != 1)
        {
            game.snake.direction = {-1,0};
            game.isRunning = true;
        }
        if(IsKeyPressed(KEY_S) && game.snake.direction.y != -1)
        {
            game.snake.direction = {0,1};
            game.isRunning = true;
        }
        if(IsKeyPressed(KEY_D) && game.snake.direction.x != -1)
        {
            game.snake.direction = {1,0};
            game.isRunning = true;
        }

        ClearBackground(GREEN);
        Rectangle rec = Rectangle{(float)offset-5, (float)offset-5, (float)cellSize*cellCount+10, (float)cellSize*cellCount+10};
        DrawRectangleLinesEx(rec, 5, DARKGREEN);
        DrawText("DNS Raylib Workshop Snake", offset-5, 20, 40, DARKGREEN);
        DrawText(TextFormat("%d", game.score), offset+cellSize*cellCount-15, 20, 40, DARKGREEN);
        game.Draw();

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}