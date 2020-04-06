#include <stdio.h>

#include "face.h"

//----------------------------------------------------------
void dumpFace( Face *face )
{
  printf("%5d,%6d,%6d", face->v1, face->v2, face->v3);
}

//----------------------------------------------------------

