using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Graphing
{
    public partial class Form1 : Form
    {
        const string Graph = "Graph";
        const string Cases = "Cases";
        List<Case> CaseBase = new List<Case>(200);
        Random rnd = new Random();
        int CurrentPlot = 0;
        float Size = 360;
        public Form1()
        {
            InitializeComponent();
            //Init stuff
            this.chart1.Series[Graph].LegendText = "Graph";
            this.chart1.Series[Cases].LegendText = "Cases";
            GenerateGraph();
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }
        void GenerateGraph()
        {
            chart1.Series[Graph].Points.Clear();
            int StepSize = 1;
            float X = 0;
            while (X < Size)
            {
                chart1.Series[Graph].Points.AddXY(X, GetY(X));
                X += StepSize;
            }
        }
        double GetY(float X)
        {
            switch (CurrentPlot)
            {
                case 0:
                    return Math.Sin(X / 180 * Math.PI) * Math.Sin(X / 180 * Math.PI);
                case 1:
                    return X * X;
                case 2:
                    return X;
                default:
                    return 0;
            }
        }

        private void Update_Tick(object sender, EventArgs e)
        {
            //Calculate new value
            double XValue = rnd.NextDouble() * Size;
            Case NewCase = new Case();
            NewCase.X = XValue;
            List<Case> NearbyCases= new List<Case>();
            double Threshold = 10;
            foreach (Case c in CaseBase)
            {
                if (NewCase.Distance(c) < Threshold)
                {
                    NearbyCases.Add(c);
                }
            }
            NearbyCases.Sort();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string selected = e.ToString();
            switch (selected)
            {
                case "Sine Squared":
                    CurrentPlot = 0;
                    break;
                case "X Squared":
                    CurrentPlot = 1;
                    break;
                case "X = Y":
                    CurrentPlot = 2;
                    break;
                default:
                    break;
            }
            GenerateGraph();
        }
    }
}
