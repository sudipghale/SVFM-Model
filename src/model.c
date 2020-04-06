#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"

//----------------------------------------------------------
Model *allocModel( int numVertices, int numFaces )
{
  Model *model = (Model*) calloc(1,sizeof(Model) );
  if(!model)
  {
    printf("calloc failed\n");
    exit(1);
  }
  Vertex *ptr_vertex = calloc (numVertices, sizeof(Vertex));
  Face *ptr_faces = calloc(numFaces, sizeof(Face));
  if(!ptr_vertex || !ptr_faces)
  {
    printf("calloc for vertix or faces failed \n");
    exit(1);
  }
  model->m_numVertices = numVertices;
  model->m_numFaces = numFaces;
  model->m_vertex = ptr_vertex;
  model->m_face = ptr_faces;

  return model;
 
}

//----------------------------------------------------------
void dumpModel( Model *model )
{
  printf( "#- Model parameters --------------------\n" );
  printf( "Vertex count : %5d\n", model->m_numVertices );
  printf( "Face count   : %5d\n", model->m_numFaces );

  printf( "\n#- Vertex list -------------------------\n" );
  for ( int i=0; i<model->m_numVertices; i++ ) {
    printf( "  [%5d]  ", i );
    dumpVertex( &model->m_vertex[i] );
    putc( '\n', stdout );
  }

  printf( "\n#- Face list ---------------------------\n" );
  for ( int i=0; i<model->m_numFaces; i++ ) {
    printf( "  [%5d]  ", i );
    dumpFace( &model->m_face[i] );
    putc( '\n', stdout );
  }

  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void freeModel( Model *model )
{
  if(model->m_vertex != NULL)
  {
    free(model->m_vertex);
  }
  if(model->m_face != NULL)
  {
    free(model->m_face);  
  }
  free(model);

}

//----------------------------------------------------------
Model *loadModel( char *fName )
{
  Model *model;
  FILE *file_prt;
  int count_vertex = 0;
  int count_face = 0;
  char buffer[500];
  int index_v =0, index_f =0;

  
  file_prt = fopen(fName, "r");
  if(file_prt == NULL)
  {
    printf("Error opening file %s\n", fName);
    exit(1);
  }

 while(fgets(buffer, sizeof(buffer), file_prt) != NULL)
 {
   if(buffer[0] != '#' && buffer[0] != '\n')
    {
      int i =0;
      while(isspace(buffer[i]))
      {
        i++; 
      }
      if(buffer[i] == 'v')
      {
        count_vertex++;
      }
      if(buffer[i] =='f')
      {
        count_face++;
      }
    }
      
 }

model = allocModel(count_vertex, count_face);
rewind(file_prt);

while(fgets(buffer, sizeof(buffer), file_prt) != NULL)
{
  char c;
  double x, y , z;
  int v1, v2, v3;
  if(buffer[0] != '#' && buffer[0] != '\n')
   {
     int i =0;
     while(isspace(buffer[i]))
     {
       i++; 
     }
     if(buffer[i] == 'v')
     {

       sscanf(buffer," %c %lf %lf %lf", &c, &x, &y, &z);
       model->m_vertex[index_v].x = x;
       model->m_vertex[index_v].y = y;
       model->m_vertex[index_v].z = z;
       index_v++;
     }
    if(buffer[i] == 'f')
    {
       sscanf(buffer," %c %d %d %d", &c, &v1, &v2, &v3);
       model->m_face[index_f].v1 = v1 -1;
       model->m_face[index_f].v2 = v2 -1;
       model->m_face[index_f].v3 = v3 -1;
       index_f++;
    }
  }
}

return model;

}

//----------------------------------------------------------

