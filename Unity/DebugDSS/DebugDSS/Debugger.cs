using System;
using System.Net.Sockets;
using System.Threading;

namespace DebugDSS
{
    internal class Debugger
    {
        private const float inc = 0.01f;

        // Network configurations

        private static bool connected;
        private static TcpClient client;
        private static NetworkStream ns;
        private static string IP = "127.0.0.1";
        private static int PORT = 55001;

        private static float[] values = { 0, 0, 0, 0, 0, 0 };

        static void Main(string[] args)
        {

            ConnectToPlatform();

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
                        case 'w':
                            values[1] += inc;
                            break;
                        case 's':
                            values[1] -= inc;
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
                        case 't':
                            values[4] += inc;
                            break;
                        case 'g':
                            values[4] -= inc;
                            break;
                        case 'y':
                            values[5] += inc;
                            break;
                        case 'h':
                            values[5] -= inc;
                            break;
                        default:
                            break;
                    }
                }

                Console.WriteLine("\nValues sent: " + string.Join(", ", values));
                SendData(values); 
                Thread.Sleep(20); //TODO: TO BE TESTED
            }

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
            Console.WriteLine("Data sent");
        }
    }
}