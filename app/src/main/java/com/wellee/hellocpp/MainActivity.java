package com.wellee.hellocpp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private EditText et1;
    private EditText et2;
    private Button result;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int sum(int x, int y);

    public void tip(){
        Toast.makeText(this,"from_native", Toast.LENGTH_LONG).show();
    }

    private void initView() {
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        et1 = findViewById(R.id.et1);
        et2 = findViewById(R.id.et2);
        result = findViewById(R.id.btn_result);
    }

    public void calculator(View view) {
        try {
            int num1 = Integer.parseInt(et1.getText().toString().trim());
            int num2 = Integer.parseInt(et2.getText().toString().trim());
            int sum = sum(num1, num2);
            result.setText(String.valueOf(sum));
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }
    }

    public void clear(View view) {
        et1.setText("");
        et2.setText("");
        result.setText("");
    }


    public native String callNativeString(String s);

    public void callNativeString(View view) {
        String s = callNativeString(((TextView) view).getText().toString());
        Log.e("WELLEE", "callNativeString————" + s);
    }
}
