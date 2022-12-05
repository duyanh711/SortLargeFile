#include "SortBigData.h"

unsigned int Size = 300000;

int main()
{
    cout << "Spliting input to chunks and Sorting chunks....\n";

    int numWays = innitnumberofFiles(Size);

    cout << "Splited to " << numWays << " sorted chunks\n";

    cout << "Start merging sorted chunks into sorted large file....\n";

    MergeTotalFiles(numWays);

    RemoveFiles(numWays);

    cout << "Finish sorting file!!!\n";
    cout << "Final sorted file name is: sorted_books_rating.csv\n";

    return 0;
}