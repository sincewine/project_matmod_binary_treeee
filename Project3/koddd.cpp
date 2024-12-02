#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

// Структура узла бинарного дерева
struct Node {
    int key;
    std::shared_ptr<Node> left, right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// Рекурсивная функция добавления элемента в дерево
std::shared_ptr<Node> insert(std::shared_ptr<Node> root, int key) {
    if (!root)
        return std::make_shared<Node>(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// Функция рисования числа с использованием линий
void drawNumber(sf::RenderWindow& window, int number, float x, float y) {
    // Для отображения цифр можно использовать стандартные пиксели или блоки
    // Просто рисуем несколько прямоугольников, представляющих число.

    // Конвертируем число в строку
    std::string numStr = std::to_string(number);

    float offsetX = 0;
    // Рисуем каждую цифру по отдельности
    for (char digit : numStr) {
        // Создаем прямоугольник для каждой цифры
        sf::RectangleShape rect(sf::Vector2f(20, 30)); // Размер прямоугольника для цифры
        rect.setFillColor(sf::Color::White);
        rect.setPosition(x + offsetX, y);

        window.draw(rect);

        // Добавляем линию для цифры
        sf::Text text;
        text.setString(std::string(1, digit));  // Одну цифру как строку
        text.setCharacterSize(20);              // Размер текста
        text.setFillColor(sf::Color::Black);    // Цвет текста
        text.setPosition(x + offsetX + 5, y + 5); // Позиция текста внутри прямоугольника

        window.draw(text);

        offsetX += 25; // Сдвиг для следующей цифры
    }
}

// Рекурсивная функция отрисовки дерева
void drawTree(sf::RenderWindow& window, std::shared_ptr<Node> node, float x, float y, float offsetX, float offsetY) {
    if (!node) return;

    // Рисуем текущий узел
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);

    window.draw(circle);

    // Рисуем число в узле
    drawNumber(window, node->key, x - 10, y - 10); // Отображаем число внутри круга

    // Рисуем линии и рекурсивно обрабатываем потомков
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - offsetX + 20, y + offsetY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->left, x - offsetX, y + offsetY, offsetX * 0.5f, offsetY);
    }
    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + offsetX + 20, y + offsetY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->right, x + offsetX, y + offsetY, offsetX * 0.5f, offsetY);
    }
}

int main() {
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Search Tree Visualization");

    // Создаем дерево
    std::shared_ptr<Node> root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    sf::Font font;
    // Основной цикл программы
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Очищаем окно
        window.clear(sf::Color::Yellow);

        // Отрисовываем дерево
        drawTree(window, root, 400, 50, 150, 100);

        // Показываем содержимое окна
        window.display();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

// Структура узла бинарного дерева
struct Node {
    int key;
    std::shared_ptr<Node> left, right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// Рекурсивная функция добавления элемента в дерево
std::shared_ptr<Node> insert(std::shared_ptr<Node> root, int key) {
    if (!root)
        return std::make_shared<Node>(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// Функция рисования числа с использованием линий
void drawNumber(sf::RenderWindow& window, int number, float x, float y) {
    // Для отображения цифр можно использовать стандартные пиксели или блоки
    // Просто рисуем несколько прямоугольников, представляющих число.

    // Конвертируем число в строку
    std::string numStr = std::to_string(number);

    float offsetX = 0;
    // Рисуем каждую цифру по отдельности
    for (char digit : numStr) {
        // Создаем прямоугольник для каждой цифры
        sf::RectangleShape rect(sf::Vector2f(20, 30)); // Размер прямоугольника для цифры
        rect.setFillColor(sf::Color::White);
        rect.setPosition(x + offsetX, y);

        window.draw(rect);

        // Добавляем линию для цифры
        sf::Text text;
        text.setString(std::string(1, digit));  // Одну цифру как строку
        text.setCharacterSize(20);              // Размер текста
        text.setFillColor(sf::Color::Black);    // Цвет текста
        text.setPosition(x + offsetX + 5, y + 5); // Позиция текста внутри прямоугольника

        window.draw(text);

        offsetX += 25; // Сдвиг для следующей цифры
    }
}

// Рекурсивная функция отрисовки дерева
void drawTree(sf::RenderWindow& window, std::shared_ptr<Node> node, float x, float y, float offsetX, float offsetY) {
    if (!node) return;

    // Рисуем текущий узел
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);

    window.draw(circle);

    // Рисуем число в узле
    drawNumber(window, node->key, x - 10, y - 10); // Отображаем число внутри круга

    // Рисуем линии и рекурсивно обрабатываем потомков
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - offsetX + 20, y + offsetY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->left, x - offsetX, y + offsetY, offsetX * 0.5f, offsetY);
    }
    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + offsetX + 20, y + offsetY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->right, x + offsetX, y + offsetY, offsetX * 0.5f, offsetY);
    }
}

int main() {
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Search Tree Visualization");

    // Создаем дерево
    std::shared_ptr<Node> root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    sf::Font font;
    // Основной цикл программы
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Очищаем окно
        window.clear(sf::Color::Yellow);

        // Отрисовываем дерево
        drawTree(window, root, 400, 50, 150, 100);

        // Показываем содержимое окна
        window.display();
    }

    return 0;
}