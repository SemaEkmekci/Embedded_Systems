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
        SerialPort sr = new SerialPort();
        private void Form1_Load(object sender, EventArgs e)
        {
            string[] portNames = SerialPort.GetPortNames();
            comboBoxPortName.Items.AddRange(portNames);
            
            
            //serialPort1.PortName = "COM5";
            //serialPort1.BaudRate = 9600;
            //serialPort1.Open();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            sr.Write("1");
            label1.Text = "LED ON";
            button1.Enabled = false;
            button2.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            sr.Write("0");
            label1.Text = "LED OFF";
            button1.Enabled = true;
            button2.Enabled = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(sr.IsOpen == true)
            {
                sr.Close();
            }
        }

        private void comboBoxPortName_SelectedIndexChanged(object sender, EventArgs e)
        {
            sr.PortName = Convert.ToString(comboBoxPortName.Text);
           
        }

        private void comboBoxBaudRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            sr.BaudRate = Convert.ToInt32(comboBoxBaudRate.Text);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (sr.IsOpen)
            {
                sr.Close();
                label1.Text = "Port ON";
                sr.Open();
            }
            else
            {
                sr.Open();
                label1.Text = "Port ON";
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (sr.IsOpen)
            {
                sr.Close();
                label1.Text = "Port OFF";
                
            }
            else
            {
                sr.Close();
                label1.Text = "Port OFF";
            }
        }
    }
}
