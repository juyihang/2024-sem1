

#include <cstdlib>
#include "AI/Max-Min_Search/WITHAI_SEARCH.h"
using namespace std;




int main() {

    //Chess_Process_Without_AI(MainBoard,800,800,1);

    Chess_Process_With_AI(MainBoard,800,800,1,16,8,false,false);

    system("pause");

    return 0;
}
