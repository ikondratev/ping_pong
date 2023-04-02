#include <raylib.h>

struct Ball
{
    float positionX, positionY;
    float speedX, speedY;
    float radius;

    void Draw()
    {
        DrawCircle((int) positionX, (int) positionY, radius, WHITE);
    }
};

struct Paddle
{
    float positionX, positionY;
    float speed;
    float width, height;

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

    Ball ball;
    ball.positionX = GetScreenWidth() / 2.0f;
    ball.positionY = GetScreenHeight() / 2.0f;
    ball.radius = 5.0f;
    ball.speedX = 100.0f;
    ball.speedY = 300.0f;

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
            leftPaddle.positionY -= leftPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_S))
        {
            leftPaddle.positionY += leftPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_UP))
        {
            rightPaddle.positionY -= rightPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_DOWN))
        {
            rightPaddle.positionY += rightPaddle.speed * GetFrameTime();
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
            winnerText = "Right player wins!";
        }

        if (ball.positionX > GetScreenWidth())
        {
            winnerText = "Left player wins!";
        }

        if (winnerText && IsKeyPressed(KEY_SPACE))
        {
            ball.positionX = GetScreenWidth() / 2;
            ball.positionY = GetScreenHeight() / 2;
            ball.speedX = 300;
            ball.speedY = 300;
            winnerText = nullptr;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            ball.Draw();
            leftPaddle.Draw();
            rightPaddle.Draw();

            if (winnerText)
            {
                int textWidth = MeasureText(winnerText, 60);
                DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, RED);
            }

            DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}



