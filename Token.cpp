#include <string>
#define SyntaxToken int
class Token
{
    enum type
    {
        inizio,
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
        importa,
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
    };
    SyntaxToken matches(std::string token)
    {
        if (token.compare("inizio") == 0)
            return type::inizio;
        if (token.compare("da") == 0)
            return type::da;
        if (token.compare("restituisci") == 0)
            return type::restituisci;
        if (token.compare("restituisce") == 0)
            return type::restituisce;
        if (token.compare("scorri") == 0)
            return type::scorri;
        if (token.compare("funzione") == 0)
            return type::funzione;
        if (token.compare("se") == 0)
            return type::se;
        if (token.compare("altrimenti") == 0)
            return type::altrimenti;
        if (token.compare("infine") == 0)
            return type::infine;
        if (token.compare("prova") == 0)
            return type::prova;
        if (token.compare("errore") == 0)
            return type::errore;
        if (token.compare("sennonché") == 0)
            return type::sennonche;
        if (token.compare("finché") == 0)
            return type::finche;
        if (token.compare("importa") == 0)
            return type::importa;
        if (token.compare("in") == 0)
            return type::inTok;
        if (token.compare("passo") == 0)
            return type::passo;
        if (token.compare("crea") == 0)
            return type::crea;
        if (token.compare("distruggi") == 0)
            return type::distruggi;
        if (token.compare("eredita") == 0)
            return type::eredita;
        if (token.compare("come") == 0)
            return type::come;
        if (token.compare("eccezione") == 0)
            return type::eccezione;
        if (token.compare("pubblico") == 0)
            return type::pubblico;
        if (token.compare("ristretto") == 0)
            return type::ristretto;
        if (token.compare("interno") == 0)
            return type::interno;
        if (token.compare("ristretto") == 0)
            return type::ristretto;
        if (token.compare("valuta") == 0)
            return type::valuta;
        if (token.compare("caso") == 0)
            return type::caso;
        if (token.compare("predefinito") == 0)
            return type::predefinito;
        if (token.compare("lancia") == 0)
            return type::lancia;
    }
};