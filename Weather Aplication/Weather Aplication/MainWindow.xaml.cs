using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Diagnostics;

namespace Weather_Aplication
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public string[] lines;

        public MainWindow()
        {
            InitializeComponent();
            run_cmd("python.exe", "./Python/GetData.py");
            lines = System.IO.File.ReadAllLines("./Python/Get_Data_For_App_Bucharest.txt");
            Background_Image();
            Return_but.Visibility = Visibility.Hidden;
            Main.Content = new Main_App();
        }

        private void run_cmd(string cmd, string args)
        {
            Process process = new Process();
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.FileName = cmd;
            startInfo.Arguments = args;
            process.StartInfo = startInfo;
            process.Start();
        }

        private void DragBar(object sender, MouseButtonEventArgs e)
        {
            base.DragMove();
        }

        private void Close_button(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void Minimize_button(object sender, RoutedEventArgs e)
        {
            WindowState = WindowState.Minimized;
        }

        private void Info_button(object sender, RoutedEventArgs e)
        {
            Main.Content = new About();
            Info_but.Visibility = Visibility.Hidden;
            Return_but.Visibility = Visibility.Visible;
        }

        private void Return_button(object sender, RoutedEventArgs e)
        {
            Main.Content = new Main_App();
            Info_but.Visibility = Visibility.Visible;
            Return_but.Visibility = Visibility.Hidden;
        }

        public void Background_Image()
        {
            DateTime now = DateTime.Now;
            Console.WriteLine(now);
            DateTime Night = DateTime.Today.AddHours(20.0);

            if (now > Night)
            {
                if (lines[6] == "mostly clear" || lines[6] == "clear")
                    back_image.ImageSource = (BitmapImage)Resources["clear_n"];
                if (lines[6] == "partly cloudy" || lines[6] == "cloudy")
                    back_image.ImageSource = (BitmapImage)Resources["cloudy_n"];
                if (lines[6] == "prevailingly cloudy")
                    back_image.ImageSource = (BitmapImage)Resources["cloudy_n"]; 
            }
            else
            {
                if (lines[6] == "mostly clear")
                    back_image.ImageSource = (BitmapImage)Resources["clear_d"];
                if (lines[6] == "partly cloudy")
                    back_image.ImageSource = (BitmapImage)Resources["cloudy_d"];
                if (lines[6] == "prevailingly cloudy")
                    back_image.ImageSource = (BitmapImage)Resources["cloudy_d"]; 
            }
            //back_image.ImageSource = (BitmapImage)Resources["bg_evening"];
        }
    }
}



