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
    /// Interaction logic for ProduseWindow.xaml
    /// </summary>
    public partial class ProduseWindow : Window
    {
        public ProduseWindow()
        {
            InitializeComponent();
            DataContext = this;

            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            var lista = (from x in db.Produse  select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Produse>(lista);
        }

        private void AddButton(object sender, RoutedEventArgs e)
        {
            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            Produse p = new Produse();
            p.Nume = Nume.Text;
            p.Pret = int.Parse(Pret.Text);
            p.Stoc = int.Parse(Stoc.Text);

            db.Produse.Add(p);
            db.SaveChanges();

            var lista = (from x in db.Produse select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Produse>(lista);
        }

        private void RemoveButton(object sender, RoutedEventArgs e)
        {
            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            var query = from x in db.Produse
                        where x.Nume == Nume.Text || x.Pret == int.Parse(Pret.Text) || x.Stoc == int.Parse(Stoc.Text)
                        select x;

            foreach (var i in query)
            {
                db.Produse.Remove(i);
            }
            db.SaveChanges();

            var lista = (from x in db.Produse select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Produse>(lista);
        }

    }
}
