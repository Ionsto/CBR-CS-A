using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace Graphing
{
    public partial class Form1 : Form
    {
        const string Graph = "Graph";
        const string Cases = "Cases";
        List<Case> CaseBase;
        Random rnd = new Random();
        int CurrentPlot = 0;
        double Size = 360;
        double RealWorldRandom = 2;
        double ChartMax = 1;
        public Form1()
        {
            InitializeComponent();
            //Init stuff
            this.chart1.Series[Graph].LegendText = "Graph";
            this.chart1.Series[Cases].LegendText = "Cases";
            CaseBase = new List<Case>(200);
            GenerateGraph();
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }
        void GenerateGraph()
        {
            chart1.ChartAreas[0].AxisY.Maximum = Double.NaN;
            chart1.ChartAreas[0].AxisY.Minimum = Double.NaN;
            chart1.Series[Graph].Points.Clear();
            chart1.Series[Cases].Points.Clear();
            int StepSize = 1;
            double X = 0;
            while (X < Size)
            {
                chart1.Series[Graph].Points.AddXY(X, GetY(X,0));
                X += StepSize;
            }
            chart1.ChartAreas[0].RecalculateAxesScale();
            ChartMax = chart1.ChartAreas[0].AxisY.Maximum;
        }
        double GetY(double X,double RND)
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
            for (int zzz = 0; zzz < 200; ++zzz)
            {
                //Calculate new value
                double StepSize = 10;
                double XValue = Math.Round(rnd.NextDouble() * Size / StepSize) * StepSize;
                Case NewCase = new Case();
                NewCase.X = XValue;
                double RandCase = 0;
                List<Case> NearbyCases = new List<Case>();
                double NearestNeigborThreshold = 50;
                double IdenticalPairThreshold = 10;
                double MinAddDistance = 20;
                foreach (Case c in CaseBase)
                {
                    c.TempDistance = NewCase.Distance(c);
                    if (c.TempDistance < NearestNeigborThreshold)
                    {
                        NearbyCases.Add(c);
                    }
                }
                NearbyCases.Sort();
                NewCase.Y = 0;
                if (NearbyCases.Count == 0)
                {
                    NewCase.Y = 0;
                    NewCase.Mutate(10 * (rnd.NextDouble() - 0.5));
                    NewCase.Error = Math.Abs(GetY(NewCase.X, 0) - NewCase.Y);
                    CaseBase.Add(NewCase);
                }
                else
                {
                    if (Math.Abs(NearbyCases[0].TempDistance) < IdenticalPairThreshold)
                    {
                        NewCase.Y = NearbyCases[0].Y;
                        NewCase.Mutate((NearbyCases[0].Error * 1.9));
                        NewCase.Error = Math.Abs(GetY(NewCase.X, 0) - NewCase.Y);
                        if (NewCase.Error < NearbyCases[0].Error)
                        {
                            CaseBase.Add(NewCase);
                        }
                        while (Math.Abs(NearbyCases[0].TempDistance) < IdenticalPairThreshold)
                        {
                            CaseBase.Remove(NearbyCases[0]);
                            NearbyCases.Remove(NearbyCases[0]);
                            if (NearbyCases.Count == 0)
                            {
                                break;
                            }
                        }

                    }
                    else
                    {
                        //Adapt
                        double[] Vars = weightedLinearRegression(NearbyCases);
                        NewCase.Y = Vars[1];
                        NewCase.Mutate(Vars[2] * 1.9);
                        NewCase.Error = Math.Abs(GetY(NewCase.X, 0) - NewCase.Y);
                        if (Math.Abs(NearbyCases[0].TempDistance) > Math.Abs(MinAddDistance))
                        {
                            CaseBase.Add(NewCase);
                        }

                    }
                }
            }
        }
        double DivZero(double a, double b)
        {
            if(b == 0 || a == 0) { return 0; }
            return a / b;
        }

        double[] weightedLinearRegression(List<Case> array)
        {
            double xw = 0;
            double x = 0;
            double yw = 0;
            double y = 0;
            double a = 0;
            double b = 0;
            double SSres = 0;
            double SStotal = 0;
            double ExpectedY = 0;
            double rsqd = 0;
            double MeanError = 0;
            // compute the weighted averages
            for (var i = 0; i < array.Count; i++)
            {
                xw += array[i].X * DivZero(1,array[i].Error);
                yw += array[i].Y * DivZero(1,array[i].Error);
                x += array[i].X;
                y += array[i].Y;
            }
            double weightedX = DivZero(xw,x);
            double weightedY = DivZero(yw, y);

            // compute the gradient and intercept
            for (var i = 0; i < array.Count; i++)
            {
                a += (array[i].Y - weightedY) * (array[i].X - weightedX) * array[i].Error;
                b += (array[i].X - weightedX) * (array[i].X - weightedX) * array[i].Error;
            }
            double gradient = DivZero(a , b);
            double intercept = (weightedY - weightedX) * gradient;
            //var string = 'y = ' + Math.round(gradient*100) / 100 + 'x + ' + Math.round(intercept*100) / 100;
            //var results = [];

            for (var i = 0; i < array.Count; i++)
            {
                ExpectedY = (gradient * array[i].X) + intercept;
                SSres += (array[i].Y - weightedY) * (array[i].Y - weightedY);
                SSres += (array[i].Y - ExpectedY) * (array[i].Y - ExpectedY);
                MeanError += array[i].Error;
            }
            MeanError = DivZero(MeanError, array.Count);
            rsqd = 1 - DivZero(SSres , SStotal);
            return new double[3] { gradient, intercept, MeanError };
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            CaseBase.Clear();
            CurrentPlot = ((ListBox)sender).SelectedIndex;
            GenerateGraph();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            chart1.Series[Cases].Points.Clear();
            foreach (Case C in CaseBase)
            {
                chart1.Series[Cases].Points.AddXY(C.X, C.Y);
            }
            chart1.ChartAreas[0].AxisY.Maximum = ChartMax;
            chart1.ChartAreas[0].AxisY.Minimum = 0;
        }
    }
}
