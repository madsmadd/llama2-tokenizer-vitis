#include <sentencepiece_processor.h>
#include "tokenizer.h"
#include <iostream>

int main()
{
    sentencepiece::SentencePieceProcessor sp;
    EmbeddingLoader e;

    e.load("embeddings_info.txt", "embeddings.bin");

    auto status = sp.Load("tokenizer.model");

    std::cout << "Vocab size: " << sp.GetPieceSize() << "\n";

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