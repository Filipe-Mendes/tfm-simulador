using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;
using System.Runtime.Remoting.Messaging;
using System.Reflection;

public class PlatformController
{
    public struct RT_MODEL_c_coder_T
    {
    }

    [DllImport("..\\..\\..\\c_coder_win64.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void rand_numb_initialize();

    [DllImport("..\\..\\..\\c_coder_win64.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void c_coder_step(
            ref RT_MODEL_c_coder_T c_coder_M,
            double accY,
            double accZ,
            double accX,
            double rotY,
            double rotZ,
            double rotX,
            ref byte[] platformData);


    // SERVER
    static IPAddress serverIP= IPAddress.Parse("127.0.0.1");
    static int serverPort = 55001;

    // CLIENT
    static IPAddress clientIP = IPAddress.Parse("127.0.0.1");
    static int clientPort = 55001;

    // CONNECTION
    static bool mockConnection = false;
    static bool connected = false;

    private static TcpClient client;
    private static NetworkStream ns;

    static void Main(string[] args)
    {
        if(args.Length < 4)
        {
            Console.WriteLine("Using default parameters:");
            Console.WriteLine("Listening on: {0}:{1}", serverIP, serverPort);
            Console.WriteLine("Connected to: {0}:{1}", clientIP, clientPort);
        }

        if (args.Length >= 4)
        {
            serverIP = IPAddress.Parse(args[0]);
            serverPort = int.Parse(args[1]);

            clientIP = IPAddress.Parse(args[2]);
            clientPort = int.Parse(args[3]);
        }

        if (args.Length == 5 && args[4].Equals("mock"))
        {
            Console.WriteLine("Simulating connection to Stewart Platform");
            mockConnection = true;
        }


        if (!mockConnection)
        {
            connected = ConnectToPlatform();
            if (!connected) Environment.Exit(1);
        }


        RT_MODEL_c_coder_T model;
        TcpListener server = null;
        try
        {

            server = new TcpListener(serverIP, serverPort);

            server.Start();

            // Buffer for reading data
            byte[] bytes = new byte[6 * sizeof(float)];
            int arraySize = 6;
            while (true)
            {
                Console.Write("\nWaiting for a connection... \n");

                // Perform a blocking call to accept requests.
                TcpClient client = server.AcceptTcpClient();
                Console.WriteLine("Connected!");

                // Get a stream object for reading and writing
                NetworkStream stream = client.GetStream();

                int bytesRead;
                float[] floatData = null;

                while ((bytesRead = stream.Read(bytes, 0, arraySize * sizeof(float))) != 0)
                {
                    int floatCount = bytesRead / sizeof(float);
                    floatData = new float[floatCount];

                    // Use Buffer.BlockCopy to convert bytes to floats
                    Buffer.BlockCopy(bytes, 0, floatData, 0, bytesRead);

                    // Process the array of floats
                    Console.WriteLine("Values received from driving simulator: " + string.Join(", ", floatData));
                }

                // Process data with dll
                byte[] platformData = new byte[25];
                try
                {
                    if (!mockConnection)
                    {
                        c_coder_step(ref model, floatData[0], floatData[1], floatData[2], floatData[3], floatData[4], floatData[5], ref platformData);
                        SendData(platformData);
                    }
                } catch (Exception e)
                {
                    Console.WriteLine("\nDriving simulator disconnected or another error occurred!\n");
                }


                // Send data to Platform


                client.Close();
            }
        }
        catch (SocketException e)
        {
            Console.WriteLine("SocketException: {0}", e);
        }
        finally
        {
            server.Stop();
        }
    }

    public static bool ConnectToPlatform()
    {
        client = new TcpClient();
        try
        {
            client.Connect(clientIP, clientPort);
            ns = client.GetStream();
            //reader = new StreamReader(ns);
            Console.WriteLine("Connected");
            return true;
        }
        catch (SocketException e)
        {
            Console.WriteLine("Could not connect to Platform. Try again.");
            return false;
        }
    }


    public static void SendData(byte[] points)
    {
/*        byte[] data = new byte[points.Length * sizeof(float)];
        int dataIndex = 0;
        foreach (float el in points)
        {
            byte[] bytes = BitConverter.GetBytes(el);
            for (int i = 0; i < sizeof(float); i++) data[dataIndex++] = bytes[i];
        }*/

        ns.Write(points, 0, points.Length);
    }
}
