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

using MySql.Data.MySqlClient;
using System.Data;
using System.Configuration;

namespace DatabaseApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        DataTable MyDataTable { get; set; }

        private MySqlConnection conn;

        public MainWindow()
        {
            InitializeComponent();
            MyDataTable = new DataTable();

            string connString = ConfigurationManager.ConnectionStrings["connString"].ToString();
            conn = new MySqlConnection(connString);
            conn.Open();

            string sqlCommand = "select * from studenti;";
            try
            {
                MySqlDataAdapter sda = new MySqlDataAdapter(sqlCommand, conn);
                sda.Fill(MyDataTable);

                MyGuiTable.DataContext = MyDataTable;
                MyGuiTable.ItemsSource = MyDataTable.DefaultView;
            }
            catch (Exception e)
            {
                MessageBox.Show("Connection Error! Data: " + e.Data);
            }
        }

        private void addButton(object sender, RoutedEventArgs e)
        {
            string id = IdBox.Text;
            string nume = NumeBox.Text;
            string nota = NotaBox.Text;
            string comment = CommentBox.Text;

            string sqlCommand = "select * from studenti;";
            string insertCommand = String.Format("insert into studenti values ('{0}', '{1}', '{2}', '{3}');", id, nume, nota, comment);

            try
            {
                MyDataTable.Clear();
                MySqlCommand ins = new MySqlCommand(insertCommand, conn);
                MySqlDataAdapter sda = new MySqlDataAdapter(sqlCommand, conn);
                ins.ExecuteNonQuery();
                sda.Fill(MyDataTable);

                MyGuiTable.DataContext = MyDataTable;
                MyGuiTable.ItemsSource = MyDataTable.DefaultView;

                MessageBox.Show("Add Command Executed!");
            }
            catch (Exception)
            {
                MessageBox.Show("Connection Error!");
            }
        }

        private void removeButton(object sender, RoutedEventArgs e)
        {
            string id = IdBox.Text;
            string nume = NumeBox.Text;
            string nota = NotaBox.Text;
            string comment = CommentBox.Text;

            string sqlCommand = "select * from studenti;";
            string deleteCommand = String.Format("delete from studenti where ID='{0}' or Nume='{1}' or Nota='{2}' or Comment='{3}';", id, nume, nota, comment);

            try
            {
                MyDataTable.Clear();
                MySqlCommand del = new MySqlCommand(deleteCommand, conn);
                MySqlDataAdapter sda = new MySqlDataAdapter(sqlCommand, conn);
                del.ExecuteNonQuery();
                sda.Fill(MyDataTable);

                MyGuiTable.DataContext = MyDataTable;
                MyGuiTable.ItemsSource = MyDataTable.DefaultView;

                MessageBox.Show("Remove Command Executed!");
            }
            catch (Exception)
            {
                MessageBox.Show("Connection Error!");
            }
        }

        private void updateButton(object sender, RoutedEventArgs e)
        {
            string id = IdBox.Text;
            string nume = NumeBox.Text;
            string nota = NotaBox.Text;
            string comment = CommentBox.Text;

            string sqlCommand = "select * from studenti;";
            string updateCommand = String.Format("update studenti set Nume='{0}', Nota='{1}', Comment='{2}' where ID={3};", nume, nota, comment, id);

            try
            {
                MyDataTable.Clear();
                MySqlCommand upd = new MySqlCommand(updateCommand, conn);
                MySqlDataAdapter sda = new MySqlDataAdapter(sqlCommand, conn);
                upd.ExecuteNonQuery();
                sda.Fill(MyDataTable);

                MyGuiTable.DataContext = MyDataTable;
                MyGuiTable.ItemsSource = MyDataTable.DefaultView;

                MessageBox.Show("Remove Command Executed!");
            }
            catch (Exception)
            {
                MessageBox.Show("Connection Error!");
            }
        }
    }
}
