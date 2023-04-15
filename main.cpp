#include <raylib.h>

struct Player
 {
    char* name;
    int score = 0;

    void updateScore()
    {
        score++;
    }
};

struct Ball
{
    float positionX, positionY;
    float speedX, speedY;
    float radius;

    void Draw()
    {
        DrawCircle((int) positionX, (int) positionY, radius, WHITE);
    }

    void DefaultPosition()
    {
            positionX = GetScreenWidth() / 2;
            positionY = GetScreenHeight() / 2;
            speedX = 300;
            speedY = 300;
    }
};

struct Paddle
{
    float positionX, positionY;
    float speed;
    float width, height;
    int score = 0;

    Rectangle GetRectangle()
    {
        return Rectangle { positionX - width / 2, positionY - height / 2, width, height };
    }

    void Draw()
    {
        DrawRectangleRec(GetRectangle(), WHITE);
    }
};

int main() {
    const char* winnerText = nullptr;

    InitWindow(800, 600, "Game");
    SetWindowState(FLAG_VSYNC_HINT);

    Player player1;
    player1.name = (char*)"Left Player";
    Player player2;
    player2.name = (char*)"Right Player";

    Ball ball;
    ball.radius = 5.0f;
    ball.DefaultPosition();

    Paddle leftPaddle;
    leftPaddle.positionX = 50;
    leftPaddle.positionY = GetScreenHeight() / 2 ;
    leftPaddle.width = 10.0f;
    leftPaddle.height = 100.0f;
    leftPaddle.speed = 500.0f;

    Paddle rightPaddle;
    rightPaddle.positionX = GetScreenWidth() - 50;
    rightPaddle.positionY = GetScreenHeight() / 2;
    rightPaddle.width = 10.0f;
    rightPaddle.height = 100.0f;
    rightPaddle.speed = 500.0f;

    while(!WindowShouldClose()) 
    {
        ball.positionX += ball.speedX * GetFrameTime();
        ball.positionY += ball.speedY * GetFrameTime();
        
        if (ball.positionY < 0)
        {
            ball.positionY = 0;
            ball.speedY *=-1;
        }

        if (ball.positionY > GetScreenHeight())
        {
            ball.positionY = GetScreenHeight();
            ball.speedY *= -1;
        }

        if (IsKeyDown(KEY_W))
        {
            if (leftPaddle.positionY > 0) {
                leftPaddle.positionY -= leftPaddle.speed * GetFrameTime();
            }     
        }

        if (IsKeyDown(KEY_S))
        {
            if (leftPaddle.positionY < GetScreenHeight()) {
                leftPaddle.positionY += leftPaddle.speed * GetFrameTime();
            }
        }

        if (IsKeyDown(KEY_UP))
        {
            if (rightPaddle.positionY > 0) {
                rightPaddle.positionY -= rightPaddle.speed * GetFrameTime();
            }
        }

        if (IsKeyDown(KEY_DOWN))
        {
            if (rightPaddle.positionY < GetScreenHeight())
            {
                rightPaddle.positionY += rightPaddle.speed * GetFrameTime();
            }
        }

        if (CheckCollisionCircleRec(Vector2{ ball.positionX, ball.positionY }, ball.radius,  leftPaddle.GetRectangle()))
        {
            if (ball.speedX < 0)
            {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.positionY - leftPaddle.positionY) / (leftPaddle.height / 2) * ball.speedX;
            }
        }

        if (CheckCollisionCircleRec(Vector2{ ball.positionX, ball.positionY }, ball.radius, rightPaddle.GetRectangle()))
        {
            if (ball.speedX > 0)
            {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.positionY - rightPaddle.positionY) / (rightPaddle.height / 2) * -ball.speedX;
            }
        }

        if (ball.positionX < 0)
        {
            // winnerText = "Right player wins!";
            player2.updateScore();
            ball.DefaultPosition();
        }

        if (ball.positionX > GetScreenWidth())
        {
            // winnerText = "Left player wins!";
            player1.updateScore();
            ball.DefaultPosition();
        }

        if (player1.score == 5) {
            winnerText = "Left player wins!";
        } 
        else if (player2.score == 5) {
            winnerText = "Right player wins!";
        }

        if (winnerText && IsKeyPressed(KEY_SPACE))
        {
            ball.DefaultPosition();
            winnerText = nullptr;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawFPS(10, 10);
            MeasureText(player1.name, 20);
            DrawText(TextFormat("%s: %d", player1.name, player1.score), MeasureText(player1.name, 20) + 50, 50, 20, RED);
            DrawText(TextFormat("%s: %d", player2.name, player2.score), GetScreenWidth() - MeasureText(player2.name, 20) * 2 - 50, 50, 20, RED);

// const char *text, int posX, int posY, int fontSize, Color color
            ball.Draw();        
            leftPaddle.Draw();
            rightPaddle.Draw();

            if (winnerText)
            {
                int textWidth = MeasureText(winnerText, 60);
                DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, RED);
            }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}



