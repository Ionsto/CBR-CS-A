﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graphing
{
    class Case : IComparable<Case>
    {
        public int CompareTo(Case cus)
        {
            return this.X.CompareTo(cus.X);
        }
        Random rnd = new Random();
        public int ChartID = 0;
        public double X = 0;
        public double Y = 0;
        public double Error = 0;
        //This is all temp
        public double TempDistance = 0;
        public double Distance(Case c)
        {
            double diff = 0;
            double tempdiff;
            tempdiff = (X - c.X);
            diff += tempdiff * tempdiff;
            return Math.Sqrt(diff);
        }
        public void Mutate(double Factor)
        {
            Y += ((rnd.NextDouble()-0.5) * Factor);
        }
    }
}
