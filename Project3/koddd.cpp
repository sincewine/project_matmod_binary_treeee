#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

// ��������� ���� ��������� ������
struct Node {
    int key;
    std::shared_ptr<Node> left, right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// ����������� ������� ���������� �������� � ������
std::shared_ptr<Node> insert(std::shared_ptr<Node> root, int key) {
    if (!root)
        return std::make_shared<Node>(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// ������� ��������� ����� � �������������� �����
void drawNumber(sf::RenderWindow& window, int number, float x, float y) {
    // ��� ����������� ���� ����� ������������ ����������� ������� ��� �����
    // ������ ������ ��������� ���������������, �������������� �����.

    // ������������ ����� � ������
    std::string numStr = std::to_string(number);

    float offsetX = 0;
    // ������ ������ ����� �� �����������
    for (char digit : numStr) {
        // ������� ������������� ��� ������ �����
        sf::RectangleShape rect(sf::Vector2f(20, 30)); // ������ �������������� ��� �����
        rect.setFillColor(sf::Color::White);
        rect.setPosition(x + offsetX, y);

        window.draw(rect);

        // ��������� ����� ��� �����
        sf::Text text;
        text.setString(std::string(1, digit));  // ���� ����� ��� ������
        text.setCharacterSize(20);              // ������ ������
        text.setFillColor(sf::Color::Black);    // ���� ������
        text.setPosition(x + offsetX + 5, y + 5); // ������� ������ ������ ��������������

        window.draw(text);

        offsetX += 25; // ����� ��� ��������� �����
    }
}

// ����������� ������� ��������� ������
void drawTree(sf::RenderWindow& window, std::shared_ptr<Node> node, float x, float y, float offsetX, float offsetY) {
    if (!node) return;

    // ������ ������� ����
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);

    window.draw(circle);

    // ������ ����� � ����
    drawNumber(window, node->key, x - 10, y - 10); // ���������� ����� ������ �����

    // ������ ����� � ���������� ������������ ��������
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
    // ������� ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Search Tree Visualization");

    // ������� ������
    std::shared_ptr<Node> root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    sf::Font font;
    // �������� ���� ���������
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ������� ����
        window.clear(sf::Color::Yellow);

        // ������������ ������
        drawTree(window, root, 400, 50, 150, 100);

        // ���������� ���������� ����
        window.display();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

// ��������� ���� ��������� ������
struct Node {
    int key;
    std::shared_ptr<Node> left, right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// ����������� ������� ���������� �������� � ������
std::shared_ptr<Node> insert(std::shared_ptr<Node> root, int key) {
    if (!root)
        return std::make_shared<Node>(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// ������� ��������� ����� � �������������� �����
void drawNumber(sf::RenderWindow& window, int number, float x, float y) {
    // ��� ����������� ���� ����� ������������ ����������� ������� ��� �����
    // ������ ������ ��������� ���������������, �������������� �����.

    // ������������ ����� � ������
    std::string numStr = std::to_string(number);

    float offsetX = 0;
    // ������ ������ ����� �� �����������
    for (char digit : numStr) {
        // ������� ������������� ��� ������ �����
        sf::RectangleShape rect(sf::Vector2f(20, 30)); // ������ �������������� ��� �����
        rect.setFillColor(sf::Color::White);
        rect.setPosition(x + offsetX, y);

        window.draw(rect);

        // ��������� ����� ��� �����
        sf::Text text;
        text.setString(std::string(1, digit));  // ���� ����� ��� ������
        text.setCharacterSize(20);              // ������ ������
        text.setFillColor(sf::Color::Black);    // ���� ������
        text.setPosition(x + offsetX + 5, y + 5); // ������� ������ ������ ��������������

        window.draw(text);

        offsetX += 25; // ����� ��� ��������� �����
    }
}

// ����������� ������� ��������� ������
void drawTree(sf::RenderWindow& window, std::shared_ptr<Node> node, float x, float y, float offsetX, float offsetY) {
    if (!node) return;

    // ������ ������� ����
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);

    window.draw(circle);

    // ������ ����� � ����
    drawNumber(window, node->key, x - 10, y - 10); // ���������� ����� ������ �����

    // ������ ����� � ���������� ������������ ��������
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
    // ������� ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Search Tree Visualization");

    // ������� ������
    std::shared_ptr<Node> root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    sf::Font font;
    // �������� ���� ���������
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ������� ����
        window.clear(sf::Color::Yellow);

        // ������������ ������
        drawTree(window, root, 400, 50, 150, 100);

        // ���������� ���������� ����
        window.display();
    }

    return 0;
}