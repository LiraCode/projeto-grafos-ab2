#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <fstream>
using namespace std;

void dfs(int node, vector<int> &vis, vector<int> adj[], stack<int> &stack) {
    vis[node] = 1; // Marca o nó como visitado
    for (auto i : adj[node]) {
        if (!vis[i]) {
            dfs(i, vis, adj, stack);
        }
    }
    stack.push(node); // Adiciona o nó à pilha após visitar todos os seus vizinhos
}

void dfs_reverse(int node, vector<int> &vis, vector<int> adjReverse[], vector<int> &component) {
    vis[node] = 1; // Marca o nó como visitado
    component.push_back(node); // Adiciona o nó à componente
    for (auto i : adjReverse[node]) {
        if (!vis[i]) {
            dfs_reverse(i, vis, adjReverse, component);
        }
    }
}

void kosaraju(int n, vector<int> adj[], vector<vector<int>> &cfcs) {
    vector<int> vis(n, 0); // Vetor de visitados
    stack<int> stack; // Pilha para armazenar a ordem dos vértices

    // Primeira passagem: DFS para preencher a pilha
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, vis, adj, stack);
        }
    }

    vector<int> adjReverse[n]; // Grafo transposto (arestas invertidas)
    for (int i = 0; i < n; i++) {
        vis[i] = 0; // Reinicia o vetor de visitados para a segunda passagem
        for (auto j : adj[i]) {
            adjReverse[j].push_back(i); // Adiciona arestas invertidas
        }
    }

    // Segunda passagem: DFS usando a ordem da pilha
    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        if (!vis[node]) {
            vector<int> component; // Armazena a componente atual
            dfs_reverse(node, vis, adjReverse, component);
            cfcs.push_back(component); // Adiciona a componente às SCCs
        }
    }
}

int main(int argc, char *argv[]) {
    string input_file = "";
    string output_file = "null";

    // Processa argumentos da linha de comando
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help" << endl;
            cout << "-h: mostra help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo do arquivo" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            output_file = argv[i + 1];
        } else if (strcmp(argv[i], "-f") == 0) {
            input_file = argv[i + 1];
        }
    }

    if (input_file == "") {
        cout << "No input file specified. Use the -f parameter" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m; // Lê o número de vértices e arestas

    vector<int> adj[n]; // Lista de adjacência do grafo

    for (int i = 0; i < m; i++) {
        int v1, v2;
        fin >> v1 >> v2;

        // Ajusta os índices para começar em 0
        v1--;
        v2--;

        adj[v1].push_back(v2); // Adiciona aresta à lista de adjacência
    }

    vector<vector<int>> cfcs; // Armazena as componentes fortemente conectadas
    kosaraju(n, adj, cfcs);

    if (output_file != "null") {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        for (const auto &component : cfcs) {
            for (size_t j = 0; j < component.size(); j++) {
                fout << component[j] + 1; // Ajusta para índice 1
                if (j < component.size() - 1) {
                    fout << " ";
                }
            }
            fout << endl; // Nova linha para cada componente
        }
        fout.close();
    } else {
        for (const auto &component : cfcs) {
            for (size_t j = 0; j < component.size(); j++) {
                cout << component[j] + 1; // Ajusta para índice 1
                if (j < component.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl; // Nova linha para cada componente
        }
    }

    return 0;
}
