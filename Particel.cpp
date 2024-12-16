using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace ParticleSystem
{
    public partial class Form1 : Form
    {
        private List<Particle> particles = new List<Particle>();
        private Random random = new Random();
        private Color backgroundColor = Color.FromArgb(15, 15, 15);

        public Form1()
        {
            InitializeComponent();
            LittleBootyBitchs();
            timer1.Interval = 1;
            timer1.Start();
            DoubleBuffered = true;
        }

        private void LittleBootyBitchs()
        {
            int numParticles = 50;
            for (int i = 0; i < numParticles; i++)
            {
                double angle = random.NextDouble() * 2 * Math.PI;
                double speed = random.Next(1, 5);
                particles.Add(new Particle()
                    {
                        Position = new PointF(random.Next(0, ClientSize.Width), random.Next(0, ClientSize.Height)),
                        Velocity = new PointF((float)(Math.Cos(angle) * speed), (float)(Math.Sin(angle) * speed)),
                        Radius = random.Next(2, 5),
                        Color = Color.DarkBlue
                    });
            }
        }
        private void BigBootyBitchs()
        {
            foreach(var particle in particles)
            {
                particle.Position = new PointF(particle.Position.X + particle.Velocity.X, particle.Position.Y + particle.Velocity.Y);
                if (particle.Position.X < 0) particle.Position = new PointF(ClientSize.Width, particle.Position.Y);
                if (particle.Position.X > ClientSize.Width) particle.Position = new PointF(0, particle.Position.Y);
                if (particle.Position.Y < 0) particle.Position = new PointF(particle.Position.X, ClientSize.Height);
                if (particle.Position.Y > ClientSize.Height) particle.Position = new PointF(particle.Position.X, 0);
            }
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            e.Graphics.Clear(backgroundColor);
            foreach(var particle in particles)
            {
                e.Graphics.FillEllipse(new SolidBrush(particle.Color),
                    particle.Position.X - particle.Radius,
                    particle.Position.Y - particle.Radius,
                    particle.Radius * 2, particle.Radius * 2);
                foreach(var otherParticle in particles)
                {
                    if (particle != otherParticle)
                    {
                        float dx = particle.Position.X - otherParticle.Position.X;
                        float dy = particle.Position.Y - otherParticle.Position.Y;
                        float distance = (float)Math.Sqrt(dx * dx + dy * dy);

                        if (distance < 50)
                        {
                            int alpha = (int)((1.0f - (distance / 50.0f)) * 255.0f);
                            e.Graphics.DrawLine(new Pen(Color.FromArgb(alpha, Color.DarkBlue), 1),
                                particle.Position, otherParticle.Position);
                        }
                    }
                }
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            this.BackColor = Color.FromArgb(16, 16, 16);
            this.FormBorderStyle = FormBorderStyle.None;
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            BigBootyBitchs();
            Invalidate();
        }
    }

    public class Particle
    {
        public PointF Position{ get; set; }
        public PointF Velocity{ get; set; }
        public int Radius{ get; set; }
        public Color Color{ get; set; }
    }
}