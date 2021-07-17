using LoggingDisplay.Managers;
using System.Windows;

namespace LoggingDisplay
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            LogManager manager = new LogManager();
            manager.StartUp();
        }
    }
}
