package com.andrei.period;

import android.app.DatePickerDialog;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.TextView;

import java.util.Calendar;
import java.util.Objects;

public class SetupFirstPeriod extends AppCompatActivity {

    public static final String FIRST_DATE = "com.andrei.period.FIRST_DATE";
    public static final String PERIOD_CYCLE = "com.andrei.period.PERIOD_CYCLE";

    private static final String TAG = "MainActivity";
    private TextView mDisplayDate;
    private TextView mDisplayCycle;
    private Button proceedButton;
    private DatePickerDialog.OnDateSetListener mDateSetListener;

    @Override
    public void onBackPressed() {
        Intent intent = new Intent(Intent.ACTION_MAIN);
        intent.addCategory(Intent.CATEGORY_HOME);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_setup_first_period);

        mDisplayDate = findViewById(R.id.mDisplayDate);
        mDisplayCycle = findViewById(R.id.displayCycle);
        proceedButton = findViewById(R.id.proceed);

        mDisplayDate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Calendar cal = Calendar.getInstance();
                int year = cal.get(Calendar.YEAR);
                int month = cal.get(Calendar.MONTH) - 1;
                int day = cal.get(Calendar.DAY_OF_MONTH);
                cal.set(year, month-2, day);

                DatePickerDialog dialog = new DatePickerDialog(
                        SetupFirstPeriod.this,
                        android.R.style.Theme_Holo_Light_Dialog_MinWidth,
                        mDateSetListener,
                        year,month,day);

                Objects.requireNonNull(dialog.getWindow()).setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
                dialog.getDatePicker().setMaxDate(System.currentTimeMillis());
                dialog.getDatePicker().setMinDate(cal.getTimeInMillis());
                dialog.show();
            }
        });

        mDateSetListener = new DatePickerDialog.OnDateSetListener() {
            @Override
            public void onDateSet(DatePicker datePicker, int year, int month, int day) {
                month = month + 1;
                String date = day + "/" + month + "/" + year;
                mDisplayDate.setText(date);
                proceedButton.setVisibility(View.VISIBLE);
            }
        };
    }

    public void saveFirstPeriod(View view) {
        String period_cycle_string = mDisplayCycle.getText().toString();
        try {
            int period_cycle_int = Integer.parseInt(period_cycle_string);

            if (period_cycle_int > 20 && period_cycle_int < 45) {
                TextView textView = findViewById(R.id.mDisplayDate);
                String first_period_date = textView.getText().toString();

                Intent intent = new Intent(this, MainActivity.class);
                intent.putExtra(FIRST_DATE, first_period_date);
                intent.putExtra(PERIOD_CYCLE, period_cycle_string);
                startActivity(intent);
            }
        } catch (Exception e) {
            Log.d("CREATION", period_cycle_string);
        }
    }


}
