
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <iomanip>
#include <algorithm>
#include <chrono>

// ��������� ���� ��������� ������
struct Node {
    std::string hash;
    std::shared_ptr<Node> left, right;

    Node(const std::string& val) : hash(val), left(nullptr), right(nullptr) {}
};

// ����������� ������� ���������� �������� � ������
std::shared_ptr<Node> insert(std::shared_ptr<Node> root, const std::string& hash) {
    if (!root)
        return std::make_shared<Node>(hash);

    if (hash < root->hash)
        root->left = insert(root->left, hash);
    else if (hash > root->hash)
        root->right = insert(root->right, hash);
    // ����� �� ���������, ���� ��� �����
    return root;
}
// ����������� ������� ������ �������� � ������
bool searchTree(std::shared_ptr<Node> root, const std::string& hash) {
    if (!root) return false;
    if (root->hash == hash) return true;

    if (hash < root->hash)
        return searchTree(root->left, hash);
    else
        return searchTree(root->right, hash);
}

// ������� ��� ���������� ���� �� ������ ������ (��� ������� ���������� std::hash)
std::string calculateHash(const std::string& password) {
    std::hash<std::string> hash_fn;
    size_t hash_value = hash_fn(password);

    // ����������� ��� � ������
    std::stringstream ss;
    ss << std::hex << hash_value;
    return ss.str();
}

// ������� ��� �������� ������ �� ������� ������
sf::Font loadFontFromMemory(const std::vector<unsigned char>& fontData) {
    sf::Font font;
    if (!font.loadFromMemory(fontData.data(), fontData.size())) {
        std::cerr << "������ �������� ������ �� ������!" << std::endl;
        exit(1);
    }
    return font;
}

// ������� ��� ������ ������� �� ����� � ���������� �� � ������
void loadPasswords(std::shared_ptr<Node>& root, std::vector<std::string>& hashes, const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "������ �������� �����!" << std::endl;
        exit(1);
    }

    std::string password;
    while (std::getline(file, password)) {
        // ������� ��������� ������ ������� � ������� ����� ������
        password.erase(std::remove(password.begin(), password.end(), '\n'), password.end());
        password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());
        password.erase(std::remove(password.begin(), password.end(), ' '), password.end());

        // ���������� ������ ������
        if (password.empty()) continue;

        std::string hash = calculateHash(password);
        root = insert(root, hash);
        hashes.push_back(hash);
    }
}

// ������� ��������� ���� � �������������� ������
void drawHash(sf::RenderWindow& window, const std::string& hash, float x, float y, sf::Font& font) {
    // ��������� ����� ������ ���� ��� ���������
    std::string displayHash = hash.substr(0, 10);  // ��������� ������ ������ 10 ��������
    // ��������, ��� ������ ���� �� �����
    if (displayHash.empty()) {
        std::cerr << "������: ��� ������!" << std::endl;
        return;  // �������, ���� ������ ������
    }

    // ������� ������ ������
    sf::Text text;
    sf::String strang(displayHash.c_str());
    // ���������, ��� ����� ��������� ��������
    if (font.getInfo().family.empty()) {
        std::cerr << "������: ����� �� ��������!" << std::endl;
        return;
    }
    // ������������� ������ � �����
    text.setString(strang);
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x, y);

    window.draw(text);
}
// ������� ������ � �������
bool searchArray(const std::vector<std::string>& hashes, const std::string& target) {
    return std::find(hashes.begin(), hashes.end(), target) != hashes.end();
}
// ����������� ������� ��������� ������
void drawTree(sf::RenderWindow& window, std::shared_ptr<Node> node, float x, float y, float offsetX, float offsetY, sf::Font& font) {
    if (!node) return;

    // ������ ������� ����
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);
    window.draw(circle);

    // ������ ��� ������ ����
    drawHash(window, node->hash, x - 10, y - 10, font);

    // ������ ����� � ���������� ������������ ��������
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - offsetX + 20, y + offsetY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->left, x - offsetX, y + offsetY, offsetX * 0.5f, offsetY, font);
    }
    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + offsetX + 20, y + offsetY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->right, x + offsetX, y + offsetY, offsetX * 0.8f, offsetY, font);
    }


}

// ������� ��� ������ ������ �� ����� � �������� ��� � ������
std::vector<unsigned char> loadFontDataFromFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "������ �������� �����!" << std::endl;
        exit(1);
    }

    // ��������� ���� � ������ ������
    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return buffer;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // �������� ������ �� �����
    std::vector<unsigned char> fontData = loadFontDataFromFile("LiberationSans-Regular.ttf");
    sf::Font font = loadFontFromMemory(fontData);

    // ������� ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Search Tree Visualization");

    // ������� ������ ��� �������� ����� �������
    std::shared_ptr<Node> root = nullptr;
    std::vector<std::string> hashes;

    // ��������� ������ �� ����� � ������ ������
    loadPasswords(root, hashes, "passwords.txt"); // ���������, ��� ���� � �������� ����������

    // ������� ��� ������
    std::string targetHash = calculateHash("ginger");

    // ����� ������� ������ � �������
    auto start = std::chrono::high_resolution_clock::now();
    bool foundInArray = searchArray(hashes, targetHash);
    auto end = std::chrono::high_resolution_clock::now();
    auto timeArray = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // ����� ������� ������ � ������
    start = std::chrono::high_resolution_clock::now();
    bool foundInTree = searchTree(root, targetHash);
    end = std::chrono::high_resolution_clock::now();
    auto timeTree = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // ����� ����������� � �������
    std::cout << "���������� ������:" << std::endl;
    std::cout << "������� " << (foundInArray ? "������" : "�� ������") << " � �������. �����: " << timeArray << " ���" << std::endl;
    std::cout << "������� " << (foundInTree ? "������" : "�� ������") << " � ������. �����: " << timeTree << " ���" << std::endl;
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
        drawTree(window, root, 400, 50, 150, 100, font);

        // ���������� ���������� ����
        window.display();
    }

    return 0;
}