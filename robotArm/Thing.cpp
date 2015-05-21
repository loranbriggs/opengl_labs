#include "Thing.h"

Thing::Thing()
{
        // dimensions
        size                =     0.5;
        x                   =     3;
        y                   =     35;
        z                   =     3;
        rx                   =     0;
        ry                   =     0;
        rz                   =     0;

}

void Thing::Reset()
{
    y = 35;
}
