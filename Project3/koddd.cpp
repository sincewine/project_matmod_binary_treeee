
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

// Структура узла бинарного дерева
struct Node {
    std::string hash;
    std::shared_ptr<Node> left, right;

    Node(const std::string& val) : hash(val), left(nullptr), right(nullptr) {}
};

// Рекурсивная функция добавления элемента в дерево
std::shared_ptr<Node> insert(std::shared_ptr<Node> root, const std::string& hash) {
    if (!root)
        return std::make_shared<Node>(hash);

    if (hash < root->hash)
        root->left = insert(root->left, hash);
    else if (hash > root->hash)
        root->right = insert(root->right, hash);
    // Дубли не вставляем, если хэш равен
    return root;
}
// Рекурсивная функция поиска элемента в дереве
bool searchTree(std::shared_ptr<Node> root, const std::string& hash) {
    if (!root) return false;
    if (root->hash == hash) return true;

    if (hash < root->hash)
        return searchTree(root->left, hash);
    else
        return searchTree(root->right, hash);
}

// Функция для вычисления хэша из строки пароля (для примера используем std::hash)
std::string calculateHash(const std::string& password) {
    std::hash<std::string> hash_fn;
    size_t hash_value = hash_fn(password);

    // Преобразуем хеш в строку
    std::stringstream ss;
    ss << std::hex << hash_value;
    return ss.str();
}

// Функция для загрузки шрифта из массива байтов
sf::Font loadFontFromMemory(const std::vector<unsigned char>& fontData) {
    sf::Font font;
    if (!font.loadFromMemory(fontData.data(), fontData.size())) {
        std::cerr << "Ошибка загрузки шрифта из памяти!" << std::endl;
        exit(1);
    }
    return font;
}

// Функция для чтения паролей из файла и добавления их в дерево
void loadPasswords(std::shared_ptr<Node>& root, std::vector<std::string>& hashes, const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        exit(1);
    }

    std::string password;
    while (std::getline(file, password)) {
        // Убираем возможные лишние пробелы и символы новой строки
        password.erase(std::remove(password.begin(), password.end(), '\n'), password.end());
        password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());
        password.erase(std::remove(password.begin(), password.end(), ' '), password.end());

        // Пропускаем пустые строки
        if (password.empty()) continue;

        std::string hash = calculateHash(password);
        root = insert(root, hash);
        hashes.push_back(hash);
    }
}

// Функция рисования хэша с использованием текста
void drawHash(sf::RenderWindow& window, const std::string& hash, float x, float y, sf::Font& font) {
    // Ограничим длину строки хэша для отрисовки
    std::string displayHash = hash.substr(0, 10);  // Оставляем только первые 10 символов
    // Проверка, что строка хэша не пуста
    if (displayHash.empty()) {
        std::cerr << "Ошибка: хэш пустой!" << std::endl;
        return;  // Выходим, если строка пустая
    }

    // Создаем объект текста
    sf::Text text;
    sf::String strang(displayHash.c_str());
    // Проверяем, что шрифт правильно загружен
    if (font.getInfo().family.empty()) {
        std::cerr << "Ошибка: шрифт не загружен!" << std::endl;
        return;
    }
    // Устанавливаем строку и шрифт
    text.setString(strang);
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x, y);

    window.draw(text);
}
// Функция поиска в массиве
bool searchArray(const std::vector<std::string>& hashes, const std::string& target) {
    return std::find(hashes.begin(), hashes.end(), target) != hashes.end();
}
// Рекурсивная функция отрисовки дерева
void drawTree(sf::RenderWindow& window, std::shared_ptr<Node> node, float x, float y, float offsetX, float offsetY, sf::Font& font) {
    if (!node) return;

    // Рисуем текущий узел
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);
    window.draw(circle);

    // Рисуем хэш внутри узла
    drawHash(window, node->hash, x - 10, y - 10, font);

    // Рисуем линии и рекурсивно обрабатываем потомков
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

// Функция для чтения шрифта из файла и загрузки его в память
std::vector<unsigned char> loadFontDataFromFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        exit(1);
    }

    // Считываем файл в вектор байтов
    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return buffer;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Загрузка шрифта из файла
    std::vector<unsigned char> fontData = loadFontDataFromFile("LiberationSans-Regular.ttf");
    sf::Font font = loadFontFromMemory(fontData);

    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Search Tree Visualization");

    // Создаем дерево для хранения хэшей паролей
    std::shared_ptr<Node> root = nullptr;
    std::vector<std::string> hashes;

    // Загружаем пароли из файла и строим дерево
    loadPasswords(root, hashes, "passwords.txt"); // Убедитесь, что файл с паролями существует

    // Элемент для поиска
    std::string targetHash = calculateHash("ginger");

    // Замер времени поиска в массиве
    auto start = std::chrono::high_resolution_clock::now();
    bool foundInArray = searchArray(hashes, targetHash);
    auto end = std::chrono::high_resolution_clock::now();
    auto timeArray = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Замер времени поиска в дереве
    start = std::chrono::high_resolution_clock::now();
    bool foundInTree = searchTree(root, targetHash);
    end = std::chrono::high_resolution_clock::now();
    auto timeTree = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Вывод результатов в консоль
    std::cout << "Результаты поиска:" << std::endl;
    std::cout << "Элемент " << (foundInArray ? "найден" : "не найден") << " в массиве. Время: " << timeArray << " мкс" << std::endl;
    std::cout << "Элемент " << (foundInTree ? "найден" : "не найден") << " в дереве. Время: " << timeTree << " мкс" << std::endl;
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
        drawTree(window, root, 400, 50, 150, 100, font);

        // Показываем содержимое окна
        window.display();
    }

    return 0;
}