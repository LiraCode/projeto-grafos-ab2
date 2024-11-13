#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int infinite = 1000000;

string bellmanFord(vector<vector<pair<int, int>>> &adj, int s) {
    int n = adj.size();
    vector<int> dist(n, infinite);
    dist[s] = 0;

    for (int l = 1; l < n - 1; l++) {
        for (int u = 1; u < n; u++){ 
          vector<pair<int, int>> edges = adj[u];
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;

                if (dist[u] != infinite && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    for (int u = 1; u < n; u++) {
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] != infinite && dist[u] + w < dist[v]) {
                return "Ciclo negativo detectado no grafo";
            }
        }
    }


    string distances = "";
    for (int i = 1; i < n; i++) {
        distances += to_string(i) + ":";
        distances += (dist[i] == infinite) ? "INF " : to_string(dist[i]) + " ";
    }
    return distances;
}

int main(int argc, char *argv[]) {
    string input_file = "";
    string output_file = "";
    int start_node = 1; // Jamais trocar

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help" << endl;
            cout << "-h: mostra help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo do arquivo" << endl;
            cout << "-i : vértice inicial" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            output_file = argv[i + 1];
        } else if (strcmp(argv[i], "-f") == 0) {
            input_file = argv[i + 1];
        } else if (strcmp(argv[i], "-i") == 0) {
            start_node = atoi(argv[i + 1]);
        }
    }

    if (input_file.empty()) {
        cout << "Nenhum arquivo de entrada especificado. Use o parâmetro -f" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Não foi possível abrir o arquivo de entrada: " << input_file << endl;
        return 1;
    }

    int n, m; // número de vértices e arestas
    fin >> n >> m;
    // Ajuste aqui: agora estamos usando n para indexação baseada em 0
    vector<vector<pair<int, int>>> adj(n + 1); // criando a matriz que emula um grafo

    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        fin >> u >> v >> w; // recebendo os vertices e peso entre arestas
        adj[u].push_back(make_pair(v, w)); // adiciona v nos vizinhos de u
    }

    fin.close();

    string distances = bellmanFord(adj, start_node);

    if (!(output_file.empty())) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        fout << distances;
        fout << endl;

        fout.close();
    }
    cout << distances << endl;

    return 0;
}
