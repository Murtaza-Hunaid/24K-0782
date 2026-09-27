#pragma comment(lib, "winmm.lib")
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <mmsystem.h>
#include "freeze.h"

using namespace std;

// ======================== ASM FUNCTIONS ========================
extern "C" int  __cdecl gameManager_stateChanger(int currentState, int command);
extern "C" void __stdcall gameManager_writeToFile(const char* buffer, int length);
extern "C" void __stdcall gameManager_writeScore(const char* buffer, int length, int score);
extern "C" int  __cdecl gameManager_getRandom(int maxValue);
extern "C" int  __stdcall gameManager_updateScores();
extern "C" int  __stdcall gameManager_getScores();
extern "C" void __stdcall gameManager_resetScores();
extern "C" void __stdcall gameManager_playGameMusic();
extern "C" void __stdcall gameManager_stopGameMusic();
extern "C" void __stdcall gameManager_playMenuMusic();
extern "C" void __stdcall gameManager_stopMenuMusic();
extern "C" int __stdcall gameManager_checkCollision(
    int birdX, int birdY, int birdW, int birdH,
    int pipeX, int pipeTopY, int pipeBottomY, int pipeW
);
extern "C" void __stdcall gameManager_playFlapSound();
extern "C" void __stdcall gameManager_playScoreSound();

// ======================== GAME STATES ========================
enum GameStates { MENU = 0, GAMEPLAY = 1, HIGHSCORE = 2, CREDITS = 3, EXIT = 4, GAMEOVER = 5 };

// ======================== PIPE STRUCT ========================
struct Pipe {
    sf::Sprite topPipe;
    sf::Sprite bottomPipe;
    float x;
    float gapY;
    bool passed = false; // used for scoring
};

int main() {
    // ======================== WINDOW SETUP ========================
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Flappy Bird ASM - Highscore", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    sf::Vector2u windowSize = window.getSize();
    int liveScore = 0;
    int scoreToSave = 0;

    // ======================== LOAD FONT ========================
    sf::Font font;
    if (!font.loadFromFile("assets/Fonts/shlop-rg.otf")) {
        cerr << "Cannot load font\n";
        return -1;
    }

    // ======================== LOAD TEXTURES ========================
    sf::Texture birdTex, pipeTex;
    if (!birdTex.loadFromFile("assets/images/bird1.png") ||
        !pipeTex.loadFromFile("assets/images/pipe.png")) {
        cerr << "Cannot load textures\n";
        return -1;
    }

    // ======================== MENU BUTTONS ========================
    float buttonWidth = 250.f, buttonHeight = 60.f, spacing = 25.f;
    int n = 4;
    float totalH = n * buttonHeight + (n - 1) * spacing;
    float startY = (windowSize.y - totalH) / 2.f;
    float startX = (windowSize.x - buttonWidth) / 2.f;

    sf::RectangleShape playButton({ buttonWidth, buttonHeight });
    sf::RectangleShape highScoreButton({ buttonWidth, buttonHeight });
    sf::RectangleShape creditsButton({ buttonWidth, buttonHeight });
    sf::RectangleShape exitButton({ buttonWidth, buttonHeight });

    playButton.setPosition(startX, startY);
    highScoreButton.setPosition(startX, startY + (buttonHeight + spacing) * 1);
    creditsButton.setPosition(startX, startY + (buttonHeight + spacing) * 2);
    exitButton.setPosition(startX, startY + (buttonHeight + spacing) * 3);

    playButton.setFillColor(sf::Color(40, 40, 40));
    highScoreButton.setFillColor(sf::Color(40, 40, 40));
    creditsButton.setFillColor(sf::Color(40, 40, 40));
    exitButton.setFillColor(sf::Color(40, 40, 40));

    sf::Text playText("PLAY", font, 28), highScoreText("HIGHSCORE", font, 28),
        creditsText("CREDITS", font, 28), exitText("EXIT", font, 28);

    auto centerText = [](sf::Text& t, sf::RectangleShape& b) {
        sf::FloatRect tb = t.getLocalBounds();
        t.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
        t.setPosition(b.getPosition().x + b.getSize().x / 2.f,
            b.getPosition().y + b.getSize().y / 2.f);
        };

    centerText(playText, playButton);
    centerText(highScoreText, highScoreButton);
    centerText(creditsText, creditsButton);
    centerText(exitText, exitButton);

    sf::Text title("FLAPPY ASM MENU", font, 40);
    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    title.setPosition(windowSize.x / 2.f, startY - 80.f);

    // ======================== BIRD SETUP (origin centered for rotation) ========================
    sf::Sprite bird(birdTex);

    // Set scale first, then set origin to local center
    float birdScale = windowSize.y / 400.f;
    bird.setScale(birdScale, birdScale);

    // use local bounds to compute center origin (unscaled), set origin to center
    sf::FloatRect local = bird.getLocalBounds();
    bird.setOrigin(local.left + local.width / 2.f, local.top + local.height / 2.f);

    // Now position bird with center coordinates (we want the bird at x = windowSize.x/4, y = center)
    bird.setPosition(windowSize.x / 4.f, windowSize.y / 2.f);

    float birdVelocity = 0.f;
    const float gravity = 0.5f;
    const float flapPower = -10.f;

    // rotation variables: angle in degrees; tilt up on flap, tilt down gradually when falling
    float birdAngle = 0.f;                // current displayed rotation angle
    const float flapTilt = -25.f;         // immediate tilt when flapping (degrees)
    const float maxDownTilt = 80.f;       // max downward tilt
    const float tiltSpeed = 2.5f;         // degrees per frame when settling downward

    vector<Pipe> pipes;
    const float pipeGap = windowSize.y / 4.f;
    const float pipeSpacing = windowSize.x / 2.f;
    const float pipeSpeed = 6.f;

    sf::Text scoreText("", font, 48);
    scoreText.setFillColor(sf::Color::White);

    string playerName;
    bool askedName = false;
    bool gameplayStarted = false;

    GameStates currentState = MENU;
    int command = 0;

    // ======================== START MENU MUSIC ========================
    gameManager_playMenuMusic();

    // ======================== GAME LOOP ========================
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) command = 5;
                if (currentState == GAMEPLAY && event.key.code == sf::Keyboard::Space) {
                    birdVelocity = flapPower;
                    // tilt the bird up immediately
                    birdAngle = flapTilt;
                    gameManager_playFlapSound();
                }
                if (currentState == GAMEOVER && event.key.code == sf::Keyboard::Space) {
                    currentState = MENU;
                    command = 5;
                    gameManager_playMenuMusic();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mp = sf::Mouse::getPosition(window);
                if (currentState == MENU) {
                    if (playButton.getGlobalBounds().contains((float)mp.x, (float)mp.y)) {
                        command = 1;
                        gameManager_stopMenuMusic();
                        gameManager_playGameMusic();
                    }
                    else if (highScoreButton.getGlobalBounds().contains((float)mp.x, (float)mp.y)) command = 2;
                    else if (creditsButton.getGlobalBounds().contains((float)mp.x, (float)mp.y)) command = 3;
                    else if (exitButton.getGlobalBounds().contains((float)mp.x, (float)mp.y)) command = 4;
                }
            }
        }

        // ======================== STATE MANAGEMENT ========================
        int next = gameManager_stateChanger(static_cast<int>(currentState), command);
        if (next != static_cast<int>(currentState)) {
            currentState = static_cast<GameStates>(next);

            if (currentState == MENU) {
                gameManager_stopGameMusic();
                gameManager_playMenuMusic();
                gameplayStarted = false;
                askedName = false;
                pipes.clear();
            }
            else if (currentState == GAMEPLAY) {
                gameManager_stopMenuMusic();
                gameManager_playGameMusic();
                gameManager_resetScores();
                gameplayStarted = true;
                askedName = false;
                pipes.clear();
                // reposition bird center
                bird.setPosition(windowSize.x / 4.f, windowSize.y / 2.f);
                birdVelocity = 0.f;
                birdAngle = 0.f;
            }
        }
        command = 0;

        window.clear(sf::Color(20, 24, 30));

        // ======================== MENU ========================
        if (currentState == MENU) {
            window.draw(title);
            window.draw(playButton); window.draw(playText);
            window.draw(highScoreButton); window.draw(highScoreText);
            window.draw(creditsButton); window.draw(creditsText);
            window.draw(exitButton); window.draw(exitText);
        }

        // ======================== GAMEPLAY ========================
        else if (currentState == GAMEPLAY) {
            // Ask player name once
            if (!askedName) {
                HWND hConsole = GetConsoleWindow();
                if (hConsole) ShowWindow(hConsole, SW_SHOW);

                cout << "Enter Your Name: " << flush;
                string tmp;
                getline(cin, tmp);
                if (tmp.empty()) tmp = "Player";
                playerName = tmp;

                if (hConsole) ShowWindow(hConsole, SW_HIDE);
                HWND hWnd = window.getSystemHandle();
                SetForegroundWindow(hWnd);
                SetActiveWindow(hWnd);
                BringWindowToTop(hWnd);
                SetFocus(hWnd);
                Sleep(50);
                window.setActive(true);
                window.requestFocus();

                askedName = true;
            }

            // Initialize pipes if empty
            if (pipes.empty()) {
                for (int i = 0; i < 5; ++i) {
                    Pipe p;
                    p.x = (float)windowSize.x + i * pipeSpacing;
                    float minY = 100.f;
                    float maxY = (float)windowSize.y - pipeGap - 100.f;
                    int range = (int)(maxY - minY);
                    if (range < 1) range = 1;
                    p.gapY = minY + gameManager_getRandom(range);

                    p.topPipe.setTexture(pipeTex);
                    p.bottomPipe.setTexture(pipeTex);
                    float pipeScaleX = windowSize.y / 200.f;
                    p.topPipe.setScale(pipeScaleX, -pipeScaleX);
                    p.bottomPipe.setScale(pipeScaleX, pipeScaleX);
                    p.topPipe.setPosition(p.x, p.gapY);
                    p.bottomPipe.setPosition(p.x, p.gapY + pipeGap);
                    pipes.push_back(p);
                }
            }

            float pipeWidth = pipeTex.getSize().x * (windowSize.y / 200.f);

            // Move pipes, update score
            for (auto& p : pipes) {
                p.x -= pipeSpeed;
                p.topPipe.setPosition(p.x, p.gapY);
                p.bottomPipe.setPosition(p.x, p.gapY + pipeGap);
            }

            // Now compute bird global bounds (AABB) for scoring/collision
            sf::FloatRect birdGlobal = bird.getGlobalBounds(); // left/top represent AABB left/top
            float birdCenterX = bird.getPosition().x;
            float birdCenterY = bird.getPosition().y;

            // Score when pipe fully passed the bird's left edge
            for (auto& p : pipes) {
                if (!p.passed && (p.x + pipeWidth) < birdGlobal.left) {
                    p.passed = true;
                    liveScore = gameManager_updateScores();
                    gameManager_playScoreSound();
                }
                if (p.x + pipeWidth < 0.f) {
                    p.x = (float)windowSize.x;
                    p.passed = false;
                    float minY = 100.f;
                    float maxY = (float)windowSize.y - pipeGap - 100.f;
                    int range = (int)(maxY - minY);
                    if (range < 1) range = 1;
                    p.gapY = minY + gameManager_getRandom(range);
                }
            }

            // Bird physics
            birdVelocity += gravity;
            bird.move(0.f, birdVelocity);

            // Update birdAngle: if birdAngle < maxDownTilt, slowly increase toward down-tilt
            if (birdAngle < maxDownTilt) {
                birdAngle += tiltSpeed;
                if (birdAngle > maxDownTilt) birdAngle = maxDownTilt;
            }

            // Apply rotation to sprite
            bird.setRotation(birdAngle);

            // Collision detection using ASM (pass AABB coords)
            bool collision = false;
            // Recompute bird global bounds after movement/rotation
            birdGlobal = bird.getGlobalBounds();
            for (auto& p : pipes) {
                int pipeTopY = (int)p.gapY;
                int pipeBottomY = (int)(p.gapY + pipeGap);
                int hit = gameManager_checkCollision(
                    (int)birdGlobal.left,
                    (int)birdGlobal.top,
                    (int)birdGlobal.width,
                    (int)birdGlobal.height,
                    (int)p.x,
                    pipeTopY,
                    pipeBottomY,
                    (int)pipeWidth
                );
                if (hit != 0) { collision = true; break; }
            }

            if (bird.getPosition().y + birdGlobal.height / 2.0f >= windowSize.y || collision) {
                if (playerName.empty()) playerName = "Player";
                gameManager_stopGameMusic();
                ScoreManager::saveScore(playerName, liveScore);

                command = 6;
                currentState = static_cast<GameStates>(
                    gameManager_stateChanger(static_cast<int>(currentState), command)
                    );

                pipes.clear();
                // reset bird center
                bird.setPosition(windowSize.x / 4.f, windowSize.y / 2.f);
                birdVelocity = 0.f;
                gameplayStarted = false;
                askedName = false;
                scoreToSave = liveScore;
                liveScore = 0;
                gameManager_resetScores();
                birdAngle = 0.f;
            }

            // Draw bird and pipes
            window.draw(bird);
            for (auto& p : pipes) {
                window.draw(p.topPipe);
                window.draw(p.bottomPipe);
            }

            // Draw score
            scoreText.setString(to_string(liveScore));
            sf::FloatRect sb = scoreText.getLocalBounds();
            scoreText.setOrigin(sb.left + sb.width / 2.f, sb.top + sb.height / 2.f);
            scoreText.setPosition(windowSize.x / 2.f, 40.f);
            window.draw(scoreText);
        }

        // ======================== GAMEOVER ========================
        else if (currentState == GAMEOVER) {
            sf::Text go("GAME OVER (ESC to go back)", font, 48);
            go.setPosition(windowSize.x / 4.f, windowSize.y / 2.f - 30.f);
            window.draw(go);

            sf::Text fs(("Score: " + to_string(scoreToSave)), font, 40);
            fs.setPosition(windowSize.x / 2.f - 60.f, windowSize.y / 2.f + 40.f);
            window.draw(fs);
        }

        // ======================== HIGHSCORE ========================
        else if (currentState == HIGHSCORE) {
            sf::Text hsTitle("HIGHSCORES (ESC to go back)", font, 32);
            hsTitle.setPosition(200, 50);
            window.draw(hsTitle);

            auto scores = ScoreManager::loadScores();
            float y = 120.f;
            for (auto& entry : scores) {
                sf::Text t(entry.first + " : " + std::to_string(entry.second), font, 28);
                t.setPosition(200, y);
                window.draw(t);
                y += 40.f;
            }
        }

        // ======================== CREDITS ========================
        else if (currentState == CREDITS) {
            sf::Text cr("CREDITS SCREEN (ESC to go back)", font, 28);
            cr.setPosition(200, 200);
            window.draw(cr);
        }

        // ======================== EXIT ========================
        else if (currentState == EXIT) {
            window.close();
        }

        window.display();
    }

    return 0;
}
