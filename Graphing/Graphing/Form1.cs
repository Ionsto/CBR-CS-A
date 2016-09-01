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
        List<Case> CaseBase = new List<Case>(200);
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
                NewCase.DY[0] = GetY(NewCase.X - (NewCase.DX * 2), RandCase);
                NewCase.DY[1] = GetY(NewCase.X - (NewCase.DX), RandCase);
                NewCase.DY[2] = GetY(NewCase.X + (NewCase.DX), RandCase);
                NewCase.DY[3] = GetY(NewCase.X + (NewCase.DX * 2), RandCase);
                List<Case> NearbyCases = new List<Case>();
                double NearestNeigborThreshold = 100;
                double IdenticalPairThreshold = 20;
                double MinAddDistance = 0;
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
                    NewCase.Mutate(100 * (rnd.NextDouble() - 0.5));
                }
                else
                {
                    if (NearbyCases[0].TempDistance < IdenticalPairThreshold)
                    {
                        NewCase.Y = NearbyCases[0].Y;
                        NewCase.Mutate((NearbyCases[0].Error * 0.01) + 0.1);
                        NewCase.Error = GetY(NewCase.X, 0) - NewCase.Y;
                        if (Math.Abs(NewCase.Error) < Math.Abs(NearbyCases[0].Error))
                        {
                            CaseBase.Remove(NearbyCases[0]);
                        }
                    }
                    else
                    {
                        //Adapt
                        double MaxDistance = NearbyCases.Last<Case>().TempDistance;
                        double Y = 0;
                        double AvDist = 0;
                        foreach (Case c in NearbyCases)
                        {
                            Y += c.Y * (1 - (c.TempDistance / MaxDistance)) * (1 / (Math.Abs(c.Error) + 0.1));
                            AvDist += Math.Abs(c.TempDistance);
                        }
                        Y /= NearbyCases.Count;
                        AvDist /= NearbyCases.Count;
                        NewCase.Y = Y;
                        NewCase.Mutate((double)Math.Sqrt(AvDist));
                    }
                }
                NewCase.Error = GetY(NewCase.X, 0) - NewCase.Y;
                if (NearbyCases.Count == 0)
                {
                    CaseBase.Add(NewCase);
                }
                else
                {

                    if (Math.Abs(NearbyCases[0].TempDistance) > Math.Abs(MinAddDistance))
                    {
                        CaseBase.Add(NewCase);
                    }
                }
            }
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
