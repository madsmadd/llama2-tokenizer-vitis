#include <sentencepiece_processor.h>
#include "tokenizer.h"
#include <iostream>
#include <sstream>

int main()
{
    sentencepiece::SentencePieceProcessor sp;
    EmbeddingLoader e;

    e.load("embeddings_info.txt", "embeddings.bin");

    auto status = sp.Load("tokenizer.model");

    std::cout << "Vocab size: " << sp.GetPieceSize() << "\n";

    std::cout << "Choose mode:\n";
    std::cout << "1. Encode text to token IDs\n";
    std::cout << "2. Decode token IDs to text\n";
    std::cout << "Enter your choice (1 or 2): ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // consume the newline character
    
    if (choice == 1) {
        // Encode mode: text -> token IDs
        std::cout << "Enter text to encode: ";
        std::string text;
        std::getline(std::cin, text);
        
        std::vector<int> ids;
        sp.Encode(text, &ids);

        std::cout << "Encoded IDs: ";
        for (int id : ids) {
            std::cout << id << " ";
        }
        std::cout << "\n";

        std::cout << "Embedding for each token:\n";
        for (int id : ids) {
            std::cout << "Token ID " << id << ": ";
            e.printTokenEmbedding(id, 5);
        }
    }
    else if (choice == 2) {
        // Decode mode: token IDs -> text
        std::cout << "Enter token IDs separated by spaces: ";
        std::string input_line;
        std::getline(std::cin, input_line);
        
        // Parse the token IDs from the input string
        std::vector<int> ids;
        std::istringstream iss(input_line);
        int id;
        while (iss >> id) {
            ids.push_back(id);
        }
        
        if (ids.empty()) {
            std::cout << "No valid token IDs entered.\n";
            return 1;
        }
        
        // Decode the token IDs back to text
        std::string decoded_text;
        sp.Decode(ids, &decoded_text);
        
        std::cout << decoded_text << "\n";
    }
    else {
        std::cout << "Invalid choice. Please enter 1 or 2.\n";
        return 1;
    }
}