std::string differ(const std::string &s, int startI, int* endI);
  
std::string fStr(std::string func, std::string& arg){
  std::ostringstream oss;
  oss << "(" << func << " " << arg << ")";
  return oss.str();
}
bool consts(std::string &s){
  return s[0] != '(' && s[0] != 'x';
}
std::string getArgs(const std::string&s, int i, int*endI){
  std::string deriv;
  if (s[i] == '('){
    deriv = differ(s,i,endI);
  }else if(s[i] == 'x'){
    deriv = '1';
    *endI = i;
  }else{
    while (s[i] != ' ' && s[i] != ')'){
      i += 1;
    }
    *endI = i - 1;
    deriv = '0';
  }
  return deriv;
}
std::string simplify(char op, std::string& s1, std::string& s2){
  std::cout << op << " " << s1 << " " << s2 << "\n";
  if (op == '+' || op == '-'){
    if (s1[0] == '0'){
      if (op == '-'){
        std::string mult = "-1";
        return simplify('*', mult, s2);
      }
      return s2;  
    }
    if (s2[0] == '0'){
      return s1;
    }
  }
  if (op == '*'){
    if (s1[0] == '0' || s2[0] == '0'){
      return "0";
    }
    if (s1 == "1"){
      return s2;  
    }
    if (s2 == "1"){
      return s1;
    }
  }
  if (op == '/'){
    if (s1[0] == '0'){
      return "0";
    }
  }
  if (op=='^'){
    if (s2[0] == '0')
      return "1";
    if (s2 == "1")
      return "x";
  }
  if (consts(s1) and consts(s2)){
    std::cout << s1 << " " << s2 <<"\n\n";
    int o1 = std::stoi(s1);
    int o2 = std::stoi(s2);
    int agg = o1 * o2;
    if (op == '+')
      agg = o1 + o2;
    else if(op == '-')
      agg = o1 - o2;
    else if(op == '/'){
      if (o1 % o2 != 0){
        std::string flt = std::to_string(o1 / (float)o2);
        int i = flt.size() - 1;
        while (i >= 0 && flt[i] == '0'){
          i -= 1;
        }
        return flt.substr(0,i+1);
      }
      agg = o1 / o2;
      return std::to_string(agg);
    }
    else if(op == '^'){
      int sum = 1;
      for (int i = 0; i < o2; i ++ ){
        sum *= o1;
      }
      agg = sum;
    }
    return std::to_string(agg);
  
  }
  std::ostringstream oss;
  oss << "(" << op << " " << s1 << " " << s2 << ")";
  return oss.str();
}
std::string differ(const std::string &s, int startI, int* endI){
  int i = startI + 1;
  char op = s[i];
  bool alpha = std::isalpha(op);
  while (s[i] != ' '){
    i += 1;
  }
  i += 1;
  // get arg 1
  int start1 = i;
  std::string d1 = getArgs(s,i,endI);
  i = *endI;
  int end1 = i;
  if (alpha){
    *endI = *endI + 1;
    std::string deriv = "";
    std::string substr = s.substr(start1,end1-start1+1);
    if (op == 'c'){
      std::string mult = "-1";
      std::string sin = fStr("sin",substr);
      deriv = simplify('*',mult,sin);
    }else if (op == 's'){
      deriv = fStr("cos",substr);
    }else if (op == 't'){
      std::string cos = fStr("cos",substr);
      std::string power = "2";
      std::string squared = simplify('^',cos,power);
      return simplify('/',d1,squared);
    }else if (op == 'e'){
      deriv = fStr("exp",substr);
    }else if(op == 'l'){
      std::string numer = "1";
      deriv = simplify('/',numer,substr);
    }
    std::string mult = simplify('*',d1,deriv);
    std::cout << "FuncStr: " << d1 << ":" << deriv <<":" << mult<<"\n";
    return mult;
  }
  i = i + 2;
  int start2 = i;
  std::string d2 = getArgs(s,i, endI);
  int end2 = *endI;
  *endI = end2 + 1; 
  if (op == '+' || op == '-'){
    std::cout << "**" << start2 << " " << end2 << "\n\n";
    return simplify(op,d1,d2);
  }
  else if(op == '*'){
    std::cout <<" "<<start2<<" "<<end2<<"\n";
    std::cout << " "<<start1<<" "<<end1<<"\n";
    std::string substr = s.substr(start2,end2-start2+1);
    std::string n1 = simplify('*',d1,substr);
    substr = s.substr(start1,end1-start1+1);
    std::string n2 = simplify('*',substr,d2);
    std::cout << "N2: " <<n2<<"\n";
    return simplify('+',n1,n2);
  }
  else if(op == '/'){
    std::string substr = s.substr(start1,end1-start1+1);
    std::string n2 = simplify('*',substr,d2);
    substr = s.substr(start2,end2-start2+1);
    std::string n1 = simplify('*',d1,substr);
    std::string sub = simplify('-',n1,n2);
    std::cout << "SUB: " << sub<< " "<< n2 <<"\n";
    std::string power = std::string("2");
    std::string denom = simplify('^',substr, power);
    substr = simplify('/',sub,denom);
    return substr;
  }
  else if(op == '^'){
    std::string substrPwr = s.substr(start2,end2-start2+1);
    std::string p = std::string("1");
    std::string power = simplify('-',substrPwr,p);
    std::string substr = s.substr(start1,end1-start1+1);
    
    
    std::string raised = simplify('^',substr,power);
    std::string timesDer= simplify('*',d1,raised);
    return simplify('*',substrPwr,timesDer);
   
  }
  // return derivative
  //return upon closing parenthesis
  return d1 + " " + d2;
}
std::string diff(const std::string &s)
{
  std::cout << s << "\n";
  int endI = 0;
  if(s[0] != '('){
    return getArgs(s, 0, &endI);
  }
  std::string st = differ(s, 0, &endI);
  std::cout << " " << st << "\n";
  return st;
}
