using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Delta_to_star : Form
    {
        public Delta_to_star()
        {
            InitializeComponent();
        }

        private void Delta_to_star_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            tR1.Text = ((R12.Value * R31.Value) / (R12.Value + R31.Value + R23.Value)).ToString();
            tR2.Text = ((R23.Value * R12.Value) / (R12.Value + R31.Value + R23.Value)).ToString();
            tR3.Text = ((R31.Value * R23.Value) / (R12.Value + R31.Value + R23.Value)).ToString();

        }

        private void tR1_TextChanged(object sender, EventArgs e)
        {

        }

        private void tR2_TextChanged(object sender, EventArgs e)
        {

        }

        private void tR3_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
