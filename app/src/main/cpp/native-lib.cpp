#include <jni.h>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <exception>

class Calculadora
{
private:
    std::vector<std::string> tokens;
    bool parentesis;
    bool isDiviAndMult;
    bool MultAndDiv();
    bool SumAndRes();
    void QuitParentresis();

public:
    Calculadora(std::vector<std::string> &tokenP);
    Calculadora(char *str);
    Calculadora(std::string& str);
    bool reducir();
    void mostrar()
    {
        for(std::string i: tokens)
            std::cout << i ;
        std::cout << std::endl;
    }
    void recorrer(int i,double Operacion);
    std::string GetResult()
    {
        if(tokens.size()<1)return std::string("error");
        return tokens[0];
    }
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

    return env->NewStringUTF(str.c_str());

}



Calculadora::Calculadora(std::vector<std::string> &tokenP):tokens(tokenP)
{
    parentesis = true;
    isDiviAndMult = true;
    //mostrar();
    reducir();
}

Calculadora::Calculadora(char *str)
{
    parentesis = true;
    isDiviAndMult = true;
    std::string str1(str);
    if(str1.empty()!=false)return;
    tokenizar(str1);
    //mostrar();
    reducir();
}

Calculadora::Calculadora(std::string& str)
{
    parentesis = true;
    isDiviAndMult = true;
    if(str.empty()!=false)return;
    tokenizar(str);
    //mostrar();
    reducir();
}

bool Calculadora::tokenizar(std::string& str)
{
    const char* c;
    std::string token;
    std::string tokenA;
    for(c=str.c_str();*c!='\0';c++)
    {
        if( *c == ' ' || *c == '*' || *c == '/' || *c == '+' || *c == '-' || *c == '(' || *c == ')' ||  *c=='\t' || *c == '\n')
        {
            if(token.empty()==false)tokens.push_back(token);
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

bool Calculadora::reducir()
{
    QuitParentresis();
    if(MultAndDiv()==true) return reducir();
    if(SumAndRes()==true) return reducir();

    return false;
}

void Calculadora::recorrer(int i,double Operacion)
{
    char str[20];
    sprintf(str,"%g",Operacion);
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
    isDiviAndMult=false;
    return false;
}

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
