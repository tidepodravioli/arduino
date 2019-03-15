Ttypes getType(Tblocks in, char compassdir){
  if(compassdir == 'n'){
    if(in == Tblocks::tl) return Ttypes::northlL;
    if(in == Tblocks::tr) return Ttypes::northlR;
    if(in == Tblocks::tb) return Ttypes::northflat;
  }
  else if(compassdir == 'e'){
    if(in == Tblocks::tb) return Ttypes::northlL;
    if(in == Tblocks::tr) return Ttypes::northflat;
    if(in == Tblocks::tl) return Ttypes::northshort;
  }
  else if(compassdir == 's'){
    if(in == Tblocks::tl) return Ttypes::northlL;
    if(in == Tblocks::tr) return Ttypes::northlR;
    if(in == Tblocks::tb) return Ttypes::northshort;
  }
  else if(compassdir == 'w'){
    if(in == Tblocks::tb) return Ttypes::northlR;
    if(in == Tblocks::tl) return Ttypes::northflat;
    if(in == Tblocks::tr) return Ttypes::northshort;
  }
}

char compassincr(char comp, bool add){
  if(add){
    if(comp == 'n') return 'e';
    else if (comp == 'e') return 's';
    else if (comp == 's') return 'w';
    else if (comp == 'w') return 'n';
  }
  else{
    if(comp == 'n') return 'w';
    else if (comp == 'w') return 's';
    else if (comp == 's') return 'e';
    else if (comp == 'e') return 'n';
  }
}
