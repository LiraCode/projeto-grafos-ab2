#!/bin/bash

# Binários
bellman=./bellman-ford

# Função remover binário antigo e compilar novamente
compilar() {
  local diretorio=$1
  local binario=$2
  
  echo -e "\e[33mCompilando $binario...\e[0m"
  cd "$diretorio" || { echo "Erro ao acessar o diretório $diretorio"; exit 1; }
  make clean || { echo "Erro ao executar make clean em $diretorio"; exit 1; }
  make || { echo "Erro ao compilar em $diretorio"; exit 1; }
  cd - > /dev/null || { echo "Erro ao retornar ao diretório anterior"; exit 1; }
  echo -e "\e[32mCompilação de $binario concluída.\e[0m"
}

# Verificar e compilar os binários
compilar "BellmanFord" "BellmanFord/bellman-ford"
compilar "Dijkstra" "Dijkstra/dijkstra"
compilar "Kosaraju" "kosaraju/kosaraju"
compilar "Kruskal" "Kruskal/kruskal"
compilar "Prim" "Prim/prim"


# Início dos testes
echo -e "\e[34mIniciando testes...\e[0m";
cd BellmanFord/
./teste.sh
cd ..
cd Bat1/
echo -e "\e[32m###############################################################################################################################\e"
echo "."

echo -e "\e[34mIniciando Bat1...\e[0m";
echo "."
./Bat1.sh
