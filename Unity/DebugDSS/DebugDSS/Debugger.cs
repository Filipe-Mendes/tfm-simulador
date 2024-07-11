using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Threading;

namespace DebugDSS
{
    internal class Debugger
    {
        private const float inc = 0.01f;
        private const int stepTimeMs = 5;
        private const int fileStep = 4;

        private const int T = 0;
        private const int X = 1;
        private const int Y = 2;
        private const int Z = 3;


        public struct Coordinate
        {
            public Coordinate(int t, double c)
            {
                T = t;
                C = c;
            }

            public int T { get; }
            public double C { get; }

            public override string ToString() => $"({T}, {C})";
        }

        // Network configurations

        private static bool connected;
        private static TcpClient client;
        private static NetworkStream ns;
        private static string IP = "127.0.0.1";
        private static int PORT = 55001;

        private static float[] values = { 0, 0, 0, 0, 0, 0 };



        static void Main(string[] args)
        {

            //ConnectToPlatform();
            //ForwardPathScenario();

            LoadFileIntoArray();

            double slope = GetSlope(268, 444, Z);
            DrawLine(slope, 208, 12, Z);

            slope = GetSlope(1704, 1848, Z);
            DrawLineForward(slope, 1988, 2124, Z);

       


            WriteArrayToFile();




            /*            // FORWARD AND COME TO REST
                        double slope = GetSlope(7016, 7104, Z);
                        DrawLine(slope, 7016, 6840, Z);

                        slope = GetSlope(35404, 36560, Z);
                        DrawLineForward(slope, 36560, 39488, Z);


                        WriteArrayToFile();*/



        }

        public static void Loop()
        {

            while (true)
            {
                if (Console.KeyAvailable)
                {
                    char input = Console.ReadKey().KeyChar;
                    switch (input)
                    {
                        case 'q':
                            values[0] += inc;
                            break;
                        case 'a':
                            values[0] -= inc;
                            break;
                        case 'z':
                            values[0] = 0;
                            break;


                        case 'w':
                            values[1] += inc;
                            break;
                        case 's':
                            values[1] -= inc;
                            break;
                        case 'x':
                            values[1] = 0;
                            break;


                        case 'e':
                            values[2] += inc;
                            break;
                        case 'd':
                            values[2] -= inc;
                            break;
                        case 'c':
                            values[2] = 0;
                            break;


                        case 'r':
                            values[3] += inc;
                            break;
                        case 'f':
                            values[3] -= inc;
                            break;
                        case 'v':
                            values[3] = 0;
                            break;


                        case 't':
                            values[4] += inc;
                            break;
                        case 'g':
                            values[4] -= inc;
                            break;
                        case 'b':
                            values[4] = 0;
                            break;


                        case 'y':
                            values[5] += inc;
                            break;
                        case 'h':
                            values[5] -= inc;
                            break;
                        case 'n':
                            values[5] = 0;
                            break;


                        default:
                            break;
                    }
                }

                SendData(values);
                Thread.Sleep(20); //TODO: TO BE TESTED
            }


        }

        /*public static void ForwardPathScenario()
        {
            SendData(values);
            float test = 2;
            var stopwatch = new Stopwatch();
            stopwatch.Start();

            values[2] = test;
            while (stopwatch.Elapsed < TimeSpan.FromSeconds(2))
            {
                SendData(values);
            }

            values[2] = 0;
            var stopwatch1 = new Stopwatch();
            stopwatch1.Start();
            while (stopwatch1.Elapsed < TimeSpan.FromSeconds(5))
            {
                SendData(values);
            }


            var stopwatch2 = new Stopwatch();
            stopwatch2.Start();

            values[2] = -test * 2;
            while (stopwatch2.Elapsed < TimeSpan.FromSeconds(1))
            {
                SendData(values);
            }

            values[2] = 0;
            while (true)
            {
                SendData(values);
            }
        }*/
        public static void ForwardPathScenario()
        {
            SendData(values);
            float test = 2;
            values[2] = test;
            SendDataInterval(2);

            values[2] = 0;
            SendDataInterval(5);


            values[2] = -test * 2;
            SendDataInterval(1);

            values[2] = 0;
            while (true)
            {
                SendData(values);
            }
        }

        public static void SpeedBumpScenario()
        {

        }

        public static void CurveScenario()
        {

        }



        public static bool ConnectToPlatform()
        {
            client = new TcpClient();
            try
            {
                client.Connect(IP, PORT);
                ns = client.GetStream();
                // reader = new StreamReader(ns);
                connected = true;
            }
            catch (SocketException e)
            {
                connected = false;
            }
            return connected;
        }

        public static void SendData(float[] points)
        {
            byte[] data = new byte[points.Length * sizeof(float)];
            int dataIndex = 0;
            foreach (float el in points)
            {
                byte[] bytes = BitConverter.GetBytes(el);
                for (int i = 0; i < sizeof(float); i++) data[dataIndex++] = bytes[i];
            }

            ns.Write(data, 0, data.Length);
            //Console.WriteLine("Data sent");
            Console.WriteLine("\nValues sent: " + string.Join(", ", values));
        }

        public static void SendDataInterval(float time)
        {
            //SendData(values);
            var stopwatch = new Stopwatch();
            stopwatch.Start();

            while (stopwatch.Elapsed < TimeSpan.FromSeconds(time))
            {
                SendData(values);
                Thread.Sleep(stepTimeMs);
            }

        }


        public static void SendLineInterval(float[] target, float time)
        {
            float[] valuesIncrement = new float[target.Length];
            for (int i = 0; i < target.Length; i++)
            {
                valuesIncrement[i] = (target[i] - values[i]) / stepTimeMs;
            }


            var stopwatch = new Stopwatch();
            stopwatch.Start();

            while (stopwatch.Elapsed < TimeSpan.FromSeconds(time))
            {
                for (int i = 0; i < target.Length; i++)
                {
                    values[i] = values[i] + valuesIncrement[i];
                }
                Thread.Sleep(stepTimeMs);
            }

        }


        public static double GetSlope(int time1, int time2, int coordinate)
        {
            double slope = (data[time2/fileStep][coordinate] - data[time1 / fileStep][coordinate]) / ((time2 ) - (time1 )); // DIVIDIR OS TIMES POR FILESTEP???
            /*Console.WriteLine(data[time2 / fileStep][coordinate]);
            Console.WriteLine(data[time1 / fileStep][coordinate]);
            Console.WriteLine(time2 / fileStep);
            Console.WriteLine(time1 / fileStep);
*/

            //double slope = ( data[time][x]-data[time + nrOfValues * fileStep][x]) / (time - (time + nrOfValues * fileStep));
            //Console.WriteLine(slope);
            return slope;
        }

        public static void DrawLine(double slope, int known, int toDiscover, int coordinate)
        {
            //int mt = toDiscover.T - known.T;
            int xToDiscover = toDiscover - known;
            Console.WriteLine(xToDiscover);

            //double b = known.C;
            double b = data[known / fileStep][coordinate];
            Console.WriteLine("B: " + b);

            double y = slope * xToDiscover + b;

            //for (int i = toDiscover.T / fileStep; i <= known.T / fileStep; i++)

            for (int i = toDiscover/fileStep; i<=known/fileStep; i++)
            {
                Console.WriteLine("i: " + i*fileStep);
                data[i][coordinate] = slope * (data[i][0] - known) + b;
                Console.WriteLine("y=" + slope + " X " + data[i][0] + " + " + b); 
            }


            //Console.WriteLine(y);

        }

        public static void DrawLineForward(double slope, int known, int toDiscover, int coordinate)
        {
            int xToDiscover = toDiscover - known;
            Console.WriteLine(xToDiscover);

            double b = data[known / fileStep][coordinate];
            Console.WriteLine("B: " + b);

            double y = slope * xToDiscover + b;


            for (int i = known / fileStep; i <= toDiscover / fileStep; i++)
            {
                Console.WriteLine("i: " + i * fileStep);
                data[i][coordinate] = slope * (data[i][0] - known) + b;
                Console.WriteLine("y=" + slope + " X " + data[i][0] + " + " + b);
            }

        }

/*        public static void DrawLineForwardEnd(double slope, int known, int toDiscover, int coordinate)
        {
            int xToDiscover = toDiscover - known;
            Console.WriteLine(xToDiscover);

            double b = data[known / fileStep][coordinate];
            Console.WriteLine("B: " + b);

            double y = slope * xToDiscover + b;


            int i = known / fileStep;
            while (data[i][coordinate] < 0)
            {
                Console.WriteLine("i: " + i * fileStep);
                data[i][coordinate] = slope * (data[i][0] - known) + b;
                Console.WriteLine("y=" + slope + " X " + data[i][0] + " + " + b);
                i++;
            }
            data[i][coordinate] = 0;

        }*/




        private static double[][] data;
        public static void LoadFileIntoArray()
        {
            try
            {
                string path = @"..\..\log_acceleration.txt";

                string[] lines = File.ReadAllLines(path);

                var dataList = new System.Collections.Generic.List<double[]>();

                foreach (string line in lines)
                {
                    if (string.IsNullOrWhiteSpace(line))
                    {
                        continue;
                    }

                    string[] parts = line.Trim().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

                    double[] dataRow = new double[parts.Length];
                    for (int j = 0; j < parts.Length; j++)
                    {
                        dataRow[j] = double.Parse(parts[j], CultureInfo.InvariantCulture);
                    }

                    dataList.Add(dataRow);
                }

                data = dataList.ToArray();

                /*for (int i = 0; i < data.Length; i++)
                {
                    Console.WriteLine(data[i][0]);
                }*/
            }

            catch (Exception e)
            {
                Console.WriteLine("An error occurred: " + e.Message);
            }
        }

        public static void WriteArrayToFile()
        {
            try
            {
                string path = @"..\..\log_acceleration_after.txt";

                using (StreamWriter writer = new StreamWriter(path))
                {
                    foreach (double[] row in data)
                    {
                        writer.WriteLine(string.Join(" ", row.Select(d => d.ToString("G", CultureInfo.InvariantCulture))));
                        writer.WriteLine("");
                    }
                }

                Console.WriteLine("Data successfully written to " + path);
            }
            catch (Exception e)
            {
                // Handle any exceptions that occur during file writing
                Console.WriteLine("An error occurred: " + e.Message);
            }
        }
    }
}
