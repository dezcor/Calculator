#include <jni.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <exception>
#include <regex>

/**
 * @class Calculadora
 * @brief Recibe la cadena de operación para resolverla.
 *
 * Separa la cadena en tokens identificando números y operaciones, realiza las operaciones
 * dentro y fuera de los paréntesis en orden algebráico.
 */

class Calculadora
{
private:
    std::vector<std::string> tokens;
    bool parentesis;
    bool isDiviAndMult;
    /**
     * @brief Realiza las operaciones de multiplicación y división.
     * @return false cuando ya no hay más operaciones por hacer.
     */
    bool MultAndDiv();
    /**
     * @brief Realiza las operaciones de suma y resta.
     * @return false cuando ya no hay más operaciones por hacer.
     */
    bool SumAndRes();
    /**
     * @brief Realiza las operaciones dentro de paréntesis.
     */
    void QuitParentresis();

public:
    /**
     * @brief Constructor para vector de strings.
     * @param tokenP Vector de operaciones.
     */
    Calculadora(std::vector<std::string> &tokenP);
    /**
     * @brief Constructor para arreglo de chars.
     * @param str Operación a realizar.
     */
    Calculadora(char *str);
    /**
     * @brief Constructor para string.
     * @param str Operación a realizar.
     */
    Calculadora(std::string& str);
    /**
     * @brief Resuelve la operación.
     *
     * Llama funciones recursivamente para hacer las operaciones.
     * @return false cuando ya no hay más operaciones a realizar.
     */
    bool reducir();
    /**
    * @brief Al realizar una operacion esta se recorre para reducir la operacion.
    * @param i Indice del token.
    * @param Operacion Operando izquierdo de la operación.
    */
    void recorrer(int i,double Operacion);
    /**
     * @brief Regresa el resultado de la operación completa
     * @return Cadena resultado.
     */
    std::string GetResult();
    /**
     * @brief Separa en la operación de entrada en tokens.
     * @param token Cadena a tokenizar.
     * @return false, si no hay tokens.
     */
    bool tokenizar(std::string& token);
};

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_dezcorjm_pruebasnk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject obj,
        jstring jstr/* this */) {
    jboolean isTrue=true;
    std::string str=env->GetStringUTFChars(jstr,&isTrue);
    try
    {
        Calculadora S(str);
        str=S.GetResult().c_str();
    }
    catch(std::exception e)
    {
        str=e.what();
    }
    std::regex Num("-?[0-9]+.?[0-9]*(E(\\+|\\-)?[0-9]*)?");
    if(std::regex_match(str,Num)==false)
    {
        return env->NewStringUTF("error");
    }
    //*************************************
    return env->NewStringUTF(str.c_str());

}



Calculadora::Calculadora(std::vector<std::string> &tokenP):tokens(tokenP)
{
    parentesis = true;
    isDiviAndMult = true;
    reducir();
}

Calculadora::Calculadora(char *str)
{
    parentesis = true;
    isDiviAndMult = true;
    std::string str1(str);
    if(str1.empty()!=false)return;
    tokenizar(str1);
    reducir();
}

Calculadora::Calculadora(std::string& str)
{
    parentesis = true;
    isDiviAndMult = true;
    if(str.empty()!=false)return;
    tokenizar(str);
    reducir();
}
//tokeniza
bool Calculadora::tokenizar(std::string& str)
{
    const char* c;
    std::string token;
    std::string tokenA;
    bool isfirst=true;
    for(c=str.c_str();*c!='\0';c++)
    {
        if( *c == ' ' || *c == '*' || *c == '/' || *c == '+' || *c == '-' || *c == '(' || *c == ')' ||  *c=='\t' || *c == '\n')
        {
            if(token.empty()==false)tokens.push_back(token);
            else
            {
                if(isfirst==true)
                {
                    if(*c=='-')
                    {
                        token+=*c;
                        isfirst=false;
                        continue;
                    }
                    else if(*c== '+')
                    {
                        token+=*c;
                        isfirst=false;
                        continue;
                    }
                    isfirst=false;
                }
                else
                {
                    const char *aux = c - 1;
                    if ((*aux == '*' || *aux == '+' || *aux == '/' || *aux == '(') && *c == '-')
                    {
                        if( *aux == '+')
                            token.pop_back();
                        else token += *c;
                        continue;
                    }
                    else if ((*aux == '*' || *aux == '-' || *aux == '/') && *c == '+')
                    {
                        if( *aux == '-')
                            continue;
                        else token += *c;
                        continue;
                    }
                }
            }
            if(*c != ' ' && *c!='\n' && *c != '\t')
            {
                tokens.push_back(tokenA=*c);
            }
            token="";
        }
        else
        {
            token += *c;
        }
    }
    if(token.empty()==false)tokens.push_back(token);
    return true;
}
//Busca los Tokens que indican operacion para realizar la operacion
bool Calculadora::reducir()
{
    QuitParentresis();//realiza cualquier operacion que este dentro de un parentesis
    if(MultAndDiv()==true) return reducir();//realiza las operaciones *,/
    if(SumAndRes()==true) return reducir();//realiza las Sumas y restas

    return false;
}

void Calculadora::recorrer(int i,double Operacion)
{
    char str[100];
    sprintf(str,"%.20f",Operacion);
    tokens[i-1]=str;
    if((i+2)<(int)tokens.size())
        tokens[i]=tokens[i+2];
    else
    {
        tokens.resize((int)tokens.size()-2);
        return;
    }
    int j=i+1;
    while(j<((int)tokens.size()-2))
    {
        tokens[j]=tokens[j+2];
        j++;
    }
    tokens.resize((int)tokens.size()-2);
}
//Busca realizar operaciones * y /
bool Calculadora::MultAndDiv()
{
    double Operacion=0;
    if(isDiviAndMult==false)return false;

    for(int i = 1; i<((int)tokens.size() -1); i++)
    {
        if(tokens[i]=="*")
        {
            Operacion = atof(tokens[i-1].c_str()) * atof(tokens[i+1].c_str());
            recorrer(i,Operacion);
            return true;
        }
        if(tokens[i]=="/")
        {
            Operacion = atof(tokens[i-1].c_str()) / atof(tokens[i+1].c_str());
            recorrer(i,Operacion);
            return true;
        }
    }
    //cuando se llega hasta este punto se considera que ya no hay mas tokens * y /
    isDiviAndMult=false;
    return false;
}
//Busca realizar operaciones + y -
bool Calculadora::SumAndRes()
{
    double Operacion = 0;
    for(int i = 1; i<( (int)tokens.size() -1 ); i++)
    {
        if(tokens[i]=="+")
        {
            Operacion = atof(tokens[i-1].c_str()) + atof(tokens[i+1].c_str());
            recorrer(i, Operacion);
            return true;
        }
        if(tokens[i]=="-")
        {
            Operacion = atof(tokens[i-1].c_str()) - atof(tokens[i+1].c_str());
            recorrer(i,Operacion);
            return true;
        }
    }
    return false;
}

//Busca las operaciones entre parentesis.
void Calculadora::QuitParentresis()
{
    int NumParetesis = 0;
    if(parentesis==false)return;
    for(int i = 0; i<(int)(tokens.size()); i++)
    {
        if(tokens[i]=="(")
        {
            NumParetesis++;
            std::vector<std::string> tokensAux;
            int j=i+1;
            while(j < (int)tokens.size() && ( tokens[j] != ")" || NumParetesis > 1))
            {
                if(tokens[j]=="(")
                    NumParetesis++;
                if(tokens[j]==")")
                    NumParetesis--;
                tokensAux.push_back(tokens[j]);
                j++;
            }
            Calculadora Calc(tokensAux);
            tokens[i] = Calc.GetResult();
            int Pi=j - i;
            j=i+1;
            while((j+Pi)<(int)tokens.size())
            {
                tokens[j]=tokens[j+Pi];
                j++;
            }
            tokens.resize( (int)tokens.size() - Pi );
            //mostrar();
            NumParetesis=0;
        }
    }
    parentesis = false;
}
//regresa el resultado
std::string Calculadora::GetResult()
{
    if(tokens.size()<1)return std::string("Error");
    char str[100];
    std::regex Num("-?[0-9]+.?[0-9]*(E(\\+|\\-)?[0-9]*)?");
    //comprueba que sea un numero valido.
    if(std::regex_match(tokens[0],Num))
    {
        sprintf(str,"%.15G",atof(tokens[0].c_str()));
        tokens[0]=str;
    }
    return tokens[0];
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_dezcorjm_pruebasnk_SimpleCalc_stringFromJNI(JNIEnv *env, jobject instance,
                                                             jstring str_) {
    jboolean isTrue = (jboolean) true;
    std::string str = env->GetStringUTFChars(str_, &isTrue);
    try {
        Calculadora S(str);
        str = S.GetResult().c_str();
    }
    catch (std::exception e) {
        str = e.what();
    }
    std::regex Num("-?[0-9]+.?[0-9]*(E(\\+|\\-)?[0-9]*)?");
    if (!std::regex_match(str, Num)) {
        return env->NewStringUTF("Error");
    }
    //*************************************
    return env->NewStringUTF(str.c_str());
}

