#include "history.h"

History::History():Table("history")
{
    id = 0;
}

History *History::currentHistory()
{
    History model;
    History* row = model.getRow<History>();
    if(!row)
        row = new History();
    return row;
}
