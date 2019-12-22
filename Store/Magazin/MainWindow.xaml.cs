using System;
using System.Collections.Generic;
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

namespace Magazin
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OpenProduse(object sender, RoutedEventArgs e)
        {
            ProduseWindow WProduse = new ProduseWindow();
            WProduse.Show();
        }

        private void OpenAngajati(object sender, RoutedEventArgs e)
        {
            AngajatiWindow WAngajati = new AngajatiWindow();
            WAngajati.Show();
        }

        private void OpenClienti(object sender, RoutedEventArgs e)
        {
            ClientiWindow WCLienti = new ClientiWindow();
            WCLienti.Show();
        }

        private void OpenVanzari(object sender, RoutedEventArgs e)
        {
            VanzariWindow WVanzari = new VanzariWindow();
            WVanzari.Show();
        }
    }
}
