int Lval = 87;
int Rval = 92;

int fwddel = 450;
int turndel = 200;
int inch = 600;

int pass = 0;
bool followline(int sensor){
  switch(sensor){
    case B00100:
      swr(Lval, Rval);
      txr("Straight");
      return true;
      break;
    case B01000:
      swr(Lval, Lval);
      txr("Slight left");
      return true;
      break;
    case B00010:
      swr(Rval,Rval);
      txr("Slight right");
      return true;
      break;
    case B11000:
      swr(Lval,Lval);
      txr("Straighten left");
      return true;
      break;
    case B00011:
      swr(Rval,Rval);
      txr("Straighten right");
      return true;
      break;
    case B10000:
      swr(Lval,Lval);
      txr("Bad left");
      return true;
      break;
    case B00001:
      swr(Rval,Rval);
      txr("Bad right");
      return true;
      break;
    case B11100:
      swr(Lval, Rval);
      delay(inch);
      if(result() == B00100){
       swr(Rval,Lval);
       delay(inch);
       txr("T-TYPE (tl)");
       tstore = tl;
       return false;
      }

      swr(Rval,Lval);
      delay(inch - fwddel);
      txr("Left turn");
      swr(Lval, Lval);
      while(result() != B00100);
      delay(turndel);

      compass = compassincr(compass, false);
      return true;
      break;
    case B00111:
      swr(Lval, Rval);
      delay(inch);
      if(result() == B00100){
        swr(Rval,Lval);
        delay(inch);
        txr("T-TYPE (tr)");
        tstore = tr;
        return false;
      }
      
      swr(Rval,Lval);
      delay(inch - fwddel);
      txr("Right turn");
      swr(Rval,Rval);
      while(result() != B00100);
      delay(turndel);

      compass = compassincr(compass, true);
      return true;
      break;
    case B00000:
      txr("U-turn");
      swr(Lval,Lval);
      while(result() != B00100);

      for(int i = 0; i <= 3; i++) compass = compassincr(compass, true);
      return true;
      break;
    case B11111:
      txr("T-TYPE (tb)");
      tstore = tb;
      return false;
      break;
      
  }
  
}

void makeDecision(Ttypes input, char comp){
  origins[decision] = comp;
  
  if(forward){
    if (input == northflat){
      switch (comp){
        case 'n':
          turn(LEFT);
          txr("nf:N:LEFT");
          break;
        case 'e':
          turn(RIGHT);
          txr("nf:E:RIGHT");
          break;
        case 'w':
          turn(LEFT);
          txr("nf:W:LEFT");
          break;
      }
    }
    else if(input == northshort){
      switch(comp){
        case 'w':
          turn(RIGHT);
          txr("ns:W:RIGHT");
          break;
        case 'e':
          turn(LEFT);
          txr("ns:E:LEFT");
          break;
        case 's':
          turn(LEFT);
          txr("ns:S:LEFT");
          break;
      }
    }
    else if(input == northlL){
      switch(comp){
        case 'n':
          turn(LEFT);
          txr("nlL:N:LEFT");
          break;
        case 's':
          turn(RIGHT);
          txr("nlL:S:RIGHT");
          break;
        case 'w':
          turn(LEFT);
          txr("nlL:W:LEFT");
          break;
      }
    }
    else if(input == northlR){
      switch(comp){
        case 'n':
          turn(RIGHT);
          txr("nlR:N:RIGHT");
          break;
        case 's':
          turn(LEFT);
          txr("nlR:S:LEFT");
          break;
        case 'e':
          turn(LEFT);
          txr("nlR:E:LEFT");          
          break;
      }
    }

    passes[decision]++;
  }
  else{
    if(input == northflat){
      if(origins[decision] == 'e'){
        switch(passes[decision]){
          case 1:
            turn(RIGHT);
            passes[decision]++;
            break;
          case 2:
            advance();
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
        else if(origins[decision] == 'w'){
          switch(passes[decision]){
            case 1:
              turn(LEFT);
              passes[decision]++;
              break;
            case 2:
              advance();
              origins[decision] = 0x0;
              decision--;
              break;
          }
      }
      else if(origins[decision] == 'n'){
        switch(passes[decision]){
          case 1:
            advance();
            passes[decision]++;
            break;
          case 2:
            turn(LEFT);
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
    }
    else if(input == northshort){
      if(origins[decision] == 'e'){
        switch(passes[decision]){
          case 1:
            turn(LEFT);
            passes[decision]++;
            break;
          case 2:
            advance();
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
      else if(origins[decision] == 's'){
        switch(passes[decision]){
          case 1:
            turn(RIGHT);
            passes[decision]++;
            break;
          case 2:
            turn(LEFT);
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
      else if(origins[decision] == 'w'){
        switch(passes[decision]){
          case 1:
            turn(RIGHT);
            passes[decision]++;
            break;
          case 2:
            advance();
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
    }
    else if(input == northlL){
      if(origins[decision] == 'n'){
        switch(passes[decision]){
          case 1:
            turn(LEFT);
            passes[decision]++;
            break;
          case 2:
            advance();
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
      else if(origins[decision] == 's'){
        switch(passes[decision]){
          case 1:
            turn(RIGHT);
            passes[decision]++;
            break;
          case 2:
            advance();
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
      else if(origins[decision] == 'w'){
        switch(passes[decision]){
          case 1:
            advance();
            passes[decision]++;
            break;
          case 2:
            turn(LEFT);
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
    }
    else if(input == northlR){
      if(origins[decision] == 'n'){
        switch(passes[decision]){
          case 1:
            turn(RIGHT);
            passes[decision]++;
            break;
          case 2:
            advance();
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
      else if(origins[decision] == 'e'){
        switch(passes[decision]){
          case 1:
            advance();
            passes[decision]++;
            break;
          case 2:
            turn(LEFT);
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
      else if(origins[decision] == 's'){
        switch(passes[decision]){
          case 1:
            turn(LEFT);
            passes[decision]++;
            break;
          case 2:
            advance();
            origins[decision] = 0x0;
            decision--;
            break;
        }
      }
    }
  }

  decision++;
}

char solvemaze(){
  
}
