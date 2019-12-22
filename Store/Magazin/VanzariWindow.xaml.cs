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
    /// Interaction logic for VanzariWindow.xaml
    /// </summary>
    public partial class VanzariWindow : Window
    {
        public VanzariWindow()
        {
            InitializeComponent();

            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            var lista = (from x in db.Vanzari select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Vanzari>(lista);
        }

        private void AddButton(object sender, RoutedEventArgs e)
        {
            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            Vanzari v = new Vanzari();
            v.ProdusId =  int.Parse(ProdusId.Text);
            v.ClientId =  int.Parse(ClientId.Text);
            v.AngajatId = int.Parse(AngajatId.Text);

            db.Vanzari.Add(v);

            db.SaveChanges();

            var lista = (from x in db.Vanzari select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Vanzari>(lista);
        }

        private void RemoveButton(object sender, RoutedEventArgs e)
        {
            MagazinDatabaseEntities db = new MagazinDatabaseEntities();

            var query = from x in db.Vanzari
                        where x.ProdusId == int.Parse(ProdusId.Text) || x.ClientId == int.Parse(ClientId.Text) || x.AngajatId == int.Parse(AngajatId.Text)
                        select x;

            foreach (var i in query)
            {
                db.Vanzari.Remove(i);
            }

            db.SaveChanges();

            var lista = (from x in db.Vanzari select x).ToList();
            dataGrid.ItemsSource = new ObservableCollection<Vanzari>(lista);
        }

    }
}
