#ifndef coordinate_h
#define coordinate_h

struct _coordinate
{
  float x;
  float y;
  int coord_id;
  struct _coordinate *next;
  struct _coordinate *previous;
};
typedef struct _coordinate Coordinate;


#endif