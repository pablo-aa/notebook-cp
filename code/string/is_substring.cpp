// equivalente ao in do python

bool is_substring(string a, string b){ // verifica se a é substring de b
    for(int i = 0; i < b.size(); i++){
        int it = i, jt = 0; // b[it], a[jt]
        
        while(it < b.size() && jt < a.size()){
            if(b[it] != a[jt])
                break;
            
            it++;
            jt++;
            
            if(jt == a.size())
                return true;
        }
    }
    
    return false;
}