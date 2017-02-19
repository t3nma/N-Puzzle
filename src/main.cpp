#include "headers/Board.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    /* BOARD INIT */
    Board s(4), e(4);

    /* BOARD INPUT */
    cin >> s >> e;

    /* BOARD OUTPUT */
    cout << "Start Configuration: \n" << s << endl << endl;
    cout << "End Configuration: \n" << e << endl << endl;

    /* BOARD MANHATTAN */
    cout << "Manhattan Distance Start->End:\n" << s.manhattanDist(e) << endl << endl;

    /* BOARD DESCENDANTS */
    cout << "Start Descendants:\n";
    vector<Board> desc = s.makeDescendants();
    for(size_t i=0; i<desc.size(); ++i)
	cout << desc[i] << endl << endl;

}
