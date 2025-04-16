all:
	g++ -std=c++11 Graph.cpp GraphTests.cpp -o graph-tests
	g++ -std=c++11 BetterPriorityQueue.cpp BPQTests.cpp Graph.cpp -o bpq-tests
	g++ -std=c++11 Graph.cpp BetterPriorityQueue.cpp Dijkstra.cpp DijkstraTests.cpp -o dijkstra

run:
	./graph-tests
	./bpq-tests
	./dijkstra

try: all run
