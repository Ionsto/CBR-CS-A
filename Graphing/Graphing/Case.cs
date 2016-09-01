using System;
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
        public double X;
        public double Y;
        public double DX = 1;
        public double[] DY = new double[4];
        public double Error = 0;
        public double Distance(Case c)
        {
            double diff = 0;
            double tempdiff;
            tempdiff = (X - c.X);
            diff += tempdiff * tempdiff;
            tempdiff = (Y - c.Y);
            diff += tempdiff * tempdiff;
            for (int i = 0; i < 4; ++i)
            {
                tempdiff = (DY[i] - c.DY[i]);
                diff += tempdiff * tempdiff;
            }
            return Math.Sqrt(diff);
        }
        public void Mutate(float Factor)
        {
            Y += (rnd.NextDouble() * 2 * Factor) - Factor;
        }
    }
}
