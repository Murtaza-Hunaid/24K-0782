/*
===== DATA STRUCTURES & ALGORITHMS USED IN THIS PROJECT =====

1. Dynamic Array
   - we are using this store the documents, words and heap element;
   - or ye apne aap ko resize bhi karli gi agr full howi to

2. Singly Linked List
    - singly se maine stack banaya hai jo search history mai kam aiga or hash table chaining collision mai
 
3. Stack (LIFO - Last In First Out)
   - yar ye search history store karega 
   - or iske top pai sab se recent search hogi jo hum assani se display kar sakte hai

4. Hash Table
   - sare words ko map karne ke leye use howa hai
   - or collision handling main echaining wali ki hai

5. Binary Search Tree (BST)
   - isme words ko sorted order main store karaya hai
   - or i think auto complete bhi kaam karega isse

6. Max Heap (Priority Queue)
   - word Frequency k hissab se hame Searches bataiga

7. KMP (Knuth-Morris-Pratt) Algorithm
   - words k pattern ko match karega
   - phrase searching mai bhi pattern ko match karega

==============================================================
*/


#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <optional> 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;


/**
 * Class: DynamicArray
 * It automatcially resizes itself when capacity s reached.
 */
template <typename T>
class DynamicArray {
private:
    T* data;      
    int capacity;
    int size;       


    void resize() { 	
        capacity *= 2;
        T* newData = new T[capacity];

       
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
    }

public:
    DynamicArray() {
        capacity = 10; 
        size = 0;
        data = new T[capacity];
    }

    ~DynamicArray() {
        if (data) {
            delete[] data;
        }
    }

    DynamicArray(const DynamicArray& other) {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Add element to the end
    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    // Remove last element
    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    // Access element at index
    T& operator[](int index) {
        return data[index];
    }

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    // Clear the array
    void clear() {
        size = 0;
    }
};

/**
 * Class: Stack
**/

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    T top() {
        if (topNode) return topNode->data;
        return T();
    }

    bool isEmpty() const { return topNode == nullptr; }

    
    string getAllAsString() {
        string s = "";
        Node* curr = topNode;
		int limit = 8; // sirf 8 recent searches dikhayega
        while (curr && limit > 0) {
            s += "> " + curr->data + "\n";
            curr = curr->next;
            limit--;
        }
        return s;
    }
};

/**
 * Struct: Document
 * Represents a loaded text file.
 */
struct Document {
    int id;
    string filename;
    string content;
};


// ALGORITHMS & SEARCH ENGINE LOGIC

/**
 * Class: KMPAlgorithm
 **/

class KMPAlgorithm {
public:
   
    static void computeLPS(string pat, int M, int* lps) {
        int len = 0; 
        int i = 1;
        lps[0] = 0;

        while (i < M) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if (len != 0) {
                    len = lps[len - 1];
                }
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }


    static int search(string txt, string pat) {
        int M = pat.length();
        int N = txt.length();
        if (M == 0 || N == 0) return 0;

        int* lps = new int[M];
        computeLPS(pat, M, lps);

        int i = 0; 
        int j = 0; 
        int count = 0;

        while (i < N) {
            if (pat[j] == txt[i]) {
                j++;
                i++;
            }

            if (j == M) {
              
                count++;
                j = lps[j - 1];
            }
            else if (i < N && pat[j] != txt[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }

        delete[] lps;
        return count;
    }
};

/**
 * Struct: SearchResult
 */
struct SearchResult {
    int docId;
    string filename;
    int frequency;
};

/**
 * Class: MaxHeap

 */
class MaxHeap {
private:
    DynamicArray<SearchResult> heap;

    // Maintain heap property moving upwards
    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;

        if (heap[index].frequency > heap[parent].frequency) {
            // Swap
            SearchResult temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;

            heapifyUp(parent);
        }
    }

    // Maintain heap property moving downwards
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap.getSize() && heap[left].frequency > heap[largest].frequency)
            largest = left;

        if (right < heap.getSize() && heap[right].frequency > heap[largest].frequency)
            largest = right;

        if (largest != index) {
            // Swap
            SearchResult temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;

            heapifyDown(largest);
        }
    }

public:
    void insert(SearchResult res) {
        heap.push_back(res);
        heapifyUp(heap.getSize() - 1);
    }

    SearchResult extractMax() {
        if (heap.isEmpty()) return { -1, "", 0 };

        SearchResult maxVal = heap[0];

        // Move last element to root
        heap[0] = heap[heap.getSize() - 1];

        // Remove the last element
        heap.pop_back();

        // Restore heap property
        if (!heap.isEmpty()) {
            heapifyDown(0);
        }

        return maxVal;
    }

    bool isEmpty() const { return heap.isEmpty(); }
};

/**
 * Class: BST (Binary Search Tree)
 */
class BSTNode {
public:
    string word;
    BSTNode* left, * right;
    BSTNode(string w) : word(w), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insertRec(BSTNode* node, string word) {
        if (node == nullptr) return new BSTNode(word);

        if (word < node->word)
            node->left = insertRec(node->left, word);
        else if (word > node->word)
            node->right = insertRec(node->right, word);

        return node;
    }

  
    void autocompleteRec(BSTNode* node, string prefix, DynamicArray<string>& results) {
        if (node == nullptr) return;

        bool startsWith = (node->word.find(prefix) == 0);

        // In-order traversal to get sorted results
        autocompleteRec(node->left, prefix, results);

        if (startsWith) {
            results.push_back(node->word);
        }

        autocompleteRec(node->right, prefix, results);
    }

public:
    BST() : root(nullptr) {}

    void insert(string word) {
        root = insertRec(root, word);
    }

    DynamicArray<string> autocomplete(string prefix) {
        DynamicArray<string> results;
        autocompleteRec(root, prefix, results);
        return results;
    }
};

/**
 * Class: HashTable (Inverted Index)
 */


struct DocFreq {
    int docId;
    int frequency;
    DocFreq* next;
    DocFreq(int id, int f) : docId(id), frequency(f), next(nullptr) {}
};

// Structure for the Hash Bucket
struct HashNode {
    string key;
    DocFreq* head; // Linked List of documents
    HashNode* next; // Next bucket in case of hash collision
    HashNode(string k) : key(k), head(nullptr), next(nullptr) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 100;
    HashNode* table[TABLE_SIZE];

    int hashFunction(string key) {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
    }

    void insert(string key, int docId) {
        int index = hashFunction(key);
        HashNode* entry = table[index];

        // 1. Search if word exists in the bucket
        while (entry != nullptr) {
            if (entry->key == key) {
                // Word found. Now check if this docId is already logged.
                DocFreq* docEntry = entry->head;
                while (docEntry != nullptr) {
                    if (docEntry->docId == docId) {
                        docEntry->frequency++;
                        return;
                    }
                    if (docEntry->next == nullptr) break;
                    docEntry = docEntry->next;
                }
                // DocId not found, append to list
                docEntry->next = new DocFreq(docId, 1);
                return;
            }
            entry = entry->next;
        }

        // 2. Word not found, create new HashNode
        HashNode* newNode = new HashNode(key);
        newNode->head = new DocFreq(docId, 1);
        newNode->next = table[index];
        table[index] = newNode;
    }

    DocFreq* search(string key) {
        int index = hashFunction(key);
        HashNode* entry = table[index];
        while (entry != nullptr) {
            if (entry->key == key) {
                return entry->head;
            }
            entry = entry->next;
        }
        return nullptr;
    }
};

/**
 * Class: Engine

 */
class Engine {
public:
    HashTable invertedIndex;
    BST autocompleteTree;
    DynamicArray<Document> documents;
    Stack<string> history;


    DynamicArray<string> tokenize(string text) {
        DynamicArray<string> tokens;
        string word = "";
        for (char c : text) {
            if (isalnum(c)) {
                word += tolower(c);
            }
            else {
                if (word.length() > 0) {
                    tokens.push_back(word);
                    word = "";
                }
            }
        }
        if (word.length() > 0) tokens.push_back(word);
        return tokens;
    }

    void addDocument(string filename, string content) {
        int newId = documents.getSize();
        documents.push_back({ newId, filename, content });

        \
        DynamicArray<string> tokens = tokenize(content);
        for (int i = 0; i < tokens.getSize(); i++) {
            string word = tokens[i];
            invertedIndex.insert(word, newId);
            autocompleteTree.insert(word);
        }
    }

    string searchWord(string query) {
        history.push(query);

        // Clean query
        string cleanQuery = "";
        for (char c : query) if (isalnum(c)) cleanQuery += tolower(c);

        DocFreq* results = invertedIndex.search(cleanQuery);

        if (results == nullptr) {
            return "No documents found containing '" + cleanQuery + "'.";
        }

        
        MaxHeap ranker;
        int count = 0;
        while (results != nullptr) {
            ranker.insert({ results->docId, documents[results->docId].filename, results->frequency });
            results = results->next;
            count++;
        }

        string output = "Found '" + cleanQuery + "' in " + to_string(count) + " document(s):\n";
        int rank = 1;
        while (!ranker.isEmpty()) {
            SearchResult res = ranker.extractMax();
            output += to_string(rank++) + ". " + res.filename + " (Freq: " + to_string(res.frequency) + ")\n";
        }
        return output;
    }

    string searchPhrase(string phrase) {
        history.push(phrase);

        // Convert phrase to lowercase
        string lowerPhrase = "";
        for (char c : phrase) lowerPhrase += tolower(c);

        MaxHeap ranker;
        bool foundAny = false;

        for (int i = 0; i < documents.getSize(); i++) {
            string lowerContent = "";
            for (char c : documents[i].content) lowerContent += tolower(c);

            // Use KMP Algorithm
            int occurrences = KMPAlgorithm::search(lowerContent, lowerPhrase);

            if (occurrences > 0) {
                ranker.insert({ documents[i].id, documents[i].filename, occurrences });
                foundAny = true;
            }
        }

        if (!foundAny) {
            return "No documents found containing the phrase.";
        }

        string output = "Phrase found. Results Ranked by Occurrence:\n";
        int rank = 1;
        while (!ranker.isEmpty()) {
            SearchResult res = ranker.extractMax();
            output += to_string(rank++) + ". " + res.filename + " (Freq: " + to_string(res.frequency) + ")\n";
        }
        return output;
    }
};


//  GUI:


class Button {
public:
    sf::RectangleShape shape;
    sf::Text label;
    bool isHovered;

    Button(float x, float y, float w, float h, const std::string& text, sf::Font& font)
        : isHovered(false)
    {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(w, h));
        shape.setFillColor(sf::Color(70, 70, 70));
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::White);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(18);
        label.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = label.getLocalBounds();
        label.setPosition(
            x + (w - textBounds.width) / 2.0f - textBounds.left,
            y + (h - textBounds.height) / 2.0f - textBounds.top
        );
    }

    bool isClicked(sf::Vector2f mousePos) {
        return shape.getGlobalBounds().contains(mousePos);
    }

    void update(sf::Vector2f mousePos) {
        if (shape.getGlobalBounds().contains(mousePos)) {
            shape.setFillColor(sf::Color(100, 100, 100));
            isHovered = true;
        }
        else {
            shape.setFillColor(sf::Color(70, 70, 70));
            isHovered = false;
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(label);
    }
};


void createFiles() {
    ofstream f1("data_cs.txt");
    f1 << "Computer science is the study of computation, automation, and information. " << "It spans theoretical disciplines (such as algorithms) to practical disciplines.";
    f1.close();

    ofstream f2("data_murtaza.txt");
    f2 << "My name is Murtaza, " << "from BCS-3F";
    f2.close();

    ofstream f3("data_dsa.txt");
    f3 << "A data structure is a data organization, management, and storage format " << "that is usually chosen for efficient access to data.";
    f3.close();
}

string readFileContent(string fn) {
    ifstream in(fn);
    if (!in) {
        cerr << "Warning: Could not read " << fn << endl;
        return "";
    }
    return string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
}

int main() {
    createFiles();

    // Initialize Engine and Load Data
    Engine engine;
    engine.addDocument("harryPotter1.txt", readFileContent("harryPotter1.txt"));
    engine.addDocument("harryPotter2.txt", readFileContent("harryPotter2.txt"));
    engine.addDocument("harryPotter3.txt", readFileContent("harryPotter3.txt"));
    engine.addDocument("data_cs.txt", readFileContent("data_cs.txt"));
    engine.addDocument("data_ai.txt", readFileContent("data_ai.txt"));
    engine.addDocument("data_dsa.txt", readFileContent("data_dsa.txt"));

    //Setup SFML Window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "DSA Mini Search Engine", sf::Style::Fullscreen);

    float screenW = (float)desktop.width;
    float screenH = (float)desktop.height;
    window.setFramerateLimit(60);

    // Load Font
    sf::Font font;

    if (!font.loadFromFile("ARIAL.TTF")) {
        cerr << "CRITICAL ERROR: 'arial.ttf' not found! Please download Arial.ttf and place it next to the executable." << endl;
        return -1;
    }

    // GUI State Variables
    string userInput = "";
    string resultText = "Welcome to the Search Engine!\nType a word and click Search.";
    string suggestionText = "";

    //  UI Components Setup
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Mini Text Search Engine");
    titleText.setCharacterSize(30);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
        (screenW - titleBounds.width) / 2,
        30
    );

    titleText.setFillColor(sf::Color::Cyan);
    titleText.setStyle(sf::Text::Bold);

    // Input Field
    sf::RectangleShape inputBox(sf::Vector2f(700, 50));
    inputBox.setPosition(
        (screenW - 700) / 2,
        100
    );

    inputBox.setFillColor(sf::Color::White);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setString("");
    inputText.setCharacterSize(24);
    inputText.setPosition(
        (screenW - 700) / 2 + 10,
        108
    );

    inputText.setFillColor(sf::Color::Black);

    // Results Area
    sf::Text resultsDisplay;
    resultsDisplay.setFont(font);
    resultsDisplay.setString(resultText);
    resultsDisplay.setCharacterSize(24);
    resultsDisplay.setPosition(
        (screenW - 800) / 2,
        280
    );

    resultsDisplay.setFillColor(sf::Color::White);

    // Suggestions Area
    sf::Text suggestionDisplay;
    suggestionDisplay.setFont(font);
	suggestionDisplay.setString(suggestionText);
	suggestionDisplay.setCharacterSize(16);
    suggestionDisplay.setPosition({ 100, 160 });
    suggestionDisplay.setFillColor(sf::Color(200, 200, 200));
    suggestionDisplay.setStyle(sf::Text::Italic);

    // History Area
    sf::Text historyLabel;
    historyLabel.setFont(font);
    historyLabel.setString("Search History");
    historyLabel.setCharacterSize(20);
    historyLabel.setPosition(screenW - 550, 250);

    historyLabel.setFillColor(sf::Color::Yellow);

    sf::Text historyDisplay;
    historyDisplay.setFont(font);
    historyDisplay.setString("");
    historyLabel.setCharacterSize(18);
    historyDisplay.setPosition(screenW - 550, 280);
    historyDisplay.setFillColor(sf::Color(200, 200, 0));

    // Buttons
    float btnW = 200;
    float btnH = 50;
    float gap = 30;
    float totalW = (btnW * 3) + (gap * 2);
    float startX = (screenW - totalW) / 2;
    float btnY = 190;

    Button btnWord(startX, btnY, btnW, btnH, "Search Word", font);
    Button btnPhrase(startX + btnW + gap, btnY, btnW, btnH, "Search Phrase", font);
    Button btnClear(startX + (btnW + gap) * 2, btnY, btnW, btnH, "Clear", font);


    // Main Event Loop
    while (window.isOpen()) {
        // Event Polling
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }


            // Text input
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8) {
                    if (!userInput.empty()) userInput.pop_back();
                }
                else if (event.text.unicode >= 32 && event.text.unicode < 127) {
                    userInput += static_cast<char>(event.text.unicode);
                }

                // Autocomplete logic (unchanged)
                if (!userInput.empty()) {
                    size_t lastSpace = userInput.find_last_of(' ');
                    std::string lastWord = (lastSpace == std::string::npos) ? userInput : userInput.substr(lastSpace + 1);

                    if (!lastWord.empty()) {
                        DynamicArray<std::string> suggs = engine.autocompleteTree.autocomplete(lastWord);
                        std::string sStr = "Suggestions: ";
                        for (int i = 0; i < std::min(3, suggs.getSize()); i++) {
                            sStr += suggs[i] + (i < std::min(3, suggs.getSize()) - 1 ? ", " : "");
                        }
                        suggestionText = (suggs.isEmpty()) ? "" : sStr;
                    }
                    else {
                        suggestionText = "";
                    }
                }
                else {
                    suggestionText = "";
                }
            }

            // Mouse click
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        sf::Mouse::getPosition(window)
                    );

                    if (btnWord.isClicked(mousePos)) {
                        if (userInput.empty()) resultText = "Please enter a word to search.";
                        else resultText = engine.searchWord(userInput);
                    }
                    else if (btnPhrase.isClicked(mousePos)) {
                        if (userInput.empty()) resultText = "Please enter a phrase to search.";
                        else resultText = engine.searchPhrase(userInput);
                    }
                    else if (btnClear.isClicked(mousePos)) {
                        userInput = "";
                        resultText = "Ready.";
                        suggestionText = "";
                    }
                }
            }
        }


        // Logic Updates
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        btnWord.update(mousePos);
        btnPhrase.update(mousePos);
        btnClear.update(mousePos);

        // Update Text Elements
        inputText.setString(userInput + "_"); // Cursor effect
        resultsDisplay.setString(resultText);
        suggestionDisplay.setString(suggestionText);
        historyDisplay.setString(engine.history.getAllAsString());

        // Drawing
        window.clear(sf::Color(30, 30, 30)); // Dark Background

        window.draw(titleText);

        // Draw Input Area
        window.draw(inputBox);
        window.draw(inputText);
        window.draw(suggestionDisplay);

        // Draw Buttons
        btnWord.draw(window);
        btnPhrase.draw(window);
        btnClear.draw(window);

        // Draw Content
        window.draw(resultsDisplay);
        window.draw(historyLabel);
        window.draw(historyDisplay);

        window.display();
    }

    return 0;
}