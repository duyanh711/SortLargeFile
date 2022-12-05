#include "SortBigData.h"

string INPUT_FILE = "Books_rating.csv"; // Name of input file
string SPLITED_FILE = "splited_file_";  // Name of splited chunk files
string SORTED_FILE = "sorted_file_";    // Name of sorted chunk files
// header of the file "Books_rating.csv"
string title = "Id,Title,Price,User_id,profileName,review/helpfulness,review/score,review/time,review/summary,review/text";

// Function to get ID of a book and compare
int GetAndCompareId(string s1, string s2)
{
    int i = 0;
    string id1 = "";
    while (s1[i] != ',' && i < s1.length())
    {
        id1.push_back(s1[i]);
        i++;
    }
    string id2 = "";
    int j = 0;
    while (s2[j] != ',' && j < s2.length())
    {
        id2.push_back(s2[j]);
        j++;
    }
    // compare string
    return id1.compare(id2);
}

// Function to sort
void quickSort(string *a, int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right;
    string mid = a[(left + right) / 2];
    do
    {
        while (a[i] < mid)
            i++;
        while (a[j] > mid)
            j--;
        if (i <= j)
            swap(a[i++], a[j--]);
    } while (i <= j);
    quickSort(a, left, j);
    quickSort(a, i, right);
}

// Function to split large file CSV to many smaller file
// Each small file contain SizeofFile lines
// Quick Sort small file by the ID
int SplitAndSort(string inputFilename, int SizeofFile)
{
    fstream inputFile;
    inputFile.open(inputFilename, ios_base ::in | ios_base::binary);
    int numberOfFiles = 0;
    bool flag = true;
    string temp;
    getline(inputFile, temp);
    while (flag && inputFile.good())
    {
        string *arr = new string[SizeofFile];
        int i = 0;
        for (i; i < SizeofFile; i++)
        {
            if (inputFile.good())
                getline(inputFile, arr[i]);
            else
            {
                flag = false;
                break;
            }
        }
        // Sort arr
        quickSort(arr, 0, i - 1);
        string fileName = SPLITED_FILE + to_string(numberOfFiles) + ".csv";
        fstream outFile;
        outFile.open(fileName, ios_base::out | ios_base::binary);
        for (int j = 0; j < i; j++)
        {
            outFile << arr[j];
            if (j != i)
                outFile << endl;
        }
        numberOfFiles++;
        delete[] arr;
        outFile.close();
    }
    inputFile.close();
    return numberOfFiles;
}

// Merge 2 file CSV into 1 file larger CSV
void MergeChunks(string filename_1, string filename_2, string foutname)
{
    fstream file_1, file_2, fout;
    file_1.open(filename_1, ios::in | ios::binary);
    file_2.open(filename_2, ios::in | ios::binary);
    fout.open(foutname, ios::out | ios::binary);
    string x;
    getline(file_1, x);
    string y;
    getline(file_2, y);
    while (!file_1.eof() && !file_2.eof())
    {
        if (GetAndCompareId(x, y) != 1)
        {
            fout << x << endl;
            getline(file_1, x);
        }
        else
        {
            fout << y << endl;
            getline(file_2, y);
        }
    }
    while (!file_1.eof())
    {
        fout << x << endl;
        getline(file_1, x);
    }
    while (!file_2.eof())
    {
        fout << y << endl;
        getline(file_2, y);
    }
    file_1.close();
    file_2.close();
    fout.close();
}

// Merge 2 file CSV into fstream
void MergeChunkstoFstream(string file_1, string file_2, fstream &fout)
{
    fstream filename_1, filename_2;
    filename_1.open(file_1, ios::in | ios::binary);
    filename_2.open(file_2, ios::in | ios::binary);
    string x;
    getline(filename_1, x);
    string y;
    getline(filename_2, y);
    while (!filename_1.eof() && !filename_2.eof())
    {
        if (GetAndCompareId(x, y) != 1)
        {
            fout << x << endl;
            getline(filename_1, x);
        }
        else
        {
            fout << y << endl;
            getline(filename_2, y);
        }
    }
    while (!filename_1.eof())
    {
        fout << x << endl;
        getline(filename_1, x);
    }
    while (!filename_2.eof())
    {
        fout << y << endl;
        getline(filename_2, y);
    }
    filename_1.close();
    filename_2.close();
    fout.close();
}

// Function to count the amount of file which splited
// A file contains size line
// return the amount of files splited
int innitnumberofFiles(int size)
{
    int numberofFiles = SplitAndSort(INPUT_FILE, size);
    return numberofFiles - 1;
}

// Finally, main file has to returned is "sorted_books_rating.csv"
// Merge all sorted small file into larger file CSV
void MergeTotalFiles(int numberofFiles)
{
    fstream *ReadFiles = new fstream[numberofFiles];
    fstream Output;
    for (int i = 0; i < numberofFiles; i++)
    {
        string s = SPLITED_FILE + to_string(i);
        ReadFiles[i].open(s, ios_base::in | ios_base::binary);
    }
    string file0 = SPLITED_FILE + to_string(0) + ".csv";
    string file1 = SPLITED_FILE + to_string(1) + ".csv";
    string a = SORTED_FILE + to_string(0) + ".csv";
    MergeChunks(file0, file1, a);
    for (int i = 2; i < numberofFiles; i++)
    {
        string b = SORTED_FILE + to_string(i) + ".csv";
        string f = SPLITED_FILE + to_string(i) + ".csv";
        if (i != numberofFiles - 1)
        {
            MergeChunks(a, f, b);
            a = b;
        }
        else
        {
            Output.open(b, ios::out | ios::binary);
            Output << title << endl;
            MergeChunkstoFstream(a, f, Output);
        }
    }
    string result = SORTED_FILE + to_string(numberofFiles - 1) + ".csv";
    rename(result.c_str(), "sorted_books_rating.csv");
    delete[] ReadFiles;
    Output.close();
}

// After sorting, remove all of small file to save memory
// not delete the last file
void RemoveFiles(int numberofFiles)
{
    for (int i = 0; i <= numberofFiles; i++)
    {
        string s = SPLITED_FILE + to_string(i);
        string fileName = s.append(".csv");
        remove(fileName.c_str());
    }

    for (int i = 0; i < numberofFiles - 1; i++)
    {
        if (i != 1)
        {
            string f = SORTED_FILE + to_string(i);
            string filesort = f.append(".csv");
            remove(filesort.c_str());
        }
    }
}
