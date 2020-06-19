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
    public partial class Main : Form
    {
        public Main()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Delta_to_star ds=new Delta_to_star();
            ds.Show();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            star_to_delta st = new star_to_delta();
            st.Show();
        }

        private void Main_Load(object sender, EventArgs e)
        {

        }
    }
}
