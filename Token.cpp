#include <string> 
class Token{
    public:
         static const std::string inizio;
/*
    Stainizio,
    da,
    restituisci,
    restituisce,
    scorri,
    funzione,
    se,
    altrimenti,
    infine,
    prova,
    errore,
    sennonche,
    finche,
    importa
    inTok,
    passo,
    crea,
    distruggi,
    eredita,
    come,
    eccezione,
    pubblico,
    ristretto,
    interno,
    valuta,
    caso,
    predefinito,
    lancia
*/
    public boolean equal(std::string a, std::string b){
        return a.compare(b)==0;
    }
};

const std::string Token::inizio = "inizio";
