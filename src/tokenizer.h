#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class EmbeddingLoader {
private:
    std::vector<float> all_embeddings;
    int vocab_size;
    int embed_dim;
    
public:
    EmbeddingLoader() : vocab_size(0), embed_dim(0) {}
    
    void load(std::string info_file_path, 
            std::string bin_file_path) {
        
        std::ifstream info_file(info_file_path);
        
        
        info_file >> vocab_size >> embed_dim;
        info_file.close();
        
        std::cout << "Vocab size: " << vocab_size << std::endl;
        std::cout << "Embedding dimension: " << embed_dim << std::endl;
        
        // Create a big vector to hold all the embeddings
        all_embeddings.resize(vocab_size * embed_dim);
        
        // Read the binary file
        std::ifstream bin_file(bin_file_path, std::ios::binary);
        
        bin_file.read(reinterpret_cast<char*>(all_embeddings.data()), 
                      vocab_size * embed_dim * sizeof(float));
        bin_file.close();
        
    }
    
    void printTokenEmbedding(int token_id, int num_values)
    {
        int start_index = token_id * embed_dim;
        std::cout << "First " << num_values << " numbers of token " << token_id << ": ";
        for (int i = 0; i < num_values && i < embed_dim; i++) {
            std::cout << all_embeddings[start_index + i] << " ";
        }
        std::cout << std::endl;
    }
    
    int getVocabSize() const { return vocab_size; }
    int getEmbedDim() const { return embed_dim; }
    
    const std::vector<float>& getEmbeddings() const { return all_embeddings; }
};

/*int main() {
    EmbeddingLoader loader;
    
    if (!loader.load()) {
        return 1;
    }
    
 
    loader.printTokenEmbedding(0);
    

    loader.printTokenEmbedding(31999);
    
    return 0;
}*/