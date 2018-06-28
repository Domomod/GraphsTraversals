final: main.o AdjMat.o EdgTab.o AdjLis.o GraMat.o Timer.hpp
	g++ main.o AdjMat.o EdgTab.o AdjLis.o GraMat.o -o final

main.o: main.cpp
	g++ -c main.cpp -o main.o 

AdjMat.o: AdjacencyMatrix.cpp AdjacencyMatrix.hpp
	g++ -c AdjacencyMatrix.cpp -o AdjMat.o

EdgTab.o: EdgeTable.cpp EdgeTable.hpp
	g++ -c EdgeTable.cpp -o EdgTab.o

AdjLis.o: AdjacencyList.cpp AdjacencyList.hpp
	g++ -c AdjacencyList.cpp -o AdjLis.o

GraMat.o: GraphMatrix.cpp GraphMatrix.hpp
	g++ -c GraphMatrix.cpp -o GraMat.o

clean:
	rm main.o AdjMat.o EdgTab.o AdjLis.o GraMat.o 

