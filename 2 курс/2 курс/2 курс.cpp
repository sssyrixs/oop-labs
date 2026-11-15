#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

enum GameState {
    SELECT_X,
    SELECT_Y,
    FLYING,
    RESULT
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Darts Game");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("forest.png")) {}

    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Vector2u size = backgroundTexture.getSize();
    backgroundSprite.setScale(sf::Vector2f(
        800.0f / (float)size.x,
        600.0f / (float)size.y
    ));
    const float PI = 3.14159f;
    const int NUM_SECTORS = 20;

    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf")) {
        // Шрифт не загружен
    }

    // =============================================
    //  ПЕРЕМЕННЫЕ ИГРЫ
    // =============================================
    GameState state = SELECT_X;
    float targetX = 400, targetY = 300;
    float selectorX = 200.0f, selectorY = 100.0f;
    float speedX = 2.5f, speedY = 2.5f;
    float dartProgress = 0.0f;
    float dartSpeed = 0.035f;
    int score = 0;

    // =============================================
    //  ПЛАШКИ
    // =============================================
    sf::RectangleShape leftBar(sf::Vector2f(30.0f, 400.0f));
    leftBar.setFillColor(sf::Color(255, 255, 255, 150));
    leftBar.setPosition({ 20.0f, 100.0f });

    sf::RectangleShape bottomBar(sf::Vector2f(400.0f, 30.0f));
    bottomBar.setFillColor(sf::Color(255, 255, 255, 150));
    bottomBar.setPosition({ 198.0f, 550.0f });

    // =============================================
    //  ПОЛЗУНКИ (ТОНКИЕ)
    // =============================================
    sf::RectangleShape sliderX(sf::Vector2f(4.0f, 16.0f));
    sliderX.setFillColor(sf::Color::Red);
    sliderX.setPosition({ 200.0f, 557.0f });

    sf::RectangleShape sliderY(sf::Vector2f(16.0f, 4.0f));
    sliderY.setFillColor(sf::Color::Blue);
    sliderY.setPosition({ 27.0f, 260.0f });

    // =============================================
    //  ДРОТИК
    // =============================================
    sf::RectangleShape dartBody(sf::Vector2f(3.0f, 25.0f));
    dartBody.setFillColor(sf::Color(180, 180, 180));
    dartBody.setOrigin({ 1.5f, 0.0f });

    sf::ConvexShape dartTail;
    dartTail.setPointCount(3);
    dartTail.setPoint(0, { 0.0f, 25.0f });
    dartTail.setPoint(1, { -10.0f, 38.0f });
    dartTail.setPoint(2, { 10.0f, 38.0f });
    dartTail.setFillColor(sf::Color(200, 50, 50));
    dartTail.setOrigin({ 0.0f, 25.0f });

    // Дротик в руке
    sf::RectangleShape handDartBody(sf::Vector2f(3.0f, 25.0f));
    handDartBody.setFillColor(sf::Color(180, 180, 180));
    handDartBody.setOrigin({ 1.5f, 0.0f });

    sf::ConvexShape handDartTail;
    handDartTail.setPointCount(3);
    handDartTail.setPoint(0, { 0.0f, 25.0f });
    handDartTail.setPoint(1, { -10.0f, 38.0f });
    handDartTail.setPoint(2, { 10.0f, 38.0f });
    handDartTail.setFillColor(sf::Color(200, 50, 50));
    handDartTail.setOrigin({ 0.0f, 25.0f });

    // =============================================
    //  ТЕКСТ
    // =============================================
    sf::Text hintText(font);
    hintText.setCharacterSize(18);
    hintText.setFillColor(sf::Color::White);
    hintText.setPosition({ 20, 20 });
    hintText.setString("Select X (use bottom bar)");

    sf::Text scoreText(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition({ 20, 50 });

    // =============================================
    //  СЕКТОРА
    // =============================================
    int sectorNumbers[NUM_SECTORS] = {
        20, 1, 18, 4, 13, 6, 10, 15, 2, 17,
        3, 19, 7, 16, 8, 11, 14, 9, 12, 5
    };

    // =============================================
    //  ГЛАВНЫЙ ЦИКЛ
    // =============================================
    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
                {
                    if (state == SELECT_X) {
                        state = SELECT_Y;
                        hintText.setString("Select Y (use left bar)");
                    }
                    else if (state == SELECT_Y) {
                        state = FLYING;
                        dartProgress = 0.0f;
                        hintText.setString("Flying!");
                    }
                    else if (state == RESULT) {
                        state = SELECT_X;
                        hintText.setString("Select X (use bottom bar)");
                        scoreText.setString("");
                    }
                }
            }
        }

        // =============================================
        //  ЛОГИКА (ПРЯМАЯ ПРИВЯЗКА — БЕЗ ПЕРЕСЧЕТА)
        // =============================================
        if (state == SELECT_X) {
            selectorX += speedX;
            if (selectorX > 596) speedX = -speedX;
            if (selectorX < 200) speedX = -speedX;

            // ПРЯМАЯ ПРИВЯЗКА: позиция ползунка = координата X
            targetX = selectorX;

            sliderX.setPosition({ selectorX, 557.0f });
        }
        else if (state == SELECT_Y) {
            selectorY += speedY;
            if (selectorY > 496) speedY = -speedY;
            if (selectorY < 100) speedY = -speedY;

            // ПРЯМАЯ ПРИВЯЗКА: позиция ползунка = координата Y
            targetY = selectorY;

            sliderY.setPosition({ 27.0f, selectorY });
        }
        else if (state == FLYING) {
            dartProgress += dartSpeed;
            if (dartProgress >= 1.0f) {
                dartProgress = 1.0f;
                state = RESULT;

                // =============================================
                //  РАСЧЕТ ОЧКОВ
                // =============================================
                float dx = targetX - 400.0f, dy = targetY - 300.0f;
                float dist = std::sqrt(dx * dx + dy * dy);

                if (dist > 200.0f) {
                    score = 0;
                    scoreText.setString("MISS! 0");
                }
                else {
                    float angle = atan2(dy, dx) * 180.0f / PI;
                    if (angle < 0) angle += 360.0f;
                    angle += 9.0f;
                    if (angle >= 360.0f) angle -= 360.0f;
                    int sectorIndex = (int)(angle / 18.0f);
                    int sectorScore = sectorNumbers[sectorIndex];

                    int multiplier = 1;
                    if (dist >= 170.0f && dist <= 200.0f) multiplier = 2;
                    else if (dist >= 100.0f && dist <= 120.0f) multiplier = 3;

                    if (dist <= 15.0f) {
                        score = 50;
                        scoreText.setString("BULLSEYE! +50");
                    }
                    else if (dist <= 40.0f) {
                        score = 25;
                        scoreText.setString("INNER BULL! +25");
                    }
                    else {
                        score = sectorScore * multiplier;
                        scoreText.setString("Sector " + std::to_string(sectorScore) +
                            " x" + std::to_string(multiplier) +
                            " = " + std::to_string(score));
                    }
                }
                hintText.setString("Click to continue");
            }
            else {
                float t = dartProgress;
                float startX = 700.0f, startY = 550.0f;
                float x = startX + (targetX - startX) * t;
                float y = startY + (targetY - startY) * t;
                float arc = -120.0f * t * (1.0f - t);
                y += arc;

                dartBody.setPosition({ x, y });
                dartTail.setPosition({ x, y });

                float angle = std::atan2(targetY - startY, targetX - startX);
                dartBody.setRotation(sf::degrees(angle * 180.0f / PI + 90.0f));
                dartTail.setRotation(sf::degrees(angle * 180.0f / PI + 90.0f));
            }
        }

        // =============================================
        //  ОТРИСОВКА
        // =============================================
        window.clear();
        if (backgroundTexture.getSize().x > 0) {
            window.draw(backgroundSprite);   // Рисуем картинку
        }
        else {
            window.clear(sf::Color(50, 150, 50));  // Если картинки нет — зелёный
        }

        // ----- МИШЕНЬ -----
        const float bullRadius = 15.0f;
        const float doubleRingInner = 170.0f;
        const float doubleRingOuter = 200.0f;
        const float tripleInner = 100.0f;
        const float tripleOuter = 120.0f;

        sf::Color colors[2] = { sf::Color(30, 30, 30), sf::Color(240, 240, 240) };
        sf::Color redColor = sf::Color(200, 30, 30);
        sf::Color greenColor = sf::Color(30, 180, 30);

        for (int i = 0; i < NUM_SECTORS; i++) {
            float startAngle = i * 360.0f / NUM_SECTORS - 9.0f;
            float endAngle = (i + 1) * 360.0f / NUM_SECTORS - 9.0f;
            float a1 = startAngle * PI / 180.0f;
            float a2 = endAngle * PI / 180.0f;

            sf::ConvexShape sector;
            sector.setPointCount(4);
            sector.setPoint(0, { 400.0f + bullRadius * cos(a1), 300.0f + bullRadius * sin(a1) });
            sector.setPoint(1, { 400.0f + tripleInner * cos(a1), 300.0f + tripleInner * sin(a1) });
            sector.setPoint(2, { 400.0f + tripleInner * cos(a2), 300.0f + tripleInner * sin(a2) });
            sector.setPoint(3, { 400.0f + bullRadius * cos(a2), 300.0f + bullRadius * sin(a2) });
            sector.setFillColor(colors[i % 2]);
            window.draw(sector);

            sf::ConvexShape sectorOuter;
            sectorOuter.setPointCount(4);
            sectorOuter.setPoint(0, { 400.0f + tripleOuter * cos(a1), 300.0f + tripleOuter * sin(a1) });
            sectorOuter.setPoint(1, { 400.0f + doubleRingOuter * cos(a1), 300.0f + doubleRingOuter * sin(a1) });
            sectorOuter.setPoint(2, { 400.0f + doubleRingOuter * cos(a2), 300.0f + doubleRingOuter * sin(a2) });
            sectorOuter.setPoint(3, { 400.0f + tripleOuter * cos(a2), 300.0f + tripleOuter * sin(a2) });
            sectorOuter.setFillColor(colors[i % 2]);
            window.draw(sectorOuter);

            sf::ConvexShape doubleRing;
            doubleRing.setPointCount(4);
            doubleRing.setPoint(0, { 400.0f + doubleRingInner * cos(a1), 300.0f + doubleRingInner * sin(a1) });
            doubleRing.setPoint(1, { 400.0f + doubleRingOuter * cos(a1), 300.0f + doubleRingOuter * sin(a1) });
            doubleRing.setPoint(2, { 400.0f + doubleRingOuter * cos(a2), 300.0f + doubleRingOuter * sin(a2) });
            doubleRing.setPoint(3, { 400.0f + doubleRingInner * cos(a2), 300.0f + doubleRingInner * sin(a2) });
            doubleRing.setFillColor((i % 2 == 0) ? redColor : greenColor);
            window.draw(doubleRing);

            sf::ConvexShape tripleRing;
            tripleRing.setPointCount(4);
            tripleRing.setPoint(0, { 400.0f + tripleInner * cos(a1), 300.0f + tripleInner * sin(a1) });
            tripleRing.setPoint(1, { 400.0f + tripleOuter * cos(a1), 300.0f + tripleOuter * sin(a1) });
            tripleRing.setPoint(2, { 400.0f + tripleOuter * cos(a2), 300.0f + tripleOuter * sin(a2) });
            tripleRing.setPoint(3, { 400.0f + tripleInner * cos(a2), 300.0f + tripleInner * sin(a2) });
            tripleRing.setFillColor((i % 2 == 0) ? greenColor : redColor);
            window.draw(tripleRing);
        }

        // Яблочко
        sf::CircleShape bullseye(bullRadius);
        bullseye.setFillColor(sf::Color::Red);
        bullseye.setPosition({ 400.0f - bullRadius, 300.0f - bullRadius });
        window.draw(bullseye);

        sf::CircleShape innerBull(8.0f);
        innerBull.setFillColor(sf::Color(50, 200, 50));
        innerBull.setPosition({ 400.0f - 8.0f, 300.0f - 8.0f });
        window.draw(innerBull);

        // Цифры
        for (int i = 0; i < NUM_SECTORS; i++) {
            float centerAngle = (i * 360.0f / NUM_SECTORS) * PI / 180.0f;
            float textRadius = 190.0f;
            float x = 400.0f + textRadius * cos(centerAngle);
            float y = 300.0f + textRadius * sin(centerAngle);

            sf::Text numText(font);
            numText.setString(std::to_string(sectorNumbers[i]));
            numText.setCharacterSize(18);
            numText.setFillColor(sf::Color::White);
            sf::FloatRect bounds = numText.getLocalBounds();
            numText.setPosition({ x - bounds.size.x / 2.0f, y - bounds.size.y / 2.0f });
            window.draw(numText);
        }

        // ----- ПОДСТАВКА -----
        sf::RectangleShape stand(sf::Vector2f(300.0f, 15.0f));
        stand.setFillColor(sf::Color(139, 69, 19));
        stand.setPosition({ 250.0f, 520.0f });
        window.draw(stand);

        sf::RectangleShape leg(sf::Vector2f(15.0f, 80.0f));
        leg.setFillColor(sf::Color(139, 69, 19));
        leg.setPosition({ 392.0f, 520.0f });
        window.draw(leg);

        // ----- ПЛАШКИ И ПОЛЗУНКИ -----
        window.draw(leftBar);
        window.draw(bottomBar);
        window.draw(sliderX);
        window.draw(sliderY);

        // ----- ДРОТИК -----
        if (state == SELECT_X || state == SELECT_Y) {
            float handX = 700.0f, handY = 550.0f;
            handDartBody.setPosition({ handX, handY });
            handDartTail.setPosition({ handX, handY });
            handDartBody.setRotation(sf::degrees(0.0f));
            handDartTail.setRotation(sf::degrees(0.0f));
            window.draw(handDartBody);
            window.draw(handDartTail);
        }

        if (state == FLYING || state == RESULT) {
            window.draw(dartBody);
            window.draw(dartTail);
        }

        // ----- ТЕКСТ -----
        window.draw(hintText);
        window.draw(scoreText);
        window.display();
    }
    return 0;
}