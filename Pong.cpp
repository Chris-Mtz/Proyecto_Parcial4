#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

const float paddleWidth = 10.f, paddleHeight = 100.f, ballRadius = 10.f;
const float paddleSpeed = 600.f, ballSpeedIncrement = 1.1f;
const sf::Vector2f windowSize(800, 600);
const sf::Vector2f paddleLeftPosition(30.f, windowSize.y / 2 - paddleHeight / 2);
const sf::Vector2f paddleRightPosition(windowSize.x - 30.f - paddleWidth, windowSize.y / 2 - paddleHeight / 2);
sf::Vector2f ballVelocity(300.f, 300.f);

void resetBall(sf::CircleShape& ball) {
    ball.setPosition(windowSize.x / 2 - ballRadius, windowSize.y / 2 - ballRadius);
    ballVelocity = {300.f, 300.f};
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Pong Game");
    window.setFramerateLimit(60);

    sf::RectangleShape paddleLeft(sf::Vector2f(paddleWidth, paddleHeight));
    sf::RectangleShape paddleRight(sf::Vector2f(paddleWidth, paddleHeight));
    sf::CircleShape ball(ballRadius);

    paddleLeft.setFillColor(sf::Color::Cyan);  // Color para la paleta izquierda
    paddleRight.setFillColor(sf::Color::Green);  // Color para la paleta derecha
    ball.setFillColor(sf::Color::White);

    paddleLeft.setPosition(paddleLeftPosition);
    paddleRight.setPosition(paddleRightPosition);
    resetBall(ball);

    sf::Font font;
    if (!font.loadFromFile("../OpenSans-Regular.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    sf::Text scoreTextLeft, scoreTextRight;
    scoreTextLeft.setFont(font);
    scoreTextLeft.setCharacterSize(30);
    scoreTextLeft.setFillColor(sf::Color::Cyan);  // Color para el marcador izquierdo
    scoreTextLeft.setPosition(windowSize.x / 4, 20.f);

    scoreTextRight.setFont(font);
    scoreTextRight.setCharacterSize(30);
    scoreTextRight.setFillColor(sf::Color::Green);  // Color para el marcador derecho
    scoreTextRight.setPosition(3 * windowSize.x / 4, 20.f);

    int scoreLeft = 0, scoreRight = 0;

    sf::Clock clock;

    // Líneas punteadas del centro
    std::vector<sf::RectangleShape> centerLines;
    for (int i = 0; i < windowSize.y / 20; i++) {
        sf::RectangleShape line(sf::Vector2f(2, 10));
        line.setFillColor(sf::Color::White);
        line.setPosition(windowSize.x / 2, i * 20 + 10);
        centerLines.push_back(line);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // Movimiento de las paletas
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddleLeft.getPosition().y > 0)
            paddleLeft.move(0.f, -paddleSpeed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddleLeft.getPosition().y + paddleHeight < windowSize.y)
            paddleLeft.move(0.f, paddleSpeed * deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddleRight.getPosition().y > 0)
            paddleRight.move(0.f, -paddleSpeed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddleRight.getPosition().y + paddleHeight < windowSize.y)
            paddleRight.move(0.f, paddleSpeed * deltaTime);

        // Movimiento de la pelota
        ball.move(ballVelocity * deltaTime);

        // Rebote de la pelota
        if (ball.getPosition().y <= 0 || ball.getPosition().y + 2 * ballRadius >= windowSize.y)
            ballVelocity.y = -ballVelocity.y;

        if (ball.getGlobalBounds().intersects(paddleLeft.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(paddleRight.getGlobalBounds())) {
            ballVelocity.x = -ballVelocity.x * ballSpeedIncrement;
            ballVelocity.y *= ballSpeedIncrement;
        }

        // Puntuación
        if (ball.getPosition().x <= 0) {
            scoreRight++;
            resetBall(ball);
        }
        if (ball.getPosition().x + 2 * ballRadius >= windowSize.x) {
            scoreLeft++;
            resetBall(ball);
        }

        // Actualizar el texto de puntuación
        scoreTextLeft.setString(std::to_string(scoreLeft));
        scoreTextRight.setString(std::to_string(scoreRight));


        window.clear();
        window.draw(paddleLeft);
        window.draw(paddleRight);
        window.draw(ball);
        for (const auto& line : centerLines)
            window.draw(line);
        window.draw(scoreTextLeft);
        window.draw(scoreTextRight);
        window.display();
    }

    return 0;
}