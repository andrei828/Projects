package com.andrei.period;

import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class PeriodAnalysis extends AppCompatActivity {

    public final static String PERIOD_START = "com.andrei.period.PERIOD_START";
    public final static String PERIOD_END = "com.andrei.period.PERIOD_END";
    public final static String PERIOD_POS = "com.andrei.period.PERIOD_POS";

    private int size;

    private boolean display;

    private String[] string_start, string_end;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_period_analysis);

        Intent intent = getIntent();

        size = Integer.parseInt(intent.getStringExtra(MainActivity.PERIOD_LIST_SIZE));
        string_start = intent.getStringArrayExtra(MainActivity.PERIOD_START_ARRAY);
        string_end = intent.getStringArrayExtra(MainActivity.PERIOD_END_ARRAY);

        SharedPreferences saved_values = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());

        if (saved_values.getInt(getString(R.string.toggled_time), 0) == 0) display = true;

        ListView mListView = findViewById(R.id.listView);

        CustomAdapter customAdapter = new CustomAdapter();
        mListView.setAdapter(customAdapter);
    }

    class CustomAdapter extends BaseAdapter {

        @Override
        public int getCount() {
            if (display)
                return size + 1;
            else
                return size;
        }

        @Override
        public Object getItem(int i) {
            return null;
        }

        @Override
        public long getItemId(int i) {
            return 0;
        }

        @Override
        public View getView(final int i, View view, ViewGroup viewGroup) {
            if (i == getCount() - 1 && display) {
                view = getLayoutInflater().inflate(R.layout.custom_row_today, null);

            } else if (i == getCount() - 1 && !display) {
                view = getLayoutInflater().inflate(R.layout.custom_row_period_today, null);

                ImageView mImageView = view.findViewById(R.id.imageView);
                TextView mStartView = view.findViewById(R.id.period_start);

                mImageView.setImageResource(R.drawable.blood_drop);
                mStartView.setText(setupDateString(string_start[i]));

            } else {
                view = getLayoutInflater().inflate(R.layout.custom_row_period_analysis, null);

                ImageView mImageView = view.findViewById(R.id.imageView);
                final TextView mStartView = view.findViewById(R.id.period_start);
                TextView mLastedView = view.findViewById(R.id.days_lasted);
                TextView mUntilPeriod = view.findViewById(R.id.days_until_next_period);
                LinearLayout linearLayout = view.findViewById(R.id.MainLinear);

                long period_interval = getTimeUntilPeriod(string_end[i], string_start[i]);
                String period_interval_string;
                if (period_interval == 1) {
                    period_interval_string = "Lasted for " + Long.toString(period_interval) + " day";
                } else {
                    period_interval_string = "Lasted for " + Long.toString(period_interval) + " days";
                }

                long next_date_long;
                String next_date_string;
                if (i == size - 1) {
                    Calendar next_date;
                    next_date = Calendar.getInstance();
                    SimpleDateFormat sdf = new SimpleDateFormat("yyyy MM dd");
                    next_date_long = getTimeUntilPeriod(sdf.format(next_date.getTime()), string_start[i]) - 1;
                } else {
                    next_date_long = getTimeUntilPeriod(string_start[i + 1], string_start[i]) - 1;
                }

                if (next_date_long == 1) {
                    next_date_string = "After " + Long.toString(next_date_long) + " day";
                } else {
                    next_date_string = "After " + Long.toString(next_date_long) + " days";
                }

                mImageView.setImageResource(R.drawable.calendar2);
                mStartView.setText(setupDateString(string_start[i]));
                mLastedView.setText(period_interval_string);
                mUntilPeriod.setText(next_date_string);

                linearLayout.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Intent intent = new Intent(getApplicationContext(), EditPeriod.class);
                        intent.putExtra(PERIOD_START, string_start[i]);
                        intent.putExtra(PERIOD_END, string_end[i]);
                        intent.putExtra(PERIOD_POS, Integer.toString(i + 1));
                        startActivity(intent);
                    }
                });
            }

            return view;
        }

        public String setupDateString(String date) {
            try {
                String[] first_date = date.split(" ");

                SimpleDateFormat sdf = new SimpleDateFormat("dd MMM yyyy");
                GregorianCalendar calendar = new GregorianCalendar(
                        Integer.parseInt(first_date[0]),
                        Integer.parseInt(first_date[1]) - 1,
                        Integer.parseInt(first_date[2])
                );

                return sdf.format(calendar.getTime());
            } catch (Exception e) {
                return "NULL";
            }
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
    }

}
