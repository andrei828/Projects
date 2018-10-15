package com.andrei.period;

import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Calendar;

import java.util.GregorianCalendar;


public class MainActivity extends AppCompatActivity {

    public final static String PERIOD_LIST_SIZE = "com.andrei.period.PERIOD_LIST_SIZE";
    public final static String PERIOD_START_ARRAY = "com.andrei.period.PERIOD_START_ARRAY";
    public final static String PERIOD_END_ARRAY = "com.andrei.period.PERIOD_END_ARRAY";

    private Switch periodSwitch;

    private long result_from_last_period, result_until_next_period;

    private int current_period_cycle;

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
        setContentView(R.layout.activity_main);

        periodSwitch = findViewById(R.id.switch1);

        Intent intent = getIntent();
        try {
            String first_period_date = intent.getStringExtra(SetupFirstPeriod.FIRST_DATE);
            current_period_cycle = Integer.parseInt(intent.getStringExtra(SetupFirstPeriod.PERIOD_CYCLE));
            addFirstDate(setupDateString(first_period_date), current_period_cycle);
        } catch (Exception e) {
            // Don't crush
        }

        String last_date = getCurrentDate();
        if (last_date.equals("null")) {
            Intent intent2 = new Intent(getApplicationContext(), SetupFirstPeriod.class);
            startActivity(intent2);
        } else {
            result_from_last_period = getTimeUntilPeriod(last_date) + 1;
            result_until_next_period = current_period_cycle - result_from_last_period + 1;

            if (result_until_next_period < 0) result_until_next_period = 0;
            else if (result_from_last_period == 0) result_from_last_period = 1;

            if (getMenToggle() == 0)
                loadDataMenOff(result_until_next_period, result_from_last_period, 0);
            else
                loadDataMenOff(result_until_next_period, result_from_last_period, 1);
        }

        periodSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
                SharedPreferences.Editor editor = sharedPreferences.edit();
                int period_list_size = sharedPreferences.getInt(getString(R.string.period_list_size), 0) + 1;

                Calendar calendar = Calendar.getInstance();
                SimpleDateFormat sdf = new SimpleDateFormat("yyyy MM dd");
                String add_last_date_string = sdf.format(calendar.getTime());

                if (isChecked) {
                    String add_last_date = getString(R.string.period_template) + Integer.toString(period_list_size);
                    editor.putInt(getString(R.string.period_list_size), period_list_size);
                    editor.putInt(getString(R.string.toggled_time), 1);
                    editor.putString(add_last_date, add_last_date_string);
                    editor.apply();

                    int new_period_cycle = current_period_cycle;
                    for (int i = 0; i < period_list_size - 1; i++) {
                        String key_string_start = getString(R.string.period_template) + Integer.toString(i + 1);
                        String key_string_next  = getString(R.string.period_template) + Integer.toString(i + 2);

                        new_period_cycle += getTimeUntilPeriod(sharedPreferences.getString(key_string_start, "null"), sharedPreferences.getString(key_string_next, "null"));
                    }

                    new_period_cycle = new_period_cycle / period_list_size;
                    editor.putInt(getString(R.string.period_cycle), new_period_cycle);
                    editor.apply();


                    String last_date = getCurrentDate();
                    result_from_last_period = getTimeUntilPeriod(last_date) + 1;
                    result_until_next_period = current_period_cycle - result_from_last_period;

                    if (result_until_next_period < 0) result_until_next_period = 0;
                    else if (result_from_last_period == 0) result_from_last_period = 1;

                    loadDataMenOff(result_until_next_period, result_from_last_period, 1);
                } else {
                    String period_end = getString(R.string.period_template_end) + Integer.toString(period_list_size - 1);

                    editor.putInt(getString(R.string.toggled_time), 0);
                    editor.putString(period_end, add_last_date_string);
                    editor.apply();
                    loadDataMenOff(result_until_next_period, result_from_last_period, 0);
                }
            }
        });
    }

    public long getTimeUntilPeriod(String date1, String date2) {

        String[] date_array1 = date1.split(" ");
        String[] date_array2 = date2.split(" ");

        Calendar cal1 = Calendar.getInstance();
        Calendar cal2 = Calendar.getInstance();

        cal1.set(Integer.parseInt(date_array1[0]), Integer.parseInt(date_array1[1]) - 1, Integer.parseInt(date_array1[2]));
        cal2.set(Integer.parseInt(date_array2[0]), Integer.parseInt(date_array2[1]) - 1, Integer.parseInt(date_array2[2]));

        return (cal2.getTimeInMillis() - cal1.getTimeInMillis()) / 1000 / 60 / 60 / 24 + 1;
    }

    public int getMenToggle() {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        return sharedPreferences.getInt(getString(R.string.toggled_time), 0);
    }

    public void loadDataMenOff(long result_until_next_period, long result_from_last_period, int toggle) {
        if (toggle == 0) loadTimerView(result_until_next_period);
        else loadTimerViewToggle(result_from_last_period);

        loadPeriodCycleCards(result_from_last_period);
    }

    public void loadTimerViewToggle(long date) {
        periodSwitch.setChecked(true);
        String date_to_string = Long.toString(date);

        TextView textView1 = findViewById(R.id.days_until_period_number);
        TextView textView2 = findViewById(R.id.days_until_period_text);

        textView1.setText(date_to_string);

        if (date == 1) textView2.setText(R.string.day_period_1);
        else if (date == 2) textView2.setText(R.string.day_period_2);
        else if (date == 3) textView2.setText(R.string.day_period_3);
        else if (date == 4) textView2.setText(R.string.day_period_4);
        else if (date == 5) textView2.setText(R.string.day_period_5);
        else if (date == 6) textView2.setText(R.string.day_period_6);
        else if (date == 7) textView2.setText(R.string.day_period_7);
    }

    public void loadTimerView(long date) {
        String date_to_string = Long.toString(date);

        TextView textView1 = findViewById(R.id.days_until_period_number);
        TextView textView2 = findViewById(R.id.days_until_period_text);

        textView1.setText(date_to_string);
        textView2.setText(R.string.text_days_until_period);
    }

    public void loadPeriodCycleCards(long date) {
        TextView textView1 = findViewById(R.id.period_cycle_description);
        TextView textView2 = findViewById(R.id.chance_of_pregnancy);

        int ovulationStart = current_period_cycle / 2 - 2;
        int ovulationEnd = current_period_cycle / 2 + 3;

        if (periodSwitch.isChecked()) {
            textView1.setText(R.string.information_period_1);
            textView2.setText(R.string.chance_of_pregnancy_low);
        } else if (date < ovulationStart) {
            textView1.setText(R.string.information_period_2);
            textView2.setText(R.string.chance_of_pregnancy_high);
        } else if (date <= ovulationEnd) {
            textView1.setText(R.string.information_period_3);
            textView2.setText(R.string.chance_of_pregnancy_very_high);
        } else if (date <= current_period_cycle && date != 0) {
            textView1.setText(R.string.information_period_4);
        } else {
            textView1.setText(R.string.information_period_5);
        }

        if (date > ovulationEnd && date < ovulationEnd + 2)
            textView2.setText(R.string.chance_of_pregnancy_high);
        else if (date >= ovulationEnd + 2 && date <= current_period_cycle)
            textView2.setText(R.string.chance_of_pregnancy_very_low);
    }

    public String setupDateString(String date)
    {
        String[] first_date = date.split("/");

        SimpleDateFormat sdf = new SimpleDateFormat("yyyy MM dd");
        GregorianCalendar calendar = new GregorianCalendar(
                Integer.parseInt(first_date[2]),
                Integer.parseInt(first_date[1]) - 1,
                Integer.parseInt(first_date[0])
        );

        return sdf.format(calendar.getTime());
    }

    public void addFirstDate(String date, int period_cycle)
    {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        SharedPreferences.Editor editor = sharedPreferences.edit();
        String key_string_date = getString(R.string.period_template) + "1";
        String key_string_date_end = getString(R.string.period_template_end) + "1";

        Calendar calendar = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy MM dd");
        GregorianCalendar cal = new GregorianCalendar(
                calendar.get(Calendar.YEAR),
                calendar.get(Calendar.MONTH) - 1,
                calendar.get(Calendar.DAY_OF_MONTH)
        );

        long days_until_period = getTimeUntilPeriod(sdf.format(cal.getTime()), date) - 1;
        if (period_cycle - days_until_period > 6) {
            editor.putInt(getString(R.string.toggled_time), 0);
            editor.putString(key_string_date_end, date);
        } else {
            editor.putInt(getString(R.string.toggled_time), 1);
            periodSwitch.toggle();
        }

        editor.putInt(getString(R.string.period_list_size), 1);
        editor.putInt(getString(R.string.period_cycle), period_cycle);
        editor.putString(key_string_date, date);

        editor.apply();
    }


    public long getTimeUntilPeriod(String date) {

        String[] date_array = date.split(" ");

        Calendar cal1 = Calendar.getInstance();
        cal1.set(Integer.parseInt(date_array[0]), Integer.parseInt(date_array[1])-1, Integer.parseInt(date_array[2]));
        Calendar cal2 = Calendar.getInstance();

        return (cal2.getTimeInMillis() - cal1.getTimeInMillis()) / 1000 / 60 / 60 / 24;
    }

    public String getCurrentDate() {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        int period_list_size = sharedPreferences.getInt(getString(R.string.period_list_size), 0);
        current_period_cycle = sharedPreferences.getInt(getString(R.string.period_cycle), 28);

        String current_period_key = getString(R.string.period_template) + Integer.toString(period_list_size);
        return sharedPreferences.getString(current_period_key, "null");
    }


    // bubble clicked to view analysis activity
    public void showPeriodAnalysis(View view) {
        Intent intent = new Intent(getApplicationContext(), PeriodAnalysis.class);
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());

        int period_list_size = sharedPreferences.getInt(getString(R.string.period_list_size), 0);
        intent.putExtra(PERIOD_LIST_SIZE, Integer.toString(period_list_size));

        String[] move_intent_start = new String[period_list_size + 1];
        String[] move_intent_end = new String[period_list_size + 1];

        for (int i = 0; i < period_list_size; i++) {
            String key_string_start = getString(R.string.period_template) + Integer.toString(i + 1);
            String key_string_end = getString(R.string.period_template_end) + Integer.toString(i + 1);

            move_intent_start[i] = sharedPreferences.getString(key_string_start, "null");
            move_intent_end[i] = sharedPreferences.getString(key_string_end, "null");
        }

        intent.putExtra(PERIOD_START_ARRAY, move_intent_start);
        intent.putExtra(PERIOD_END_ARRAY, move_intent_end);

        startActivity(intent);
    }

}
