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
    public partial class circuits : Form
    {
        public circuits()
        {
            InitializeComponent();
        }

        private void Start_Click(object sender, EventArgs e)
        {
            Main M1 = new Main();
            M1.Show();
        }
    }
}
