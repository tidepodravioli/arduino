const int inchlength = 10;

void mov(direc dir)
{
  switch(dir){
    case INCH:
    break;

    case STRAIGHT:
    break;

    case LEFT:
    break;

    case RIGHT:
    break;
  }
}

bool decision()
{
  mov(INCH);
  if(mes() == empty) return false;
  else return true;
}

bool win()
{
  mov(INCH);
  
}

int mes()
{
  return empty;
}
