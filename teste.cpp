#include <iostream>
#include <vector>
#include <algorithm>

// Função para imprimir um vetor
void printVector(const std::vector<int>& v) {
    for (int num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Função para gerar permutações de um subconjunto
void generatePermutations(std::vector<int>& subset, std::vector<std::vector<int>>& permutations) {
    do {
        permutations.push_back(subset);
    } while(std::next_permutation(subset.begin(), subset.end()));
}

// Função principal
int main() {
    int n;
    std::cout << "Digite o valor de n (n >= 3): ";
    std::cin >> n;

    if (n < 3) {
        std::cout << "A sequência deve ter pelo menos 3 valores." << std::endl;
        return 1;
    }

    // Preparar o vetor original com os números de 0 a n-1
    std::vector<int> original(n);
    for (int i = 0; i < n; ++i) {
        original[i] = i;
    }

    // Vector para armazenar todas as permutações possíveis
    std::vector<std::vector<int>> allPermutations;

    // Gerar subconjuntos de tamanho k e suas permutações
    for (int k = 3; k <= n; ++k) {
        std::vector<bool> mask(n, false);
        std::fill(mask.begin(), mask.begin() + k, true);
        
        do {
            std::vector<int> subset;
            for (int i = 0; i < n; ++i) {
                if (mask[i]) {
                    subset.push_back(original[i]);
                }
            }

            // Gerar e adicionar as permutações do subset atual
            generatePermutations(subset, allPermutations);

        } while (std::prev_permutation(mask.begin(), mask.end()));
    }

    // Imprimir todas as permutações
    std::cout << "Todas as permutações possíveis de tamanho >= 3 são:" << std::endl;
    for (const auto& perm : allPermutations) {
        printVector(perm);
    }

    return 0;
}
