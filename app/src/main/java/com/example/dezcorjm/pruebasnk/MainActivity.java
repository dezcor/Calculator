package com.example.dezcorjm.pruebasnk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements android.view.View.OnClickListener {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
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
    EditText tbxResult;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btNueve = (Button) findViewById(R.id.btNueve);
        btNueve.setOnClickListener(this);
        btOcho = (Button) findViewById(R.id.btOcho);
        btOcho.setOnClickListener(this);
        btSiete = (Button) findViewById(R.id.btSiete);
        btSiete.setOnClickListener(this);
        btSeis = (Button) findViewById(R.id.btSeis);
        btSeis.setOnClickListener(this);
        btSinco = (Button) findViewById(R.id.btSinco);
        btSinco.setOnClickListener(this);
        btCuatro = (Button) findViewById(R.id.btCuatro);
        btCuatro.setOnClickListener(this);
        btTres = (Button) findViewById(R.id.btTres);
        btTres.setOnClickListener(this);
        btDos = (Button) findViewById(R.id.btDos);
        btDos.setOnClickListener(this);
        btUno = (Button) findViewById(R.id.btUno);
        btUno.setOnClickListener(this);
        btCero = (Button) findViewById(R.id.btCero);
        btCero.setOnClickListener(this);
        btPunto = (Button) findViewById(R.id.btPunto);
        btPunto.setOnClickListener(this);
        btMult = (Button) findViewById(R.id.btMult);
        btMult.setOnClickListener(this);
        btDiv = (Button) findViewById(R.id.btDiv);
        btDiv.setOnClickListener(this);
        btSum = (Button) findViewById(R.id.btSum);
        btSum.setOnClickListener(this);
        btResta = (Button) findViewById(R.id.btResta);
        btResta.setOnClickListener(this);
        btParenteisL = (Button) findViewById(R.id.btParentL);
        btParenteisL.setOnClickListener(this);
        btParenteisR = (Button) findViewById(R.id.btParentR);
        btParenteisR.setOnClickListener(this);
        btDel = (Button) findViewById(R.id.btDel);
        btDel.setOnClickListener(this);
        btDelAll = (Button) findViewById(R.id.btDelAll);
        btDelAll.setOnClickListener(this);
        btIgual = (Button) findViewById(R.id.btIgual);
        btIgual.setOnClickListener(this);
        // Example of a call to a native method
        tbxX = (EditText) findViewById(R.id.tbxX);
        // Example of a call to a native method
        tbxResult = (EditText) findViewById(R.id.tbxResult);
    }

    @Override
    public void onClick(View view)
    {
        switch (view.getId())
        {
            case R.id.btNueve:
                tbxX.getText().append('9');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btOcho:
                tbxX.getText().append('8');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btSiete:
                tbxX.getText().append('7');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btSeis:
                tbxX.getText().append('6');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btSinco:
                tbxX.getText().append('5');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btCuatro:
                tbxX.getText().append('4');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btTres:
                tbxX.getText().append('3');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btDos:
                tbxX.getText().append('2');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btUno:
                tbxX.getText().append('1');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btCero:
                tbxX.getText().append('0');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btPunto:
                tbxX.getText().append('.');
                break;
            case R.id.btParentL:
                tbxX.getText().append(')');
                tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                break;
            case R.id.btParentR:
                tbxX.getText().append('(');
                break;
            case R.id.btMult:
                tbxX.getText().append('*');
                break;
            case R.id.btDiv:
                tbxX.getText().append('/');
                break;
            case R.id.btResta:
                tbxX.getText().append('-');
                break;
            case R.id.btSum:
                tbxX.getText().append('+');
                break;
            case R.id.btDel:
                if(tbxX.getText().length()>0) {
                    tbxX.getText().delete(tbxX.getText().length() - 1, tbxX.getText().length());
                    tbxResult.setText(stringFromJNI(tbxX.getText().toString()));
                }
                break;
            case R.id.btDelAll:
                tbxX.getText().clear();
                tbxResult.getText().clear();
                break;
            case R.id.btIgual:
                tbxX.getText().clear();
                break;

        };
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(String str);


}
