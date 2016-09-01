using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graphing
{
    class Case : IComparable<Case>
    {

    {
        public int CompareTo(Case cus)

        {

            return this.Y.CompareTo(cus.Y);

        }
        public double X;
        public double Y;
        public double Error;
        public double Distance(Case c)
        {
            return X - c.X;
        }
    }
}
