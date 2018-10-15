package com.andrei.period;

import android.app.DatePickerDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Objects;

public class EditPeriod extends AppCompatActivity {

    private String start_date, end_date, days_until_string, pos;

    private DatePickerDialog.OnDateSetListener mDateSetListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_period);

        Intent intent = getIntent();
        start_date = intent.getStringExtra(PeriodAnalysis.PERIOD_START);
        end_date = intent.getStringExtra(PeriodAnalysis.PERIOD_END);
        pos = intent.getStringExtra(PeriodAnalysis.PERIOD_POS);

        final TextView start_textView = findViewById(R.id.start_period);
        TextView lasted_textView = findViewById(R.id.days_period);

        long days_until = getTimeUntilPeriod(end_date, start_date);
        days_until_string = Long.toString(days_until);

        String[] first_date = start_date.split(" ");
        SimpleDateFormat sdf = new SimpleDateFormat("dd MMM yyyy");
        GregorianCalendar calendar = new GregorianCalendar(
                Integer.parseInt(first_date[0]),
                Integer.parseInt(first_date[1]) - 1,
                Integer.parseInt(first_date[2])
        );

        start_textView.setText(sdf.format(calendar.getTime()));
        lasted_textView.setText(days_until_string);
        lasted_textView.setHint(days_until_string);

        start_textView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Calendar cal = Calendar.getInstance();
                int year = cal.get(Calendar.YEAR);
                int month = cal.get(Calendar.MONTH) - 1;
                int day = cal.get(Calendar.DAY_OF_MONTH);
                cal.set(year, month - 2, day);

                DatePickerDialog dialog = new DatePickerDialog(
                        EditPeriod.this,
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
                SimpleDateFormat sdf1 = new SimpleDateFormat("dd MMM yyyy");
                SimpleDateFormat sdf2 = new SimpleDateFormat("yyyy MM dd");
                GregorianCalendar calendar = new GregorianCalendar(
                        year,
                        month,
                        day
                );
                start_textView.setText(sdf1.format(calendar.getTime()));
                start_date = sdf2.format(calendar.getTime());
            }
        };
    }

    public long getTimeUntilPeriod(String date1, String date2) {

        String[] date_array1 = date1.split(" ");
        String[] date_array2 = date2.split(" ");

        Calendar cal1 = Calendar.getInstance();
        Calendar cal2 = Calendar.getInstance();

        cal1.set(Integer.parseInt(date_array1[0]), Integer.parseInt(date_array1[1])-1, Integer.parseInt(date_array1[2]));
        cal2.set(Integer.parseInt(date_array2[0]), Integer.parseInt(date_array2[1]) - 1, Integer.parseInt(date_array2[2]));

        return (cal1.getTimeInMillis() - cal2.getTimeInMillis()) / 1000 / 60 / 60 / 24 + 1;
    }

    public void ConfirmClicked(View view) {
        EditText editText = findViewById(R.id.days_period);

        SharedPreferences saved_values = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        SharedPreferences.Editor editor = saved_values.edit();

        String edit_start_string_shared = getString(R.string.period_template) + pos;
        String edit_end_string_shared = getString(R.string.period_template_end) + pos;

        String[] date = start_date.split(" ");
        Calendar calendar = Calendar.getInstance();
        calendar.set(Integer.parseInt(date[0]), Integer.parseInt(date[1]) - 1, Integer.parseInt(date[2]));

        long period_days = 86400000 * (Integer.parseInt(editText.getText().toString()) - 1);
        period_days += calendar.getTimeInMillis();

        calendar.setTimeInMillis(period_days);
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy MM dd");

        String update_end = sdf.format(calendar.getTime());
        editor.putString(edit_end_string_shared, update_end);
        editor.putString(edit_start_string_shared, start_date);
        editor.apply();

        Intent intent = new Intent(getApplicationContext(), MainActivity.class);
        startActivity(intent);
    }

    public void DeleteClicked(View view) {
        SharedPreferences saved_values = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        SharedPreferences.Editor editor = saved_values.edit();

        int period_list_size = saved_values.getInt(getString(R.string.period_list_size), 0);

        for (int i = Integer.parseInt(pos); i < period_list_size; i++) {
            String getKey_start = getString(R.string.period_template) + Integer.toString(i);
            String getKey_end = getString(R.string.period_template_end) + Integer.toString(i);

            String getKey_start_next = getString(R.string.period_template) + Integer.toString(i + 1);
            String getKey_end_next = getString(R.string.period_template_end) + Integer.toString(i + 1);

            editor.putString(getKey_start, saved_values.getString(getKey_start_next, "0"));
            editor.putString(getKey_end, saved_values.getString(getKey_end_next, "0"));
        }

        period_list_size--;
        editor.putInt(getString(R.string.period_list_size), period_list_size);
        editor.apply();

        Intent intent = new Intent(getApplicationContext(), MainActivity.class);
        startActivity(intent);
    }


}
