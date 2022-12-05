#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int GetAndCompareId(string s1, string s2);

void MergeChunks(string filename_1, string filename_2, string foutname);

void MergeChunkstoFstream(string file_1, string file_2, fstream &fout);

void quickSort(string *a, int left, int right);

int SplitAndSort(fstream &inputFile, int SizeofFile);

int innitnumberofFiles(int size);

void MergeTotalFiles(int numberofFiles);

void RemoveFiles(int numberofFiles);
