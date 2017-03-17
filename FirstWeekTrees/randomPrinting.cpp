#include <iostream>
#include <map>      //map
#include <iomanip>  //map setwd()
#include <string>   //to_string
#include <fstream>  //I/O file
#include <stdlib.h>     //rand, srand
#include <time.h>       /* time */
#include <vector>   //vector
#include <algorithm>	//remove

using namespace std;

struct sequence_t {
  string seqName;
  string seqString;
} ;

void printSequence(sequence_t sequence){
	cout<<sequence.seqName<</*" - "<<sequence.seqString<<*/endl;
}

void printVector(vector <sequence_t> sequenceVector){
    for(int i=0; i<sequenceVector.size(); i++){
    	printSequence(sequenceVector[i]);
        //cout<<sequenceVector[i].seqName<<" - "<<sequenceVector[i].seqString<<endl;
    }
    cout<<endl;
}
void print2dVector(vector<vector<sequence_t>> vector2D){
	for (int i =0 ; i< vector2D.size();i++){
		printVector(vector2D[i]);
	}
}
vector<sequence_t> readFile(string fileName){
	vector<sequence_t> readingVector;
	string nameSequence;
	string stringSequence;

    std::ifstream infile("dummyTest.txt");
    while (infile >> nameSequence ){
    	infile >> stringSequence;
    	sequence_t sequenceAux;

    	sequenceAux.seqName = nameSequence;
    	sequenceAux.seqString = stringSequence;

    	readingVector.push_back(sequenceAux);

    }
    //printVector(readingVector);
    return readingVector;
}

vector<sequence_t> pickRandomSequence(int numberSequences, vector<sequence_t> &listSequence){
	vector<sequence_t> resultList;
	double randomNumber;
	int indice = 0;
	//cout<<"***** pickRandom ****"<<endl;
	//cout<<"listSequence: SIZE "<<listSequence.size()<<endl;
	for(int i=0; i<numberSequences; i++){
		if(!listSequence.empty()){
			srand (time(0));
			//randomNumber = rand() % listSequence.size();     // v2 in the range 0 to size-1
			randomNumber = indice;

			/*cout <<randomNumber<<" - ";
			printSequence(listSequence[randomNumber]);*/

			resultList.push_back(listSequence[randomNumber]);		//insert element to the bucketList
			listSequence.erase(listSequence.begin()+randomNumber);	//remove element to avoid duplicates
		}
	}
	//cout<<"***** OUT pickRandom ****"<<endl;
	return resultList;
}

vector<vector<sequence_t>> fillTheBucket(int bucketSize, vector<sequence_t> &sequenceList, vector<sequence_t> elementVector){
	//cout<<"fillTheBucket ";
	//printVector(elementVector);

	vector<vector<sequence_t>> result;
	vector<sequence_t> auxResult;

	for(int i=0; i<elementVector.size(); i++){
		auxResult=pickRandomSequence(bucketSize,sequenceList);
		auxResult.insert(auxResult.begin(),elementVector[i]);
		//cout<<"auxResult: "<<endl;
		//printVector(auxResult);
		result.push_back(auxResult);
	}
	//cout<<"vector result"<<endl;
	print2dVector(result);
	//cout<<"vector END"<<endl;
	return result;
}
void recursivity(int bucketSize, vector<sequence_t> &sequenceList,vector<sequence_t> result,vector<vector<sequence_t>> auxDosVector){
	vector<vector<sequence_t>> resultDosD;
	vector<vector<sequence_t>> auxResultMerged;
	//while(!sequenceList.empty()){
		for (int i =0 ; i< auxDosVector.size();i++){
			/*cout<<"sended to recursivity INSIDE: "<<endl;
			printVector(auxDosVector[i]);
			cout<<endl;*/
			resultDosD=fillTheBucket(bucketSize-1, sequenceList, auxDosVector[i]);
			//cout<<"* * *"<<endl;
			//print2dVector(resultDosD);
			//cout<<"- - -"<<endl;
			//return recursivity(bucketSize, sequenceList, result,resultDosD);
			auxResultMerged.insert(auxResultMerged.end(),resultDosD.begin(),resultDosD.end());
		}
		auxDosVector=auxResultMerged;
		if (!sequenceList.empty()){recursivity(bucketSize, sequenceList, result,auxDosVector);}
	//}
}
int main() {

	int bucketSize= 3;
	vector<sequence_t> sequenceList;
	vector<sequence_t> result;
	vector<vector<sequence_t>> auxDosVector, resultDosD;

	sequenceList = readFile("dummyTest.txt");
	cout<<"MAIN: "<<sequenceList.size()<<endl;
	//printVector(sequenceList);
	result = pickRandomSequence(bucketSize, sequenceList);
	cout<<"First Nodes: "<<endl;
	printVector(result);
	cout<<"---"<<endl;
	auxDosVector = fillTheBucket(bucketSize-1, sequenceList, result);
	//cout<<"print 2D: "<<endl;
	recursivity(bucketSize, sequenceList, result,auxDosVector);
/*	auxDosVector = fillTheBucket(bucketSize-1, sequenceList, result);
	for (int i =0 ; i< auxDosVector.size();i++){
		//printVector(dosVector[i]);
		cout<<"***"<<endl;
		resultDosD=fillTheBucket(bucketSize-1, sequenceList, auxDosVector[i]);
		cout<<"***---***"<<endl;
	}*/

	//print the results

	cout<<"END: "<<sequenceList.size()<<endl;

	return 0;
}