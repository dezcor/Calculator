package com.example.dezcorjm.pruebasnk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.util.Locale;

public class SimpleCalc extends AppCompatActivity implements android.view.View.OnClickListener  {

    Button btNueve;
    Button btOcho;
    Button btSiete;
    Button btSeis;
    Button btSinco;
    Button btCuatro;
    Button btTres;
    Button btDos;
    Button btUno;
    Button btCero;
    Button btPunto;
    Button btParenteisR;
    Button btParenteisL;
    Button btDel;
    Button btDelAll;
    Button btMult;
    Button btSum;
    Button btResta;
    Button btDiv;
    Button btIgual;
    EditText tbxX;

    double arg1, arg2, ans;
    boolean isFirst, huboOper;
    int operacion; //1->suma,2->resta,3->mult,4->div,5->porcent

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_simple_calc);
        btNueve = findViewById(R.id.btNueve);
        btNueve.setOnClickListener(this);
        btOcho =  findViewById(R.id.btOcho);
        btOcho.setOnClickListener(this);
        btSiete =  findViewById(R.id.btSiete);
        btSiete.setOnClickListener(this);
        btSeis =  findViewById(R.id.btSeis);
        btSeis.setOnClickListener(this);
        btSinco =  findViewById(R.id.btSinco);
        btSinco.setOnClickListener(this);
        btCuatro = findViewById(R.id.btCuatro);
        btCuatro.setOnClickListener(this);
        btTres =  findViewById(R.id.btTres);
        btTres.setOnClickListener(this);
        btDos = findViewById(R.id.btDos);
        btDos.setOnClickListener(this);
        btUno = findViewById(R.id.btUno);
        btUno.setOnClickListener(this);
        btCero = findViewById(R.id.btCero);
        btCero.setOnClickListener(this);
        btPunto = findViewById(R.id.btPunto);
        btPunto.setOnClickListener(this);
        btMult = findViewById(R.id.btMult);
        btMult.setOnClickListener(this);
        btDiv = findViewById(R.id.btDiv);
        btDiv.setOnClickListener(this);
        btSum = findViewById(R.id.btSum);
        btSum.setOnClickListener(this);
        btResta = findViewById(R.id.btResta);
        btResta.setOnClickListener(this);
        btParenteisL =  findViewById(R.id.btParentL);
        btParenteisL.setOnClickListener(this);
        btParenteisR = findViewById(R.id.btParentR);
        btParenteisR.setOnClickListener(this);
        btDel =  findViewById(R.id.btDel);
        btDel.setOnClickListener(this);
        btDelAll = findViewById(R.id.btDelAll);
        btDelAll.setOnClickListener(this);
        btIgual = findViewById(R.id.btIgual);
        btIgual.setOnClickListener(this);
        // Example of a call to a native method
        tbxX =  findViewById(R.id.tbxX);
        tbxX.setFocusableInTouchMode(false);

        isFirst = true;
        huboOper = true;
    }

    @Override
    public void onClick(View view)
    {
        char Mult;
        int Nivel;
        String Punto;
        if(huboOper) tbxX.setText("");
        switch (view.getId())
        {
            case R.id.btNueve:
                tbxX.getText().append('9');
                huboOper = false;
                break;
            case R.id.btOcho:
                tbxX.getText().append('8');
                huboOper = false;
                break;
            case R.id.btSiete:
                tbxX.getText().append('7');
                huboOper = false;
                break;
            case R.id.btSeis:
                tbxX.getText().append('6');
                huboOper = false;
                break;
            case R.id.btSinco:
                tbxX.getText().append('5');
                huboOper = false;
                break;
            case R.id.btCuatro:
                tbxX.getText().append('4');
                huboOper = false;
                break;
            case R.id.btTres:
                tbxX.getText().append('3');
                huboOper = false;
                break;
            case R.id.btDos:
                tbxX.getText().append('2');
                huboOper = false;
                break;
            case R.id.btUno:
                tbxX.getText().append('1');
                huboOper = false;
                break;
            case R.id.btCero:
                tbxX.getText().append('0');
                huboOper = false;
                break;
            case R.id.btPunto:
                if(tbxX.getText().length()>0)//comprobar que se puede poner el punto.
                {
                    Punto=tbxX.getText().toString();
                    Mult=Punto.charAt(Punto.length() - 1);
                    if(Mult=='+' || Mult == '*' || Mult == '/' ||Mult == '-')
                    {
                        tbxX.getText().append('0');
                        tbxX.getText().append('.');
                    }
                    else if(Mult=='.')
                    {
                        tbxX.getText().delete(tbxX.getText().length() - 1, tbxX.getText().length());
                        tbxX.getText().append('.');
                    }
                    else
                    {
                        int count=0;
                        for(int i=Punto.length()-1;i>0;i--)
                        {
                            Mult=Punto.charAt(i);
                            if(Mult=='+' || Mult == '*' || Mult == '/' ||Mult == '-')
                            {
                                break;
                            }
                            else if(Mult=='.')
                            {
                                count++;
                                break;
                            }
                        }
                        if(count==0)
                            tbxX.getText().append('.');
                    }
                }
                else
                {
                    tbxX.getText().append('0');
                    tbxX.getText().append('.');
                }

                break;
            case R.id.btParentL:
                //Agregar código
                break;
            case R.id.btParentR:
                //Agregar código
                break;
            case R.id.btMult:
                if(tbxX.getText().length()>=1)
                {
                    arg2 = Double.parseDouble(tbxX.getText().toString());
                    operacion = 3;
                    Solve();
                }
                break;
            case R.id.btDiv:
                if(tbxX.getText().length()>=1)
                {
                    arg2 = Double.parseDouble(tbxX.getText().toString());
                    operacion = 4;
                    Solve();
                }
                break;
            case R.id.btResta:
                if(tbxX.getText().length()>0)//puede estar al principio
                {
                    arg2 = Double.parseDouble(tbxX.getText().toString());
                    operacion = 2;
                    Solve();
                }
                tbxX.getText().append('-');
                break;
            case R.id.btSum:
                if(tbxX.getText().length()>=1) //Comprueba que almenos hay un algo para sumar
                {
                    arg2 = Double.parseDouble(tbxX.getText().toString());
                    operacion = 1;
                    Solve();
                }
                break;
            case R.id.btDel:
                if(tbxX.getText().length()>0) {
                    tbxX.getText().delete(tbxX.getText().length() - 1, tbxX.getText().length());
                }
                break;
            case R.id.btDelAll:
                tbxX.getText().clear();
                isFirst = true;
                break;
            case R.id.btIgual:
                arg2 = Double.parseDouble(tbxX.getText().toString());
                Solve();
                isFirst = true;
                break;

        }
    }

    void Solve(){
        if(isFirst) {
            ans = arg2;
            isFirst = false;
        }else{
            if (operacion == 1) {
                ans = arg1 + arg2;
            } else if (operacion == 2) {
                ans = arg1 - arg2;
            } else if (operacion == 3) {
                ans = arg1 * arg2;
            } else if (operacion == 4) {
                ans = arg1 / arg2;
            } else if (operacion == 5) {
                //Falta código
            }
        }
        arg1 = ans;
        String s = String.format(Locale.getDefault(),"%.2f",ans);
        tbxX.setText(s);
        huboOper = true;
    }
}
