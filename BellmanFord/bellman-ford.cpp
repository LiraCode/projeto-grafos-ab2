#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int infinite = 1000000;

string bellmanFord(vector<vector<pair<int, int>>>& adj, int s) {
    int n = adj.size();
    vector<int> dist(n, infinite);
    dist[s] = 0;

    cout << "Iniciando o algoritmo de Bellman-Ford..." << endl;

    // Relaxa as arestas (n-1) vezes
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {  // Começa de 0, pois agora usamos índice baseado em 0
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int wt = edge.second;
                if (dist[u] != infinite && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                    cout << "Relaxando aresta (" << u << ", " << v << ") com peso " << wt << endl;
                }
            }
        }
    }

    // Relaxamento adicional para verificar ciclos negativos
    for (int u = 0; u < n; u++) {
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int wt = edge.second;
            if (dist[u] != infinite && dist[u] + wt < dist[v]) {
                return "Ciclo negativo detectado!";
            }
        }
    }

    // Construa a string com as distâncias
    string distances = "";
    for (int i = 0; i < n; ++i) {  // Agora começamos de 0
        if (dist[i] != infinite) {
            distances += to_string(i) + ":" + to_string(dist[i]) + " ";
        } else {
            distances += to_string(i) + ":infinite ";
        }
    }
    return distances;
}

int main(int argc, char *argv[]) {
    string input_file = "";
    string output_file = "";
    int start_node = 0; // Mudança: agora o índice de vértices é 0-based

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

    if (input_file == "") {
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

    cout << "Número de vértices: " << n << ", número de arestas: " << m << endl;

    // Ajuste aqui: agora estamos usando n para indexação baseada em 0
    vector<vector<pair<int, int>>> adj(n);  // 0-based indexing

    // lendo as arestas
    int v1, v2, w;
    for (int i = 0; i < m; ++i) {
        fin >> v1 >> v2 >> w;
        adj[v1].push_back({v2, w}); // Adiciona a aresta v1 -> v2 com peso w
        cout << "Aresta lida: " << v1 << " -> " << v2 << " com peso " << w << endl;
    }
    fin.close();

    string distances = bellmanFord(adj, start_node);

    if (!output_file.empty()) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Não foi possível abrir o arquivo de saída: " << output_file << endl;
            return 1;
        }
        fout << distances;
        fout << endl;
        fout.close();
    }
    cout << distances << endl;

    return 0;
}
