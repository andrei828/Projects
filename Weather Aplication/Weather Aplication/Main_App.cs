using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace Weather_Aplication
{
    /// <summary>
    /// Interaction logic for Main_App.xaml
    /// </summary>
    public partial class Main_App : Page
    {
        public string[] lines;

        public List<string> Citites;

        public Main_App()
        {
            DataContext = this;
            InitializeComponent();
            InitCities();
            SetLines("Bucharest");
        }

        private void SetLines(string City)
        {
            try
            {
                lines = System.IO.File.ReadAllLines("./Python/Get_Data_For_App_" + City + ".txt");
                City_Name.Content = City;
                startclock();
                Current_Day();
                Current_Day_Temp_Image();
                Day_1();
                Day_2();
                Day_3();
                Day_4();
            }
            catch
            {
                // do nothing and do not freeze ;)
            }
        }

        private void startclock()
        {
            DispatcherTimer timer;
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += tickevent1;
            timer.Start();
        }

        private void tickevent1(object sender, EventArgs e)
        {
            Current_Time.Content = DateTime.Now.ToString("HH:mm") + ", " + lines[3];
        }

        public void Current_Day()
        {
            TextBox_Search.Visibility = Visibility.Hidden;
            Current_Temp_Max.Content = lines[7];
            Current_Temp_Min.Content = lines[8];
            Current_Humidity.Content= lines[1] + " %";
            Current_Wind.Content = lines[9];
            Current_Wind_Speed.Content = lines[10];
            Current_Status.Content = lines[6];
            
            DateTime now = DateTime.Now;
            DateTime Night = DateTime.Today.AddHours(20.0);

            string status = lines[6];
            if (now > Night)
            {
                if (status == "mostly clear" || status == "clear")
                    Current_Day_Image.Source = (BitmapImage)Resources["clear_night"];
                if (status == "partly cloudy" || status == "cloudy")
                    Current_Day_Image.Source = (BitmapImage)Resources["fair_night"];
                if (status == "prevailingly cloudy")
                    Current_Day_Image.Source = (BitmapImage)Resources["fair_night"];
            }
            else
            {
                if (status == "mostly clear" || status == "clear")
                    Current_Day_Image.Source = (BitmapImage)Resources["clear_day"];
                if (status == "partly cloudy" || status == "cloudy")
                    Current_Day_Image.Source = (BitmapImage)Resources["partly_cloudy_day"];
                if (status == "prevailingly cloudy")
                    Current_Day_Image.Source = (BitmapImage)Resources["fair_day"];
            }
        }

        public void Day_1()
        {
            string day_1 = lines[12].Trim(new Char[] { '(', '\'', ')' });
            Next_day_1.Content = day_1.Replace("\'", "");
            
            Next_day_1_Temp_Max.Content = lines[16] + "°C";
            Next_day_1_Temp_Min.Content = lines[17] + "°C";

            string status = lines[15];
            if (status == "mostly clear" || status == "clear")
                Next_day_1_Image.Source = (BitmapImage)Resources["clear_day"];
            if (status == "partly cloudy" || status == "cloudy")
                Next_day_1_Image.Source = (BitmapImage)Resources["partly_cloudy_day"];
            if (status == "prevailingly cloudy")
                Next_day_1_Image.Source = (BitmapImage)Resources["fair_day"];


        }

        public void Day_2()
        {
            string day_2 = lines[21].Trim(new Char[] { '(', '\'', ')' });
            Next_day_2.Content = day_2.Replace("\'", "");

            Next_day_2_Temp_Max.Content = lines[25] + "°C";
            Next_day_2_Temp_Min.Content = lines[26] + "°C";

            string status = lines[24];
            if (status == "mostly clear" || status == "clear")
                Next_day_2_Image.Source = (BitmapImage)Resources["clear_day"];
            if (status == "partly cloudy" || status == "cloudy")
                Next_day_2_Image.Source = (BitmapImage)Resources["partly_cloudy_day"];
            if (status == "prevailingly cloudy")
                Next_day_2_Image.Source = (BitmapImage)Resources["fair_day"];


        }

        public void Day_3()
        {
            string day_3 = lines[30].Trim(new Char[] { '(', '\'', ')' });
            Next_day_3.Content = day_3.Replace("\'", "");

            Next_day_3_Temp_Max.Content = lines[34] + "°C";
            Next_day_3_Temp_Min.Content = lines[35] + "°C";

            string status = lines[33];
            if (status == "mostly clear" || status == "clear")
                Next_day_3_Image.Source = (BitmapImage)Resources["clear_day"];
            if (status == "partly cloudy" || status == "cloudy")
                Next_day_3_Image.Source = (BitmapImage)Resources["partly_cloudy_day"];
            if (status == "prevailingly cloudy")
                Next_day_3_Image.Source = (BitmapImage)Resources["fair_day"];


        }

        public void Day_4()
        {
            string day_4 = lines[39].Trim(new Char[] { '(', '\'', ')' });
            Next_day_4.Content = day_4.Replace("\'", "");

            Next_day_4_Temp_Max.Content = lines[43] + "°C";
            Next_day_4_Temp_Min.Content = lines[44] + "°C";

            string status = lines[42];
            if (status == "mostly clear" || status == "clear")
                Next_day_4_Image.Source = (BitmapImage)Resources["clear_day"];
            if (status == "partly cloudy" || status == "cloudy")
                Next_day_4_Image.Source = (BitmapImage)Resources["partly_cloudy_day"];
            if (status == "prevailingly cloudy")
                Next_day_4_Image.Source = (BitmapImage)Resources["fair_day"];
        }

        public void Current_Day_Temp_Image()
        {
            Current_Temp.Text = lines[0] + "°C";
        }

        private void Search(object sender, MouseButtonEventArgs e)
        {
            TextBox_Search.Visibility = Visibility.Visible;
            search_image.Visibility = Visibility.Hidden;
            TextBox_Search.Text = "";
            TextBox_Search.Focus();
        }

        private void UseSuggestion(object sender, MouseButtonEventArgs e)
        {
            SetLines((string)Suggest_City.Content);
            Suggest_City.Content = "";
            Suggest_City.Visibility = Visibility.Hidden;
            search_image.Visibility = Visibility.Visible;
        }

        private void GetCityString(object sender, KeyEventArgs e)
        {
            string search_city = TextBox_Search.Text.ToLower();
            bool found = true;
            foreach (string city in Citites)
            {
                found = true;
                string tmp = city.ToLower();
                for (int i = 0; i < search_city.Length; i++)
                {
                    if (search_city[i] != tmp[i]) 
                    {
                        found = false;
                        Suggest_City.Visibility = Visibility.Hidden;
                        Suggest_City.Content = "";
                        break;
                    }  
                }
                if (found && search_city.Length > 0)
                {
                    Suggest_City.Visibility = Visibility.Visible;
                    Suggest_City.Content = city;
                    break;
                }
            }

            if (e.Key == Key.Enter)
            {
                search_city = (string)Suggest_City.Content;
                TextBox_Search.Visibility = Visibility.Hidden;
                Suggest_City.Visibility = Visibility.Hidden;
                search_image.Visibility = Visibility.Visible;
                SetLines(search_city);
            }

            if (e.Key == Key.Down)
            {
                TextBox_Search.Text = Suggest_City.Content.ToString();
            }
        }

        private void HideSuggestion(object sender, KeyEventArgs e)
        {
            if (TextBox_Search.Text == "")
            {
                Suggest_City.Content = "";
                Suggest_City.Visibility = Visibility.Hidden;
            }
        }

        private void Loading()
        {
            City_Name.Content = "Loading...";
            search_image.Visibility = Visibility.Hidden;
            Current_Time.Visibility = Visibility.Hidden;
            
        }

        private void InitCities()
        {
            Citites = new List<string>() {
                        "Amsterdam", "Ankara", "Athens", "Belgrade",
                        "Berlin", "Bratislava", "Brussels", "Bucharest",
                        "Budapest", "Copenhagen", "Dublin Airport", "Helsinki",
                        "Kiev", "Chisinau", "Lisbon", "Ljubljana", "London",
                        "Luxembourg", "Madrid", "Malta", "Minsk", "Moscow",
                        "Oslo", "Paris", "Podgorica", "Praha-Libus",
                        "Pratica Di Mare", "Reykjavik", "Riga", "Sarajevo-Bejelave",
                        "Skopje", "Sofia", "Stockholm", "Tallinn", "Tirana",
                        "Vaduz", "Vienna", "Vilnius", "Warsaw", "Zagreb / Maksimir" };
        }
    }
}