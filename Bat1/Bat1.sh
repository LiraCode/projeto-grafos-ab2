#!/bin/bash

# Verifica o sistema operacional e define os caminhos dos binários
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Para Linux
	echo "OS Linux"
    prim=../Prim/prim
	kruskal=../Kruskal/kruskal
	dijkstra=../Dijkstra/dijkstra
	kosaraju=../Kosaraju/kosaraju
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # Para macOS
	echo "OS macOS"
    prim=../Prim/prim
	kruskal=../Kruskal/kruskal
	dijkstra=../Dijkstra/dijkstra
	kosaraju=../Kosaraju/kosaraju
elif [[ "$OSTYPE" == "cygwin" || "$OSTYPE" == "msys" ]]; then
    # Para Windows (Cygwin ou MSYS)
	echo "OS Windows"
    kosaraju=./kosaraju.bin
	prim=./prim.bin
	kruskal=./kruskal.bin
	dijkstra=./dijkstra.bin
else
    echo "Sistema operacional não identificado. variáveis de path padrão"
    prim=../Prim/prim
kruskal=../Kruskal/kruskal
dijkstra=../Dijkstra/dijkstra
kosaraju=../Kosaraju/kosaraju
fi

# Exibe os caminhos dos binários
echo "path relativo dos binários definidos:"
echo "Prim: $prim"
echo "Kruskal: $kruskal"
echo "Dijkstra: $dijkstra"
echo "Kosaraju: $kosaraju"

echo "Testando algoritmo de Kosaraju"
for i in instances_scc/*.dat
do
	echo -e "\e[33mInstância $i\e[0m";
	$kosaraju -f $i | ./ordena.sh > temp;

	j=$(basename $i);
	diff -w temp ./scc/$j > /dev/null ;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done

echo "Testando algoritmo de Kruskal"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	val=$($kruskal -f $i);
	correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);
	[ $val -eq $correto ] && echo -e "Custo \e[32mOK\e[0m" || echo  -e "\e[31mCusto incorreto\e[0m";

	$kruskal -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mNão é um subgrafo\e[0m";
	fi

done


echo -e "\n\n";

echo "Testando algoritmo de Prim"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	val=$($prim -f $i);
	correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);
	[ $val -eq $correto ] && echo -e "Custo \e[32mOK\e[0m" || echo  -e "\e[31mCusto incorreto\e[0m";

	$prim -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mNão é um subgrafo\e[0m";
	fi

done


echo "Testando algoritmo de Dijkstra"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	$dijkstra -f $i > temp;

	j=$(basename $i);
	diff -w temp ./sp/$j > /dev/null ;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done
