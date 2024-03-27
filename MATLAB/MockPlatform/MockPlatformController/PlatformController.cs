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

    // SERVER
    static IPAddress serverIP= IPAddress.Parse("127.0.0.1");
    static int serverPort = 502;

    // CLIENT
    static IPAddress clientIP = IPAddress.Parse("127.0.0.1");
    static int clientPort = 55002;

    // CONNECTION
    static bool mockConnection = true;
    static bool connected = false;

    private static TcpClient client;
    private static NetworkStream ns;

    static void Main(string[] args)
    {
        if(args.Length < 4)
        {
            Console.WriteLine("Using default parameters:");
        }

        if (args.Length >= 4)
        {
            serverIP = IPAddress.Parse(args[0]);
            serverPort = int.Parse(args[1]);

            clientIP = IPAddress.Parse(args[2]);
            clientPort = int.Parse(args[3]);
        }

        Console.WriteLine("Listening on: {0}:{1}", serverIP, serverPort);
        Console.WriteLine("Connected to: {0}:{1}", clientIP, clientPort);

        if (args.Length == 5)
        {
            if (args[4].Equals("mock"))
            {
                Console.WriteLine("Simulating connection to Stewart Platform");
                mockConnection = true;

            } else
            {
                Console.WriteLine("Argument not recognized.");
                Environment.Exit(1);
            }
        }


/*        if (!mockConnection)
        {
            connected = ConnectToPlatform();
            if (!connected) Environment.Exit(1);
        }*/

        TcpListener server = null;
        try
        {

            server = new TcpListener(serverIP, serverPort);
            server.Start();

            // Buffer for reading data
            int arraySize = 25;
            //byte[] bytes = new byte[arraySize * sizeof(float)];
            byte[] bytes = new byte[arraySize];


            while (true)
            {
                Console.Write("\nWaiting for a connection... \n");

                // Perform a blocking call to accept requests.
                TcpClient client = server.AcceptTcpClient();
                Console.WriteLine("Connected!");




                // Get a stream object for reading and writing
                NetworkStream stream = client.GetStream();

                int bytesRead;
                //float[] floatData = null;

                /*int k = 0;
                while (k < arraySize)
                {
                    bytesRead = stream.Read(bytes, 0, bytes.Length);
                    k += bytesRead;
                }*/

                bytesRead = 0;
                //while ((bytesRead = stream.Read(bytes, 0, arraySize * sizeof(float))) != 0)
                while (true)
                    {
                    try
                    {
                        bytesRead = stream.Read(bytes, 0, arraySize);
                        
                    } catch (Exception e)
                    {
                        Console.WriteLine(e);
                    }
                    if(bytesRead ==0)
                    {
                        Console.WriteLine("break");
                        break;
                    }

                    Console.WriteLine(bytesRead + " Values received from driving simulator: " + string.Join(", ", bytes));
                    
                }

                // Send data to Platform
                Console.WriteLine("before client close");
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

/*    public static bool ConnectToPlatform()
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
        // byte[] data = new byte[points.Length * sizeof(float)];
        // int dataIndex = 0;
        // foreach (float el in points)
        // {
        //     byte[] bytes = BitConverter.GetBytes(el);
        //     for (int i = 0; i < sizeof(float); i++) data[dataIndex++] = bytes[i];
        // }

        ns.Write(points, 0, points.Length);
        Console.WriteLine("data sent nr of points:" + points.Length);
        Console.WriteLine("data 0: " + points[0]);
    }
*/
}
