#include "headers/Configuration.h"
#include <iostream>
#include <vector>

int main()
{
    Board b(2);
    cin >> b;
    
    Configuration c(b);
    cout << c << endl;

    vector<Configuration> configs = c.makeDescendants();
    for(size_t i=0; i<configs.size(); ++i)
	cout << configs[i];
    
    return 0;
}
