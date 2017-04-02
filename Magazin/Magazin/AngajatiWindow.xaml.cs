using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using System.Windows.Shapes;

namespace Magazin
{
    /// <summary>
    /// Interaction logic for AngajatiWindow.xaml
    /// </summary>
    public partial class AngajatiWindow : Window
    {
        public AngajatiWindow()
        {
            InitializeComponent();

            DataContext = this;

            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            var lista = (from x in db.Angajati select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Angajati>(lista);
        }

        private void AddButton(object sender, RoutedEventArgs e)
        {
            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            Angajati a = new Angajati();
            a.Nume = Nume.Text;
            a.Salariu = int.Parse(Salariu.Text);

            db.Angajati.Add(a);

            db.SaveChanges();

            var lista = (from x in db.Angajati select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Angajati>(lista);
        }

        private void RemoveButton(object sender, RoutedEventArgs e)
        {
            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            var query = from x in db.Angajati
                        where x.Nume == Nume.Text || x.Salariu == int.Parse(Salariu.Text)
                        select x;
            
            foreach (var i in query)
            {
                db.Angajati.Remove(i);
            }

            db.SaveChanges();

            var lista = (from x in db.Angajati select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Angajati>(lista);
        }
    }
}
