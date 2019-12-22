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
    /// Interaction logic for ClientiWindow.xaml
    /// </summary>
    public partial class ClientiWindow : Window
    {
        public ClientiWindow()
        {
            InitializeComponent();

            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            var lista = (from x in db.Clienti select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Clienti>(lista);
        }

        private void AddButton(object sender, RoutedEventArgs e)
        {
            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            Clienti c = new Clienti():
            c.Nume = Nume.Text;

            db.Clienti.Add(c);

            db.SaveChanges();

            var lista = (from x in db.Clienti select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Clienti>(lista);
        }

        private void RemoveButton(object sender, RoutedEventArgs e)
        {
            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            var query = from x in db.Clienti
                        where x.Nume == Nume.Text
                        select x;

            foreach (var i in query)
            {
                db.Clienti.Remove(i);
            }

            db.SaveChanges();

            var lista = (from x in db.Clienti select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Clienti>(lista);
        }
    }
}
