using System;
using System.Windows.Forms;
using System.IO.Ports;


namespace Project_1
{
    public partial class Form1 : Form
    {
        int sema;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            serialPort1.PortName = "COM5";
            string[] portNames = SerialPort.GetPortNames();

            serialPort1.BaudRate = 9600;
            serialPort1.Open();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Write("1");
            label1.Text = "LED ON";
            button1.Enabled = false;
            button2.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Write("0");
            label1.Text = "LED OFF";
            button1.Enabled = true;
            button2.Enabled = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(serialPort1.IsOpen == true)
            {
                serialPort1.Close();
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

       
    }
}
